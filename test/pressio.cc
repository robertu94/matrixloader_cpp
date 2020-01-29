#include <matrixloader_ext/builders/pressio.h>
#include <matrixloader_ext/adapters/pressio.h>
#include <gtest/gtest.h>

TEST(Pressio, convert) {
  auto data = pressio_data::owning(pressio_double_dtype, {3, 4});
  auto ptr = static_cast<double*>(data.data());
  //zero-initialize memory
  for (int i = 0; i < data.num_elements(); ++i) {
    ptr[i] = 0.0;
  }
  ptr[0] = 4.0;
  ptr[4] = 5.0;

  auto builder = std::make_unique<PressioMatrixBuilder</*to_type*/float>>();
  PressioMatrixAdapter</*from type*/double, decltype(builder)::element_type> adapter(std::move(builder));
  auto converted = adapter.convert(data);

  auto converted_ptr = static_cast</*to_type*/float*>(converted.data());
  EXPECT_EQ(converted.dtype(), pressio_float_dtype);
  EXPECT_EQ(converted.get_dimension(0), 3);
  EXPECT_EQ(converted.get_dimension(1), 4);
  for (int i = 0; i < data.num_elements(); ++i) {
    EXPECT_EQ(converted_ptr[i], ptr[i]);
  }

}

