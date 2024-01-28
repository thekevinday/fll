#include "test-console.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameter_reset__parameter_checking(void **state) {

  {
    const f_status_t status = f_console_parameter_reset(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_console_parameter_reset__works(void **state) {

  const f_string_t argv[] = {
    "program",
    "-f",
    "first",
    "-st",
    "--second",
    "third",
    "other",
    "+F",
    "++fifth",
    "fifth",
    "--sixth",
    "sixth",
    "--seventh",
    "seventh",
    "7",
    "other",
    "free",
    "-4",
    "+fast",
    "-staff",
    "-mMxx",
    "mixed 1",
    "mixed 2, value 1",
    "mixed 2, value 2",
    0,
  };

  const f_string_static_t s_f = macro_f_string_static_t_initialize_1("f", 0, 1);
  const f_string_static_t s_s = macro_f_string_static_t_initialize_1("s", 0, 1);
  const f_string_static_t s_t = macro_f_string_static_t_initialize_1("t", 0, 1);
  const f_string_static_t s_F = macro_f_string_static_t_initialize_1("F", 0, 1);
  const f_string_static_t s_N = macro_f_string_static_t_initialize_1("N", 0, 1);
  const f_string_static_t s_m = macro_f_string_static_t_initialize_1("m", 0, 1);
  const f_string_static_t s_M = macro_f_string_static_t_initialize_1("M", 0, 1);
  const f_string_static_t s_x = macro_f_string_static_t_initialize_1("x", 0, 1);
  const f_string_static_t s_second = macro_f_string_static_t_initialize_1("second", 0, 6);
  const f_string_static_t s_third = macro_f_string_static_t_initialize_1("third", 0, 5);
  const f_string_static_t s_fifth = macro_f_string_static_t_initialize_1("fifth", 0, 5);
  const f_string_static_t s_sixth = macro_f_string_static_t_initialize_1("sixth", 0, 5);
  const f_string_static_t s_seventh = macro_f_string_static_t_initialize_1("seventh", 0, 7);
  const f_string_static_t s_not_found = macro_f_string_static_t_initialize_1("not_found", 0, 9);
  const f_string_static_t s_mixed_1 = macro_f_string_static_t_initialize_1("mixed_1", 0, 7);
  const f_string_static_t s_mixed_2 = macro_f_string_static_t_initialize_1("mixed_2", 0, 7);
  const f_string_static_t s_mixed_3 = macro_f_string_static_t_initialize_1("mixed_3", 0, 7);
  const f_string_static_t s_other = macro_f_string_static_t_initialize_1("other", 0, 5);

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(24, argv, 0);
  const uint8_t parameters_total = 12;

  f_console_parameter_t parameter[] = {
    macro_f_console_parameter_t_initialize_2(s_f, f_string_empty_s, f_string_empty_s, 1, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_s, s_second, f_string_empty_s, 1, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_t, s_third, f_string_empty_s, 1, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_F, f_string_empty_s, f_string_empty_s, 0, f_console_flag_inverse_e),
    macro_f_console_parameter_t_initialize_2(f_string_empty_s, s_fifth, f_string_empty_s, 1, f_console_flag_inverse_e),
    macro_f_console_parameter_t_initialize_2(f_string_empty_s, s_sixth, f_string_empty_s, 1, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(f_string_empty_s, s_seventh, f_string_empty_s, 2, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_N, s_not_found, f_string_empty_s, 0, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_m, s_mixed_1, f_string_empty_s, 1, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_M, s_mixed_2, f_string_empty_s, 2, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(s_x, s_mixed_3, f_string_empty_s, 0, f_console_flag_normal_e),
    macro_f_console_parameter_t_initialize_2(f_string_empty_s, f_string_empty_s, s_other, 0, f_console_flag_simple_e),
  };

  f_console_parameters_t parameters = macro_f_console_parameters_t_initialize_1(parameter, parameters_total, 0);

  {
    {
      f_state_t state = f_state_t_initialize;
      f_console_parameter_process(arguments, &parameters, &state, 0);

      assert_int_equal(state.status, F_okay);
    }

    parameter[0].flag |= f_console_flag_disable_e;

    {
      const f_status_t status = f_console_parameter_reset(&parameters);

      assert_int_equal(status, F_okay);
    }

    for (f_number_unsigned_t i = 0; i < parameters.arguments.size; ++i) {
      assert_int_equal(parameters.arguments.array[i].used, 0);
    } // for

    for (uint8_t i = 0; i < parameters_total; ++i) {

      assert_int_equal(parameter[i].flag & f_console_flag_disable_e, 0);
      assert_int_equal(parameter[i].result, f_console_result_none_e);
      assert_int_equal(parameter[i].locations.used, 0);
      assert_int_equal(parameter[i].locations_sub.used, 0);
      assert_int_equal(parameter[i].values.used, 0);
      assert_int_equal(parameter[i].location, 0);
      assert_int_equal(parameter[i].location_sub, 0);
    } // for

    assert_int_equal(parameters.remaining.used, 0);
  }

  f_console_parameters_delete(&parameters);
}

#ifdef __cplusplus
} // extern "C"
#endif
