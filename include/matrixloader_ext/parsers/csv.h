#include "matrixloader_parser.h"

/**
 * \file
 * \brief parser for CSV
 */

/**
 * Parses CSV format
 *
 * \tparam MatrixBuilder the builder to construct a matrix with
 */
template <class MatrixBuilder>
class CsvParser: public MatrixParser<MatrixBuilder>
{
	public:
    /**
     * constructs a matrix parser object
     */
		CsvParser(std::unique_ptr<MatrixBuilder>&& builder): MatrixParser<MatrixBuilder>(std::move(builder)) {}

    /**
     * set the number of header_rows, defaults 0
     */
    void set_header_rows(unsigned int rows) { header_rows = rows; }


    /**
     * parses a input file
     */
		typename MatrixBuilder::matrix_type load(std::istream& in) override {
      size_t row = 0;
      size_t columns = 0;
      for(std::string line; std::getline(in, line); row++) {
        if(row < header_rows) continue;
        std::istringstream line_ss(std::move(line));
        size_t column = 0;
        for(std::string value; std::getline(line_ss, value,','); ++column) {
          this->builder->set_entry(row - header_rows, column, std::stold(value));
        }
        columns = column;
      }
      this->builder->reserve(row-header_rows, columns, (row-header_rows)*columns);
      return this->builder->build();
    }

  private:
    unsigned int header_rows = 0;

};

