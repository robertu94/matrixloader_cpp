#ifndef MATRIXLOADER_PARSER_H
#define MATRIXLOADER_PARSER_H
#include <iosfwd>
#include <memory>

/**
 * \file
 * \brief contains the definitions for creating new parsers
 */

/**
 * Responsible for parsing matrix files into a series of calls to the builder object
 *
 * \tparam MatrixBuilder the builder class to be used
 */
template <class MatrixBuilder>
class MatrixParser
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
		MatrixParser(std::unique_ptr<MatrixBuilder>&& builder): builder(std::move(builder)) {}

    /**
     * parses a input file
     */
		virtual typename MatrixBuilder::matrix_type load(std::istream& in)=0;
};

#endif /* end of include guard: MATRIXLOADER_PARSER_H */
