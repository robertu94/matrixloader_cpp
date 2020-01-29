#include <matrixloader_ext/builders/armadillo.h>
#include <matrixloader_ext/adapters/armadillo.h>
#include <gtest/gtest.h>

TEST(Armadillo, adapt_dense_to_sparse) {
  arma::Mat<double> dense(3, 3, arma::fill::ones);
  auto builder = std::make_unique<ArmadilloSparseMatrixBuilder<double>>();
  ArmadilloDenseMatrixAdapter<double, decltype(builder)::element_type> adapter(std::move(builder));
  auto converted = adapter.convert(dense);

  EXPECT_EQ(converted.n_rows, 3);
  EXPECT_EQ(converted.n_cols, 3);
  EXPECT_EQ(converted.n_nonzero, 9);
  std::for_each(std::begin(converted), std::end(converted), 
      [] (double const& it) {
        EXPECT_EQ(1, it);
      });

}


TEST(Armadillo, adapt_sparse_to_dense) {
  arma::SpMat<double> sparse(3,3);
  sparse(0,0) = 4.0;
  sparse(2,2) = 5.0;

  
  auto builder = std::make_unique<ArmadilloDenseMatrixBuilder<double>>();
  ArmadilloSparseMatrixAdapter<double, decltype(builder)::element_type> adapter(std::move(builder));
  auto converted = adapter.convert(sparse);
  EXPECT_EQ(converted.n_rows, 3);
  EXPECT_EQ(converted.n_cols, 3);
  EXPECT_EQ(converted(0,0), 4.0);
  EXPECT_EQ(converted(1,1), 0.0);
  EXPECT_EQ(converted(2,2), 5.0);
}
