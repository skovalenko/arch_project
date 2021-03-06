#include "frequency_processor.h"
#include <qdebug.h>

const unsigned int frequency_processor::DEFAULT_FREQUENCY_VALUE = 1;

frequency_processor::frequency_processor()
{
}

void frequency_processor::process(const std::string &buffer)
{
    qDebug() << "frequency_processor::process";

    __fill_frequency_table(buffer);
}


void frequency_processor::__fill_frequency_table(const std::string &buffer)
{
    qDebug() << "frequency_processor::__fill_frequency_table";

    for (int i = 0; i < buffer.size(); ++i)
    {
        if ((i % 10000000) == 0) qDebug() << "frequency_processor::process i=" << i;
        //insert symbol
        ret_t ret = __freq_table.insert(value_type_t(buffer[i], DEFAULT_FREQUENCY_VALUE));

        //if this symbol already exists - update counter
        if (!ret.second)
        {
            ++(ret.first->second);
        }
    }
}

const frequency_processor::frequency_table_t frequency_processor::get_table() const
{
    return __freq_table;
}
