#include "test-execute.h"
#include "test-execute-status_to_status.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_execute_status_to_status__fails(void **state) {

  for (uint8_t i = 0; i < 0xff; ++i) {

    // Skip past all valid execute codes.
    if (i == F_execute_none) continue;
    if (i == F_execute_access) continue;
    if (i == F_execute_bad) continue;
    if (i == F_execute_buffer) continue;
    if (i == F_execute_busy) continue;
    if (i == F_execute_capability) continue;
    if (i == F_execute_control_group) continue;
    if (i == F_execute_child) continue;
    if (i == F_execute_directory_not) continue;
    if (i == F_execute_failure) continue;
    if (i == F_execute_file_found_not) continue;
    if (i == F_execute_file_type_directory) continue;
    if (i == F_execute_fork_not) continue;
    if (i == F_execute_format_not) continue;
    if (i == F_execute_group) continue;
    if (i == F_execute_input_output) continue;
    if (i == F_execute_limit) continue;
    if (i == F_execute_loop) continue;
    if (i == F_execute_memory_not) continue;
    if (i == F_execute_name_not) continue;
    if (i == F_execute_nice) continue;
    if (i == F_execute_parameter) continue;
    if (i == F_execute_pipe) continue;
    if (i == F_execute_processor) continue;
    if (i == F_execute_prohibited) continue;
    if (i == F_execute_resource_not) continue;
    if (i == F_execute_schedule) continue;
    if (i == F_execute_terminal) continue;
    if (i == F_execute_terminal_known_not) continue;
    if (i == F_execute_terminal_not) continue;
    if (i == F_execute_terminal_prohibited) continue;
    if (i == F_execute_terminal_valid_not) continue;
    if (i == F_execute_too_large) continue;
    if (i == F_execute_user) continue;
    if (i == F_execute_valid_not) continue;

    const f_status_t status = f_execute_status_to_status(i);

    assert_int_equal(status, F_status_set_error(F_known_not));
  } // for
}

void test__f_execute_status_to_status__works(void **state) {

  const uint8_t status_executes[] = {
    F_execute_none,
    F_execute_access,
    F_execute_bad,
    F_execute_buffer,
    F_execute_busy,
    F_execute_capability,
    F_execute_control_group,
    F_execute_child,
    F_execute_directory_not,
    F_execute_failure,
    F_execute_file_found_not,
    F_execute_file_type_directory,
    F_execute_fork_not,
    F_execute_format_not,
    F_execute_group,
    F_execute_input_output,
    F_execute_limit,
    F_execute_loop,
    F_execute_memory_not,
    F_execute_name_not,
    F_execute_nice,
    F_execute_parameter,
    F_execute_pipe,
    F_execute_processor,
    F_execute_prohibited,
    F_execute_resource_not,
    F_execute_schedule,
    F_execute_terminal,
    F_execute_terminal_known_not,
    F_execute_terminal_not,
    F_execute_terminal_prohibited,
    F_execute_terminal_valid_not,
    F_execute_too_large,
    F_execute_user,
    F_execute_valid_not,
  };

  const f_status_t statuss[] = {
    F_none,
    F_access,
    F_execute_not,
    F_buffer,
    F_busy,
    F_capability,
    F_control_group,
    F_child,
    F_directory_not,
    F_failure,
    F_file_found_not,
    F_file_type_directory,
    F_fork_not,
    F_format_not,
    F_group,
    F_input_output,
    F_limit,
    F_loop,
    F_memory_not,
    F_name_not,
    F_nice,
    F_parameter,
    F_pipe,
    F_processor,
    F_prohibited,
    F_resource_not,
    F_schedule,
    F_terminal,
    F_terminal_known_not,
    F_terminal_not,
    F_terminal_prohibited,
    F_terminal_valid_not,
    F_too_large,
    F_user,
    F_valid_not,
  };

  for (uint8_t i = 0; i < 35; ++i) {

    {
      const f_status_t status = f_execute_status_to_status(status_executes[i]);

      assert_int_equal(status, statuss[i]);
    }

    {
      const f_status_t status = f_execute_status_to_status(status_executes[i]);

      assert_int_equal(status, statuss[i]);
    }
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
