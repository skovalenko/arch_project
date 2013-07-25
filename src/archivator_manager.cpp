#include "archivator_manager.h"
#include "file.h"
#include "assert.h"
archivator_manager::archivator_manager()
    : __haffman_tree(0)
{

}

archivator_manager::~archivator_manager()
{
    delete __haffman_tree;
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

    //create queue of tree items
    priority_queue_t item_queue;
    __create_queue(table, item_queue);

    //process queue and create haffman tree
    __create_haffman_tree(item_queue);

    return true;
}

void archivator_manager::__create_queue(const frequency_table_t &table, priority_queue_t& queue) const
{
    assert(queue.empty());

    for (const_frequency_iterator_t iter = table.begin(); iter != table.end(); ++iter)
    {
        queue.push(new tree_item_t(tree_item_data(iter->first, iter->second)));
    }
}

void archivator_manager::__create_haffman_tree(priority_queue_t &queue)
{
    assert(!queue.empty());

    std::cout << "start" << std::endl;
    while (queue.size() > 1)
    {
        std::cout << "size" << queue.size() << std::endl;
        //get first two items of the queue
        const tree_item_t* first = queue.top();
        queue.pop();

        const tree_item_t* second = queue.top();
        queue.pop();

        //create fake node
        tree_item_t* node = new tree_item_t(tree_item_data());
        node->set_left_child(first);
        node->set_right_item(second);

        queue.push(node);
    }

    __haffman_tree = new haffman_tree(binary_tree(queue.top()));
}
