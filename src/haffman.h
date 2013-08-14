#ifndef HAFFMAN_H
#define HAFFMAN_H
#include "tree.h"
#include <map>
#include <string>
#include <inttypes.h>
#include <bitset>
#include <qdebug.h>

class haffman_table;
class haffman_tree;

class haffman_tree
{
private:
    typedef tree_item <tree_item_data> data_t;

    const data_t*  __root_item;

    //void __process_tree(const data_t* const item, haffman_table* const table, const byte_code& code = byte_code()) const;
    void __process_tree(const data_t* const item, haffman_table* const table, const std::string& code = std::string()) const;
public:
    haffman_tree(const data_t* root);

    haffman_table* make_haffman_table() const;
};

class haffman_table
{
private:
    //typedef std::map <const char, const byte_code>   table_t;
    typedef std::map <const char, const std::string>   table_t;
    typedef table_t::value_type                      value_type_t;
    typedef table_t::const_iterator                  iterator_t;
    table_t __table;

public:
    haffman_table();

    void insert(const char c, const std::string& code);

    bool get_symbol_code(const char c, std::string& code) const;

    void size()
    {
        qDebug() << __table.size();
    }

    void print()
    {
        for (table_t::const_iterator iter = __table.begin(); iter != __table.end(); ++iter)
        {
            std::cout << iter->first << " - " << iter->second << std::endl;
        }
    }
};



#endif
