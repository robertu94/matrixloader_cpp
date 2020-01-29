#ifndef MATRIXLOADER_DENSE_H
#define MATRIXLOADER_DENSE_H
#include <matrixloader_builder.h>
#include <algorithm>
#include <memory>

/**
 * \file
 * \brief helper class for dense matrices
 */

namespace {
  /**
   * Copies or Zero initializes memory
   *
   * \param[in] old_values the memory to copy from
   * \param[in] old_rows the old number of rows
   * \param[in] old_columns the old number of columns
   * \param[in] new_values the memory to fill/allocate
   * \param[in] new_rows the new number of rows
   * \param[in] new_columns the new number of columns
   * \param[in] use_row_order -- the elements are in row-major order
   *
   * \tparam T the type of elements to copy
   */
  template <class T>
  void copy_resized(T* old_values, size_t old_rows, size_t old_columns,
              T* new_values, size_t new_rows, size_t new_columns,
              bool use_row_order
              )
  {
    if(old_rows == new_rows && old_columns == new_columns) return;
    if(use_row_order)
    {
      for (size_t i = 0; i < std::min(new_rows,old_rows); ++i) {
        for (size_t j = 0; j < std::min(new_columns,old_columns); ++j) {
            new_values[i*new_columns + j] = old_values[i*old_columns + j];
        }
      }
      
      //zero initialize new values not set by previous code;
      for (size_t i = std::min(new_rows, old_rows); i < new_rows; ++i) {
        for (size_t j = std::min(new_columns, old_columns); j < new_columns; ++j) {
            new_values[i*new_columns + j] = 0;
        }
      }

    } else {
      for (size_t j = 0; j < std::min(new_columns,old_columns); ++j) {
        for (size_t i = 0; i < std::min(new_rows,old_rows); ++i) {
            new_values[i*new_rows + j] = old_values[i*old_rows + j];
        }
      }
      //zero initialize new values not set by previous code;
      for (size_t j = std::min(new_columns, old_columns); j < new_columns; ++j) {
        for (size_t i = std::min(new_rows, old_rows); i < new_rows; ++i) {
            new_values[i*new_rows + j] = 0;
        }
      }
    }

  }
}

/**
 * A helper class to do  memory management for Dense Matrix builders
 *
 * \tparam Matrix the type of the matrix
 * \tparam Value the type of elements of the matrix
 */
template <class Matrix, class Value>
class DenseMatrixBuilder: public MatrixBuilder<Matrix, Value>
{
	private:
    /** the number of rows currently in the matrix */
    size_t n_rows = 0;
    /** the number of columns currently in the matrix */
    size_t n_columns = 0;
    /** the elements are currently in row major order */
    bool row_major = true;

    /**
     * resizes the matrix to a new size
     *
     * \param[in] new_rows the number of rows after resizing
     * \param[in] new_columns the number of columns after resizing
     */
    void resize(size_t new_rows, size_t new_columns) {
      auto tmp = std::make_unique<Value[]>(new_rows * new_columns);
      copy_resized(
          value.get(), this->n_rows, this->n_columns,
          tmp.get(), new_rows, new_columns,
          row_major
          );

      this->n_rows = new_rows;
      this->n_columns = new_columns;
      this->value = std::move(tmp);
    }

  protected:
    /** returns the number of rows in the matrix */
    size_t get_rows() const { return n_rows; }
    /** returns the number of columns in the matrix */
    size_t get_columns() const { return n_columns; }
    /** returns the number of elements in the matrix */
    size_t get_elements() const { return n_rows * n_columns; }
    /** returns the size of the dense matrix in bytes */
    size_t get_size_in_bytes() const { return sizeof(Value) * n_rows * n_columns; }
    /** pointer to the memory of the dense matrix */
    std::unique_ptr<Value[]> value;

	public:
    /**construct a row major matrix*/
    DenseMatrixBuilder()=default;
    /**construct a row or column major matrix*/
    DenseMatrixBuilder(bool row_major): row_major(row_major) {}

    /** reserve the memory for the matrix and set the size 
     *
     * \param[in] rows the number of rows to reserve
     * \param[in] columns the number of columns to reserve
     * \param[in] nonzeros the number of nonzero elements to reserve (ignored)
     * */
		void reserve(size_t rows, size_t columns, size_t nonzeros) override
		{
      auto new_rows = std::max(this->n_rows, rows);
      auto new_columns = std::max(this->n_columns, rows);
      if(new_rows == this->n_rows && new_columns == this->n_columns) return;
      else resize(rows, columns);
		}

    /** set an entry in the matrix
     *
     * \param[in] row the position to set
     * \param[in] column the column to set
     * \param[in] value the value to set
     * */
		void set_entry(size_t row, size_t column, Value const& value) override
		{
      if(row >= this->n_rows || column >= this->n_columns) {
        resize(row >= this->n_rows ? row + 1 : this->n_rows, column >= this->n_columns ? column + 1: this->n_columns);
      }
      if(row_major) {
        this->value[this->n_columns * row + column] = value;
      } else {
        this->value[this->n_rows * column + row] = value;
      }
		}
};
#endif /* end of include guard: MATRIXLOADER_DENSE_H */
