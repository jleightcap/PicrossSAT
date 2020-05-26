#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "io.h"
#include "board.h"
#include "sat.h"

TEST(IO, Tokenize)
{
    // empty string
    std::string empty("");
    auto empty_tokens = tokenize(empty);
    EXPECT_EQ(empty_tokens.size(), 0);

    // empty list, tab and space ignored
    std::string raw1("[        ]");
    auto tokens1 = tokenize(raw1);
    std::vector<std::string> expected1 = {"[", "]"};
    EXPECT_EQ(tokens1.size(), expected1.size());
    for (size_t ii = 0; ii < tokens1.size(); ii++)
        EXPECT_EQ(tokens1[ii], expected1[ii]);

    // various sized lists
    std::string raw2("[1] [2 3] [4]");
    auto tokens2 = tokenize(raw2);
    std::vector<std::string> expected2 = {"[", "1", "]", "[", "2", "3", "]", "[", "4", "]"};
    EXPECT_EQ(tokens2.size(), expected2.size());
    for (size_t ii = 0; ii < tokens2.size(); ii++)
        EXPECT_EQ(tokens2[ii], expected2[ii]);

    // multi-digit
    std::string raw3("[123]");
    auto tokens3 = tokenize(raw3);
    std::vector<std::string> expected3 = {"[", "123", "]"};
    EXPECT_EQ(tokens3.size(), expected3.size());
    for (size_t ii = 0; ii < tokens3.size(); ii++)
        EXPECT_EQ(tokens3[ii], expected3[ii]);
}



TEST(IO, Parse)
{
    // empty
    std::string empty("");
    auto parse0 = parse(empty);
    EXPECT_EQ(parse0.size(), 0);

    // singleton
    std::string raw1("[1]");
    auto parse1 = parse(raw1);
    EXPECT_EQ(parse1[0][0], 1);

    // mixed sizes
    std::string raw2("[1] [2 3] [456]");
    auto parse2 = parse(raw2);
    EXPECT_EQ(parse2.size(), 3);
    EXPECT_EQ(parse2[0][0], 1);     // [1]
    EXPECT_EQ(parse2[0].size(), 1);
    EXPECT_EQ(parse2[1][0], 2);     // [2 3]
    EXPECT_EQ(parse2[1][1], 3);
    EXPECT_EQ(parse2[1].size(), 2);
    EXPECT_EQ(parse2[2][0], 456);   // [456]
    EXPECT_EQ(parse2[2].size(), 1);
}



TEST(IO, Print)
{
    // empty board
    std::vector<std::vector<boardState>> empty;
    auto empty_board = board_string(&empty);
    EXPECT_EQ(empty_board, "");

    // non-empty, mixed state
    std::vector<std::vector<boardState>> board
        = {{FALSE,FALSE,FALSE}, {TRUE,TRUE,TRUE}, {UNKNOWN,FALSE,UNKNOWN}};
    auto print_board = board_string(&board);
    EXPECT_EQ(print_board, "xxx\n███\n x \n");
}



TEST(Board, Construct)
{
    // board initialization
    std::vector<std::vector<int>> vec1 = {{1}};
    Board b1(2, &vec1, &vec1);
    EXPECT_EQ((*b1.getBoard())[0][0], UNKNOWN);

    // setting memory of board
    b1.setBoard(TRUE, 1, 1);
    EXPECT_EQ((*b1.getBoard())[1][1], TRUE);
}
