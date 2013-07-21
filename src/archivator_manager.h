#ifndef ARCHIVATOR_MANAGER_H
#define ARCHIVATOR_MANAGER_H
#include "frequency_processor.h"
#include "tree.h"
#include <queue>
#include <vector>

class archivator_manager
{
private:
    typedef frequency_processor::frequency_table_t frequency_table_t;
    typedef frequency_processor::iterator_t        frequency_iterator_t;
    typedef frequency_processor::const_iterator_t  const_frequency_iterator_t;
    typedef tree_item <tree_item_data>             tree_item_t;
    typedef tree_item_t*                           tree_item_ptr_t;
    typedef std::vector <tree_item_ptr_t>          vector_t;
    typedef std::priority_queue <tree_item_ptr_t, vector_t, data_comparator > priority_queue_t;

    frequency_processor __freq_processor;


    void __create_queue(const frequency_table_t& table, priority_queue_t& queue) const;

public:
    archivator_manager();

    bool process_file(const std::string& file_name);
};


#endif
