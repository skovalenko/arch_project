#ifndef FREQUENCY_PROCESSOR_H
#define FREQUENCY_PROCESSOR_H
#include <map>
#include <string>

// this class defines a number of occurrences of each symbol
// and store them in the table - std::map
class frequency_processor
{
public:
    typedef std::map <const char, unsigned int> frequency_table_t;
    typedef frequency_table_t::value_type       value_type_t;
    typedef frequency_table_t::iterator         iterator_t;
    typedef frequency_table_t::const_iterator   const_iterator_t;
    typedef std::pair <iterator_t, bool>        ret_t;

private:
    static const unsigned int DEFAULT_FREQUENCY_VALUE;
    frequency_table_t __freq_table;

    //read all buffer and fill frequency table
    void __fill_frequency_table(const std::string& buffer);

public:
    frequency_processor();

    void process(const std::string& buffer);
    const frequency_table_t get_table() const;
};

#endif // FREQUENCY_PROCESSOR_H
