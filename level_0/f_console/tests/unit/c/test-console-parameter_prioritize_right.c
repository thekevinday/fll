#include "test-console.h"
#include "test-console-parameter_prioritize_right.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameter_prioritize_right__fails(void **state) {

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_uint16s_t choices = f_uint16s_t_initialize;
  f_array_length_t decision = f_array_length_t_initialize;

  {
    uint16_t choices_array[1] = { 20 };
    choices.array = choices_array;
    choices.used = 1;

    f_console_parameter_t parameter = f_console_parameter_t_initialize;
    f_console_parameter_t parameters_array[1] = { parameter };
    parameters.array = parameters_array;
    parameters.used = 1;

    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, &decision);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  f_console_parameters_delete(&parameters);
}

void test__f_console_parameter_prioritize_right__parameter_checking(void **state) {

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_uint16s_t choices = f_uint16s_t_initialize;

  {
    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    uint16_t choices_array[1] = { f_array_length_t_initialize };
    choices.array = choices_array;

    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  f_console_parameters_delete(&parameters);
}

void test__f_console_parameter_prioritize_right__works(void **state) {

  f_console_parameters_t parameters = f_console_parameters_t_initialize;
  f_uint16s_t choices = f_uint16s_t_initialize;
  f_array_length_t decision = f_array_length_t_initialize;

  {
    uint16_t choices_array[1] = { 0 };
    choices.array = choices_array;

    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, &decision);

    assert_int_equal(status, F_data_not);
  }

  {
    uint16_t choices_array[1] = { 0 };
    choices.array = choices_array;
    choices.used = 1;

    f_console_parameter_t parameter = f_console_parameter_t_initialize;
    f_console_parameter_t parameters_array[1] = { parameter };
    parameters.array = parameters_array;
    parameters.used = 1;

    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, &decision);

    assert_int_equal(status, F_data_not);
  }

  {
    uint16_t choices_array[2] = { 0, 1 };
    choices.array = choices_array;
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

    const f_status_t status = f_console_parameter_prioritize_right(parameters, choices, &decision);

    assert_int_equal(status, F_none);
    assert_int_equal(decision, 0);
  }

  f_console_parameters_delete(&parameters);
}

#ifdef __cplusplus
} // extern "C"
#endif
