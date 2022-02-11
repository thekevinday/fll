#include "test-console.h"
#include "test-console-parameters_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameters_delete__frees_memory(void **state) {

  const f_array_length_t size = 3;

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
    const f_status_t status = f_type_array_lengths_resize(3, &parameters.array[0].locations);

    assert_int_equal(status, F_none);
    assert_int_not_equal(parameters.array[0].locations.size, 0);
    assert_non_null(parameters.array[0].locations.array);
  }

  {
    const f_status_t status = f_type_array_lengths_resize(size, &parameters.array[0].locations_sub);

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

#ifndef _di_level_0_parameter_checking_
  void test__f_console_parameters_delete__parameter_checking(void **state) {

    {
      const f_status_t status = f_console_parameters_delete(0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

#ifdef __cplusplus
} // extern "C"
#endif
