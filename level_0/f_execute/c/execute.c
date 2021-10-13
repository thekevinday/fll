#include "execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_execute_status_from_status_
  uint8_t f_execute_status_from_status(f_status_t status) {

    if (F_status_set_fine(status) == F_none) {
      return F_execute_none;
    }

    if (F_status_set_fine(status) == F_access) {
      return F_execute_access;
    }

    if (F_status_set_fine(status) == F_buffer) {
      return F_execute_buffer;
    }

    if (F_status_set_fine(status) == F_busy) {
      return F_execute_busy;
    }

    if (F_status_set_fine(status) == F_capability) {
      return F_execute_capability;
    }

    if (F_status_set_fine(status) == F_control_group) {
      return F_execute_control_group;
    }

    if (F_status_set_fine(status) == F_child) {
      return F_execute_child;
    }

    if (F_status_set_fine(status) == F_directory_not) {
      return F_execute_directory_not;
    }

    if (F_status_set_fine(status) == F_execute_not) {
      return F_execute_off;
    }

    if (F_status_set_fine(status) == F_failure) {
      return F_execute_failure;
    }

    if (F_status_set_fine(status) == F_file_found_not) {
      return F_execute_file_found_not;
    }

    if (F_status_set_fine(status) == F_file_type_directory) {
      return F_execute_file_type_directory;
    }

    if (F_status_set_fine(status) == F_group) {
      return F_execute_group;
    }

    if (F_status_set_fine(status) == F_input_output) {
      return F_execute_input_output;
    }

    if (F_status_set_fine(status) == F_limit) {
      return F_execute_limit;
    }

    if (F_status_set_fine(status) == F_loop) {
      return F_execute_loop;
    }

    if (F_status_set_fine(status) == F_memory_not) {
      return F_execute_memory_not;
    }

    if (F_status_set_fine(status) == F_name_not) {
      return F_execute_name_not;
    }

    if (F_status_set_fine(status) == F_nice) {
      return F_execute_nice;
    }

    if (F_status_set_fine(status) == F_parameter) {
      return F_execute_parameter;
    }

    if (F_status_set_fine(status) == F_pipe) {
      return F_execute_pipe;
    }

    if (F_status_set_fine(status) == F_processor) {
      return F_execute_processor;
    }

    if (F_status_set_fine(status) == F_prohibited) {
      return F_execute_prohibited;
    }

    if (F_status_set_fine(status) == F_resource_not) {
      return F_execute_resource_not;
    }

    if (F_status_set_fine(status) == F_schedule) {
      return F_execute_schedule;
    }

    if (F_status_set_fine(status) == F_too_large) {
      return F_execute_too_large;
    }

    if (F_status_set_fine(status) == F_user) {
      return F_execute_user;
    }

    if (F_status_set_fine(status) == F_valid_not) {
      return F_execute_valid_not;
    }

    return F_execute_code_last;
  }
#endif // _di_f_execute_status_from_status_

#ifndef _di_f_execute_status_to_status_
  f_status_t f_execute_status_to_status(uint8_t status) {

    if (status == F_execute_none) {
      return F_none;
    }

    if (status == F_execute_access) {
      return F_access;
    }

    if (status == F_execute_buffer) {
      return F_buffer;
    }

    if (status == F_execute_busy) {
      return F_busy;
    }

    if (status == F_execute_capability) {
      return F_capability;
    }

    if (status == F_execute_control_group) {
      return F_control_group;
    }

    if (status == F_execute_child) {
      return F_child;
    }

    if (status == F_execute_directory_not) {
      return F_directory_not;
    }

    if (status == F_execute_failure) {
      return F_failure;
    }

    if (status == F_execute_file_found_not) {
      return F_file_found_not;
    }

    if (status == F_execute_file_type_directory) {
      return F_file_type_directory;
    }

    if (status == F_execute_group) {
      return F_group;
    }

    if (status == F_execute_input_output) {
      return F_input_output;
    }

    if (status == F_execute_limit) {
      return F_limit;
    }

    if (status == F_execute_loop) {
      return F_loop;
    }

    if (status == F_execute_memory_not) {
      return F_memory_not;
    }

    if (status == F_execute_name_not) {
      return F_name_not;
    }

    if (status == F_execute_nice) {
      return F_nice;
    }

    if (status == F_execute_off) {
      return F_execute_not;
    }

    if (status == F_execute_parameter) {
      return F_parameter;
    }

    if (status == F_execute_pipe) {
      return F_pipe;
    }

    if (status == F_execute_processor) {
      return F_processor;
    }

    if (status == F_execute_prohibited) {
      return F_prohibited;
    }

    if (status == F_execute_resource_not) {
      return F_resource_not;
    }

    if (status == F_execute_schedule) {
      return F_schedule;
    }

    if (status == F_execute_too_large) {
      return F_too_large;
    }

    if (status == F_execute_user) {
      return F_user;
    }

    if (status == F_execute_valid_not) {
      return F_valid_not;
    }

    return F_status_set_error(F_known_not);
  }
#endif // _di_f_execute_status_to_status_

#ifdef __cplusplus
} // extern "C"
#endif
