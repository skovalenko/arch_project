#include "file.h"
#include <assert.h>

file_io_base::file_io_base(const std::string &file_name, const OPEN_TYPE type, const bool bin_mode)
    : __binary_mode(bin_mode)
{
    std::ios_base::openmode mode;
    if (bin_mode) mode = stream_t::binary;

    switch (type)
    {
    case WRITER:    
        mode |= stream_t::out;
        __fd.open(file_name.c_str(), mode);
        break;

    case READER:
        mode |= stream_t::in;
        __fd.open(file_name.c_str(), mode);
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


file_reader::file_reader(const std::string &file_name, const bool bin_mode)
    : file_io_base(file_name, READER, bin_mode)
{
}

void file_reader::read(std::string &buffer)
{
    if (!__fd.is_open()) return;

    std::string tmp;

    while (!__fd.eof())
    {
        std::getline(__fd, tmp);
        buffer.append(tmp);
    }
}

file_writer::file_writer(const std::string &file_name, const bool bin_mode)
    : file_io_base(file_name, WRITER, bin_mode)
{
}

void file_writer::write(const std::string &buffer)
{
    if (!__fd.is_open()) return;

    __fd << buffer;
}
