# LibMatrixLoader

LibMatrixLoader provides a collection of tools to read in matrix files from a variety of input file formats to formats used by different tensor libraries

## Using LibMatrixLoader

Here is a minimal example with error handling of how to use LibMatrixLoader.

```cpp
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
```

## Getting Started

After skimming the example, LibMatrixLoader has a few major types that you will need to use:

Type                     | Use 
-------------------------|----------------------------------------------------------------------
`MatrixAdapter`          | Converts between various matrix types using the generic builder interface
`MatrixBuilder`          | Builds various matrix input files using a standard interface
`MatrixParser`           | Parses various matrix input files to the generic builder interface

## Dependencies

+ `cmake` version `3.13` or later
+ either:
  + `gcc-8.3.0` or later
  + `clang-9.0.0` or later

LibMatrixLoader optionally also depends on the following optional dependencies:

+ LibPressio version 0.31.1 or later to provide LibPressio plugins
+ Armadillo version 6.3 or later to provide Armadillo plugins
+ Doxygen to provide create the documentation


## Building and Installing LibMatrixLoader

LibMatrixLoader uses CMake to configure build options.  See CMake documentation to see how to configure options

+ `CMAKE_INSTALL_PREFIX` - install the library to a local directory prefix
+ `BUILD_DOCS` - build the project documentation
+ `BUILD_TESTING` - build the test cases

```bash
BUILD_DIR=build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake ..
make
make test
make install
```

To build the documentation:


```bash
BUILD_DIR=build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake .. -DBUILD_DOCS=ON
make docs
# the html docs can be found in $BUILD_DIR/html/index.html
# the man pages can be found in $BUILD_DIR/man/
```


## Stability

As of version 1.0.0, LibMatrixLoader will follow the following API stability guidelines:

+ The functions defined in files in `./include` are to considered stable
+ The functions defined in files in subdirectories of `./include` are considered unstable

Stable means:

+ New APIs may be introduced with the increase of the minor version number.
+ APIs may gain additional overloads for C++ compatible interfaces with an increase in the minor version number.
+ An API may change the number or type of parameters with an increase in the major version number.
+ An API may be removed with the change of the major version number

Unstable means:

+ The API may change for any reason with the increase of the minor version number

Additionally, the performance of functions, memory usage patterns may change for both stable and unstable code with the increase of the patch version.


## Bug Reports

Please files bugs to the Github Issues page on the robertu94 github repository.

Please read this post on [how to file a good bug report](https://codingnest.com/how-to-file-a-good-bug-report/).  After reading this post, please provide the following information specific to LibMatrixLoader:

+ Your OS version and distribution information, usually this can be found in `/etc/os-release`
+ the output of `cmake -L $BUILD_DIR`
+ the version of each of LibMatrixLoader's dependencies listed in the README that you have installed. Where possible, please provide the commit hashes.


