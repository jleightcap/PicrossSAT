#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "io.h"

TEST(IO, Tokenize) { 
  // these are invalid user strings, just verifies brackets/spaces.
  std::string raw1("[        ]");
  std::vector<std::string> tokens1 = tokenize(raw1);
  EXPECT_EQ(tokens1[0], "[");
  EXPECT_EQ(tokens1[1], "]");

  std::string raw2("1 [2 3] 4");
  std::vector<std::string> tokens2 = tokenize(raw2);
  EXPECT_EQ(tokens2[0], "1");
  EXPECT_EQ(tokens2[1], "[");
  EXPECT_EQ(tokens2[2], "2");
  EXPECT_EQ(tokens2[3], "3");
  EXPECT_EQ(tokens2[4], "]");
  EXPECT_EQ(tokens2[5], "4");
}

TEST(IO, Parse) {
  std::string raw1("[1]");
  std::vector<std::vector<int>> parse1 = parse(raw1);
  EXPECT_EQ(parse1[0][0], 1);

  std::string raw2("[1] [2 3] [4 5 6]");
  std::vector<std::vector<int>> parse2 = parse(raw2);
  EXPECT_EQ(parse2.size(), 3);
  EXPECT_EQ(parse2[0][0], 1);     // [1]
  EXPECT_EQ(parse2[0].size(), 1);
  EXPECT_EQ(parse2[1][0], 2);     // [2 3]
  EXPECT_EQ(parse2[1][1], 3);
  EXPECT_EQ(parse2[1].size(), 2);
  EXPECT_EQ(parse2[2][0], 4);     // [4 5 6]
  EXPECT_EQ(parse2[2][1], 5);
  EXPECT_EQ(parse2[2][2], 6);
  EXPECT_EQ(parse2[2].size(), 3);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
