#include "archivator_manager.h"
#include "file.h"
#include "assert.h"

archivator_manager::archivator_manager()
    : __haffman_tree(0),
      __haffman_table(0)
{

}

archivator_manager::~archivator_manager()
{
    delete __haffman_tree;
}

void archivator_manager::__read_file(const std::string &file_name, std::string &buffer) const
{
    qDebug() << "archivator_manager::__read_file";

    //open file (auto class)
    file_reader auto_reader(file_name);

    //read it
    auto_reader.read(buffer);
}

void archivator_manager::__write_content(const std::string &file_name, const std::string &buffer) const
{
    qDebug() << "archivator_manager::__write_file";

    file_writer auto_writer(file_name);
    auto_writer.write(buffer);
}

bool archivator_manager::__encode(const std::string &buffer, std::string &out_content) const
{
    qDebug() << "archivator_manager::__encode";
    std::string symbol_code;
    std::string buff;

    qDebug() << "archivator_manager::__encode in size = " << buffer.size();

///    __haffman_table->print();


    for (size_t i = 0; i < buffer.size(); ++i)
    {
        if ((i % 1000000) == 0) qDebug() << "archivator_manager::__encode i=" << i;
        if (!__haffman_table->get_symbol_code(buffer[i], symbol_code))
        {
            qDebug() << "archivator_manager::encode_file - unknown symbol";
            return false;
        }

        //qDebug() << "symbol=" << buffer[i] << "code=" << symbol_code.c_str();

        buff += symbol_code;

        if (buff.size() >= 8)
        {
            std::bitset <8> tmp(buff.substr(0, 8));
            out_content += (uint8_t)tmp.to_ulong();
            buff = buff.substr(8);
        }

/*
        int tmp = bit_count + symbol_code.get_length();
        if (tmp < 8)
        {
            qDebug() << "bitcount=" << bit_count;
            qDebug() << "code=" << (int)symbol_code.get_code();
            qDebug() << "code=" << (int)(symbol_code.get_code() << (8 - tmp));
            byte_buffer |= (symbol_code.get_code() << (8 - tmp));
            bit_count = tmp;
            qDebug() << "current_code=" << (int)byte_buffer;
        }
        else if (tmp == 8)
        {
            byte_buffer |= symbol_code.get_code();
            bit_count = 0;
            qDebug() << "current_code=" << (int)byte_buffer;
            out_content += byte_buffer;
            byte_buffer = 0;
        }
        else if (tmp > 8)
        {
            qDebug() << "bitcount=" << bit_count;

            int offset = tmp - 8;
            qDebug() << "offset=" << offset;
            byte_buffer |= symbol_code.get_code() >> offset;
            qDebug() << "current_code=" << (int)byte_buffer;
            out_content += byte_buffer;
            bit_count = symbol_code.get_length() - offset;
            byte_buffer = symbol_code.get_code() << 8 - offset;
        }
        */
    }

    qDebug() << "archivator_manager::__encode out size = " << out_content.size();

    return true;
}

bool archivator_manager::__prepare_encoder(const std::string &file_content)
{
    qDebug() << "archivator_manager::__prepare_encoder";

    //count the number of occurrences for each character
    __freq_processor.process(file_content);

    //get table
    const frequency_table_t& table = __freq_processor.get_table();

    //create queue of tree items
    priority_queue_t item_queue;

    //for (const_frequency_iterator_t iter = table.begin(); iter != table.end(); ++iter)
    for (const_frequency_iterator_t iter = table.begin(); iter != table.end(); ++iter)
    {
        item_queue.push(new tree_item_t(tree_item_data(iter->first, iter->second)));
    }

    if (item_queue.empty())
    {
        qDebug() << "archivator_manager::__prepare_encoder - queue is empty";
        return false;
    }

    //process queue
    while (item_queue.size() != 1)
    {
        //get first two items of the queue
        const tree_item_t* first = item_queue.top();
        item_queue.pop();

        const tree_item_t* second = item_queue.top();
        item_queue.pop();

        //create fake node
        tree_item_t* node = new tree_item_t(tree_item_data(first->get_data().number + second->get_data().number));

        //add childs to fake node
        node->set_left_child(first);
        node->set_right_item(second);

        //push fake node to queue
        item_queue.push(node);
    }

    if (!item_queue.top())
    {
        qDebug() << "archivator_manager::__prepare_encoder - bad ptr";
        return false;
    }

    //create haffman tree and haffman table
    __haffman_tree = new haffman_tree(item_queue.top());
    __haffman_table = __haffman_tree->make_haffman_table();

    if (!__haffman_table)
    {
        qDebug() << "archivator_manager::__prepare_encoder - table isn't created";
        return false;
    }

    return true;
}

bool archivator_manager::encode_file(const std::string &file_name, const std::string &file_out)
{
    qDebug() << "archivator_manager::encode_file";

    std::string file_content;

    __read_file(file_name, file_content);

    if (file_content.empty())
    {
        qDebug() << "archivator_manager::encode_file - file is empty";
        return false;
    }

    //prepare haffman table
    if (!__prepare_encoder(file_content)) return false;

    std::string out_content;
    __haffman_table->size();
    __encode(file_content, out_content);

    qDebug() << "deflated=" << ((float)out_content.size() / (float)file_content.size()) * 100 << "%";

    __write_content(file_out, out_content);




    return true;
}

bool archivator_manager::decode_file(const std::string &file_name, const std::string &file_out)
{
    qDebug() << "archivator_manager::decode_file";

    std::string file_content;

    __read_file(file_name, file_content);

}
