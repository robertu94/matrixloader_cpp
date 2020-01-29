#ifndef LIBMATRIXLOADER_TEST_MOCKS
#define LIBMATRIXLOADER_TEST_MOCKS
#include <gmock/gmock.h>
#include <libmatrixloader.h>

using ::testing::NaggyMock;

class MockBuilder : public MatrixBuilder<std::array<double,9>,double> {
  public:
  MOCK_METHOD(void, reserve, (size_t rows, size_t columns, size_t nonzeros), (override));
  MOCK_METHOD(void, set_entry, (size_t row, size_t column, double const& value), (override));
  MOCK_METHOD((std::array<double,9>), build, (), (const override));
};


#endif /* end of include guard: LIBMATRIXLOADER_TEST_MOCKS */
