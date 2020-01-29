#include <gtest/gtest.h>
#include <string>
#include <sstream>


#include "matrixloader_ext/parsers/csv.h"
#include "mocks.h"


TEST(Parsers, CsvNoHeader) {
  std::string csv_no_header = R"(1,2,3
1.5,2.5,3.5
1.9,2.9,3.9)";
  using MockType = NaggyMock<MockBuilder>;
  auto  builder = std::make_unique<MockType>();

  EXPECT_CALL(*builder, reserve(3,3,9));
  EXPECT_CALL(*builder, set_entry(0,0,1.0));
  EXPECT_CALL(*builder, set_entry(0,1,2.0));
  EXPECT_CALL(*builder, set_entry(0,2,3.0));
  EXPECT_CALL(*builder, set_entry(1,0,1.5));
  EXPECT_CALL(*builder, set_entry(1,1,2.5));
  EXPECT_CALL(*builder, set_entry(1,2,3.5));
  EXPECT_CALL(*builder, set_entry(2,0,1.9));
  EXPECT_CALL(*builder, set_entry(2,1,2.9));
  EXPECT_CALL(*builder, set_entry(2,2,3.9));
  EXPECT_CALL(*builder, build());

  std::istringstream ss(csv_no_header);


  CsvParser<MockType> parser(std::move(builder));
  parser.load(ss);
}

TEST(Parsers, CsvWithSpace) {
  std::string csv_no_header = R"(1, 2,3 
1.5,2.5 ,3.5
1.9 ,2.9,3.9)";
  using MockType = NaggyMock<MockBuilder>;
  auto  builder = std::make_unique<MockType>();

  EXPECT_CALL(*builder, reserve(3,3,9));
  EXPECT_CALL(*builder, set_entry(0,0,1.0));
  EXPECT_CALL(*builder, set_entry(0,1,2.0));
  EXPECT_CALL(*builder, set_entry(0,2,3.0));
  EXPECT_CALL(*builder, set_entry(1,0,1.5));
  EXPECT_CALL(*builder, set_entry(1,1,2.5));
  EXPECT_CALL(*builder, set_entry(1,2,3.5));
  EXPECT_CALL(*builder, set_entry(2,0,1.9));
  EXPECT_CALL(*builder, set_entry(2,1,2.9));
  EXPECT_CALL(*builder, set_entry(2,2,3.9));
  EXPECT_CALL(*builder, build());

  std::istringstream ss(csv_no_header);


  CsvParser<MockType> parser(std::move(builder));
  parser.load(ss);
}

TEST(Parsers, CsvWithHeader) {
  std::string csv_with_header = R"(a,b,c
1,2,3
1.5,2.5,3.5
1.9,2.9,3.9)";
  using MockType = NaggyMock<MockBuilder>;
  auto  builder = std::make_unique<MockType>();

  EXPECT_CALL(*builder, reserve(3,3,9));
  EXPECT_CALL(*builder, set_entry(0,0,1.0));
  EXPECT_CALL(*builder, set_entry(0,1,2.0));
  EXPECT_CALL(*builder, set_entry(0,2,3.0));
  EXPECT_CALL(*builder, set_entry(1,0,1.5));
  EXPECT_CALL(*builder, set_entry(1,1,2.5));
  EXPECT_CALL(*builder, set_entry(1,2,3.5));
  EXPECT_CALL(*builder, set_entry(2,0,1.9));
  EXPECT_CALL(*builder, set_entry(2,1,2.9));
  EXPECT_CALL(*builder, set_entry(2,2,3.9));
  EXPECT_CALL(*builder, build());

  std::istringstream ss(csv_with_header);


  CsvParser<MockType> parser(std::move(builder));
  parser.set_header_rows(1);
  parser.load(ss);
}
