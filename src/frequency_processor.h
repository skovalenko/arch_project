#ifndef FREQUENCY_PROCESSOR_H
#define FREQUENCY_PROCESSOR_H
#include <queue>
#include <map>

struct symbol_stat
{
    char         symbol;
    unsigned int number;

    symbol_stat(const char c, const unsigned int n)
        : symbol(c),
          number(n)
    {}

    bool operator()(const symbol_stat& s)
    {
        return number < s.number;
    }
};

class frequency_processor
{
public:
    typedef std::priority_queue <symbol_stat>   queue_t;
    typedef std::map <char, unsigned int>       frequency_table_t;

    frequency_processor();
};

#endif // FREQUENCY_PROCESSOR_H
