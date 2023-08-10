#include "test-console.h"
#include "test-console-parameters_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameters_delete__frees_memory(void **state) {

  const f_number_unsigned_t size = 3;

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_console_parameter_t parameter = f_console_parameter_t_initialize;
  f_console_parameter_t parameters_array[1] = { parameter };

  parameters.array = parameters_array;
  parameters.used = 1;

  {
    const f_status_t status = f_string_dynamics_resize(size, &parameters.arguments);

    assert_int_equal(status, F_none);
    assert_int_not_equal(parameters.arguments.size, 0);
    assert_non_null(parameters.arguments.array);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_number_unsigned_t), (void **) &parameters.array[0].locations.array, &parameters.array[0].locations.used, &parameters.array[0].locations.size);

    assert_int_equal(status, F_none);
    assert_int_not_equal(parameters.array[0].locations.size, 0);
    assert_non_null(parameters.array[0].locations.array);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_number_unsigned_t), (void **) &parameters.array[0].locations_sub.array, &parameters.array[0].locations_sub.used, &parameters.array[0].locations_sub.size);

    assert_int_equal(status, F_none);
    assert_int_not_equal(parameters.array[0].locations_sub.size, 0);
    assert_non_null(parameters.array[0].locations_sub.array);
  }

  {
    const f_status_t status = f_console_parameters_delete(&parameters);

    assert_int_equal(status, F_none);
    assert_int_equal(parameters.arguments.size, 0);
    assert_int_equal(parameters.array[0].locations.size, 0);
    assert_int_equal(parameters.array[0].locations_sub.size, 0);
  }
}

void test__f_console_parameters_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_console_parameters_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
