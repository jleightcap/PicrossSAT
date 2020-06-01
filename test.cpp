#include "gtest/gtest.h"

#include <vector>
#include <string>

#include "io.h"
#include "board.h"
#include "sat.h"

using std::string;
using std::vector;

TEST(IO, Tokenize)
{
    // empty string
    string empty("");
    auto empty_tokens = tokenize(empty);
    EXPECT_EQ(empty_tokens.size(), 0);

    // empty list, tab and space ignored
    string raw1("[        ]");
    auto tokens1 = tokenize(raw1);
    vector<string> expected1 = {"[", "]"};
    EXPECT_EQ(tokens1.size(), expected1.size());
    for (size_t ii = 0; ii < tokens1.size(); ii++)
        EXPECT_EQ(tokens1[ii], expected1[ii]);

    // various sized lists
    string raw2("[1] [2 3] [4]");
    auto tokens2 = tokenize(raw2);
    vector<string> expected2 = {"[", "1", "]", "[", "2", "3", "]", "[", "4", "]"};
    EXPECT_EQ(tokens2.size(), expected2.size());
    for (size_t ii = 0; ii < tokens2.size(); ii++)
        EXPECT_EQ(tokens2[ii], expected2[ii]);

    // multi-digit
    string raw3("[123]");
    auto tokens3 = tokenize(raw3);
    vector<string> expected3 = {"[", "123", "]"};
    EXPECT_EQ(tokens3.size(), expected3.size());
    for (size_t ii = 0; ii < tokens3.size(); ii++)
        EXPECT_EQ(tokens3[ii], expected3[ii]);
}



TEST(IO, Parse)
{
    // empty
    string empty("");
    auto parse0 = parse(empty);
    EXPECT_EQ(parse0.size(), NULL);

    // singleton
    string raw1("[1]");
    auto parse1 = parse(raw1);
    EXPECT_EQ(parse1[0][0], 1);

    // mixed sizes
    string raw2("[1] [2 3] [456]");
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
    vector<vector<boardState>> empty;
    auto empty_board = boardString(&empty);
    EXPECT_EQ(empty_board, "");

    // non-empty, mixed state
    vector<vector<boardState>> board
        = {{FALSE,FALSE,FALSE}, {TRUE,TRUE,TRUE}, {UNKNOWN,FALSE,UNKNOWN}};
    auto print_board = boardString(&board);
    EXPECT_EQ(print_board, "xxx\n███\n x \n");
}



TEST(Board, Construct)
{
    // board initialization
    vector<vector<int>> vec1 = {{1}, {1}};
    Board b1(&vec1, &vec1);
    EXPECT_EQ((*b1.getBoard())[0][0], UNKNOWN);

    // setting memory of board
    b1.setBoard(TRUE, 1, 1);
    EXPECT_EQ((*b1.getBoard())[1][1], TRUE);
}

TEST(SAT, sumPermute)
{
    // base case
    auto v1 = sumPermute(1,1,1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1[0].size(), 1);
    EXPECT_EQ(v1[0][0], 1);

    // excess height
    auto v2_h = sumPermute(1,2,1);
    EXPECT_EQ(v2_h.size(), 1);
    EXPECT_EQ(v2_h[0].size(), 1);
    EXPECT_EQ(v2_h[0][0], 1);

    // excess width
    auto v2_w = sumPermute(1,1,2);
    EXPECT_EQ(v2_w.size(), 1);
    EXPECT_EQ(v2_w[0].size(), 1);
    EXPECT_EQ(v2_w[0][0], 1);

    // 4 cells in width of 4, with height limit 3
    auto v3 = sumPermute(4,3,4);
    EXPECT_EQ(v3.size(), 4);
    vector<int> v3_0 = {1,1,1,1};
    vector<int> v3_1 = {2,1,1};
    vector<int> v3_2 = {2,2};
    vector<int> v3_3 = {3,1};
    for (size_t nn = 0; nn < v3[0].size(); nn++)
        EXPECT_EQ(v3[0][nn], v3_0[nn]);
    for (size_t nn = 0; nn < v3[1].size(); nn++)
        EXPECT_EQ(v3[1][nn], v3_1[nn]);
    for (size_t nn = 0; nn < v3[2].size(); nn++)
        EXPECT_EQ(v3[2][nn], v3_2[nn]);
    for (size_t nn = 0; nn < v3[3].size(); nn++)
        EXPECT_EQ(v3[3][nn], v3_3[nn]);
}
