#include <fstream>
#include <libmatrixloader.h>
#include <matrixloader_ext/builders/pressio.h>
#include <matrixloader_ext/builders/armadillo.h>
#include <matrixloader_ext/adapters/armadillo.h>
#include <matrixloader_ext/parsers/csv.h>

int main(int argc, char *argv[])
{

  //we want to build a dense armadillo matrix (arma::Mat<double>)
  auto builder = std::make_unique<ArmadilloDenseMatrixBuilder<double>>();

  //we want to load from a csv file with 1 header row
  CsvParser<decltype(builder)::element_type> parser(std::move(builder));
  parser.set_header_rows(1);

  //loading here from a string, but std::ifstream works too!
  std::string csv_with_header = R"(a,b,c
1,2,3
1.5,2.5,3.5
1.9,2.9,3.9)";
  std::istringstream csv_file(csv_with_header);

  //load the matrix
  auto matrix = parser.load(csv_file);

  //we can then convert it to a pressio_data structure
  auto pressio_builder = std::make_unique<PressioMatrixBuilder<double>>();
  ArmadilloDenseMatrixAdapter<double, PressioMatrixBuilder<double>> adapter(std::move(pressio_builder));
  auto converted = adapter.convert(matrix);
  return 0;
}
