#ifndef TREE_H
#define TREE_H
#include <assert.h>
#include <stack>
#include <iostream>

struct tree_item_data
{
    const char          symbol;
    const unsigned int  number;
    const bool          fake;

    tree_item_data(const char c, const unsigned int n)
        : symbol(c),
          number(n),
          fake(false)
    {}

    tree_item_data(const unsigned int n)
        : symbol(' '),
          number(n),
          fake(true)
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
/*
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
    friend class binary_tree;
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
            assert(!__st.empty() && !iter.__st.empty());
            return (__st.top() != iter.__st.top());
        }

        iterator& operator++()
        {

            assert(!__st.empty());

            const data_t* tmp = __st.top();
            __st.pop();

            if (tmp->get_left_child())  __st.push(tmp->get_left_child());
            if (tmp->get_right_child()) __st.push(tmp->get_right_child());
            return *this;
        }


//        const tree_item_data& operator*() const
//        {
//            return __st.top()->get_data();
//        }

        const data_t* operator->() const
        {
            return __st.top();
        }

    };

    iterator begin() const
    {
        return iterator(__root);
    }

    iterator end() const
    {
        iterator iter(__root);

        while (true)
        {
            if (iter.__st.size() == 1)
            {
                const data_t* d = iter.__st.top();
                if (!d->get_left_child() && !d->get_right_child()) return iter;
            }

            ++iter;
        }

        return iter;
    }
};
*/
#endif
