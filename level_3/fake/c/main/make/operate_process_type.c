#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_type_break_
  void fake_make_operate_process_type_break(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    main->setting.state.status = F_none;

    if (!main->cache_arguments.used || f_compare_dynamic(fake_make_operation_argument_success_s, main->cache_arguments.array[0]) == F_equal_to) {
      main->setting.state.status = F_signal_abort;
    }
    else if (f_compare_dynamic(fake_make_operation_argument_failure_s, main->cache_arguments.array[0]) == F_equal_to) {
      main->setting.state.status = F_status_set_error(F_signal_abort);
    }
    else {
      main->setting.state.status = F_none;

      return;
    }

    fake_make_print_verbose_operate_break(&main->program.message, main->cache_arguments);
  }
#endif // _di_fake_make_operate_process_type_break_

#ifndef _di_fake_make_operate_process_type_build_
  void fake_make_operate_process_type_build(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_build_operate(data_make->data, main->cache_arguments.used ? &main->cache_arguments : 0, F_false);
    if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;

    fake_make_operate_process_return(data_make, F_status_is_error(main->setting.state.status) ? 1 : 0);
  }
#endif // _di_fake_make_operate_process_type_build_

#ifndef _di_fake_make_operate_process_type_clean_
  void fake_make_operate_process_type_clean(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_clean_operate(data_make->data);
    if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;

    fake_make_operate_process_return(data_make, F_status_is_error(main->setting.state.status) ? 1 : 0);
  }
#endif // _di_fake_make_operate_process_type_clean_

#ifndef _di_fake_make_operate_process_type_compile_
  int fake_make_operate_process_type_compile(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return 0;

    fake_main_t * const main = data_make->main;

    const int result = fake_execute(data_make->data, data_make->environment, data_make->setting_build.build_compiler);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_execute));
    }
    else if (main->setting.state.status == F_child) {
      return result;
    }

    fake_make_operate_process_return(data_make, result);

    return 0;
  }
#endif // _di_fake_make_operate_process_type_compile_

#ifndef _di_fake_make_operate_process_type_condition_
  void fake_make_operate_process_type_condition(fake_make_data_t * const data_make, fake_state_process_t * const state_process) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    main->setting.state.status = F_none;

    if (state_process->condition == fake_make_operation_if_type_if_define_e) {
      fake_make_operate_process_type_if_define(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_equal_e) {
      state_process->condition_result = fake_condition_result_true_e;

      for (f_array_length_t i = 2; i < main->cache_arguments.used; ++i) {

        if (f_compare_dynamic(main->cache_arguments.array[1], main->cache_arguments.array[i]) == F_equal_to_not) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      } // for
    }
    else if (state_process->condition == fake_make_operation_if_type_if_equal_not_e) {
      state_process->condition_result = fake_condition_result_true_e;

      f_array_length_t i = 1;
      f_array_length_t j = 0;

      for (; i < main->cache_arguments.used; ++i) {

        for (j = i + 1; j < main->cache_arguments.used; ++j) {

          if (f_compare_dynamic(main->cache_arguments.array[i], main->cache_arguments.array[j]) == F_equal_to) {
            state_process->condition_result = fake_condition_result_false_e;
            i = main->cache_arguments.used;

            break;
          }
        } // for
      } // for
    }
    else if (state_process->condition == fake_make_operation_if_type_if_exist_e) {
      fake_make_operate_process_type_if_exist(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_failure_e) {
      if (state_process->success) {
        state_process->condition_result = fake_condition_result_false_e;
      }
      else {
        state_process->condition_result = fake_condition_result_true_e;
      }
    }
    else if (state_process->condition == fake_make_operation_if_type_if_greater_e || state_process->condition == fake_make_operation_if_type_if_greater_equal_e || state_process->condition == fake_make_operation_if_type_if_less_e || state_process->condition == fake_make_operation_if_type_if_less_equal_e) {
      fake_make_operate_process_type_if_greater_if_lesser(data_make, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_group_e) {
      fake_make_operate_process_type_if_group(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_is_e) {
      fake_make_operate_process_type_if_is(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_mode_e) {
      fake_make_operate_process_type_if_mode(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_define_e) {
      fake_make_operate_process_type_if_define(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_parameter_e) {
      fake_make_operate_process_type_if_parameter(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_exist_e) {
      fake_make_operate_process_type_if_exist(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_group_e) {
      fake_make_operate_process_type_if_group(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_is_e) {
      fake_make_operate_process_type_if_is(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_mode_e) {
      fake_make_operate_process_type_if_mode(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_not_owner_e) {
      fake_make_operate_process_type_if_owner(data_make, F_true, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_owner_e) {
      fake_make_operate_process_type_if_owner(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_parameter_e) {
      fake_make_operate_process_type_if_parameter(data_make, F_false, state_process);
    }
    else if (state_process->condition == fake_make_operation_if_type_if_success_e) {
      if (state_process->success) {
        state_process->condition_result = fake_condition_result_true_e;
      }
      else {
        state_process->condition_result = fake_condition_result_false_e;
      }
    }

    if (state_process->block) {
      if (state_process->operation == fake_make_operation_type_and_e) {
        if (state_process->block_result == fake_condition_result_true_e && state_process->condition_result == fake_condition_result_true_e) {
          state_process->condition_result = fake_condition_result_true_e;
        }
        else {
          state_process->condition_result = fake_condition_result_false_e;
        }
      }
      else if (state_process->operation == fake_make_operation_type_or_e) {
        if (state_process->block_result == fake_condition_result_true_e || state_process->condition_result == fake_condition_result_true_e) {
          state_process->condition_result = fake_condition_result_true_e;
        }
        else {
          state_process->condition_result = fake_condition_result_false_e;
        }
      }
    }
  }
#endif // _di_fake_make_operate_process_type_condition_

#ifndef _di_fake_make_operate_process_type_copy_
  void fake_make_operate_process_type_copy(fake_make_data_t * const data_make, const bool clone) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    const f_array_length_t total = main->cache_arguments.used - 1;
    f_status_t failed = F_none;
    fake_local_t local = macro_fake_local_t_initialize_1(main, &main->cache_map, &failed);

    main->cache_recurse_do.action = &fake_do_copy_action;
    main->cache_recurse_do.handle = &fake_do_copy_handle;
    main->cache_recurse_do.state.custom = (void *) &local;
    main->cache_recurse_do.state.code = fake_state_code_local_e;
    main->cache_recurse_do.flag = f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_before_e | f_directory_recurse_do_flag_after_e;

    if (clone) {
      main->cache_recurse_do.state.code |= fake_state_code_clone_e;
    }
    else {
      macro_f_mode_t_set_default_umask(main->cache_recurse_do.mode, main->program.umask);
    }

    fake_string_dynamic_reset(&main->cache_recurse_do.path);
    fake_string_dynamic_reset(&main->cache_recurse_do.path_cache);

    bool existing = F_true;
    f_array_length_t i = 0;
    const f_string_t *function = 0;
    const f_string_static_t *operation = 0;
    uint8_t type = fll_error_file_type_path_e;

    // The first argument may designate not to dereference links.
    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      main->cache_recurse_do.flag |= f_file_stat_flag_reference_e;
    }

    // Confirm if the destination is a file when there are three or more arguments (after the potential no dereference argument).
    if (main->cache_arguments.used == 2 + i) {
      main->setting.state.status = f_directory_is(main->cache_arguments.array[1]);

      if (F_status_is_error(main->setting.state.status)) {
        function = &macro_fake_f(f_directory_is);
        operation = &f_file_operation_identify_s;
      }
      else if (main->setting.state.status == F_false || main->setting.state.status == F_file_found_not || main->setting.state.status == F_data_not) {
        existing = F_false;
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      for (; i < total; ++i) {

        fake_string_dynamic_reset(&main->cache_map.name);

        main->setting.state.status = f_string_dynamic_append_nulless(main->cache_arguments.array[total], &main->cache_map.name);

        if (F_status_is_error(main->setting.state.status)) {
          function = &macro_fake_f(f_string_dynamic_append_nulless);
          operation = &f_file_operation_process_s;

          break;
        }

        if (existing) {
          main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &main->cache_map.name);

          if (F_status_is_error(main->setting.state.status)) {
            function = &macro_fake_f(f_string_dynamic_append_assure);
            operation = &f_file_operation_process_s;

            break;
          }

          main->setting.state.status = f_file_name_base(main->cache_arguments.array[i], &main->cache_map.name);

          if (F_status_is_error(main->setting.state.status)) {
            function = &macro_fake_f(f_file_name_base);
            operation = &f_file_operation_process_s;

            break;
          }
        }

        main->setting.state.status = f_directory_is(main->cache_arguments.array[i]);

        if (main->setting.state.status == F_true) {
          fl_directory_do(main->cache_arguments.array[i], &main->cache_recurse_do);

          if (F_status_is_error(main->cache_recurse_do.state.status)) {
            main->setting.state.status = main->cache_recurse_do.state.status;

            function = &macro_fake_f(fl_directory_do);
            operation = clone ? &f_file_operation_clone_s : &f_file_operation_copy_s;
            type = fll_error_file_type_directory_e;

            break;
          }
        }
        else if (main->setting.state.status == F_false) {
          if (clone) {
            main->setting.state.status = f_file_clone(main->cache_arguments.array[i], main->cache_map.name, F_file_default_write_size_d, f_file_stat_flag_group_e | f_file_stat_flag_owner_e | (f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e));
          }
          else {
            main->setting.state.status = f_file_copy(main->cache_arguments.array[i], main->cache_map.name, main->cache_recurse_do.mode, F_file_default_write_size_d, f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e);
          }

          if (F_status_is_error(main->setting.state.status)) {
            function = clone ? &macro_fake_f(f_file_clone) : &macro_fake_f(f_file_copy);
            operation = clone ? &f_file_operation_clone_s : &f_file_operation_copy_s;
            type = fll_error_file_type_file_e;

            break;
          }

          fake_make_print_verbose_operate_copy(&main->program.message, clone, main->cache_arguments.array[i], main->cache_map.name);
        }
        else if (F_status_is_error(main->setting.state.status)) {
          function = &macro_fake_f(f_directory_is);
          operation = &f_file_operation_identify_s;
          type = fll_error_file_type_directory_e;

          break;
        }
      } // for
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, *function, main->cache_arguments.array[1], *operation, type);

      main->setting.state.status = F_status_set_error(F_failure);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_type_copy_

#ifndef _di_fake_make_operate_process_type_define_
  void fake_make_operate_process_type_define(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    if (main->cache_arguments.used > 1) {
      main->setting.state.status = f_environment_set(main->cache_arguments.array[0], main->cache_arguments.array[1], F_true);
    }
    else {
      main->setting.state.status = f_environment_set(main->cache_arguments.array[0], f_string_empty_s, F_true);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(f_environment_set));
    }
    else {
      fake_make_print_verbose_operate_define(&main->program.message, main->cache_arguments.array[0]);

      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_type_define_

#ifndef _di_fake_make_operate_process_type_deletes_
  void fake_make_operate_process_type_deletes(fake_make_data_t * const data_make, const bool all) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    const int recursion_max = all ? F_directory_max_descriptors_d : 0;
    struct stat file_stat;

    main->setting.state.status = F_none;

    for (f_array_length_t i = 0; i < main->cache_arguments.used; ++i) {

      memset(&file_stat, 0, sizeof(struct stat));

      main->setting.state.status = f_file_stat(main->cache_arguments.array[i], F_false, &file_stat);

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_file_found_not) {
          fake_make_print_warning_file_not_found(&main->program.warning, main->cache_arguments.array[i]);

          main->setting.state.status = F_none;
        }
        else {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_stat), main->cache_arguments.array[i], f_file_operation_delete_s, fll_error_file_type_file_e);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }
      else if (macro_f_file_type_is_directory(file_stat.st_mode)) {
        if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
          main->setting.state.status = f_directory_remove_custom(main->cache_arguments.array[i], recursion_max, F_false, fake_clean_remove_recursively_verbosely);
        }
        else {
          main->setting.state.status = f_directory_remove(main->cache_arguments.array[i], recursion_max, F_false);
        }

        if (F_status_set_fine(main->setting.state.status) == F_file_found_not) {
          fake_make_print_verbose_operate_file_not_found(&main->program.message, F_true, main->cache_arguments.array[i]);

          main->setting.state.status = F_none;
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_directory_remove), main->cache_arguments.array[i], f_file_operation_delete_s, fll_error_file_type_directory_e);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }
      else {
        main->setting.state.status = f_file_remove(main->cache_arguments.array[i]);

        if (F_status_set_fine(main->setting.state.status) == F_file_found_not) {
          if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
            fake_make_print_verbose_operate_file_not_found(&main->program.message, F_false, main->cache_arguments.array[i]);
          }

          main->setting.state.status = F_none;
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_remove), main->cache_arguments.array[i], f_file_operation_delete_s, fll_error_file_type_file_e);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }

      fake_make_print_verbose_operate_delete(&main->program.message, main->cache_arguments.array[i]);
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_deletes_

#ifndef _di_fake_make_operate_process_type_exit_
  void fake_make_operate_process_type_exit(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    main->setting.state.status = F_none;

    if (!main->cache_arguments.used || f_compare_dynamic(fake_make_operation_argument_success_s, main->cache_arguments.array[0]) == F_equal_to) {
      main->setting.state.status = F_signal_quit;
    }
    else if (f_compare_dynamic(fake_make_operation_argument_failure_s, main->cache_arguments.array[0]) == F_equal_to) {
      main->setting.state.status = F_status_set_error(F_signal_quit);

      // Forcing exit forces fail mode.
      data_make->setting_make.fail = fake_make_operation_fail_exit_e;
      data_make->error.prefix = fl_print_error_s;
      data_make->error.suffix = f_string_empty_s;
      data_make->error.context = main->program.context.set.error;
      data_make->error.notable = main->program.context.set.notable;
      main->program.error.to.stream = F_type_error_d;
      main->program.error.to.id = F_type_descriptor_error_d;
      data_make->error.set = &main->program.context.set;
    }
    else {
      main->setting.state.status = F_none;

      return;
    }

    fake_make_print_verbose_operate_exiting_as(&main->program.message, main->cache_arguments);
  }
#endif // _di_fake_make_operate_process_type_exit_

#ifndef _di_fake_make_operate_process_type_fail_
  void fake_make_operate_process_type_fail(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    if (f_compare_dynamic(fake_make_operation_argument_exit_s, main->cache_arguments.array[0]) == F_equal_to) {
      data_make->setting_make.fail = fake_make_operation_fail_exit_e;
      data_make->error.prefix = fl_print_error_s;
      data_make->error.suffix = f_string_empty_s;
      data_make->error.context = main->program.context.set.error;
      data_make->error.notable = main->program.context.set.notable;
      main->program.error.to.stream = F_type_error_d;
      main->program.error.to.id = F_type_descriptor_error_d;
      data_make->error.set = &main->program.context.set;
    }
    else if (f_compare_dynamic(fake_make_operation_argument_warn_s, main->cache_arguments.array[0]) == F_equal_to) {
      data_make->setting_make.fail = fake_make_operation_fail_warn_e;
      data_make->error.prefix = fl_print_warning_s;
      data_make->error.suffix = f_string_empty_s;
      data_make->error.context = main->program.context.set.warning;
      data_make->error.notable = main->program.context.set.notable;
      main->program.error.to.stream = F_type_output_d;
      main->program.error.to.id = F_type_descriptor_output_d;
      data_make->error.set = &main->program.context.set;
    }
    else {
      data_make->setting_make.fail = fake_make_operation_fail_ignore_e;
      main->program.error.to.stream = 0;
      main->program.error.to.id = -1;
    }

    fake_make_print_verbose_operate_set_failure_state(&main->program.message, data_make->setting_make.fail);
  }
#endif // _di_fake_make_operate_process_type_fail_

#ifndef _di_fake_make_operate_process_type_groups_
  void fake_make_operate_process_type_groups(fake_make_data_t * const data_make, const bool all) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    gid_t id = 0;
    bool dereference = F_true;
    f_array_length_t i = 0;

    main->setting.state.status = F_none;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    id = (gid_t) fake_make_get_id(data_make, F_false, main->cache_arguments.array[i++]);

    if (F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_status_set_error(F_failure);
    }

    for (; i < main->cache_arguments.used; ++i) {

      fake_make_assure_inside_project(data_make, main->cache_arguments.array[i]);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_operation_path_outside(&data_make->error, macro_fake_f(fake_make_assure_inside_project), main->cache_argument.used ? main->cache_argument : main->cache_arguments.array[i]);

        continue;
      }

      if (all) {
        main->setting.state.status = fll_file_role_change_all(main->cache_arguments.array[i], -1, id, dereference, fake_max_recursion_depth_d);
      }
      else {
        main->setting.state.status = f_file_role_change(main->cache_arguments.array[i], -1, id, dereference);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, all ? macro_fake_f(fll_file_role_change_all) : macro_fake_f(f_file_role_change), main->cache_arguments.array[i], f_file_operation_change_group_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      fake_make_print_verbose_operate_set_role(&main->program.message, all ? 0x1 : 0x0, main->cache_arguments.array[i], (f_number_unsigned_t) id);
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_groups_

#ifndef _di_fake_make_operate_process_type_if_define_
  void fake_make_operate_process_type_if_define(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    state_process->condition_result = fake_condition_result_true_e;

    // Multiple properties may pass and so if any of them fail, then they all fail.
    if (if_not) {
      for (f_array_length_t i = 2; i < main->cache_arguments.used; ++i) {

        if (f_environment_exists(main->cache_arguments.array[i]) == F_true) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      } // for
    }
    else {
      for (f_array_length_t i = 1; i < main->cache_arguments.used; ++i) {

        if (f_environment_exists(main->cache_arguments.array[i]) != F_true) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      } // for
    }
  }
#endif // _di_fake_make_operate_process_type_if_define_

#ifndef _di_fake_make_operate_process_type_if_exist_
  void fake_make_operate_process_type_if_exist(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    f_array_length_t i = if_not ? 2 : 1;
    bool dereference = F_true;

    main->setting.state.status = F_none;

    if (i == main->cache_arguments.used) {
      if (if_not) {
        state_process->condition_result = fake_condition_result_true_e;
      }
      else {
        state_process->condition_result = fake_condition_result_false_e;
      }

      main->setting.state.status = F_none;

      return;
    }

    state_process->condition_result = fake_condition_result_true_e;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    for (; i < main->cache_arguments.used; ++i) {

      main->setting.state.status = f_file_exists(main->cache_arguments.array[i], dereference);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_exists), main->cache_arguments.array[i], f_file_operation_find_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (if_not) {
        if (main->setting.state.status == F_true) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
      else {
        if (main->setting.state.status != F_true) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_if_exist_

#ifndef _di_fake_make_operate_process_type_if_is_
  void fake_make_operate_process_type_if_is(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
    // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
    // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
    // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
    uint8_t type = 0;

    f_array_length_t i = if_not ? 2 : 1;
    bool dereference = F_true;

    main->setting.state.status = F_none;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    if (i == main->cache_arguments.used) {
      if (if_not) {
        state_process->condition_result = fake_condition_result_true_e;
      }
      else {
        state_process->condition_result = fake_condition_result_false_e;
      }

      main->setting.state.status = F_none;

      return;
    }

    for (; i < main->cache_arguments.used; ++i) {

      if (f_compare_dynamic(fake_make_operation_argument_if_is_for_s, main->cache_arguments.array[i]) == F_equal_to) {
        ++i;

        break;
      }

      if (f_compare_dynamic(f_file_type_name_block_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x1;
      }
      else if (f_compare_dynamic(f_file_type_name_character_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x2;
      }
      else if (f_compare_dynamic(f_file_type_name_directory_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x4;
      }
      else if (f_compare_dynamic(f_file_type_name_fifo_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x8;
      }
      else if (f_compare_dynamic(f_file_type_name_link_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x10;
      }
      else if (f_compare_dynamic(f_file_type_name_regular_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x20;
      }
      else if (f_compare_dynamic(f_file_type_name_socket_s, main->cache_arguments.array[i]) == F_equal_to) {
        type |= 0x40;
      }
    } // for

    uint8_t type_file = 0;
    mode_t mode_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (; i < main->cache_arguments.used; ++i, mode_file = 0) {

      main->setting.state.status = f_file_mode_read(main->cache_arguments.array[i], dereference, &mode_file);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_mode_read), main->cache_arguments.array[i], f_file_operation_get_type_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (macro_f_file_type_is_block(mode_file)) {
        type_file = 0x1;
      }
      else if (macro_f_file_type_is_character(mode_file)) {
        type_file = 0x2;
      }
      else if (macro_f_file_type_is_directory(mode_file)) {
        type_file = 0x4;
      }
      else if (macro_f_file_type_is_fifo(mode_file)) {
        type_file = 0x8;
      }
      else if (macro_f_file_type_is_link(mode_file)) {
        type_file = 0x10;
      }
      else if (macro_f_file_type_is_regular(mode_file)) {
        type_file = 0x20;
      }
      else if (macro_f_file_type_is_socket(mode_file)) {
        type_file = 0x40;
      }

      if (if_not) {
        if (type & type_file) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
      else {
        if (!(type & type_file)) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_if_is_

#ifndef _di_fake_make_operate_process_type_if_greater_if_lesser_
  void fake_make_operate_process_type_if_greater_if_lesser(fake_make_data_t * const data_make, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    f_string_range_t range = f_string_range_t_initialize;
    f_number_unsigned_t number_left = 0;
    f_number_unsigned_t number_right = 0;

    bool is_negative_left = F_false;
    bool is_negative_right = F_false;

    f_array_length_t i = 1;

    main->setting.state.status = F_none;
    state_process->condition_result = fake_condition_result_true_e;

    range.start = 0;
    range.stop = main->cache_arguments.array[i].used - 1;

    if (main->cache_arguments.array[i].string[0] == f_string_ascii_plus_s.string[0]) {
      range.start = 1;
    }
    else if (main->cache_arguments.array[i].string[0] == f_string_ascii_minus_s.string[0]) {
      range.start = 1;
      is_negative_left = F_true;
    }

    if (range.start > range.stop) {
      main->setting.state.status = F_status_set_error(F_failure);
    }
    else {
      main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, main->cache_arguments.array[i], range, &number_left);
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      for (i = 2; i < main->cache_arguments.used; ++i, main->setting.state.status = F_none, number_left = number_right, is_negative_left = is_negative_right) {

        if (main->cache_arguments.array[i].used) {
          range.start = 0;
          range.stop = main->cache_arguments.array[i].used - 1;

          is_negative_right = F_false;

          if (main->cache_arguments.array[i].string[0] == f_string_ascii_plus_s.string[0]) {
            range.start = 1;
          }
          else if (main->cache_arguments.array[i].string[0] == f_string_ascii_minus_s.string[0]) {
            range.start = 1;
            is_negative_right = F_true;
          }

          if (range.start > range.stop) {
            main->setting.state.status = F_status_set_error(F_failure);
          }
          else {
            main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, main->cache_arguments.array[i], range, &number_right);
          }
        }
        else {
          main->setting.state.status = F_status_set_error(F_failure);
        }

        if (F_status_is_error(main->setting.state.status)) break;

        if (state_process->condition == fake_make_operation_if_type_if_greater_e) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left > number_right)) {
              state_process->condition_result = fake_condition_result_false_e;

              break;
            }
          }
          else if (!is_negative_left && is_negative_right) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
        else if (state_process->condition == fake_make_operation_if_type_if_greater_equal_e) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left >= number_right)) {
              state_process->condition_result = fake_condition_result_false_e;

              break;
            }
          }
          else if (!is_negative_left && is_negative_right) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
        else if (state_process->condition == fake_make_operation_if_type_if_less_e) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left < number_right)) {
              state_process->condition_result = fake_condition_result_false_e;

              break;
            }
          }
          else if (is_negative_left && !is_negative_right) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
        else if (state_process->condition == fake_make_operation_if_type_if_less_equal_e) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left <= number_right)) {
              state_process->condition_result = fake_condition_result_false_e;

              break;
            }
          }
          else if (is_negative_left && !is_negative_right) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
      } // for
    }

    if (F_status_is_error(main->setting.state.status)) {
      state_process->condition_result = fake_condition_result_error_e;

      if ((i == 1 && number_left > F_number_t_size_unsigned_d) || (i > 1 && number_right > F_number_t_size_unsigned_d)) {
        fake_make_print_error_out_of_range_number(&main->program.error, main->cache_arguments.array[i], F_number_t_size_unsigned_d, F_number_t_size_unsigned_d);
      }
      else {
        fake_make_print_error_unsupported_number(&main->program.error, main->cache_arguments.array[i]);
      }

      main->setting.state.status = F_status_set_error(F_failure);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_type_if_greater_if_lesser_

#ifndef _di_fake_make_operate_process_type_if_group_
  void fake_make_operate_process_type_if_group(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    uid_t id = 0;
    f_array_length_t i = if_not ? 2 : 1;
    bool dereference = F_true;

    main->setting.state.status = F_none;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    id = (uid_t) fake_make_get_id(data_make, F_true, main->cache_arguments.array[i++]);

    if (F_status_is_error(main->setting.state.status)) {
      state_process->condition_result = fake_condition_result_error_e;

      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id));

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    state_process->condition_result = fake_condition_result_true_e;

    for (uid_t id_file = 0; i < main->cache_arguments.used; ++i, id_file = 0) {

      main->setting.state.status = f_file_group_read(main->cache_arguments.array[i], dereference, &id_file);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_group_read), main->cache_arguments.array[i], f_file_operation_get_group_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (if_not) {
        if (id == id_file) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
      else {
        if (id != id_file) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_if_group_

#ifndef _di_fake_make_operate_process_type_if_mode_
  void fake_make_operate_process_type_if_mode(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    f_file_mode_t mode_rule = 0;
    mode_t mode_match = 0;
    bool is = F_false;

    if (f_compare_dynamic(fake_make_operation_argument_is_s, main->cache_arguments.array[if_not ? 2 : 1]) == F_equal_to) {
      is = F_true;
    }

    {
      uint8_t mode_replace = 0;

      fake_make_get_id_mode(data_make, main->cache_arguments.array[if_not ? 3 : 2], &mode_rule, &mode_replace);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id_mode));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      main->setting.state.status = f_file_mode_to_mode(mode_rule, &mode_match);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error(&main->program.error, macro_fake_f(f_file_mode_to_mode));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }
    }

    mode_t mode_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (f_array_length_t i = if_not ? 4 : 3; i < main->cache_arguments.used; ++i, mode_file = 0) {

      main->setting.state.status = f_file_mode_read(main->cache_arguments.array[i], F_true, &mode_file);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_mode_read), main->cache_arguments.array[i], f_file_operation_get_mode_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (if_not) {
        if (is) {
          if (mode_match == (mode_file & F_file_mode_all_d)) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
        else {
          if (mode_match & mode_file) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
      }
      else {
        if (is) {
          if (mode_match != (mode_file & F_file_mode_all_d)) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
        else {
          if (!(mode_match & mode_file)) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        }
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_if_mode_

#ifndef _di_fake_make_operate_process_type_if_owner_
  void fake_make_operate_process_type_if_owner(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    uid_t id = 0;
    f_array_length_t i = if_not ? 2 : 1;
    bool dereference = F_true;

    main->setting.state.status = F_none;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    id = (uid_t) fake_make_get_id(data_make, F_true, main->cache_arguments.array[i++]);

    if (F_status_is_error(main->setting.state.status)) {
      state_process->condition_result = fake_condition_result_error_e;

      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id));

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    state_process->condition_result = fake_condition_result_true_e;

    for (uid_t id_file = 0; i < main->cache_arguments.used; ++i, id_file = 0) {

      main->setting.state.status = f_file_owner_read(main->cache_arguments.array[i], dereference, &id_file);

      if (F_status_is_error(main->setting.state.status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fake_print_error_file(&main->program.error, macro_fake_f(f_file_owner_read), main->cache_arguments.array[i], f_file_operation_get_owner_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (if_not) {
        if (id == id_file) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
      else {
        if (id != id_file) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_if_owner_

#ifndef _di_fake_make_operate_process_type_if_parameter_
  void fake_make_operate_process_type_if_parameter(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process) {

    if (!data_make || !data_make->main || !state_process) return;

    fake_main_t * const main = data_make->main;

    const f_string_static_t reserved_name[] = {
      fake_make_parameter_variable_build_s,
      fake_make_parameter_variable_color_s,
      fake_make_parameter_variable_data_s,
      fake_make_parameter_variable_define_s,
      fake_make_parameter_variable_fakefile_s,
      fake_make_parameter_variable_mode_s,
      fake_make_parameter_variable_process_s,
      fake_make_parameter_variable_settings_s,
      fake_make_parameter_variable_sources_s,
      fake_make_parameter_variable_verbosity_s,
      fake_make_parameter_variable_work_s,
      fake_make_parameter_variable_option_build_s,
      fake_make_parameter_variable_option_color_s,
      fake_make_parameter_variable_option_data_s,
      fake_make_parameter_variable_option_define_s,
      fake_make_parameter_variable_option_fakefile_s,
      fake_make_parameter_variable_option_mode_s,
      fake_make_parameter_variable_option_process_s,
      fake_make_parameter_variable_option_settings_s,
      fake_make_parameter_variable_option_sources_s,
      fake_make_parameter_variable_option_verbosity_s,
      fake_make_parameter_variable_option_work_s,
      fake_make_parameter_variable_value_build_s,
      fake_make_parameter_variable_value_color_s,
      fake_make_parameter_variable_value_data_s,
      fake_make_parameter_variable_value_define_s,
      fake_make_parameter_variable_value_fakefile_s,
      fake_make_parameter_variable_value_mode_s,
      fake_make_parameter_variable_value_process_s,
      fake_make_parameter_variable_value_settings_s,
      fake_make_parameter_variable_value_sources_s,
      fake_make_parameter_variable_value_verbosity_s,
      fake_make_parameter_variable_value_work_s,
    };

    const bool reserved_parameter[] = {
      main->setting.build.used,
      F_true,
      main->setting.data.used,
      main->setting.defines.used,
      main->setting.fakefile.used,
      main->setting.modes.used,
      main->setting.process.used,
      main->setting.settings.used,
      main->setting.sources.used,
      F_true,
      main->setting.work.used,
      main->program.parameters.array[fake_parameter_build_e].result & f_console_result_value_e,
      (main->program.parameters.array[fake_parameter_light_e].result & f_console_result_found_e) || (main->program.parameters.array[fake_parameter_dark_e].result & f_console_result_found_e) || (main->program.parameters.array[fake_parameter_no_color_e].result & f_console_result_found_e),
      main->program.parameters.array[fake_parameter_data_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_define_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_fakefile_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_mode_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_process_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_settings_e].result & f_console_result_value_e,
      main->program.parameters.array[fake_parameter_sources_e].result & f_console_result_value_e,
      (main->program.parameters.array[fake_parameter_verbosity_quiet_e].result & f_console_result_found_e) || (main->program.parameters.array[fake_parameter_verbosity_normal_e].result & f_console_result_found_e) || (main->program.parameters.array[fake_parameter_verbosity_verbose_e].result & f_console_result_found_e) || (main->program.parameters.array[fake_parameter_verbosity_debug_e].result & f_console_result_found_e),
      main->program.parameters.array[fake_parameter_work_e].result & f_console_result_value_e,
      data_make->parameter_value.build.used,
      data_make->parameter_value.color.used,
      data_make->parameter_value.data.used,
      data_make->parameter_value.define.used,
      data_make->parameter_value.fakefile.used,
      data_make->parameter_value.mode.used,
      data_make->parameter_value.process.used,
      data_make->parameter_value.settings.used,
      data_make->parameter_value.sources.used,
      data_make->parameter_value.verbosity.used,
      data_make->parameter_value.work.used,
    };

    f_array_length_t i = if_not ? 2 : 1;
    f_array_length_t j = 0;

    // 0 = unknown, 1 = fail, 2 = pass.
    uint8_t result = 0;

    state_process->condition_result = fake_condition_result_true_e;

    // Multiple properties may pass and so if any of them fail, then they all fail.
    for (; i < main->cache_arguments.used && !result; ++i) {

      for (j = 0; j < 33; ++j) {

        if (f_compare_dynamic(reserved_name[j], main->cache_arguments.array[i]) == F_equal_to) {
          result = reserved_parameter[j] ? 2 : 1;

          break;
        }
      } // for

      if (!result) {
        for (j = 0; j < data_make->setting_make.parameter.used; ++j) {

          if (f_compare_dynamic(main->cache_arguments.array[i], data_make->setting_make.parameter.array[j].name) == F_equal_to) {
            result = 2;

            break;
          }
        } // for

        if (j == data_make->setting_make.parameter.used) {
          result = 1;
        }
      }

      if (result == 2 && i + 1 < main->cache_arguments.used) {
        result = 0;
      }
    } // for

    if (if_not) {
      if (result == 2) {
        state_process->condition_result = fake_condition_result_false_e;
      }
      else {
        state_process->condition_result = fake_condition_result_true_e;
      }
    }
    else if (result == 2) {
      state_process->condition_result = fake_condition_result_true_e;
    }
    else {
      state_process->condition_result = fake_condition_result_false_e;
    }
  }
#endif // _di_fake_make_operate_process_type_if_parameter_

#ifndef _di_fake_make_operate_process_type_index_
  int fake_make_operate_process_type_index(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return 0;

    fake_main_t * const main = data_make->main;

    const int result = fake_execute(data_make->data, data_make->environment, data_make->setting_build.build_indexer);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_execute));
    }

    if (main->setting.state.status == F_child) return result;

    fake_make_operate_process_return(data_make, result);

    return 0;
  }
#endif // _di_fake_make_operate_process_type_index_

#ifndef _di_fake_make_operate_process_type_link_
  void fake_make_operate_process_type_link(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    // 0x1 = force, 0x2 = strict.
    uint8_t flag = 0;

    if (main->cache_arguments.used > 2) {
      if (f_compare_dynamic(fake_make_operation_argument_force_s, main->cache_arguments.array[1]) != F_equal_to) {
        flag |= 0x1;
      }
      else if (f_compare_dynamic(fake_make_operation_argument_strict_s, main->cache_arguments.array[1]) == F_equal_to) {
        flag |= 0x2;
      }

      if (main->cache_arguments.used > 3) {
        if (f_compare_dynamic(fake_make_operation_argument_force_s, main->cache_arguments.array[2]) != F_equal_to) {
          flag |= 0x1;
        }
        else if (f_compare_dynamic(fake_make_operation_argument_strict_s, main->cache_arguments.array[2]) == F_equal_to) {
          flag |= 0x2;
        }
      }
    }

    if ((flag & 0x1) && f_file_exists(main->cache_arguments.array[main->cache_arguments.used - 1], F_false) == F_true) {
      if (f_directory_is(main->cache_arguments.array[main->cache_arguments.used - 1]) == F_true) {
        main->setting.state.status = f_directory_remove(main->cache_arguments.array[main->cache_arguments.used - 1], F_directory_max_descriptors_d, F_false);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_directory_remove), main->cache_arguments.array[main->cache_arguments.used - 1], f_file_operation_delete_s, fll_error_file_type_directory_e);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }
      else {
        main->setting.state.status = f_file_remove(main->cache_arguments.array[main->cache_arguments.used - 1]);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_remove), main->cache_arguments.array[main->cache_arguments.used - 1], f_file_operation_delete_s, fll_error_file_type_file_e);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }
    }

    main->setting.state.status = f_file_link(main->cache_arguments.array[0], main->cache_arguments.array[main->cache_arguments.used - 1]);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, macro_fake_f(f_file_link), main->cache_arguments.array[main->cache_arguments.used - 1], f_file_operation_link_s, fll_error_file_type_file_e);

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    fake_make_print_verbose_operate_symbolic_link(&main->program.message, main->cache_arguments.array[main->cache_arguments.used - 1], main->cache_arguments.array[0]);

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_link_

#ifndef _di_fake_make_operate_process_type_modes_
  void fake_make_operate_process_type_modes(fake_make_data_t * const data_make, const bool all) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    main->setting.state.status = F_none;

    f_file_mode_t mode_rule = 0;
    uint8_t replace = 0;

    fake_make_get_id_mode(data_make, main->cache_arguments.array[0], &mode_rule, &replace);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id_mode));

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    mode_t mode = 0;
    mode_t mode_file = 0;

    for (f_array_length_t i = 1; i < main->cache_arguments.used; ++i, mode = 0) {

      main->setting.state.status = f_file_mode_read(main->cache_arguments.array[i], F_true, &mode_file);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_file_mode_read), main->cache_arguments.array[i], f_file_operation_change_group_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      main->setting.state.status = f_file_mode_determine(mode_file, mode_rule, replace, macro_f_file_type_is_directory(mode_file), &mode);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_file_mode_determine), main->cache_arguments.array[i], f_file_operation_change_group_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (all) {
        main->setting.state.status = fll_file_mode_set_all(main->cache_arguments.array[i], F_true, mode, fake_max_recursion_depth_d);
      }
      else {
        main->setting.state.status = f_file_mode_set(main->cache_arguments.array[i], mode);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, all ? macro_fake_f(fll_file_mode_set_all) : macro_fake_f(f_file_mode_set), main->cache_arguments.array[i], f_file_operation_change_group_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      fake_make_print_verbose_operate_set_mode(&main->program.message, main->cache_arguments.array[i], mode);
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_modes_

#ifndef _di_fake_make_operate_process_type_move_
  void fake_make_operate_process_type_move(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    const f_array_length_t total = main->cache_arguments.used - 1;

    bool existing = F_true;

    // In this case, the destination could be a file, so confirm this.
    if (main->cache_arguments.used == 2) {
      main->setting.state.status = f_directory_is(main->cache_arguments.array[1]);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, macro_fake_f(f_directory_is), main->cache_arguments.array[1], f_file_operation_identify_s, fll_error_file_type_directory_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (main->setting.state.status == F_false || main->setting.state.status == F_file_found_not) {
        existing = F_false;
      }
    }

    const f_string_t *function = 0;
    const f_string_static_t *operation = 0;
    f_string_static_t *file = 0;

    for (f_array_length_t i = 0; i < total; ++i) {

      fake_string_dynamic_reset(&main->cache_argument);

      main->setting.state.status = f_string_dynamic_append_nulless(main->cache_arguments.array[total], &main->cache_argument);

      if (F_status_is_error(main->setting.state.status)) {
        function = &macro_fake_f(f_string_dynamic_append_nulless);
        operation = &f_file_operation_process_s;
        file = &main->cache_arguments.array[i];

        break;
      }

      if (existing) {
        main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &main->cache_argument);

        if (F_status_is_error(main->setting.state.status)) {
          function = &macro_fake_f(f_string_dynamic_append_assure);
          operation = &f_file_operation_process_s;
          file = &main->cache_arguments.array[i];

          break;
        }

        main->setting.state.status = f_file_name_base(main->cache_arguments.array[i], &main->cache_argument);

        if (F_status_is_error(main->setting.state.status)) {
          function = &macro_fake_f(f_file_name_base);
          operation = &f_file_operation_process_s;
          file = &main->cache_arguments.array[i];

          return;
        }
      }

      main->cache_argument.string[main->cache_argument.used] = 0;

      main->setting.state.status = f_file_rename(main->cache_arguments.array[i], main->cache_argument);

      if (F_status_is_error(main->setting.state.status)) {
        function = &macro_fake_f(f_file_rename);
        operation = &f_file_operation_move_s;
        file = &main->cache_argument;

        break;
      }
    } // for

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, *function, *file, *operation, fll_error_file_type_path_e);

      main->setting.state.status = F_status_set_error(F_failure);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_type_move_

#ifndef _di_fake_make_operate_process_type_operate_
  int fake_make_operate_process_type_operate(fake_make_data_t * const data_make, f_array_lengths_t * const section_stack) {

    if (!data_make || !data_make->main) return 0;

    fake_main_t * const main = data_make->main;

    f_array_length_t id_section = 0;

    for (; id_section < data_make->fakefile.used; ++id_section) {

      if (f_compare_dynamic_partial_string(main->cache_arguments.array[0].string, main->buffer, main->cache_arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
        break;
      }
    } // for

    if (id_section == data_make->fakefile.used) return 0;

    const int result = fake_make_operate_section(data_make, id_section, section_stack);

    // Ensure that a break only happens within its active state_process->operation stack.
    if (main->setting.state.status == F_signal_abort) {
      main->setting.state.status = F_none;
    }
    else if (F_status_set_fine(main->setting.state.status) == F_signal_abort) {
      main->setting.state.status = F_status_set_error(F_failure);
    }

    return result;
  }
#endif // _di_fake_make_operate_process_type_operate_

#ifndef _di_fake_make_operate_process_type_owners_
  void fake_make_operate_process_type_owners(fake_make_data_t * const data_make, const bool all) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    uid_t id = 0;
    bool dereference = F_true;
    f_array_length_t i = 0;

    if (f_compare_dynamic(fake_make_operation_argument_no_dereference_s, main->cache_arguments.array[i]) == F_equal_to) {
      ++i;
      dereference = F_false;
    }

    id = (uid_t) fake_make_get_id(data_make, F_true, main->cache_arguments.array[i++]);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id));

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    for (; i < main->cache_arguments.used; ++i) {

      fake_make_assure_inside_project(data_make, main->cache_arguments.array[i]);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_operation_path_outside(&data_make->error, macro_fake_f(fake_make_assure_inside_project), main->cache_argument.used ? main->cache_argument : main->cache_arguments.array[i]);

        continue;
      }

      if (all) {
        main->setting.state.status = fll_file_role_change_all(main->cache_arguments.array[i], id, -1, dereference, fake_max_recursion_depth_d);
      }
      else {
        main->setting.state.status = f_file_role_change(main->cache_arguments.array[i], id, -1, dereference);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_file(&main->program.error, all ? macro_fake_f(fll_file_role_change_all) : macro_fake_f(f_file_role_change), main->cache_arguments.array[i], f_file_operation_change_owner_s, fll_error_file_type_file_e);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      fake_make_print_verbose_operate_set_role(&main->program.message, all ? 0x3 : 0x2, main->cache_arguments.array[i], (f_number_unsigned_t) id);
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_owners_

#ifndef _di_fake_make_operate_process_type_parameter_
  void fake_make_operate_process_type_parameter(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    bool found = F_false;
    f_array_length_t i = 0;

    for (; i < data_make->setting_make.parameter.used; ++i) {

      if (f_compare_dynamic(main->cache_arguments.array[0], data_make->setting_make.parameter.array[i].name) == F_equal_to) {
        found = F_true;

        break;
      }
    } // for

    if (found) {
      for (f_array_length_t j = 0; j < data_make->setting_make.parameter.array[i].value.size; ++j) {

        main->setting.state.status = f_string_dynamic_resize(0, &data_make->setting_make.parameter.array[i].value.array[j]);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_resize));

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      } // for

      if (data_make->setting_make.parameter.array[i].value.size) {
        main->setting.state.status = f_string_dynamics_resize(0, &data_make->setting_make.parameter.array[i].value);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_resize));

          main->setting.state.status = F_status_set_error(F_failure);
        }
      }
    }
    else {
      main->setting.state.status = f_string_map_multis_resize(fake_allocation_small_d, &data_make->setting_make.parameter);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_map_multis_resize));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      main->setting.state.status = f_string_dynamic_append_nulless(main->cache_arguments.array[0], &data_make->setting_make.parameter.array[data_make->setting_make.parameter.used].name);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      i = data_make->setting_make.parameter.used++;
    }

    data_make->setting_make.parameter.array[i].value.used = 0;

    if (main->cache_arguments.used > 1) {
      main->setting.state.status = f_string_dynamics_resize(main->cache_arguments.used - 1, &data_make->setting_make.parameter.array[i].value);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_resize));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      for (f_array_length_t j = 0; j < data_make->setting_make.parameter.array[i].value.size; ++j) {

        main->setting.state.status = f_string_dynamic_append_nulless(main->cache_arguments.array[j + 1], &data_make->setting_make.parameter.array[i].value.array[j]);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          main->setting.state.status = F_status_set_error(F_failure);
        }

        ++data_make->setting_make.parameter.array[i].value.used;
      } // for
    }

     main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_parameter_

#ifndef _di_fake_make_operate_process_type_pop_
  void fake_make_operate_process_type_pop(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    f_string_dynamic_t *argument = &data_make->path.stack.array[data_make->path.stack.used - 1];

    f_string_dynamic_resize(0, argument);

    --data_make->path.stack.used;

    main->setting.state.status = f_path_change(*argument);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_operation_path_stack_max(&data_make->error, macro_fake_f(f_path_change), *argument);

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
      fake_make_path_relative(data_make, *argument);

      // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fake_make_path_relative));

        fake_make_print_verbose_operate_set_path(&main->program.message, *argument);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      fake_make_print_verbose_operate_set_path(&main->program.message, main->cache_argument);
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_pop_

#ifndef _di_fake_make_operate_process_type_print_
  void fake_make_operate_process_type_print(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_string_dynamic_reset(&main->cache_1);

    {
      f_array_length_t i = 0;

      // Pre-allocate the cache to reduce allocations.
      {
        f_array_length_t total = main->cache_arguments.used;

        for (; i < main->cache_arguments.used; ++i) {
          total += main->cache_arguments.array[i].used;
        } // for

        main->setting.state.status = f_string_dynamic_increase_by(total, &main->cache_1);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_file_stream_open));

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }

      for (i = 0; i < main->cache_arguments.used; ++i) {

        if (i) {
          main->setting.state.status = f_string_dynamic_append(f_string_space_s, &main->cache_1);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

            main->setting.state.status = F_status_set_error(F_failure);

            return;
          }
        }

        fake_make_operate_process_buffer_escape(data_make, main->cache_arguments.array[i], &main->cache_1);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_file_stream_open));

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      } // for
    }

    f_file_stream_lock(main->program.message.to);

    fll_print_dynamic_raw(main->cache_1, main->program.message.to);
    fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);

    f_file_stream_unlock(main->program.message.to);

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_print_

#ifndef _di_fake_make_operate_process_type_skeleton_
  void fake_make_operate_process_type_skeleton(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_skeleton_operate(data_make->data);
    if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;

    fake_make_operate_process_return(data_make, F_status_is_error(main->setting.state.status) ? 1 : 0);
  }
#endif // _di_fake_make_operate_process_type_skeleton_

#ifndef _di_fake_make_operate_process_type_to_
  void fake_make_operate_process_type_to(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_make_assure_inside_project(data_make, main->cache_arguments.array[0]);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_operation_path_outside(&data_make->error, macro_fake_f(fake_make_assure_inside_project), main->cache_argument.used ? main->cache_argument : main->cache_arguments.array[0]);

      if (F_status_set_fine(main->setting.state.status) == F_false) {
        main->setting.state.status = F_status_set_error(F_failure);
      }

      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    main->setting.state.status = f_path_change(main->cache_arguments.array[0]);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_operation_path_stack_max(&data_make->error, macro_fake_f(f_path_change), main->cache_arguments.array[0]);
    }
    else {
      main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, &data_make->path.stack);

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_array_too_large) {
          fake_print_error_operation_path_stack_max(&data_make->error, macro_fake_f(f_string_dynamics_increase_by), fake_common_file_path_stack_s);

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }

        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      // Copy the entire real path, including the trailing NULL.
      ++main->cache_argument.used;

      main->setting.state.status = f_string_dynamic_append_nulless(main->cache_argument, &data_make->path.stack.array[data_make->path.stack.used]);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
        fake_make_path_relative(data_make, data_make->path.stack.array[data_make->path.stack.used]);

        // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(fake_make_path_relative));

          fake_make_print_verbose_operate_set_path(&main->program.message, data_make->path.stack.array[data_make->path.stack.used]);
        }
        else {
          fake_make_print_verbose_operate_set_path(&main->program.message, main->cache_argument);
        }
      }

      ++data_make->path.stack.used;
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_to_

#ifndef _di_fake_make_operate_process_type_top_
  void fake_make_operate_process_type_top(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    {
      main->setting.state.status = f_path_change_at(data_make->path.top.id);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error_operation_path_stack_max(&data_make->error, macro_fake_f(f_path_change), main->cache_arguments.array[0]);

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }
    }

    fake_make_print_verbose_operate_set_path(&main->program.message, f_string_empty_s);

    // Clear stack, except for the project root.
    for (f_array_length_t i = 1; i < data_make->path.stack.used; ++i) {
      f_string_dynamic_resize(0, &data_make->path.stack.array[i]);
    } // for

    data_make->path.stack.used = 1;

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_top_

#ifndef _di_fake_make_operate_process_type_touch_
  void fake_make_operate_process_type_touch(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->program.umask);

    for (f_array_length_t i = 1; i < main->cache_arguments.used; ++i) {

      if (f_compare_dynamic(fake_make_operation_argument_file_s, main->cache_arguments.array[0]) == F_equal_to) {
        main->setting.state.status = f_file_touch(main->cache_arguments.array[i], mode.regular, F_false);

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[i], &main->cache_argument))) {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_touch), main->cache_argument, f_file_operation_touch_s, fll_error_file_type_file_e);
          }
          else {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_touch), main->cache_arguments.array[i], f_file_operation_touch_s, fll_error_file_type_file_e);
          }

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }
      else if (f_compare_dynamic(fake_make_operation_argument_directory_s, main->cache_arguments.array[0]) == F_equal_to) {
        main->setting.state.status = f_directory_touch(main->cache_arguments.array[i], mode.directory);

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[i], &main->cache_argument))) {
            fake_print_error_file(&main->program.error, macro_fake_f(f_directory_touch), main->cache_argument, f_file_operation_touch_s, fll_error_file_type_directory_e);
          }
          else {
            fake_print_error_file(&main->program.error, macro_fake_f(f_directory_touch), main->cache_arguments.array[i], f_file_operation_touch_s, fll_error_file_type_directory_e);
          }

          main->setting.state.status = F_status_set_error(F_failure);

          return;
        }
      }

      fake_make_print_verbose_operate_touch(&main->program.message, main->cache_arguments.array[i]);
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_type_touch_

#ifndef _di_fake_make_operate_process_type_write_
  void fake_make_operate_process_type_write(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    f_file_t file = f_file_t_initialize;

    main->setting.state.status = f_file_exists(main->cache_arguments.array[0], F_true);

    if (main->cache_arguments.used == 1 || main->setting.state.status == F_false) {
      main->setting.state.status = f_file_stream_open(main->cache_arguments.array[0], f_file_open_mode_truncate_s, &file);

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[0], &main->cache_argument))) {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_open), main->cache_argument, f_file_operation_open_s, fll_error_file_type_file_e);
        }
        else {
          fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_open), main->cache_arguments.array[0], f_file_operation_open_s, fll_error_file_type_file_e);
        }

        main->setting.state.status = F_status_set_error(F_failure);

        return;
      }

      // Keep the stream open if there is a string to write to it.
      if (main->cache_arguments.used > 1) {
        main->setting.state.status = F_false;
      }
      else {
        main->setting.state.status = F_none;

        f_file_stream_flush(file);
        f_file_stream_close(&file);
      }
    }

    if (F_status_is_error_not(main->setting.state.status) && main->cache_arguments.used > 1) {
      if (main->setting.state.status != F_false) {
        main->setting.state.status = f_file_stream_open(main->cache_arguments.array[0], f_file_open_mode_append_s, &file);

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[0], &main->cache_argument))) {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_open), main->cache_argument, f_file_operation_open_s, fll_error_file_type_file_e);
          }
          else {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_open), main->cache_arguments.array[0], f_file_operation_open_s, fll_error_file_type_file_e);
          }
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        for (f_array_length_t i = 1; i < main->cache_arguments.used; ++i) {

          fake_string_dynamic_reset(&main->cache_1);

          fake_make_operate_process_buffer_escape(data_make, main->cache_arguments.array[i], &main->cache_1);

          if (F_status_is_error(main->setting.state.status)) {
            if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[0], &main->cache_argument))) {
              fake_print_error_file(&main->program.error, macro_fake_f(fake_make_operate_process_buffer_escape), main->cache_argument, f_file_operation_write_s, fll_error_file_type_file_e);
            }
            else {
              fake_print_error_file(&main->program.error, macro_fake_f(fake_make_operate_process_buffer_escape), main->cache_arguments.array[0], f_file_operation_write_s, fll_error_file_type_file_e);
            }

            break;
          }

          main->setting.state.status = f_file_stream_write(file, main->cache_1, 0);

          if (F_status_is_error(main->setting.state.status)) {
            if (F_status_is_error_not(fl_path_canonical(main->cache_arguments.array[0], &main->cache_argument))) {
              fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_write), main->cache_argument, f_file_operation_write_s, fll_error_file_type_file_e);
            }
            else {
              fake_print_error_file(&main->program.error, macro_fake_f(f_file_stream_write), main->cache_arguments.array[0], f_file_operation_write_s, fll_error_file_type_file_e);
            }

            break;
          }

          if (i + 1 < main->cache_arguments.used) {
            main->setting.state.status = f_file_stream_write(file, f_string_ascii_space_s, 0);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_file_stream_write));

              break;
            }
          }
        } // for
      }

      f_file_stream_flush(file);
      f_file_stream_close(&file);
    }

    main->setting.state.status = F_status_is_error(main->setting.state.status) ? F_status_set_error(F_failure) : F_none;
  }
#endif // _di_fake_make_operate_process_type_write_

#ifdef __cplusplus
} // extern "C"
#endif
