#include "tree.h"

bool data_comparator::operator()(const tree_item_data& d1, const tree_item_data& d2)
{
    return d1.number > d2.number;
}
