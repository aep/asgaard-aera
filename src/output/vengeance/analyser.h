#ifndef ANALYSER_H_asoidnasjkld
#define ANALYSER_H_asoidnasjkld

#include <QObject>
#include <QFlags>




class Analyser : public QObject
{
Q_OBJECT
public:


    static QString table_plural(QString);
    static QString table_singular(QString);

    enum FieldAttribute
    {
        NoAttributes  = 0x0,
        NotNull       = 0x1,
        AutoIncrement = 0x2
    };

    Q_DECLARE_FLAGS(FieldAttributes, FieldAttribute)

    enum KeyType
    {
        UnknownKeyType,
        IndexKey,
        PrimaryKey,
        UniqueKey
    };


    struct Field
    {
        QString name;
        QString datatype;
        FieldAttributes attributes;
    };

    struct Key
    {
        KeyType type;
        QList<Field*> fields;
    };

    struct Table
    {
        QString name;
        QList<Field*> fields;
        QList<Key*> keys;
    };


    Analyser(QObject * parent=0);
    QList<Analyser::Table *>  analyse();
private:
    QList<Table *> tables;
    void parseShowCreate(QString);

};

Q_DECLARE_OPERATORS_FOR_FLAGS(Analyser::FieldAttributes)


#endif
