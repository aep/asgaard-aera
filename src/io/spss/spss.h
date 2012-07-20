/*
 *
 * pspp-0.6.2/doc/dev/system-file-format.texi
 *
 */

#include <stdint.h>
#include <QDataStream>
#include <QFile>
#include "../../shared/plugin.h"
#include "../../shared/plugin++.hpp"

namespace Spss
{
    struct Header
    {
        char     magic[4];
        char     product[60];
        int32_t  layoutCode;  // file layout code
        int32_t  caseSize;    // number of OBS elements per case, integer
        int32_t  compression;
        int32_t  weightIndex; // index of weight variable, integer
        int32_t  numCases;    // number of cases
        double   bias;        // compression bias, this is an 8 byte float (double). FIXME I can't figure this one out yet
        char     cdate [9];   // creation date
        char     ctime [8];   // creation time;
        char     label [64];  // file label
    };

    // type 2
    struct VariableRecord
    {
        int32_t  width;
        int32_t  hasVariableLabel;
        int32_t  missingValue;
        int32_t  printFormat;
        int32_t  writeFormat;
        char     name[8 + 1];
        int32_t  labelSize;
        char     label[255];
        int64_t  continuations;
    };

    // type 3
    struct ValueLabel
    {
        double     value;      // values are always 8byte in SPSS (double)
        int32_t    labelSize;
        char       label[255];
    };
    struct ValueLabelRecord
    {
        QList<ValueLabel> labels;
        QList<int32_t>    variableReferences;
    };

    // type 7 sub 3
    struct MachineIntegerInfo
    {
        int32_t majorVersion;
        int32_t minorVersion;
        int32_t subVersion;
        int32_t machineCode;
        int32_t floatFormat;
        int32_t compressionCode;
        int32_t integerFormat;
        int32_t characterCode;
    };

    class Case;
    class AERA_PLUGIN_LOCAL Value : public Aera::Object
    {
    public:
        Value(Case *_p, const ValueLabelRecord *_vlr);
        Case *p;
        const ValueLabelRecord *vlr;


        enum Type
        {
            String,
            Numeric,
        };
        Type mType;

        QByteArray s_value;
        double     d_value;

        virtual aera_type type();
        virtual bool get_string(const char **);
        virtual bool get_double(double *);

    };

    class File;
    class AERA_PLUGIN_LOCAL Case : public Aera::Object
    {
    public:
        Case(File *_p);
        QList<Value> values;
        File *p;

        virtual aera_type type() { return aera_object; };
        virtual aera_object_iterator object_iterate();
    };

    class AERA_PLUGIN_LOCAL CaseIterator : public Aera::Object
    {
    public:
        CaseIterator(Case *p);
        virtual bool object_end();
        virtual bool object_next(const char **v, aera_item *);
        Case *p;
        int at;
    };

    class AERA_PLUGIN_LOCAL File: public Aera::Object
    {
    public:
        File(const QString &fn);
        virtual aera_type type() { return aera_array; };
        virtual aera_array_iterator array_iterate();

        virtual aera_attribute_iterator attribute_iterate();

        QFile file;
        QDataStream in;
        Header header;
        QList<VariableRecord>   variables;
        QList<ValueLabelRecord> valueLabels;
    };

    class AERA_PLUGIN_LOCAL FileIterator : public Aera::Object
    {
    public:
        FileIterator(File *_p);

        virtual bool array_end();
        virtual bool array_next(aera_item *);

        File *p;
        QFile file;
        QDataStream in;
        QList<uint8_t> opCodeBuffer;
    };

    class AERA_PLUGIN_LOCAL FileAttributeIterator: public Aera::Object
    {
    public:
        FileAttributeIterator(const File *_p);

        const File*p;
        int at;

        virtual bool attribute_next(const char **, aera_item *);
        virtual bool attribute_end();
    };

    enum Opcode
    {
        Nop           = 0,
        Eof           = 252,
        NotCompressed = 253,
        Spaces        = 254,
        Missing       = 255
    };

};


