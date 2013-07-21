#include "archivator_manager.h"
#include "file.h"
#include "assert.h"

archivator_manager::archivator_manager()
{

}

bool archivator_manager::process_file(const std::string &file_name)
{
    //open file and read it
    file_reader auto_reader(file_name);

    std::string file_content;
    auto_reader.read(file_content);

    //count the number of occurrences for each character
    __freq_processor.process(file_content);

    //get table
    const frequency_table_t& table = __freq_processor.get_table();

    priority_queue_t queue;

    __create_queue(table, queue);

    while (!queue.empty())
    {
        std::cout << queue.top()->get_data().number << std::endl;
        queue.pop();
    }

    return true;
}

void archivator_manager::__create_queue(const frequency_table_t &table, priority_queue_t& queue) const
{
    assert(queue.empty());

    for (const_frequency_iterator_t iter = table.begin(); iter != table.end(); ++iter)
    {
        std::cout << "c= " << iter->first << "; n= " << iter->second << std::endl;
        tree_item_ptr_t item = new tree_item_t(tree_item_data(iter->first, iter->second));
        queue.push(item);
    }
}
