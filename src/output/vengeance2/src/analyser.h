#ifndef ANALYSER_H_asoidnasjkld
#define ANALYSER_H_asoidnasjkld

#include <string>
#include <vector>

class Analyser
{
public:
    static std::string table_plural   (std::string);
    static std::string table_singular (std::string);

    enum KeyType
    {
        UnknownKeyType,
        IndexKey,
        PrimaryKey,
        UniqueKey
    };

    struct Field
    {
        std::string name;
        std::string datatype;
    };

    struct Key
    {
        KeyType type;
        std::vector<Field*> fields;
    };

    struct Table
    {
        std::string name;
        std::vector<Field*> fields;
        std::vector<Key*> keys;
    };

    Analyser();
    std::vector<Analyser::Table *>  analyse();
private:
    std::vector<Table *> tables;
    void parseShowCreate(std::string );

};


#endif
