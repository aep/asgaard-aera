#include <QApplication>
#include <stdint.h>
#include <stdexcept>
#include <QDataStream>
#include <QTextCodec>

#include <QFile>
#include <QDebug>

#include "spss.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QFile f(argv[1]);
    f.open(QFile::ReadOnly);
    QDataStream in(&f);

    Spss::File sf;
    in >> sf;

#if 0

    Spss::File x;
    x.header = sf.header;
    Spss::VariableRecord v1 = sf.variables.first();
    v1.width = 0;
    v1.hasVariableLabel = 1;
    v1.labelSize = 8;
    memcpy(v1.label, "TURBO\0", 9);

    v1.missingValue = 0;
    // v1.printFormat =
    // v1.writeFormat =
    memcpy(v1.name, "THESHIAT", 8);
    v1.continuations = 0;

    x.variables.append(v1);

    QFile f2(argv[2]);
    f2.open(QFile::WriteOnly | QFile::Truncate);
    QDataStream out(&f2);


    out << x;
    out << (uint8_t)108;
    out << (uint8_t)0;
    out << (uint8_t)0;
    out << (uint8_t)0;

    out << (uint8_t)0;
    out << (uint8_t)0;
    out << (uint8_t)0;
    out << (uint8_t)0;
#endif
}
