#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include <string>

class file_io_base
{
protected:
    typedef std::fstream stream_t;
    stream_t __fd;

    enum OPEN_TYPE {WRITER, READER} ;


public:
    file_io_base(const std::string& file_name, const OPEN_TYPE type);

    virtual ~file_io_base() = 0;
};

class file_reader : public file_io_base
{
public:
    file_reader(const std::string& file_name);

    void read(std::string& buffer);
};

class file_writer : public file_io_base
{
public:
    file_writer(const std::string& file_name);

    void write(const std::string& buffer);
};

#endif // FILE_H
