#include <gtest/gtest.h>
#include "file.h"
#include <string>

TEST(test_file_io, test_reader_and_writer)
{
    const std::string text("test_string123");
    const std::string fname("text");

    do
    {
        file_writer wr(fname);
        wr.write(text);
    }
    while (false);

    file_reader rd(fname);
    std::string buffer;
    rd.read(buffer);

    ASSERT_STREQ(text.c_str(), buffer.c_str());
}
