#ifndef ARCHIVATOR_MANAGER_H
#define ARCHIVATOR_MANAGER_H
#include "frequency_processor.h"
#include "tree.h"
#include <queue>
#include <vector>
#include "haffman.h"
#include <Qt/qdebug.h>


// this class manages the process of archiving
class archivator_manager
{
private:
    typedef frequency_processor::frequency_table_t frequency_table_t;
    typedef frequency_processor::const_iterator_t  const_frequency_iterator_t;
    typedef tree_item <tree_item_data>             tree_item_t;
    typedef tree_item_t*                           tree_item_ptr_t;
    typedef std::vector <tree_item_ptr_t>          vector_t;

    // need for std::priority_queue
    struct data_comparator
    {
        bool operator()(const tree_item_ptr_t& d1, const tree_item_ptr_t& d2) const
        {
            return d1->get_data().number > d2->get_data().number;
        }
    };

    typedef std::priority_queue <const tree_item_ptr_t, vector_t, data_comparator > priority_queue_t;

    frequency_processor __freq_processor;
    haffman_tree*       __haffman_tree;
    haffman_table*      __haffman_table;

    void __read_file(const std::string& file_name, std::string& buffer) const;
    void __write_content(const std::string& file_name, const std::string& buffer) const;
    bool __prepare_encoder(const std::string& file_content);
    bool __encode(const std::string& buffer, std::string& out_content) const;


public:
    archivator_manager();
    ~archivator_manager();

    bool encode_file(const std::string& file_name, const std::string& file_out);
    bool decode_file(const std::string& file_name, const std::string& file_out);
};


#endif
