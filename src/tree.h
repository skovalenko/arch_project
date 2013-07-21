#ifndef TREE_H
#define TREE_H


struct tree_item_data
{
    char          symbol;
    unsigned int  number;

    tree_item_data(const char c, unsigned int n)
        : symbol(c),
          number(n)
    {
    }
};

struct data_comparator
{
    bool operator()(const tree_item_data& d1, const tree_item_data& d2);
};

template <class data>
class tree_item
{
private:
    //item data
    data __data;

    //left and right child
    tree_item* __left;
    tree_item* __right;

public:
    tree_item(const data& d)
        : __data(d),
          __left(0),
          __right(0)
    {
    }

    void set_left_child(const tree_item* item)
    {
        __left = item;
    }

    void set_right_item(const tree_item* item)
    {
        __right = item;
    }

    const data& get_data() const
    {
        return __data;
    }
};

#endif
