#ifndef MATRIXLOADER_PRESSIO_H
#define MATRIXLOADER_PRESSIO_H

/**
 * \file
 * \brief builders for LibPressio
 */

#include <matrixloader_builder.h>
#include <matrixloader_ext/utils/dense.h>
#include <libpressio_ext/cpp/data.h>
#include <libpressio_ext/cpp/dtype.h>

/**
 * constructs a pressio_data object
 *
 * \tparam Value the type of the pressio_data object to construct
 */
template <class Value>
class PressioMatrixBuilder: public DenseMatrixBuilder<pressio_data, Value>
{

  public:
    /**
     * constructs a presiso_data object
     */
		pressio_data build() const override {
      return pressio_data::copy(
          pressio_dtype_from_type<Value>(),
            this->value.get(),
            {this->get_rows(), this->get_columns()}
          );
      
    }
};

#endif /* end of include guard: MATRIXLOADER_PRESSIO */
