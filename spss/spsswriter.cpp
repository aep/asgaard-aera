#include "spss.h"

#include <stdexcept>
#include <QDataStream>
#include <QDebug>

using namespace Spss;

static QDataStream &operator << (QDataStream &out, const Spss::Header &header)
{
    out.setByteOrder(QDataStream::LittleEndian);
    out.writeRawData(header.magic, sizeof(header.magic));
    out.writeRawData(header.product, sizeof(header.product));

    out << header.layoutCode;
    out << header.caseSize;
    out << header.compression;
    out << header.weightIndex;
    out << header.numCases;
    out << header.bias;

    out.writeRawData(header.cdate,sizeof(header.cdate));
    out.writeRawData(header.ctime,sizeof(header.ctime));
    out.writeRawData(header.label,sizeof(header.label));

    //garbage
    out.writeRawData("\0\0\0", 3);

    return out;
}

static QDataStream &operator << (QDataStream &out, const Spss::VariableRecord &vr)
{
    out << vr.width;
    out << vr.hasVariableLabel;


    //TODO: "missing value" ignored
    // see reader impl
    // out << vr.missingValue;
    out << uint32_t(0);

    out << vr.printFormat;
    out << vr.writeFormat;
    out.writeRawData(vr.name, sizeof(vr.name));

    if (vr.hasVariableLabel) {
        out << vr.labelSize;
        out.writeRawData(vr.label, vr.labelSize);
        //padding to 8
        int o = (vr.labelSize % 8);
        if (o)
            for (o; o < 8; o++)
                out.writeRawData('\0',1);
    }

    return out;
}

QDataStream &operator  << (QDataStream &out, const Spss::File &f)
{
    out <<  f.header;


    foreach(const VariableRecord &vr, f.variables) {
        // record type
        out << int32_t(2);
        out << vr;
    }



    out << int32_t(999);
    out.writeRawData("\0\0\0\0", 4);



    return out;
}


