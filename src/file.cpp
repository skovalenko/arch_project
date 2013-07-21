#include "file.h"
#include <assert.h>

file_io_base::file_io_base(const std::string &file_name, const OPEN_TYPE type)
{
    switch (type)
    {
    case WRITER:
        __fd.open(file_name.c_str(), stream_t::out/* | stream_t::app*/);
        break;

    case READER:
        __fd.open(file_name.c_str(), stream_t::in);
        break;

    default:
        assert(!"Unknow type");
        break;
    }
}

file_io_base::~file_io_base()
{
    if (__fd.is_open())
    {
        __fd.close();
    }
}


file_reader::file_reader(const std::string &file_name)
    : file_io_base(file_name, READER)
{
}

void file_reader::read(std::string &buffer)
{
    if (!__fd.is_open()) return;

    while (!__fd.eof())
    {
        __fd >> buffer;
    }
}

file_writer::file_writer(const std::string &file_name)
    : file_io_base(file_name, WRITER)
{
}

void file_writer::write(const std::string &buffer)
{
    if (!__fd.is_open()) return;

    __fd << buffer;
}
