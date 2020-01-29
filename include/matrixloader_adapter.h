#ifndef MATRIXLOADER_ADAPTER_H
#define MATRIXLOADER_ADAPTER_H
#include <memory>

/**
 * \file
 * \brief base class for adapters that convert from one matrix type to another
 */

/**
 * constructs one matrix type from another using the builder interface
 *
 * \tparam MatrixType the type of the matrix convert from (input)
 * \tparam MatrixBuilder  the type of the matrix builder factory
 */
template <class MatrixType, class MatrixBuilder>
class MatrixAdapter
{
	protected:
    /**
     * pointer to the builder used by the parser to construct the matrix
     */
		std::unique_ptr<MatrixBuilder> builder;
	public:
    /**
     * constructs a matrix parser object
     */
		MatrixAdapter(std::unique_ptr<MatrixBuilder>&& builder): builder(std::move(builder)) {}

    /**
     * converts a matrix of this type to builder type
     */
		virtual typename MatrixBuilder::matrix_type convert(MatrixType const& matrix)=0;
};

#endif /* end of include guard: MATRIXLOADER_ADAPTER_H */
