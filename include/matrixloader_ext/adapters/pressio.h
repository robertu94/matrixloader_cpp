#ifndef MATRIXLOADER_PRESSIO_ADAPTER_H
#define MATRIXLOADER_PRESSIO_ADAPTER_H
#include <matrixloader_adapter.h>
#include <libpressio_ext/cpp/data.h>
#include <libpressio_ext/cpp/dtype.h>
#include <cassert>

/**
 * \file
 * \brief Adapters for LibPressio
 */



/**
 * Convert a matrix from a pressio_data buffer
 *
 * \tparam Type the type of the input type
 * \tparam MatrixBuilder the type of the builder interface
 */
template <class Type, class MatrixBuilder>
class PressioMatrixAdapter: public MatrixAdapter<pressio_data, MatrixBuilder> {

  public:
  /**
   * Use the parent classes constructors
   */
  using MatrixAdapter<pressio_data, MatrixBuilder>::MatrixAdapter;

  /**
   * convert from a pressio_data object
   *
   * \param[in] matrix the matrix to convert
   * \returns the converted matrix
   */
  typename MatrixBuilder::matrix_type convert(pressio_data const& matrix) override {
    size_t rows = matrix.get_dimension(0);
    size_t columns = matrix.get_dimension(1);
    assert(matrix.dtype() == pressio_dtype_from_type<Type>());
    auto ptr = static_cast<Type*>(matrix.data());
    
    
    this->builder->reserve(rows, columns, rows*columns);

    for (int j = 0; j < rows; ++j) {
      for (int i = 0; i < columns; ++i) {
        auto value = *ptr;
        if(value != 0) {
          this->builder->set_entry(j, i, value);
        }
        ++ptr;
      }
    }

    return this->builder->build();


  }
};

#endif /* end of include guard */
