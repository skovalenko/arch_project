#ifndef HAFFMAN_H
#define HAFFMAN_H
#include "tree.h"
#include <map>
#include <string>

class haffman_table;
class haffman_tree;

class haffman_tree
{
private:
    const tree __core;

public:
    haffman_tree(const tree& bt);

    haffman_table convert_to_table() const;

};

class haffman_table
{
private:
    typedef std::map <const char, const std::string> table_t;
    table_t __table;

public:
    haffman_table();

    void insert(const char c, const std::string& str);
};



#endif
