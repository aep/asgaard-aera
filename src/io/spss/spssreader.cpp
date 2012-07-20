#include "spss.h"

#include <stdexcept>
#include <QDataStream>
#include <QDebug>
#include <QByteArray>
#include <QFile>


using namespace Spss;

static QDataStream &operator >> (QDataStream &in, Spss::MachineIntegerInfo &r)
{
    in >> r.majorVersion;
    in >> r.minorVersion;
    in >> r.subVersion;
    in >> r.machineCode;
    in >> r.floatFormat;
    in >> r.compressionCode;
    in >> r.integerFormat;
    in >> r.characterCode;
    return in;
}

static QDataStream &operator >> (QDataStream &in, Spss::ValueLabelRecord &vr)
{
    int32_t numLabels;
    in >> numLabels;
    //qDebug() << "number of labels:" << numLabels;

    vr.labels.clear();

    // pairs

    for (int i = 0; i < numLabels; i++) {
        ValueLabel l;
        in >> l.value;

        uint8_t labelSize, paddedSize;
        in >> labelSize;
        paddedSize = labelSize;
        // pad to 7 or 8 or whatever the fuck. serious brain damage.
        if ((paddedSize + 1) % 8)
            paddedSize += 8 - ((paddedSize + 1) % 8);

        in.readRawData(l.label, paddedSize);
        if (labelSize < sizeof(l.label))
            l.label[labelSize] = 0;

        l.labelSize = labelSize;

        //qDebug() << "value : " << l.value;
        //qDebug() << "label : " << l.label;

        vr.labels.append(l);
    }

    // now "references" to variables follow
    // in a record type 4

    int32_t recordType;
    in >> recordType;

    if (recordType != 4)
        throw std::runtime_error("record type 3 must be followed by type 4");

    int32_t numVariables;
    in >> numVariables;

    //qDebug() << "numrefs: " << numVariables;

    for (int i = 0; i < numVariables; i++) {
        int32_t ref;
        in >> ref;
        vr.variableReferences << ref;
        //qDebug() << "ref" << ref;
    }

    return in;
}

static QDataStream &operator >> (QDataStream &in, Spss::Header &header)
{
    in.readRawData(header.magic, 4);
    if (strncmp(header.magic,"$FL2", 4) != 0)
        throw std::runtime_error("doesn't look like a spss native file");

    in.readRawData(header.product, 60);

    in.setByteOrder(QDataStream::LittleEndian);

    in >> header.layoutCode;
    in >> header.caseSize;
    in >> header.compression;
    in >> header.weightIndex;
    in >> header.numCases;
    in >> header.bias;
    in.readRawData(header.cdate, 9);
    in.readRawData(header.ctime, 8);
    in.readRawData(header.label, 64);
    //garbage
    in.skipRawData(3);

    if (header.layoutCode != 2)
        throw std::runtime_error("only layout 2 supported");

    return in;
}

static QDataStream &operator >> (QDataStream &in, Spss::VariableRecord &vr)
{
    in >> vr.width;
    in >> vr.hasVariableLabel;
    in >> vr.missingValue;
    in >> vr.printFormat;
    in >> vr.writeFormat;
    memset(vr.name, 0, sizeof(vr.name));
    in.readRawData(vr.name, 8);
    vr.name[8] = 0;

    if (vr.width > 255)
        throw std::runtime_error("variable too big");

    if (vr.hasVariableLabel) {
        uint32_t labelSize;
        in >> labelSize;

        // align to 4.
        if (labelSize % 4)
            labelSize += 4 - labelSize % 4;

        if (labelSize > sizeof(vr.label))
            throw std::runtime_error("variable size is too big");
        in.readRawData(vr.label, labelSize);
        if (labelSize < sizeof(vr.label))
                vr.label[labelSize] = 0;

        vr.labelSize = labelSize;
    }

    //TODO
    in.skipRawData(8 * abs(vr.missingValue));


    /*
    qDebug () << "name:" <<   QByteArray(vr.name, 8);
    qDebug () << "width:" << vr.width;
    // yes, this is 4 bytes for indicating that there's another 4 bytes,
    // indicating the size which can be max 255 and is aligned to 4
    // serious crackheads...
    qDebug () << "has variable label:" << vr.hasVariableLabel;
    qDebug () << "has missing value:"  << vr.missingValue;
    qDebug () << "print format:"       << vr.printFormat;;
    qDebug () << "write format:"       << vr.writeFormat;
    qDebug() << "label: " << QByteArray(vr.label, sizeof(vr.label));
    */
    return in;
}

/*
 * opcodes come in blocks of 8
 * followed by data blocks of 8, specified by the "opcodes"
 * strings look like this:
 *
 * [ NotC, NotC, NotC, NotC, NotC, NotC, NotC, NotC ]
 * [ a , c, t, u , a , l, , d ]
 * [ a , t, a,   , c , o  , m ]
 * [ e , s, ,  h , e , r  , e ]
 * [ .. ] [ .. ] [ .. ] [ .. ] [ .. ]
 * [ NotC, NotC, NotC, NotC, NotC, NotC, NotC, NotC ]
 * [ .. ]
 *
 * where the amount of opcodes we expect is field.width / 8
 * yes this is retard
 */

static uint8_t nextOpcode(QDataStream &in, QList<uint8_t> &opCodeBuffer)
{
    if (opCodeBuffer.isEmpty()) {
        for (int i = 0; i < 8; i++) {
            uint8_t code;
            in >> code;
            opCodeBuffer.append(code);
        }
    }
    return opCodeBuffer.takeFirst();
}


static bool readNumericValue(
        QDataStream &in,
        const Spss::File &f,
        const Spss::VariableRecord &vr,
        QList<uint8_t> &opCodeBuffer,
        Spss::Value &v
        )
{
    if (f.header.compression) {
        uint8_t code = nextOpcode(in, opCodeBuffer);
        switch (code) {
            case Spss::Missing:
            case Spss::Spaces:
            case Spss::Eof:
                return false;
            case Spss::NotCompressed:
                in >> v.d_value;
                return true;
            default:
                v.d_value = code - f.header.bias;
                return true;
        }
    } else {
        in >> v.d_value;
        return true;
    }
}

static bool readStringValue(
        QDataStream &in,
        const Spss::File &f,
        const Spss::VariableRecord &vr,
        QList<uint8_t> &opCodeBuffer,
        Spss::Value &v
        )
{
    for (int i = 0; i < vr.continuations + 1; i++ ) {
        char buf[9];
        if (f.header.compression) {
            uint8_t code = nextOpcode(in, opCodeBuffer);
            switch (code) {
                case Spss::Spaces:
                    v.s_value.append("        ");
                    break;
                case Spss::NotCompressed:
                    in.readRawData(buf, 8);
                    buf[8] = 0;
                    v.s_value.append(buf);
                    break;
                case Spss::Eof:
                case Spss::Missing:
                default:
                    return false;
            }
        } else {
            in.readRawData(buf, 8);
            buf[8] = 0;
            v.s_value.append(buf);
        }
    }
    //qDebug() << (v.s_value.size() - vr.width) << "bytes where padding";
    v.s_value.resize(vr.width);
    return true;
}


static bool readCase(QDataStream &in, const Spss::File &f, QList<uint8_t> &opCodeBuffer, Spss::Case &c)
{
    c.values.clear();

    int i = 0;
    const ValueLabelRecord *vlr;
    foreach(const VariableRecord &vr, f.variables) {
        foreach (const ValueLabelRecord &_vlr, f.valueLabels) {
            if (_vlr.variableReferences.contains(i)) {
                vlr = &_vlr;
                break;
            }
        }
        i++;
        Spss::Value v(&c, vlr);
        v.d_value = -1.5;

        if (vr.width == 0) {
            readNumericValue(in, f, vr, opCodeBuffer, v);
            v.mType = Spss::Value::Numeric;
        } else {
            readStringValue(in, f, vr, opCodeBuffer, v);
            v.mType = Spss::Value::String;
        }
        c.values.append(v);
    }

    return true;
}

QDataStream &operator >> (QDataStream &in, Spss::File &f)
{
    in >> f.header;

    /*
    qDebug() << "layout code"      << f.header.layoutCode;
    qDebug() << "case size"        << f.header.caseSize;
    qDebug() << "compression"      << f.header.compression;
    qDebug() << "weight index"     << f.header.weightIndex;
    qDebug() << "number of cases " << f.header.numCases;
    qDebug() << "Bias" << f.header.bias;
    */
    f.variables.clear();
    f.valueLabels.clear();

    for (;;) {
        int32_t recordType;
        in >> recordType;
        //qDebug () << "--------------------------";
        //qDebug() << "record type" << recordType;
        switch (recordType) {
            case 2: {
                VariableRecord r;
                memset(&r, 0, sizeof(VariableRecord));
                in >> r;
                // variable records are repeated to match up the width of the _value_
                // i think this is because the value records are split into 8byte blocks too
                // so some ancient parser in some crippled language can map them
                if (r.width == -1)
                    f.variables.last().continuations++;
                else
                    f.variables << r;
                break;
            }
            case 3: {
                ValueLabelRecord r;
                in >> r;
                f.valueLabels << r;
                break;
            }
            case 7: {
                int32_t subType;
                in >> subType;
                int32_t subSize;
                in >> subSize;
                int32_t subCount;
                in >> subCount;
                /*
                qDebug() << "subtype" << subType;
                qDebug() << "subsize" << subSize;
                qDebug() << "subcount" << subCount;
                */
                switch (subType) {
                    case 3: {
                        if (subSize != 4 || subCount != 8)
                            throw std::runtime_error("unexpected subrecord layout");
                        MachineIntegerInfo r;
                        in >> r;
                        break;
                    }
                    default:
                        qWarning("unrecognized extended subtype %i. information might be lost.", subType);
                        in.skipRawData(subCount * subSize);
                };
                break;
            }
            case 999:
                // 4 bytes garbage
                in.skipRawData(4);
                goto bb;
                break;
            default:
                throw std::runtime_error("unrecognized recordType");
        }
        continue;
bb:
        break;
    }


    return in;
}

// --

File::File(const QString &fn)
    : Object()
    , file(fn)
    , in(&file)
{
    file.open(QFile::ReadOnly);
    in >> *this;
}


aera_object_iterator File::array_iterate()
{
    return new FileIterator(this);
}

aera_attribute_iterator File::attribute_iterate()
{
    return new FileAttributeIterator(this);
}

// --

FileIterator::FileIterator(File *_p)
    : Object()
    , p(_p)
    , file(_p->file.fileName())
    , in(&file)
{
    file.open(QFile::ReadOnly);
    file.seek(p->file.pos());
}

bool FileIterator::array_end()
{
    return in.atEnd();
}

bool FileIterator::array_next(aera_item *v)
{
    if (in.atEnd())
        return false;
    //qDebug () << "--------------------------";
    Case *c = new Case(p);
    if (!readCase(in, *p, opCodeBuffer, *c)) {
        delete c;
        return false;
    }
    *v = c;
    return true;
}

// --

Case::Case(File *_p)
    : Object()
    , p(_p)
{
}

aera_object_iterator Case::object_iterate()
{
    return new CaseIterator(this);
}

//--

CaseIterator::CaseIterator(Case *_p)
    : Object()
    , p(_p)
    , at(-1)
{
}

bool CaseIterator::object_end()
{
    return (at >= p->values.size());
}

bool CaseIterator::object_next(const char **v, aera_item *k)
{
    ++at;
    if (object_end())
        return false;


    const VariableRecord &vr = p->p->variables.at(at);

    *v = vr.name;
    *k = new Value(p->values.at(at));
    return true;
}

//--

Value::Value(Case *_p, const ValueLabelRecord *_vlr)
    : Object()
    , p(_p)
    , vlr(_vlr)
{
}

aera_type Value::type()
{
    if (mType == Value::String)
        return aera_string;
    else
        return aera_double;
}
bool Value::get_string(const char **v)
{
    *v = s_value.data();
    return true;
}
bool Value::get_double(double *v)
{
    *v = d_value;
    return true;
}

//--

FileAttributeIterator::FileAttributeIterator(const File *_p)
    : Object()
    , p(_p)
    , at(-1)
{
}

bool FileAttributeIterator::attribute_next(const char **k, aera_item *v)
{
    ++at;
    switch(at) {
        case 0:
            *k = "spss::header";
            *v = 0;
            return true;
            break;
        case 1:
            *k = "spss::variables";
            *v = 0;
            return true;
            break;
        case 2:
            *k = "spss::values";
            *v = 0;
            return true;
            break;
    }
    return false;
}

bool FileAttributeIterator::attribute_end()
{
    return (at > 1);
}

// -------------------------------------

struct SpssContext
{
    QByteArray fileName;
};

static aera_context spss_open(int argc, char **argv)
{
    if (argc < 1)
        return 0;

    SpssContext *c = new SpssContext;
    c->fileName = argv[0];
    return reinterpret_cast<aera_context>(c);
}

static aera_item spss_pull(aera_context _c)
{
    const SpssContext *c = reinterpret_cast<const SpssContext*>(_c);
    return new Spss::File(c->fileName);
}

static void spss_close(aera_context _c)
{
    const SpssContext *c = reinterpret_cast<const SpssContext*>(_c);
    delete c;
}

static aera_plugin_interface spss_plugin =
{
    spss_open,
    spss_pull,
    0,
    spss_close
};


#include "../../shared/plugin++.cpp"


extern "C" {

AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
AERA_PLUGIN_EXPORT aera_type_interface *aera_types()
{
    return &Aera::types;
}

AERA_PLUGIN_EXPORT aera_plugin_interface *aera_plugin()
{
    return &spss_plugin;
}

}

