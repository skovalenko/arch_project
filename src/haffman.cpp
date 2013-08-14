#include "haffman.h"
#include <iostream>

haffman_tree::haffman_tree(const data_t* root)
    : __root_item(root)
{}

haffman_table* haffman_tree::make_haffman_table() const
{
    haffman_table* table = new haffman_table;

    __process_tree(__root_item, table);

    return table;
}

void haffman_tree::__process_tree(const data_t * const item, haffman_table * const table, const std::string &code) const
{
    const data_t* left = item->get_left_child();
    bool process_status = false;

    if (left)
    {
        process_status = true;
        __process_tree(left, table, code + '0');
    }

    const data_t* right = item->get_right_child();
    if (right)
    {
        process_status = true;
        __process_tree(right, table, code + '1');
    }

    if (!process_status) table->insert(item->get_data().symbol, code);
}

haffman_table::haffman_table()
{

}

void haffman_table::insert(const char c, const std::string &code)
{
    __table.insert(value_type_t(c, code));
}

bool haffman_table::get_symbol_code(const char c, std::string &code) const
{
    iterator_t iter = __table.find(c);

    if (iter == __table.end()) return false;

    code = iter->second;

    return true;

}
