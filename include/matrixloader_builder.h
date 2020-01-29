#ifndef MATRIXLOADER_BUILDER_H
#define MATRIXLOADER_BUILDER_H
#include <cstddef>

/** \file 
 *  \brief interface to building matrices
 */

/**
 * Adapter pattern used to construct matrices in the native library
 * \tparam Matrix the type of the matrix constructed
 * \tparam ValueType the type of the values in the matrix
 */
template<class Matrix, class ValueType>
class MatrixBuilder
{
	public:
    /**
     * virtual destructor to provide inheritance
     */
		virtual ~MatrixBuilder() = default;
    /**
     * trait that provides the matrix type constructed by this builder
     */
		using matrix_type = Matrix;
    /**
     * trait that provides the value type stored in a matrix constructed by this builder
     */
		using value_type = ValueType;
    /**
     * Provide a hint to the implementation as to the number of rows, columns,
     * and nonzeros that will be provided via reserve.  Implementation MAY
     * ignore this call. The parser MAY call this method at any time during the
     * parsing process. Calling this function mutliple times results in
     * undefined behavior.
     *
     * \param[in] rows the number of rows to reserve or use
     * \param[in] columns the number of columns to reserve or use
     * \param[in] nonzeros the number of nonzeros in the matrix
     */
		virtual void reserve(size_t rows, size_t columns, size_t nonzeros)=0;

    /**
     * Sets a value in the matrix
     *
     * \param[in] row the row to set
     * \param[in] column the column to set
     * \param[in] value the value to set
     */
		virtual void set_entry(size_t const row, size_t const column, ValueType const& value)=0;

    /**
     * Constructs the matrix. Calling this method more than once on the same
     * object MAY result in undefined behavior
     *
     * \returns the constructed matrix
     */
		virtual Matrix build() const=0;
};

#endif /* end of include guard: MATRIXLOADER_BUILDER_H */
