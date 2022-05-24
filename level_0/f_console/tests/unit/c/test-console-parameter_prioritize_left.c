#include "test-console.h"
#include "test-console-parameter_prioritize_left.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameter_prioritize_left__fails(void **state) {

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_console_parameter_ids_t choices = f_console_parameter_ids_t_initialize;
  f_console_parameter_id_t decision = f_console_parameter_id_t_initialize;

  {
    f_console_parameter_id_t ids_array[1] = { 20 };
    choices.id = ids_array;
    choices.used = 1;

    f_console_parameter_t parameter = f_console_parameter_t_initialize;
    f_console_parameter_t parameters_array[1] = { parameter };
    parameters.array = parameters_array;
    parameters.used = 1;

    const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, &decision);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  f_console_parameters_delete(&parameters);
}

#ifndef _di_level_0_parameter_checking_
  void test__f_console_parameter_prioritize_left__parameter_checking(void **state) {

    f_console_parameters_t parameters = f_console_parameters_t_initialize;
    f_console_parameter_ids_t choices = f_console_parameter_ids_t_initialize;

    {
      const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }

    {
      f_console_parameter_id_t ids_array[1] = { f_console_parameter_id_t_initialize };
      choices.id = ids_array;

      const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }

    f_console_parameters_delete(&parameters);
  }
#endif // _di_level_0_parameter_checking_

void test__f_console_parameter_prioritize_left__works(void **state) {

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_console_parameter_ids_t choices = f_console_parameter_ids_t_initialize;
  f_console_parameter_id_t decision = f_console_parameter_id_t_initialize;

  {
    f_console_parameter_id_t ids_array[1] = { 0 };
    choices.id = ids_array;

    const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, &decision);

    assert_int_equal(status, F_data_not);
  }

  {
    f_console_parameter_id_t ids_array[1] = { 0 };
    choices.id = ids_array;
    choices.used = 1;

    f_console_parameter_t parameter = f_console_parameter_t_initialize;
    f_console_parameter_t parameters_array[1] = { parameter };
    parameters.array = parameters_array;
    parameters.used = 1;

    const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, &decision);

    assert_int_equal(status, F_data_not);
  }

  {
    f_console_parameter_id_t ids_array[2] = { 0, 1 };
    choices.id = ids_array;
    choices.used = 2;

    f_console_parameter_t parameter_1 = f_console_parameter_t_initialize;
    f_console_parameter_t parameter_2 = f_console_parameter_t_initialize;

    parameter_1.result = f_console_result_found_e;
    parameter_1.location = 5;
    parameter_1.location_sub = 6;
    parameter_2.result = f_console_result_found_e;
    parameter_2.location = 3;
    parameter_2.location_sub = 4;

    f_console_parameter_t parameters_array[2] = { parameter_1, parameter_2 };
    parameters.array = parameters_array;
    parameters.used = 2;

    const f_status_t status = f_console_parameter_prioritize_left(parameters, choices, &decision);

    assert_int_equal(status, F_none);
    assert_int_equal(decision, 1);
  }

  f_console_parameters_delete(&parameters);
}

#ifdef __cplusplus
} // extern "C"
#endif
