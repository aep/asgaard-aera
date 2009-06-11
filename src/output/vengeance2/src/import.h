#include <QObject>
#include <QXmlQuery>
#include "analyser.h"
#include <QXmlNamePool>
#include <QAbstractXmlReceiver>
#include <QHash>

namespace Receivers
{

    struct StateEngine
    {
        QXmlNamePool  namePool;
        QList<Analyser::Table *> scheme;
        QHash<QString,int> uf_updated;
        QHash<QString,int> uf_inserted;
        int deepnes;
    };


    class Row : public QAbstractXmlReceiver 
    {
    public:

        Row(StateEngine * state,Analyser::Table* t,Row*parent=0);
        ~Row();
        virtual void startElement ( const QXmlName & name );
        virtual void attribute ( const QXmlName & name, const QStringRef & value );
        virtual void qualify();
        virtual void endElement ();
        virtual bool hasDelegate ();


    
        virtual void atomicValue ( const QVariant & value ){}
        virtual void characters ( const QStringRef &  ){}
        virtual void comment ( const QString & ){}
        virtual void endDocument (){}
        virtual void endOfSequence (){}
        virtual void namespaceBinding ( const QXmlName &){}
        virtual void processingInstruction ( const QXmlName & , const QString &  ){}
        virtual void startDocument (){}
        virtual void startOfSequence (){}


        virtual bool canQualify(QString field);



        virtual QHash<QString,QString> finalyEval(bool reverse=false);

    private:
        Analyser::Key* qualificator;
        Analyser::Table* table;
        Row * delegate;
        StateEngine * state;
        QHash<QString,QString> member_fields;
        QHash<QString,QString> sub_eval_result;
        QList<Analyser::Key*> qualified_keys;
        Row * parent;
        bool qualified;
    };
};







class Import : public QObject
{
public:
    Import(QList<Analyser::Table *> scheme );
    void import(QByteArray d);
private:
    QXmlQuery query;
    QList<Analyser::Table *> m_scheme;
};
