#include <gtest/gtest.h>
#include "frequency_processor.h"

TEST(test_freq_processor, frequency_calc)
{
    const std::string test_string("123112aba");

    frequency_processor pr;
    pr.process(test_string);

    const frequency_processor::frequency_table_t table = pr.get_table();

    ASSERT_EQ(5, table.size());
    EXPECT_EQ(3, table.at('1'));
    EXPECT_EQ(2, table.at('2'));
    EXPECT_EQ(1, table.at('3'));
    EXPECT_EQ(2, table.at('a'));
    EXPECT_EQ(1, table.at('b'));
}
