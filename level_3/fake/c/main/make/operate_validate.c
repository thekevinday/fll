#include "../fake.h"
#include "../print.h"
#include "../make.h"
#include "operate_validate.h"
#include "operate_validate_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_validate_
  void fake_make_operate_validate(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_array_lengths_t * const section_stack, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    if (state_process->operation == fake_make_operation_type_break_e) {
      *status = fake_make_operate_validate_type_break(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_build_e) {
      *status = fake_make_operate_validate_type_build(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clean_e || state_process->operation == fake_make_operation_type_top_e || state_process->operation == fake_make_operation_type_skeleton_e) {
      *status = fake_make_operate_validate_type_clean_top_skeleton(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clone_e) {
      *status = fake_make_operate_validate_type_clone(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_compile_e) {
      *status = fake_make_operate_validate_type_compile(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_copy_e) {
      *status = fake_make_operate_validate_type_copy(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_define_e) {
      *status = fake_make_operate_validate_type_define(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_delete_e || state_process->operation == fake_make_operation_type_deletes_e) {
      *status = fake_make_operate_validate_type_delete(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_else_e) {
      *status = fake_make_operate_validate_type_else(data_make, state_process);
    }
    else if (state_process->operation == fake_make_operation_type_exit_e) {
      *status = fake_make_operate_validate_type_exit(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_fail_e) {
      *status = fake_make_operate_validate_type_exit(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_group_e || state_process->operation == fake_make_operation_type_groups_e || state_process->operation == fake_make_operation_type_mode_e || state_process->operation == fake_make_operation_type_modes_e || state_process->operation == fake_make_operation_type_owner_e || state_process->operation == fake_make_operation_type_owners_e) {
      *status = fake_make_operate_validate_type_permission(data_make, state_process);
    }
    else if (state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e) {
      *status = fake_make_operate_validate_type_condition(data_make, state_process);
    }
    else if (state_process->operation == fake_make_operation_type_index_e) {
      *status = fake_make_operate_validate_type_index(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_link_e) {
      *status = fake_make_operate_validate_type_link(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_move_e) {
      *status = fake_make_operate_validate_type_move(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_operate_e) {
      *status = fake_make_operate_validate_type_operate(data_make, section_stack);
    }
    else if (state_process->operation == fake_make_operation_type_run_e || state_process->operation == fake_make_operation_type_shell_e) {
      *status = fake_make_operate_validate_type_run(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_parameter_e) {
      *status = fake_make_operate_validate_type_parameter(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_pop_e) {
      *status = fake_make_operate_validate_type_pop(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_to_e) {
      *status = fake_make_operate_validate_type_to(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_touch_e) {
      *status = fake_make_operate_validate_type_touch(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_write_e) {
      *status = fake_make_operate_validate_type_write(data_make);
    }

    // Note: There is nothing to validate for fake_make_operation_type_print_e.
  }
#endif // _di_fake_make_operate_validate_

#ifndef _di_fake_make_operate_validate_define_name_
  f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) {

    if (!name.used) return F_none;
    if (!isalpha(name.string[0]) && name.string[0] != '_') return F_false;

    for (f_array_length_t i = 1; i < name.used; ++i) {
      if (!isalnum(name.string[i]) && name.string[i] != '_') return F_false;
    } // for

    return F_true;
  }
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif
