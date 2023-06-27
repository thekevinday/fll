#include "test-type_array.h"
#include "test-type_array-files_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_files_append__parameter_checking(void **state) {

  const f_file_t data = f_file_t_initialize;

  {
    const f_status_t status = f_files_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_files_append__works(void **state) {

  const f_file_t source = macro_f_file_t_initialize_id(3);
  f_files_t destination = f_files_t_initialize;

  {
    const f_status_t status = f_files_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].id, source.id);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
