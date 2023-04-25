#include "test-console.h"
#include "test-console-environment_process.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_environment_process__data_not(void **state) {

  const f_string_t *argv = 0;
  const f_string_t *envp = 0;

  // Test both a valid and an invalid argc.
  for (uint8_t argc = 0; argc < 2; ++argc) {

    f_string_maps_t maps = f_string_maps_t_initialize;

    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

    {
      const f_status_t status = f_console_environment_process(arguments, &maps);

      assert_int_equal(status, F_data_not);
    }

    f_string_maps_resize(0, &maps);
  } // for
}

void test__f_console_environment_process__parameter_checking(void **state) {

  const f_console_arguments_t arguments = f_console_arguments_t_initialize;

  {
    const f_status_t status = f_console_environment_process(arguments, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_console_environment_process__works(void **state) {

  const uint8_t argc = 0;
  const f_string_t *argv = 0;
  const f_string_t envp[] = {
    "a=b",
    "c_d=e f g",
    "H=i=i=i",
    "j_j=k-ake!",
    "l012=",
    0,
  };

  const f_string_t names[] = {
    "a",
    "c_d",
    "H",
    "j_j",
    "l012",
    0,
  };

  const f_string_t values[] = {
    "b",
    "e f g",
    "i=i=i",
    "k-ake!",
    "",
    0,
  };

  f_string_maps_t maps = f_string_maps_t_initialize;

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

  {
    const f_status_t status = f_console_environment_process(arguments, &maps);

    assert_int_equal(status, F_none);
    assert_int_equal(maps.used, 5);
    assert_int_equal(maps.array[0].name.used, 1);
    assert_int_equal(maps.array[0].value.used, 1);
    assert_int_equal(maps.array[1].name.used, 3);
    assert_int_equal(maps.array[1].value.used, 5);
    assert_int_equal(maps.array[2].name.used, 1);
    assert_int_equal(maps.array[2].value.used, 5);
    assert_int_equal(maps.array[3].name.used, 3);
    assert_int_equal(maps.array[3].value.used, 6);
    assert_int_equal(maps.array[4].name.used, 4);
    assert_int_equal(maps.array[4].value.used, 0);

    // Construct NULL terminated strings to perform validation.
    for (uint8_t i = 0; i < 5; ++i) {

      {
        char buffer[maps.array[i].name.used + 1];

        memcpy(buffer, maps.array[i].name.string, sizeof(f_char_t) * maps.array[i].name.used);
        buffer[maps.array[i].name.used] = 0;

        assert_string_equal(buffer, names[i]);
      }

      {
        char buffer[maps.array[i].value.used + 1];

        memcpy(buffer, maps.array[i].value.string, sizeof(f_char_t) * maps.array[i].value.used);
        buffer[maps.array[i].value.used] = 0;

        assert_string_equal(buffer, values[i]);
      }
    } // for
  }

  f_string_maps_resize(0, &maps);
}

#ifdef __cplusplus
} // extern "C"
#endif
