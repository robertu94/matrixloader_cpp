#ifndef MATRIXLOADER_ARMADILLO_ADAPTER_H
#define MATRIXLOADER_ARMADILLO_ADAPTER_H
#include <matrixloader_adapter.h>
#include <algorithm>
#include <armadillo>

/**
 * \file
 * \brief Adapters for Armadillo
 */


/**
 * Adapts from a Sparse Matrix
 * \tparam MatrixBuilder the builder interface used
 * \tparam Type the type contained in the sparse matrix
 */
template <class Type, class MatrixBuilder>
class ArmadilloSparseMatrixAdapter: public MatrixAdapter<arma::SpMat<Type>, MatrixBuilder> {
  public:
  using MatrixAdapter<arma::SpMat<Type>, MatrixBuilder>::MatrixAdapter;

  /**
   * converts from a sparse matrix
   *
   * \param[in] matrix the type to convert from
   * \returns the converted matrix
   */
  typename MatrixBuilder::matrix_type convert(arma::SpMat<Type> const& matrix) override {
    this->builder->reserve(matrix.n_rows, matrix.n_cols, matrix.n_nonzero);
    auto begin = std::begin(matrix);
    auto end = std::end(matrix);
    while(begin != end) {
      this->builder->set_entry(begin.row(), begin.col(), (*begin));
      ++begin;
    }
    return this->builder->build();
  }
};

/**
 * Adapts from a Dense Matrix
 * \tparam MatrixBuilder the builder interface used
 * \tparam Type the type contained in the sparse matrix
 */
template <class Type, class MatrixBuilder>
class ArmadilloDenseMatrixAdapter: public MatrixAdapter<arma::Mat<Type>, MatrixBuilder> {
  public:
  using MatrixAdapter<arma::Mat<Type>, MatrixBuilder>::MatrixAdapter;

  /**
   * converts from a dense matrix
   *
   * \param[in] matrix the type to convert from
   * \returns the converted matrix
   */
  typename MatrixBuilder::matrix_type convert(arma::Mat<Type> const& matrix) override {
    //assume the matrix is dense with many nonzeros
    this->builder->reserve(matrix.n_rows, matrix.n_cols, matrix.n_rows * matrix.n_cols);

    //in armadillo, memory is in stored in column major order
    //use memptr() interface to avoid unnecessary recalculation of index position
    auto ptr = matrix.memptr();
    for (int i = 0; i < matrix.n_cols; ++i) {
      for (int j = 0; j < matrix.n_rows; ++j) {
        auto value = *ptr;
        if(value != 0) {
          this->builder->set_entry(i, j, value);
        }
        ++ptr;
      }
    }
    return this->builder->build();
  }
};

#endif /* end of include guard: MATRIXLOADER_ARMADILLO_ADAPTER_H */
