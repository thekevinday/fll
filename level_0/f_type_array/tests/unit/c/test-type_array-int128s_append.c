#include "test-type_array.h"
#include "test-type_array-int128s_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int128s_append__parameter_checking(void **state) {

  const int128_t data = 0;

  {
    const f_status_t status = f_int128s_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_int128s_append__works(void **state) {

  const int128_t source = 3;
  f_int128s_t destination = f_int128s_t_initialize;

  {
    const f_status_t status = f_int128s_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0], source);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
