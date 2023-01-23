#include "test-console.h"
#include "test-console-parameter_process.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_parameter_process__incomplete_arguments(void **state) {

  const f_string_t argv[] = {
    "program",
    "--second",
    0,
  };

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(2, argv, 0);

  f_console_parameter_t parameter[] = {
    macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
  };

  f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 9);

  {
    const f_status_t status = f_console_parameter_process(arguments, &parameters);

    assert_int_equal(status, F_complete_not);

    assert_int_equal(parameter[0].result, f_console_result_none_e);
    assert_int_equal(parameter[0].locations.used, 0);
    assert_int_equal(parameter[0].locations_sub.used, 0);
    assert_int_equal(parameter[0].values.used, 0);
    assert_int_equal(parameter[0].location, 0);
    assert_int_equal(parameter[0].location_sub, 0);

    assert_int_equal(parameter[1].result, f_console_result_found_e);
    assert_int_equal(parameter[1].locations.used, 1);
    assert_int_equal(parameter[1].locations_sub.used, 1);
    assert_int_equal(parameter[1].values.used, 0);
    assert_int_equal(parameter[1].location, 1);
    assert_int_equal(parameter[1].location_sub, 0);
    assert_int_equal(parameter[1].locations.array[0], 1);
    assert_int_equal(parameter[1].locations_sub.array[0], 0);

    assert_int_equal(parameter[2].result, f_console_result_none_e);
    assert_int_equal(parameter[2].locations.used, 0);
    assert_int_equal(parameter[2].locations_sub.used, 0);
    assert_int_equal(parameter[2].values.used, 0);
    assert_int_equal(parameter[2].location, 0);
    assert_int_equal(parameter[2].location_sub, 0);

    assert_int_equal(parameter[3].result, f_console_result_none_e);
    assert_int_equal(parameter[3].locations.used, 0);
    assert_int_equal(parameter[3].locations_sub.used, 0);
    assert_int_equal(parameter[3].values.used, 0);
    assert_int_equal(parameter[3].location, 0);
    assert_int_equal(parameter[3].location_sub, 0);

    assert_int_equal(parameter[4].result, f_console_result_none_e);
    assert_int_equal(parameter[4].locations.used, 0);
    assert_int_equal(parameter[4].locations_sub.used, 0);
    assert_int_equal(parameter[4].values.used, 0);
    assert_int_equal(parameter[4].location, 0);
    assert_int_equal(parameter[4].location_sub, 0);

    assert_int_equal(parameter[5].result, f_console_result_none_e);
    assert_int_equal(parameter[5].locations.used, 0);
    assert_int_equal(parameter[5].locations_sub.used, 0);
    assert_int_equal(parameter[5].values.used, 0);
    assert_int_equal(parameter[5].location, 0);
    assert_int_equal(parameter[5].location_sub, 0);

    assert_int_equal(parameter[6].result, f_console_result_none_e);
    assert_int_equal(parameter[6].locations.used, 0);
    assert_int_equal(parameter[6].locations_sub.used, 0);
    assert_int_equal(parameter[6].values.used, 0);
    assert_int_equal(parameter[6].location, 0);
    assert_int_equal(parameter[6].location_sub, 0);

    assert_int_equal(parameter[7].result, f_console_result_none_e);
    assert_int_equal(parameter[7].locations.used, 0);
    assert_int_equal(parameter[7].locations_sub.used, 0);
    assert_int_equal(parameter[7].values.used, 0);
    assert_int_equal(parameter[7].location, 0);
    assert_int_equal(parameter[7].location_sub, 0);

    assert_int_equal(parameter[8].result, f_console_result_none_e);
    assert_int_equal(parameter[8].locations.used, 0);
    assert_int_equal(parameter[8].locations_sub.used, 0);
    assert_int_equal(parameter[8].values.used, 0);
    assert_int_equal(parameter[8].location, 0);
    assert_int_equal(parameter[8].location_sub, 0);

    assert_int_equal(parameters.remaining.used, 0);
  }

  f_console_parameters_delete(&parameters);
}

void test__f_console_parameter_process__no_arguments_no_program(void **state) {

  const f_string_t argv[] = {
    0,
  };

  // Test both a valid and an invalid argc.
  for (uint8_t argc = 0; argc < 2; ++argc) {

    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, 0);

    f_console_parameter_t parameter[] = {
      macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
    };

    f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 9);

    {
      const f_status_t status = f_console_parameter_process(arguments, &parameters);

      assert_int_equal(status, F_data_not);

      assert_int_equal(parameter[0].result, f_console_result_none_e);
      assert_int_equal(parameter[0].locations.used, 0);
      assert_int_equal(parameter[0].values.used, 0);
      assert_int_equal(parameter[0].location, 0);
      assert_int_equal(parameter[0].location_sub, 0);

      assert_int_equal(parameter[1].result, f_console_result_none_e);
      assert_int_equal(parameter[1].locations.used, 0);
      assert_int_equal(parameter[1].values.used, 0);
      assert_int_equal(parameter[1].location, 0);
      assert_int_equal(parameter[1].location_sub, 0);

      assert_int_equal(parameter[2].result, f_console_result_none_e);
      assert_int_equal(parameter[2].locations.used, 0);
      assert_int_equal(parameter[2].values.used, 0);
      assert_int_equal(parameter[2].location, 0);
      assert_int_equal(parameter[2].location_sub, 0);

      assert_int_equal(parameter[3].result, f_console_result_none_e);
      assert_int_equal(parameter[3].locations.used, 0);
      assert_int_equal(parameter[3].values.used, 0);
      assert_int_equal(parameter[3].location, 0);
      assert_int_equal(parameter[3].location_sub, 0);

      assert_int_equal(parameter[4].result, f_console_result_none_e);
      assert_int_equal(parameter[4].locations.used, 0);
      assert_int_equal(parameter[4].values.used, 0);
      assert_int_equal(parameter[4].location, 0);
      assert_int_equal(parameter[4].location_sub, 0);

      assert_int_equal(parameter[5].result, f_console_result_none_e);
      assert_int_equal(parameter[5].locations.used, 0);
      assert_int_equal(parameter[5].values.used, 0);
      assert_int_equal(parameter[5].location, 0);
      assert_int_equal(parameter[5].location_sub, 0);

      assert_int_equal(parameter[6].result, f_console_result_none_e);
      assert_int_equal(parameter[6].locations.used, 0);
      assert_int_equal(parameter[6].values.used, 0);
      assert_int_equal(parameter[6].location, 0);
      assert_int_equal(parameter[6].location_sub, 0);

      assert_int_equal(parameter[7].result, f_console_result_none_e);
      assert_int_equal(parameter[7].locations.used, 0);
      assert_int_equal(parameter[7].values.used, 0);
      assert_int_equal(parameter[7].location, 0);
      assert_int_equal(parameter[7].location_sub, 0);

      assert_int_equal(parameter[8].result, f_console_result_none_e);
      assert_int_equal(parameter[8].locations.used, 0);
      assert_int_equal(parameter[8].values.used, 0);
      assert_int_equal(parameter[8].location, 0);
      assert_int_equal(parameter[8].location_sub, 0);

      assert_int_equal(parameters.remaining.used, 0);
    }

    f_console_parameters_delete(&parameters);
  } // for
}

void test__f_console_parameter_process__no_arguments(void **state) {

  const f_string_t argv[] = {
    "program",
    0,
  };

  // Test both valid and invalid argc.
  for (uint8_t argc = 0; argc < 2; ++argc) {

    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, 0);

    f_console_parameter_t parameter[] = {
      macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
    };

    f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 9);

    {
      const f_status_t status = f_console_parameter_process(arguments, &parameters);

      assert_int_equal(status, argc ? F_none : F_data_not);

      assert_int_equal(parameter[0].result, f_console_result_none_e);
      assert_int_equal(parameter[0].locations.used, 0);
      assert_int_equal(parameter[0].locations_sub.used, 0);
      assert_int_equal(parameter[0].values.used, 0);
      assert_int_equal(parameter[0].location, 0);
      assert_int_equal(parameter[0].location_sub, 0);

      assert_int_equal(parameter[1].result, f_console_result_none_e);
      assert_int_equal(parameter[1].locations.used, 0);
      assert_int_equal(parameter[1].locations_sub.used, 0);
      assert_int_equal(parameter[1].values.used, 0);
      assert_int_equal(parameter[1].location, 0);
      assert_int_equal(parameter[1].location_sub, 0);

      assert_int_equal(parameter[2].result, f_console_result_none_e);
      assert_int_equal(parameter[2].locations.used, 0);
      assert_int_equal(parameter[2].locations_sub.used, 0);
      assert_int_equal(parameter[2].values.used, 0);
      assert_int_equal(parameter[2].location, 0);
      assert_int_equal(parameter[2].location_sub, 0);

      assert_int_equal(parameter[3].result, f_console_result_none_e);
      assert_int_equal(parameter[3].locations.used, 0);
      assert_int_equal(parameter[3].locations_sub.used, 0);
      assert_int_equal(parameter[3].values.used, 0);
      assert_int_equal(parameter[3].location, 0);
      assert_int_equal(parameter[3].location_sub, 0);

      assert_int_equal(parameter[4].result, f_console_result_none_e);
      assert_int_equal(parameter[4].locations.used, 0);
      assert_int_equal(parameter[4].locations_sub.used, 0);
      assert_int_equal(parameter[4].values.used, 0);
      assert_int_equal(parameter[4].location, 0);
      assert_int_equal(parameter[4].location_sub, 0);

      assert_int_equal(parameter[5].result, f_console_result_none_e);
      assert_int_equal(parameter[5].locations.used, 0);
      assert_int_equal(parameter[5].locations_sub.used, 0);
      assert_int_equal(parameter[5].values.used, 0);
      assert_int_equal(parameter[5].location, 0);
      assert_int_equal(parameter[5].location_sub, 0);

      assert_int_equal(parameter[6].result, f_console_result_none_e);
      assert_int_equal(parameter[6].locations.used, 0);
      assert_int_equal(parameter[6].locations_sub.used, 0);
      assert_int_equal(parameter[6].values.used, 0);
      assert_int_equal(parameter[6].location, 0);
      assert_int_equal(parameter[6].location_sub, 0);

      assert_int_equal(parameter[7].result, f_console_result_none_e);
      assert_int_equal(parameter[7].locations.used, 0);
      assert_int_equal(parameter[7].locations_sub.used, 0);
      assert_int_equal(parameter[7].values.used, 0);
      assert_int_equal(parameter[7].location, 0);
      assert_int_equal(parameter[7].location_sub, 0);

      assert_int_equal(parameter[8].result, f_console_result_none_e);
      assert_int_equal(parameter[8].locations.used, 0);
      assert_int_equal(parameter[8].locations_sub.used, 0);
      assert_int_equal(parameter[8].values.used, 0);
      assert_int_equal(parameter[8].location, 0);
      assert_int_equal(parameter[8].location_sub, 0);

      assert_int_equal(parameters.remaining.used, 0);
    }

    f_console_parameters_delete(&parameters);
  } // for
}

void test__f_console_parameter_process__null_arguments(void **state) {

  const f_string_t *argv = 0;

  // Test both a valid and an invalid argc.
  for (uint8_t argc = 0; argc < 2; ++argc) {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, 0);

    f_console_parameter_t parameter[] = {
      macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
      macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
      macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
    };

    f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 9);

    {
      const f_status_t status = f_console_parameter_process(arguments, &parameters);

      assert_int_equal(status, F_data_not);

      assert_int_equal(parameter[0].result, f_console_result_none_e);
      assert_int_equal(parameter[0].locations.used, 0);
      assert_int_equal(parameter[0].locations_sub.used, 0);
      assert_int_equal(parameter[0].values.used, 0);
      assert_int_equal(parameter[0].location, 0);
      assert_int_equal(parameter[0].location_sub, 0);

      assert_int_equal(parameter[1].result, f_console_result_none_e);
      assert_int_equal(parameter[1].locations.used, 0);
      assert_int_equal(parameter[1].locations_sub.used, 0);
      assert_int_equal(parameter[1].values.used, 0);
      assert_int_equal(parameter[1].location, 0);
      assert_int_equal(parameter[1].location_sub, 0);

      assert_int_equal(parameter[2].result, f_console_result_none_e);
      assert_int_equal(parameter[2].locations.used, 0);
      assert_int_equal(parameter[2].locations_sub.used, 0);
      assert_int_equal(parameter[2].values.used, 0);
      assert_int_equal(parameter[2].location, 0);
      assert_int_equal(parameter[2].location_sub, 0);

      assert_int_equal(parameter[3].result, f_console_result_none_e);
      assert_int_equal(parameter[3].locations.used, 0);
      assert_int_equal(parameter[3].locations_sub.used, 0);
      assert_int_equal(parameter[3].values.used, 0);
      assert_int_equal(parameter[3].location, 0);
      assert_int_equal(parameter[3].location_sub, 0);

      assert_int_equal(parameter[4].result, f_console_result_none_e);
      assert_int_equal(parameter[4].locations.used, 0);
      assert_int_equal(parameter[4].locations_sub.used, 0);
      assert_int_equal(parameter[4].values.used, 0);
      assert_int_equal(parameter[4].location, 0);
      assert_int_equal(parameter[4].location_sub, 0);

      assert_int_equal(parameter[5].result, f_console_result_none_e);
      assert_int_equal(parameter[5].locations.used, 0);
      assert_int_equal(parameter[5].locations_sub.used, 0);
      assert_int_equal(parameter[5].values.used, 0);
      assert_int_equal(parameter[5].location, 0);
      assert_int_equal(parameter[5].location_sub, 0);

      assert_int_equal(parameter[6].result, f_console_result_none_e);
      assert_int_equal(parameter[6].locations.used, 0);
      assert_int_equal(parameter[6].locations_sub.used, 0);
      assert_int_equal(parameter[6].values.used, 0);
      assert_int_equal(parameter[6].location, 0);
      assert_int_equal(parameter[6].location_sub, 0);

      assert_int_equal(parameter[7].result, f_console_result_none_e);
      assert_int_equal(parameter[7].locations.used, 0);
      assert_int_equal(parameter[7].locations_sub.used, 0);
      assert_int_equal(parameter[7].values.used, 0);
      assert_int_equal(parameter[7].location, 0);
      assert_int_equal(parameter[7].location_sub, 0);

      assert_int_equal(parameter[8].result, f_console_result_none_e);
      assert_int_equal(parameter[8].locations.used, 0);
      assert_int_equal(parameter[8].locations_sub.used, 0);
      assert_int_equal(parameter[8].values.used, 0);
      assert_int_equal(parameter[8].location, 0);
      assert_int_equal(parameter[8].location_sub, 0);

      assert_int_equal(parameters.remaining.used, 0);
    }

    f_console_parameters_delete(&parameters);
  } // for
}

void test__f_console_parameter_process__only_remaining(void **state) {

  const f_string_t argv[] = {
    "program",
    "anything",
    "--",
    "can go here",
    "+h",
    "--help",
    "../`~!@#$%^&*()_-+={[}]:;\"'<,>./?",
    "-soo",
    "-oso",
    "-oos",
    "+soo",
    "+oso",
    "+oos",
    "--seconds",
    "--seconds",
    "--seconds",
    "++seconds",
    "++seconds",
    "++seconds",
    0,
  };

  const int total = 19;

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(total, argv, 0);

  f_console_parameter_t parameter[] = {
    macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
  };

  f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 9);

  {
    const f_status_t status = f_console_parameter_process(arguments, &parameters);

    assert_int_equal(status, F_none);

    assert_int_equal(parameter[0].result, f_console_result_none_e);
    assert_int_equal(parameter[0].locations.used, 0);
    assert_int_equal(parameter[0].values.used, 0);
    assert_int_equal(parameter[0].location, 0);
    assert_int_equal(parameter[0].location_sub, 0);

    assert_int_equal(parameter[1].result, f_console_result_none_e);
    assert_int_equal(parameter[1].locations.used, 0);
    assert_int_equal(parameter[1].values.used, 0);
    assert_int_equal(parameter[1].location, 0);
    assert_int_equal(parameter[1].location_sub, 0);

    assert_int_equal(parameter[2].result, f_console_result_none_e);
    assert_int_equal(parameter[2].locations.used, 0);
    assert_int_equal(parameter[2].values.used, 0);
    assert_int_equal(parameter[2].location, 0);
    assert_int_equal(parameter[2].location_sub, 0);

    assert_int_equal(parameter[3].result, f_console_result_none_e);
    assert_int_equal(parameter[3].locations.used, 0);
    assert_int_equal(parameter[3].values.used, 0);
    assert_int_equal(parameter[3].location, 0);
    assert_int_equal(parameter[3].location_sub, 0);

    assert_int_equal(parameter[4].result, f_console_result_none_e);
    assert_int_equal(parameter[4].locations.used, 0);
    assert_int_equal(parameter[4].values.used, 0);
    assert_int_equal(parameter[4].location, 0);
    assert_int_equal(parameter[4].location_sub, 0);

    assert_int_equal(parameter[5].result, f_console_result_none_e);
    assert_int_equal(parameter[5].locations.used, 0);
    assert_int_equal(parameter[5].values.used, 0);
    assert_int_equal(parameter[5].location, 0);
    assert_int_equal(parameter[5].location_sub, 0);

    assert_int_equal(parameter[6].result, f_console_result_none_e);
    assert_int_equal(parameter[6].locations.used, 0);
    assert_int_equal(parameter[6].values.used, 0);
    assert_int_equal(parameter[6].location, 0);
    assert_int_equal(parameter[6].location_sub, 0);

    assert_int_equal(parameter[7].result, f_console_result_none_e);
    assert_int_equal(parameter[7].locations.used, 0);
    assert_int_equal(parameter[7].values.used, 0);
    assert_int_equal(parameter[7].location, 0);
    assert_int_equal(parameter[7].location_sub, 0);

    assert_int_equal(parameter[8].result, f_console_result_none_e);
    assert_int_equal(parameter[8].locations.used, 0);
    assert_int_equal(parameter[8].values.used, 0);
    assert_int_equal(parameter[8].location, 0);
    assert_int_equal(parameter[8].location_sub, 0);

    assert_int_equal(parameters.remaining.used, total - 1);
    assert_string_equal(argv[parameters.remaining.array[0]], argv[1]);
    assert_string_equal(argv[parameters.remaining.array[1]], argv[2]);
    assert_string_equal(argv[parameters.remaining.array[2]], argv[3]);
    assert_string_equal(argv[parameters.remaining.array[3]], argv[4]);
    assert_string_equal(argv[parameters.remaining.array[4]], argv[5]);
    assert_string_equal(argv[parameters.remaining.array[5]], argv[6]);
    assert_string_equal(argv[parameters.remaining.array[6]], argv[7]);
    assert_string_equal(argv[parameters.remaining.array[7]], argv[8]);
    assert_string_equal(argv[parameters.remaining.array[8]], argv[9]);
    assert_string_equal(argv[parameters.remaining.array[9]], argv[10]);
    assert_string_equal(argv[parameters.remaining.array[10]], argv[11]);
    assert_string_equal(argv[parameters.remaining.array[11]], argv[12]);
    assert_string_equal(argv[parameters.remaining.array[12]], argv[13]);
    assert_string_equal(argv[parameters.remaining.array[13]], argv[14]);
    assert_string_equal(argv[parameters.remaining.array[14]], argv[15]);
    assert_string_equal(argv[parameters.remaining.array[15]], argv[16]);
    assert_string_equal(argv[parameters.remaining.array[16]], argv[17]);
    assert_string_equal(argv[parameters.remaining.array[17]], argv[18]);
  }

  f_console_parameters_delete(&parameters);
}

void test__f_console_parameter_process__parameter_checking(void **state) {

  const f_console_arguments_t arguments = f_console_arguments_t_initialize;

  {
    const f_status_t status = f_console_parameter_process(arguments, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_console_parameter_process__works(void **state) {

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

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(24, argv, 0);

  f_console_parameter_t parameter[] = {
    macro_f_console_parameter_t_initialize("f", 0, 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("s", "second", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("t", "third", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("F", 0, 0, 0, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "fifth", 0, 1, f_console_type_inverse_e),
    macro_f_console_parameter_t_initialize(0, "sixth", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, "seventh", 0, 2, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("N", "not_found", 0, 0, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("m", "mixed_1", 0, 1, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("M", "mixed_2", 0, 2, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize("x", "mixed_3", 0, 0, f_console_type_normal_e),
    macro_f_console_parameter_t_initialize(0, 0, "other", 0, f_console_type_other_e),
  };

  f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(parameter, 12);

  {
    const f_status_t status = f_console_parameter_process(arguments, &parameters);

    assert_int_equal(status, F_none);

    assert_int_equal(parameter[0].result, f_console_result_additional_e);
    assert_int_equal(parameter[0].locations.used, 1);
    assert_int_equal(parameter[0].locations_sub.used, 1);
    assert_int_equal(parameter[0].values.used, 1);
    assert_int_equal(parameter[0].location, 1);
    assert_int_equal(parameter[0].location_sub, 1);
    assert_int_equal(parameter[0].locations.array[0], 1);
    assert_int_equal(parameter[0].locations_sub.array[0], 1);
    assert_string_equal(argv[parameter[0].values.array[0]], argv[2]);

    assert_int_equal(parameter[1].result, f_console_result_additional_e);
    assert_int_equal(parameter[1].locations.used, 1);
    assert_int_equal(parameter[1].locations_sub.used, 1);
    assert_int_equal(parameter[1].values.used, 1);
    assert_int_equal(parameter[1].location, 3);
    assert_int_equal(parameter[1].location_sub, 1);
    assert_int_equal(parameter[1].locations.array[0], 3);
    assert_int_equal(parameter[1].locations_sub.array[0], 1);
    assert_string_equal(argv[parameter[1].values.array[0]], argv[4]);

    assert_int_equal(parameter[2].result, f_console_result_additional_e);
    assert_int_equal(parameter[2].locations.used, 1);
    assert_int_equal(parameter[2].locations_sub.used, 1);
    assert_int_equal(parameter[2].values.used, 1);
    assert_int_equal(parameter[2].location, 3);
    assert_int_equal(parameter[2].location_sub, 2);
    assert_int_equal(parameter[2].locations.array[0], 3);
    assert_int_equal(parameter[2].locations_sub.array[0], 2);
    assert_string_equal(argv[parameter[2].values.array[0]], argv[5]);

    assert_int_equal(parameter[3].result, f_console_result_found_e);
    assert_int_equal(parameter[3].locations.used, 1);
    assert_int_equal(parameter[3].locations_sub.used, 1);
    assert_int_equal(parameter[3].values.used, 0);
    assert_int_equal(parameter[3].location, 7);
    assert_int_equal(parameter[3].location_sub, 1);
    assert_int_equal(parameter[3].locations.array[0], 7);
    assert_int_equal(parameter[3].locations_sub.array[0], 1);

    assert_int_equal(parameter[4].result, f_console_result_additional_e);
    assert_int_equal(parameter[4].locations.used, 1);
    assert_int_equal(parameter[4].locations_sub.used, 1);
    assert_int_equal(parameter[4].values.used, 1);
    assert_int_equal(parameter[4].location, 8);
    assert_int_equal(parameter[4].location_sub, 0);
    assert_int_equal(parameter[4].locations.array[0], 8);
    assert_int_equal(parameter[4].locations_sub.array[0], 0);
    assert_string_equal(argv[parameter[4].values.array[0]], argv[9]);

    assert_int_equal(parameter[5].result, f_console_result_additional_e);
    assert_int_equal(parameter[5].locations.used, 1);
    assert_int_equal(parameter[5].locations_sub.used, 1);
    assert_int_equal(parameter[5].values.used, 1);
    assert_int_equal(parameter[5].location, 10);
    assert_int_equal(parameter[5].location_sub, 0);
    assert_int_equal(parameter[5].locations.array[0], 10);
    assert_int_equal(parameter[5].locations_sub.array[0], 0);
    assert_string_equal(argv[parameter[5].values.array[0]], argv[11]);

    assert_int_equal(parameter[6].result, f_console_result_additional_e);
    assert_int_equal(parameter[6].locations.used, 1);
    assert_int_equal(parameter[6].locations_sub.used, 1);
    assert_int_equal(parameter[6].values.used, 2);
    assert_int_equal(parameter[6].location, 12);
    assert_int_equal(parameter[6].location_sub, 0);
    assert_int_equal(parameter[6].locations.array[0], 12);
    assert_int_equal(parameter[6].locations_sub.array[0], 0);
    assert_string_equal(argv[parameter[6].values.array[0]], argv[13]);
    assert_string_equal(argv[parameter[6].values.array[1]], argv[14]);

    assert_int_equal(parameter[7].result, f_console_result_none_e);
    assert_int_equal(parameter[7].locations.used, 0);
    assert_int_equal(parameter[7].locations_sub.used, 0);
    assert_int_equal(parameter[7].values.used, 0);
    assert_int_equal(parameter[7].location, 0);
    assert_int_equal(parameter[7].location_sub, 0);

    assert_int_equal(parameter[8].result, f_console_result_additional_e);
    assert_int_equal(parameter[8].locations.used, 1);
    assert_int_equal(parameter[8].locations_sub.used, 1);
    assert_int_equal(parameter[8].values.used, 1);
    assert_int_equal(parameter[8].location, 20);
    assert_int_equal(parameter[8].location_sub, 1);
    assert_int_equal(parameter[8].locations.array[0], 20);
    assert_int_equal(parameter[8].locations_sub.array[0], 1);
    assert_string_equal(argv[parameter[8].values.array[0]], argv[21]);

    assert_int_equal(parameter[9].result, f_console_result_additional_e);
    assert_int_equal(parameter[9].locations.used, 1);
    assert_int_equal(parameter[9].locations_sub.used, 1);
    assert_int_equal(parameter[9].values.used, 2);
    assert_int_equal(parameter[9].location, 20);
    assert_int_equal(parameter[9].location_sub, 2);
    assert_int_equal(parameter[9].locations.array[0], 20);
    assert_int_equal(parameter[9].locations_sub.array[0], 2);
    assert_string_equal(argv[parameter[9].values.array[0]], argv[22]);
    assert_string_equal(argv[parameter[9].values.array[1]], argv[23]);

    assert_int_equal(parameter[10].result, f_console_result_found_e);
    assert_int_equal(parameter[10].locations.used, 1);
    assert_int_equal(parameter[10].locations_sub.used, 2);
    assert_int_equal(parameter[10].values.used, 0);
    assert_int_equal(parameter[10].location, 20);
    assert_int_equal(parameter[10].location_sub, 4);
    assert_int_equal(parameter[10].locations.array[0], 20);
    assert_int_equal(parameter[10].locations_sub.array[0], 3);
    assert_int_equal(parameter[10].locations_sub.array[1], 4);

    assert_int_equal(parameter[11].result, f_console_result_found_e);
    assert_int_equal(parameter[11].locations.used, 2);
    assert_int_equal(parameter[11].locations_sub.used, 2);
    assert_int_equal(parameter[11].values.used, 0);
    assert_int_equal(parameter[11].location, 15);
    assert_int_equal(parameter[11].location_sub, 0);
    assert_int_equal(parameter[11].locations.array[0], 6);
    assert_int_equal(parameter[11].locations.array[1], 15);
    assert_int_equal(parameter[11].locations_sub.array[0], 0);

    assert_int_equal(parameters.remaining.used, 4);
    assert_string_equal(argv[parameters.remaining.array[0]], argv[16]);
    assert_string_equal(argv[parameters.remaining.array[1]], argv[17]);
    assert_string_equal(argv[parameters.remaining.array[2]], argv[18]);
    assert_string_equal(argv[parameters.remaining.array[3]], argv[19]);
  }

  f_console_parameters_delete(&parameters);
}

#ifdef __cplusplus
} // extern "C"
#endif
