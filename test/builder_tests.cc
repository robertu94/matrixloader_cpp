#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <libmatrixloader.h>

template <class Builder>
class BuilderTests: public ::testing::Test {
  void SetUp() {
    builder = std::make_unique<Builder>();
  }

  protected:
  std::unique_ptr<Builder> builder;
};

TYPED_TEST_SUITE_P(BuilderTests);

TYPED_TEST_P(BuilderTests, Sparse)
{
  this->builder->reserve(2, 8, 4);
  this->builder->set_entry(0,0, 1.0);
  this->builder->set_entry(1,0, 1.0);
  this->builder->set_entry(0,1, 1.0);
  //this should force a resize since the reserve hint was wrong
  this->builder->set_entry(2,3, 1.0);
  this->builder->build();
}

TYPED_TEST_P(BuilderTests, Dense)
{
  double value = 0;
  this->builder->reserve(5,5,25);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      this->builder->set_entry(i,j, ++value);
    }
  }
  auto matrix = this->builder->build();
  (void)matrix;
}

REGISTER_TYPED_TEST_SUITE_P(BuilderTests, Sparse, Dense);

#if LIBMATRIXLOADER_HAS_ARMADILLO
#include<matrixloader_ext/builders/armadillo.h>
using Types = ::testing::Types<ArmadilloSparseMatrixBuilder<double>, ArmadilloDenseMatrixBuilder<double>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Armadillo, BuilderTests, Types);
#endif

#if LIBMATRIXLOADER_HAS_LIBPRESSIO
#include<matrixloader_ext/builders/pressio.h>
INSTANTIATE_TYPED_TEST_SUITE_P(Pressio, BuilderTests, PressioMatrixBuilder<double>);
#endif
