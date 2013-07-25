#ifndef TREE_H
#define TREE_H
#include <assert.h>
#include <stack>

struct tree_item_data
{
    char          symbol;
    unsigned int  number;
    bool          fake;

    tree_item_data(const char c, unsigned int n)
        : symbol(c),
          number(n),
          fake(false)
    {}

    tree_item_data()
        : fake(true)
    {}
};

template <class data>
class tree_item
{
private:
    //item data
    data __data;

    //left and right child
    const tree_item* __left;
    const tree_item* __right;

public:
    explicit tree_item(const data& d)
        : __data(d),
          __left(0),
          __right(0)
    {
    }

    void set_left_child(const tree_item* const item)
    {
        if (this == item) assert(true);
        __left = item;
    }

    void set_right_item(const tree_item* const item)
    {
        if (this == item) assert(true);
        __right = item;
    }

    const tree_item* get_left_child() const
    {
        return __left;
    }

    const tree_item* get_right_child() const
    {
        return __right;
    }

    const data& get_data() const
    {
        return __data;
    }

    data& get_data()
    {
        return __data;
    }
};

class binary_tree
{
private:
    typedef tree_item <tree_item_data> data_t;
    const data_t* __root;

public:
    explicit binary_tree(const data_t* item)
        : __root(item)
    {}

    class iterator
    {
    private:
        typedef std::stack <const data_t*> stack_t;
        stack_t __st;

    public:
        iterator(const data_t* item)
        {
            __st.push(item);
        }

        bool operator!=(const iterator& iter) const
        {
            return (__st.top() == iter.__st.top());
        }

        iterator& operator++()
        {
            assert(__st.empty());

            const data_t* tmp = __st.top();
            __st.pop();

            if (tmp->get_left_child())  __st.push(tmp->get_left_child());
            if (tmp->get_right_child()) __st.push(tmp->get_right_child());
            return *this;
        }

/*
        const tree_item_data& operator*() const
        {
            return __st.top()->get_data();
        }

        const data_t* operator->() const
        {
            return __st.top();
        }
*/
    };
};

#endif
