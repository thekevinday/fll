#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-operate.h"
#include "private-make-operate_process_type.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_type_copy_
  f_status_t fake_make_operate_process_type_copy(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool clone) {

    f_status_t status = F_none;
    f_status_t status_file = F_none;

    const f_array_length_t total = arguments.used - 1;
    f_array_length_t destination_length = 0;

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;
    f_mode_t mode = f_mode_t_initialize;

    if (clone) {
      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        recurse.output = data_make->main->output.to;
        recurse.verbose = fake_verbose_print_clone;
      }
    }
    else {
      macro_f_mode_t_set_default_umask(mode, data_make->main->umask);

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        recurse.output = data_make->main->output.to;
        recurse.verbose = fake_verbose_print_copy;
      }
    }

    bool existing = F_true;

    // In this case, the destination could be a file, so confirm this.
    if (arguments.used == 2) {
      status = f_directory_is(arguments.array[1].string);

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_is", F_true, arguments.array[1].string, "identify", fll_error_file_type_directory_e);

        return F_status_set_error(F_failure);
      }

      if (status == F_false || status == F_file_found_not) {
        existing = F_false;
      }
    }

    for (f_array_length_t i = 0; i < total; ++i) {

      destination_length = arguments.array[total].used;

      if (existing) {
        destination_length += arguments.array[i].used + 1;
      }

      char destination[destination_length + 1];

      memcpy(destination, arguments.array[total].string, arguments.array[total].used);

      if (existing) {
        memcpy(destination + arguments.array[total].used + 1, arguments.array[i].string, arguments.array[i].used);
        destination[arguments.array[total].used] = f_path_separator_s[0];
      }

      destination[destination_length] = 0;

      status_file = f_directory_is(arguments.array[i].string);

      if (status_file == F_true) {
        if (clone) {
          status_file = fl_directory_clone(arguments.array[i].string, destination, arguments.array[i].used, destination_length, F_true, recurse);
        }
        else {
          status_file = fl_directory_copy(arguments.array[i].string, destination, arguments.array[i].used, destination_length, mode, recurse);
        }

        if (F_status_is_error(status_file)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status_file), clone ? "fl_directory_clone" : "fl_directory_copy", F_true, arguments.array[i].string, clone ? "clone" : "copy", fll_error_file_type_directory_e);

          status = F_status_set_error(F_failure);
        }
      }
      else if (status_file == F_false) {
        if (clone) {
          status_file = f_file_clone(arguments.array[i].string, destination, F_true, recurse.size_block, recurse.exclusive);
        }
        else {
          status_file = f_file_copy(arguments.array[i].string, destination, mode, recurse.size_block, recurse.exclusive);
        }

        if (F_status_is_error(status_file)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status_file), clone ? "f_file_clone" : "f_file_copy", F_true, arguments.array[i].string, clone ? "clone" : "copy", fll_error_file_type_file_e);

          status = F_status_set_error(F_failure);
        }
        else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
          flockfile(data_make->main->output.to.stream);

          fl_print_format("%c%s '%[%Q%]' to '", data_make->main->output.to.stream, f_string_eol_s[0], clone ? "Cloned" : "Copied", data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable);
          fl_print_format("%[%S%]'.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, destination, data_make->main->context.set.notable, f_string_eol_s[0]);

          funlockfile(data_make->main->output.to.stream);
        }
      }
      else if (F_status_is_error(status_file)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[i].string, "identify", fll_error_file_type_directory_e);

        return F_status_set_error(F_failure);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_copy_

#ifndef _di_fake_make_operate_process_type_deletes_
  f_status_t fake_make_operate_process_type_deletes(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;

    const int recursion_max = all ? F_directory_descriptors_max_d : 0;
    struct stat file_stat;

    for (f_array_length_t i = 0; i < arguments.used; ++i) {

      memset(&file_stat, 0, sizeof(struct stat));

      status = f_file_stat(arguments.array[i].string, F_false, &file_stat);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_file_found_not) {
          if (data_make->main->warning.verbosity == f_console_verbosity_verbose_e) {
            flockfile(data_make->main->warning.to.stream);

            fl_print_format("%c%[%SThe file '%]", data_make->main->warning.to.stream, data_make->main->warning.prefix, f_string_eol_s[0]);
            fl_print_format("%[%Q%]", data_make->main->warning.to.stream, data_make->main->warning.notable, arguments.array[i], data_make->main->warning.notable);
            fl_print_format("%[' cannot be found.%]%c", data_make->main->warning.to.stream, f_string_eol_s[0]);

            funlockfile(data_make->main->warning.to.stream);
          }

          status = F_none;
        }
        else {
          fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_stat", F_true, arguments.array[i].string, "delete", fll_error_file_type_file_e);

          return status;
        }
      }
      else if (macro_f_file_type_is_directory(file_stat.st_mode)) {
        if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
          status = f_directory_remove_custom(arguments.array[i].string, recursion_max, F_false, fake_clean_remove_recursively_verbosely);
        }
        else {
          status = f_directory_remove(arguments.array[i].string, recursion_max, F_false);
        }

        if (F_status_set_fine(status) == F_file_found_not) {
          if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
            fll_print_format("%cThe directory '%[%Q%]' does not exist.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable, f_string_eol_s[0]);
          }

          status = F_none;
        }

        if (F_status_is_error(status)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_remove", F_true, arguments.array[i].string, "delete", fll_error_file_type_directory_e);

          return status;
        }
        else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
          fll_print_format("%cRemoved '%[%Q%]'.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable, f_string_eol_s[0]);
        }
      }
      else {
        status = f_file_remove(arguments.array[i].string);

        if (F_status_set_fine(status) == F_file_found_not) {
          if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
            fll_print_format("%cThe file '%[%Q%]' does not exist.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable, f_string_eol_s[0]);
          }

          status = F_none;
        }

        if (F_status_is_error(status)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_remove", F_true, arguments.array[i].string, "delete", fll_error_file_type_file_e);

          return status;
        }

        if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
          fll_print_format("%cRemoved '%[%Q%]'.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable, f_string_eol_s[0]);
        }
      }
    } // for

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_deletes_

#ifndef _di_fake_make_operate_process_type_fail_
  void fake_make_operate_process_type_fail(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    if (fl_string_dynamic_compare_string(fake_make_operation_argument_exit_s, arguments.array[0], fake_make_operation_argument_exit_s_length) == F_equal_to) {
      data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;
      data_make->error.prefix = fl_print_error_s;
      data_make->error.suffix = 0;
      data_make->error.context = data_make->main->context.set.error;
      data_make->error.notable = data_make->main->context.set.notable;
      data_make->error.to.stream = F_type_error_d;
      data_make->error.to.id = F_type_descriptor_error_d;
      data_make->error.set = &data_make->main->context.set;
    }
    else if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn_s, arguments.array[0], fake_make_operation_argument_warn_s_length) == F_equal_to) {
      data_make->setting_make.fail = fake_make_operation_fail_type_warn_e;
      data_make->error.prefix = fl_print_warning_s;
      data_make->error.suffix = 0;
      data_make->error.context = data_make->main->context.set.warning;
      data_make->error.notable = data_make->main->context.set.notable;
      data_make->error.to.stream = F_type_warning_d;
      data_make->error.to.id = F_type_descriptor_warning_d;
      data_make->error.set = &data_make->main->context.set;
    }
    else {
      data_make->setting_make.fail = fake_make_operation_fail_type_ignore_e;
      data_make->error.to.stream = 0;
      data_make->error.to.id = -1;
    }

    if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
      flockfile(data_make->main->output.to.stream);

      f_print_terminated("Set failure state to '", data_make->main->output.to.stream);

      if (data_make->setting_make.fail == fake_make_operation_fail_type_exit_e) {
        fl_print_format("%[%s%]", data_make->main->output.to.stream, data_make->main->context.set.notable, fake_make_operation_argument_exit_s, data_make->main->context.set.notable);
      }
      else if (data_make->setting_make.fail == fake_make_operation_fail_type_warn_e) {
        fl_print_format("%[%s%]", data_make->main->output.to.stream, data_make->main->context.set.notable, fake_make_operation_argument_warn_s, data_make->main->context.set.notable);
      }
      else {
        fl_print_format("%[%s%]", data_make->main->output.to.stream, data_make->main->context.set.notable, fake_make_operation_argument_ignore_s, data_make->main->context.set.notable);
      }

      fl_print_format("'.%c", data_make->main->output.to.stream, f_string_eol_s[0]);

      funlockfile(data_make->main->output.to.stream);
    }
  }
#endif // _di_fake_make_operate_process_type_fail_

#ifndef _di_fake_make_operate_process_type_groups_
  f_status_t fake_make_operate_process_type_groups(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;
    f_status_t status_file = F_none;

    gid_t id = 0;

    status = fake_make_get_id_group(data_make->main, data_make->error, arguments.array[0], &id);
    if (F_status_is_error(status)) return 0;

    for (f_array_length_t i = 1; i < arguments.used; ++i) {

      status_file = fake_make_assure_inside_project(data_make, arguments.array[i]);

      if (F_status_is_error(status_file)) {
        status = status_file;

        fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

        continue;
      }

      if (all) {
        status_file = fll_file_role_change_all(arguments.array[i].string, -1, id, F_false, fake_make_operation_recursion_depth_max_d);
      }
      else {
        status_file = f_file_role_change(arguments.array[i].string, -1, id, F_false);
      }

      if (F_status_is_error(status_file)) {
        status = status_file;

        fll_error_file_print(data_make->error, F_status_set_fine(status), all ? "fll_file_role_change_all" : "f_file_role_change", F_true, arguments.array[i].string, "change group of", fll_error_file_type_file_e);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        flockfile(data_make->main->output.to.stream);

        fl_print_format("%s group of '%[%s%]", data_make->main->output.to.stream, all ? "Recursively changed" : "Changed", data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable);
        fl_print_format("' to %[%ul%].%c", data_make->main->output.to.stream, data_make->main->context.set.notable, id, data_make->main->context.set.notable, f_string_eol_s[0]);

        funlockfile(data_make->main->output.to.stream);
      }
    } // for

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_groups_

#ifndef _di_fake_make_operate_process_type_if_defined_
  void fake_make_operate_process_type_if_defined(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    const f_string_static_t argument = if_not ? arguments.array[2] : arguments.array[1];

    const f_string_t reserved_name[] = {
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

    const f_array_length_t reserved_length[] = {
      fake_make_parameter_variable_build_s_length,
      fake_make_parameter_variable_color_s_length,
      fake_make_parameter_variable_data_s_length,
      fake_make_parameter_variable_define_s_length,
      fake_make_parameter_variable_fakefile_s_length,
      fake_make_parameter_variable_mode_s_length,
      fake_make_parameter_variable_process_s_length,
      fake_make_parameter_variable_settings_s_length,
      fake_make_parameter_variable_sources_s_length,
      fake_make_parameter_variable_verbosity_s_length,
      fake_make_parameter_variable_work_s_length,
      fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_value_s_length,
    };

    const bool reserved_defined[] = {
      data_make->main->path_build.used,
      F_true,
      data_make->main->path_data.used,
      data_make->main->define.used,
      data_make->main->fakefile.used,
      data_make->main->mode.used,
      data_make->main->process.used,
      data_make->main->settings.used,
      data_make->main->path_sources.used,
      F_true,
      data_make->main->path_work.used,
      data_make->main->parameters[fake_parameter_path_build_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_light_e].result == f_console_result_found_e || data_make->main->parameters[fake_parameter_dark_e].result == f_console_result_found_e || data_make->main->parameters[fake_parameter_no_color_e].result == f_console_result_found_e,
      data_make->main->parameters[fake_parameter_path_data_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_define_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_fakefile_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_mode_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_process_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_settings_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_path_sources_e].result == f_console_result_additional_e,
      data_make->main->parameters[fake_parameter_verbosity_quiet_e].result == f_console_result_found_e || data_make->main->parameters[fake_parameter_verbosity_normal_e].result == f_console_result_found_e || data_make->main->parameters[fake_parameter_verbosity_verbose_e].result == f_console_result_found_e || data_make->main->parameters[fake_parameter_verbosity_debug_e].result == f_console_result_found_e,
      data_make->main->parameters[fake_parameter_path_work_e].result == f_console_result_additional_e,
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

    if (fl_string_dynamic_compare_string(fake_make_operation_argument_environment_s, argument, fake_make_operation_argument_environment_s_length) == F_equal_to) {
      state_process->condition_result = fake_condition_result_true_e;

      if (if_not) {
        for (f_array_length_t i = 3; i < arguments.used; ++i) {

          if (f_environment_exists(arguments.array[i].string) == F_true) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        } // for
      }
      else {
        for (f_array_length_t i = 2; i < arguments.used; ++i) {

          if (f_environment_exists(arguments.array[i].string) != F_true) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        } // for
      }

      return;
    }

    f_array_length_t i = if_not ? 3 : 2;
    f_array_length_t j = 0;

    // 0 = unknown, 1 = fail, 2 = pass.
    uint8_t result = 0;

    state_process->condition_result = fake_condition_result_true_e;

    // Multiple properties may pass and so if any of them fail, then they all fail.
    for (; i < arguments.used; ++i) {

      for (j = 0; j < 33; ++j) {

        if (fl_string_dynamic_compare_string(reserved_name[j], arguments.array[i], reserved_length[j]) == F_equal_to) {
          result = reserved_defined[j] ? 2 : 1;

          break;
        }
      } // for

      if (!result) {
        for (j = 0; j < data_make->setting_make.parameter.used; ++j) {

          if (fl_string_dynamic_compare(arguments.array[i], data_make->setting_make.parameter.array[j].name) == F_equal_to) {
            result = 2;

            break;
          }
        } // for
      }

      if (result < 2) {
        result = 1;

        break;
      }

      if (i + 1 < arguments.used) {
        result = 0;
      }
    } // for

    if (if_not) {
      if (result < 2) {
        state_process->condition_result = fake_condition_result_true_e;
      }
      else {
        state_process->condition_result = fake_condition_result_false_e;
      }
    }
    else if (result < 2) {
      state_process->condition_result = fake_condition_result_false_e;
    }
  }
#endif // _di_fake_make_operate_process_type_if_defined_

#ifndef _di_fake_make_operate_process_type_if_exists_
  f_status_t fake_make_operate_process_type_if_exists(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    f_status_t status = F_none;

    state_process->condition_result = fake_condition_result_true_e;

    for (f_array_length_t i = if_not ? 2 : 1; i < arguments.used; ++i) {

      status = f_file_exists(arguments.array[i].string);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_exists", F_true, arguments.array[i].string, "find", fll_error_file_type_file_e);

        break;
      }

      if (if_not) {
        if (status == F_true) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
      else {
        if (status == F_false) {
          state_process->condition_result = fake_condition_result_false_e;

          break;
        }
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_exists_

#ifndef _di_fake_make_operate_process_type_if_is_
  f_status_t fake_make_operate_process_type_if_is(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    f_status_t status = F_none;

    // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
    // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
    // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
    // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
    uint8_t type = 0;

    f_array_length_t i = if_not ? 2 : 1;

    status = F_none;

    for (; i < arguments.used; ++i) {

      if (fl_string_dynamic_compare_string(fake_make_operation_argument_if_is_for_s, arguments.array[i], fake_make_operation_argument_if_is_for_s_length) == F_equal_to) {
        ++i;

        break;
      }

      if (fl_string_dynamic_compare_string(F_file_type_name_block_s, arguments.array[i], F_file_type_name_block_s_length) == F_equal_to) {
        type |= 0x1;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_character_s, arguments.array[i], F_file_type_name_character_s_length) == F_equal_to) {
        type |= 0x2;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_directory_s, arguments.array[i], F_file_type_name_directory_s_length) == F_equal_to) {
        type |= 0x4;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_fifo_s, arguments.array[i], F_file_type_name_fifo_s_length) == F_equal_to) {
        type |= 0x8;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_link_s, arguments.array[i], F_file_type_name_link_s_length) == F_equal_to) {
        type |= 0x10;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_regular_s, arguments.array[i], F_file_type_name_regular_s_length) == F_equal_to) {
        type |= 0x20;
      }
      else if (fl_string_dynamic_compare_string(F_file_type_name_socket_s, arguments.array[i], F_file_type_name_socket_s_length) == F_equal_to) {
        type |= 0x40;
      }
    } // for

    uint8_t type_file = 0;
    mode_t mode_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (; i < arguments.used; ++i, mode_file = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "get type of", fll_error_file_type_file_e);

        break;
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

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_is_

#ifndef _di_fake_make_operate_process_type_if_greater_if_lesser_
  f_status_t fake_make_operate_process_type_if_greater_if_lesser(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, fake_state_process_t *state_process) {

    f_status_t status = F_none;

    f_string_range_t range = f_string_range_t_initialize;
    f_number_unsigned_t number_left = 0;
    f_number_unsigned_t number_right = 0;

    bool is_negative_left = F_false;
    bool is_negative_right = F_false;

    f_array_length_t i = 1;

    state_process->condition_result = fake_condition_result_true_e;

    // @fixme This needs to handle converting numbers with decimals (like 1.01), perhaps operate on them as strings or provide a special processor.
    range.start = 0;
    range.stop = arguments.array[i].used - 1;

    if (arguments.array[i].string[0] == '+') {
      range.start = 1;
    }
    else if (arguments.array[i].string[0] == '-') {
      range.start = 1;
      is_negative_left = F_true;
    }

    if (range.start > range.stop) {
      status = F_status_set_error(F_failure);
    }
    else {
      status = fl_conversion_string_to_number_unsigned(arguments.array[i].string, range, &number_left);
    }

    if (F_status_is_error_not(status)) {
      for (i = 2; i < arguments.used; ++i, status = F_none, number_left = number_right, is_negative_left = is_negative_right) {

        if (arguments.array[i].used) {
          range.start = 0;
          range.stop = arguments.array[i].used - 1;

          is_negative_right = F_false;

          if (arguments.array[i].string[0] == '+') {
            range.start = 1;
          }
          else if (arguments.array[i].string[0] == '-') {
            range.start = 1;
            is_negative_right = F_true;
          }

          if (range.start > range.stop) {
            status = F_status_set_error(F_failure);
          }
          else {
            status = fl_conversion_string_to_number_unsigned(arguments.array[i].string, range, &number_right);
          }
        }
        else {
          status = F_status_set_error(F_failure);
        }

        if (F_status_is_error(status)) break;

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

    if (F_status_is_error(status)) {
      state_process->condition_result = fake_condition_result_error_e;

      if (data_make->main->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        if ((i == 1 && number_left > F_number_t_size_unsigned_d) || (i > 1 && number_right > F_number_t_size_unsigned_d)) {
          fl_print_format("%c%[%SThe number '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
          fl_print_format("%[' may only be between the ranges -%un to %un.%]%c", data_make->error.to.stream, data_make->error.context, F_number_t_size_unsigned_d, F_number_t_size_unsigned_d, data_make->error.context, f_string_eol_s[0]);
        }
        else {
          fl_print_format("%c%[%SInvalid or unsupported number provided '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
          fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, F_number_t_size_unsigned_d, F_number_t_size_unsigned_d, data_make->error.context, f_string_eol_s[0]);
        }

        funlockfile(data_make->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_greater_if_lesser_

#ifndef _di_fake_make_operate_process_type_if_group_
  f_status_t fake_make_operate_process_type_if_group(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_group(data_make->main, data_make->error, arguments.array[if_not ? 2 : 1], &id);
    if (F_status_is_error(status)) return status;

    uid_t id_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (f_array_length_t i = if_not ? 3 : 2; i < arguments.used; ++i, id_file = 0) {

      status = f_file_group_read(arguments.array[i].string, &id_file);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_group_read", F_true, arguments.array[i].string, "get group of", fll_error_file_type_file_e);

        break;
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

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_group_

#ifndef _di_fake_make_operate_process_type_if_mode_
  f_status_t fake_make_operate_process_type_if_mode(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    f_status_t status = F_none;
    f_file_mode_t mode_rule = 0;
    mode_t mode_match = 0;
    bool is = F_false;

    if (fl_string_dynamic_compare_string(fake_make_operation_argument_is_s, arguments.array[if_not ? 2 : 1], fake_make_operation_argument_is_s_length) == F_equal_to) {
      is = F_true;
    }

    {
      uint8_t mode_replace = 0;

      status = fake_make_get_id_mode(data_make->main, data_make->error, arguments.array[if_not ? 3 : 2], &mode_rule, &mode_replace);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        return status;
      }

      status = f_file_mode_to_mode(mode_rule, &mode_match);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_print(data_make->error, F_status_set_fine(status), "f_file_mode_to_mode", F_true);

        return status;
      }
    }

    mode_t mode_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (f_array_length_t i = if_not ? 4 : 3; i < arguments.used; ++i, mode_file = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "get mode of", fll_error_file_type_file_e);

        break;
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

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_mode_

#ifndef _di_fake_make_operate_process_type_if_owner_
  f_status_t fake_make_operate_process_type_if_owner(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool if_not, fake_state_process_t *state_process) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_owner(data_make->main, data_make->error, arguments.array[if_not ? 2 : 1], &id);
    if (F_status_is_error(status)) return status;

    uid_t id_file = 0;

    state_process->condition_result = fake_condition_result_true_e;

    for (f_array_length_t i = if_not ? 3 : 2; i < arguments.used; ++i, id_file = 0) {

      status = f_file_owner_read(arguments.array[i].string, &id_file);

      if (F_status_is_error(status)) {
        state_process->condition_result = fake_condition_result_error_e;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_owner_read", F_true, arguments.array[i].string, "get owner of", fll_error_file_type_file_e);

        break;
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

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_owner_

#ifndef _di_fake_make_operate_process_type_modes_
  f_status_t fake_make_operate_process_type_modes(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;

    f_file_mode_t mode_rule = 0;
    uint8_t replace = 0;

    status = fake_make_get_id_mode(data_make->main, data_make->error, arguments.array[0], &mode_rule, &replace);
    if (F_status_is_error(status)) return 0;

    mode_t mode = 0;
    mode_t mode_file = 0;

    for (f_array_length_t i = 1; i < arguments.used; ++i, mode = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file_e);

        break;
      }

      status = f_file_mode_determine(mode_file, mode_rule, replace, macro_f_file_type_is_directory(mode_file), &mode);

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_determine", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file_e);

        break;
      }

      if (all) {
        status = fll_file_mode_set_all(arguments.array[i].string, mode, fake_make_operation_recursion_depth_max_d);
      }
      else {
        status = f_file_mode_set(arguments.array[i].string, mode);
      }

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), all ? "fll_file_mode_set_all" : "f_file_mode_set", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file_e);

        break;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("Changed mode of '%Q' to %#@u.%c", data_make->main->output.to.stream, arguments.array[i], mode, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_modes_

#ifndef _di_fake_make_operate_process_type_move_
  f_status_t fake_make_operate_process_type_move(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;
    f_status_t status_file = F_none;

    const f_array_length_t total = arguments.used -1;

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;

    f_array_length_t destination_length = 0;

    if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
      recurse.output = data_make->main->output.to;
      recurse.verbose = fake_verbose_print_move;
    }

    bool existing = F_true;

    // In this case, the destination could be a file, so confirm this.
    if (arguments.used == 2) {
      status_file = f_directory_is(arguments.array[1].string);

      if (F_status_is_error(status_file)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_is", F_true, arguments.array[1].string, "identify", fll_error_file_type_directory_e);

        return F_status_set_error(F_failure);
      }

      if (status_file == F_false || status_file == F_file_found_not) {
        existing = F_false;
      }
    }

    for (f_array_length_t i = 0; i < total; ++i) {

      destination_length = arguments.array[total].used;

      if (existing) {
        destination_length += arguments.array[i].used + 1;
      }

      char destination[destination_length + 1];

      memcpy(destination, arguments.array[total].string, arguments.array[total].used);

      if (existing) {
        memcpy(destination + arguments.array[total].used + 1, arguments.array[i].string, arguments.array[i].used);
        destination[arguments.array[total].used] = f_path_separator_s[0];
      }

      destination[destination_length] = 0;

      status_file = fll_file_move(arguments.array[i].string, destination, arguments.array[i].used, destination_length, recurse);

      if (F_status_is_error(status_file)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "fll_file_move", F_true, arguments.array[i].string, "move", fll_error_file_type_directory_e);

        status = F_status_set_error(F_failure);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_move_

#ifndef _di_fake_make_operate_process_type_owners_
  f_status_t fake_make_operate_process_type_owners(fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_owner(data_make->main, data_make->error, arguments.array[0], &id);
    if (F_status_is_error(status)) return status;

    f_status_t status_file = F_none;

    for (f_array_length_t i = 1; i < arguments.used; ++i) {

      status_file = fake_make_assure_inside_project(data_make, arguments.array[i]);

      if (F_status_is_error(status_file)) {
        status = status_file;

        fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

        continue;
      }

      if (all) {
        status_file = fll_file_role_change_all(arguments.array[i].string, id, -1, F_false, fake_make_operation_recursion_depth_max_d);
      }
      else {
        status_file = f_file_role_change(arguments.array[i].string, id, -1, F_false);
      }

      if (F_status_is_error(status_file)) {
        status = status_file;

        fll_error_file_print(data_make->error, F_status_set_fine(status), all ? "fll_file_role_change_all" : "f_file_role_change", F_true, arguments.array[i].string, "change owner of", fll_error_file_type_file_e);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("%s owner of '%Q' to %u.%c", data_make->main->output.to.stream, all ? "Recursively changed" : "Changed", arguments.array[i], id, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_owners_

#ifndef _di_fake_make_operate_process_type_parameter_
  f_status_t fake_make_operate_process_type_parameter(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    bool found = F_false;
    f_array_length_t i = 0;

    for (; i < data_make->setting_make.parameter.used; ++i) {

      if (fl_string_dynamic_compare(arguments.array[0], data_make->setting_make.parameter.array[i].name) == F_equal_to) {
        found = F_true;

        break;
      }
    } // for

    if (found) {
      for (f_array_length_t j = 0; j < data_make->setting_make.parameter.array[i].value.size; ++j) {

        status = f_string_dynamic_resize(0, &data_make->setting_make.parameter.array[i].value.array[j]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true);

          return status;
        }
      } // for

      if (data_make->setting_make.parameter.array[i].value.size) {
        status = f_string_dynamics_resize(0, &data_make->setting_make.parameter.array[i].value);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamics_resize", F_true);

          return status;
        }
      }
    }
    else {
      status = f_string_map_multis_resize(F_memory_default_allocation_small_d, &data_make->setting_make.parameter);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_map_multis_resize", F_true);

        return status;
      }

      status = f_string_dynamic_append(arguments.array[0], &data_make->setting_make.parameter.array[data_make->setting_make.parameter.used].name);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

        return status;
      }

      status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[data_make->setting_make.parameter.used].name);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

        return status;
      }

      i = data_make->setting_make.parameter.used++;
    }

    data_make->setting_make.parameter.array[i].value.used = 0;

    if (arguments.used > 1) {
      status = f_string_dynamics_resize(arguments.used - 1, &data_make->setting_make.parameter.array[i].value);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamics_resize", F_true);

        return status;
      }

      for (f_array_length_t j = 0; j < data_make->setting_make.parameter.array[i].value.size; ++j) {

        status = f_string_dynamic_append(arguments.array[j + 1], &data_make->setting_make.parameter.array[i].value.array[j]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

          return status;
        }

        ++data_make->setting_make.parameter.array[i].value.used;
      } // for
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_parameter_

#ifndef _di_fake_make_operate_process_type_pop_
  f_status_t fake_make_operate_process_type_pop(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    f_string_dynamic_resize(0, &data_make->path.stack.array[data_make->path.stack.used - 1]);

    --data_make->path.stack.used;

    status = f_path_change(data_make->path.stack.array[data_make->path.stack.used - 1].string);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_stack_max(data_make->main, data_make->error, F_status_set_fine(status), "f_path_change", data_make->path.stack.array[data_make->path.stack.used - 1].string);

      return 0;
    }

    if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
      status = fake_make_path_relative(data_make, data_make->path.stack.array[data_make->path.stack.used - 1]);

      // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "fake_make_path_relative", F_true);
        fll_print_format("Changed to project path '%[%Q%]'.%c", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->path.stack.array[data_make->path.stack.used - 1], data_make->main->context.set.notable, f_string_eol_s[0]);
      }
      else {
        fll_print_format("Changed to project path '%[%Q%]'.%c", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->path_cache, data_make->main->context.set.notable, f_string_eol_s[0]);
      }
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_pop_

#ifndef _di_fake_make_operate_process_type_to_
  f_status_t fake_make_operate_process_type_to(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    status = fake_make_assure_inside_project(data_make, arguments.array[0]);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string);

      if (F_status_set_fine(status) == F_false) {
        status = F_status_set_error(F_failure);
      }

      return status;
    }

    status = f_path_change(arguments.array[0].string);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_stack_max(data_make->main, data_make->error, F_status_set_fine(status), "f_path_change", arguments.array[0].string);
    }
    else {
      status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, &data_make->path.stack);

      if (F_status_set_fine(status) == F_array_too_large) {
        fake_print_message_section_operation_path_stack_max(data_make->main, data_make->error, F_array_too_large, "f_string_dynamics_increase_by", "path stack");

        return status;
      }

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "macro_f_string_dynamics_t_resize", F_true);

        return status;
      }

      // Copy the entire real path, including the trailing NULL.
      ++data_make->path_cache.used;

      status = f_string_dynamic_append(data_make->path_cache, &data_make->path.stack.array[data_make->path.stack.used]);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

        return status;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        status = fake_make_path_relative(data_make, data_make->path.stack.array[data_make->path.stack.used]);

        // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "fake_make_path_relative", F_true);
          fll_print_format("Changed to project path '%[%Q%]'.%c", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->path.stack.array[data_make->path.stack.used], data_make->main->context.set.notable, f_string_eol_s[0]);
        }
        else {
          fll_print_format("Changed to project path '%[%Q%]'.%c", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->path_cache, data_make->main->context.set.notable, f_string_eol_s[0]);
        }
      }

      ++data_make->path.stack.used;
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_to_

#ifndef _di_fake_make_operate_process_type_top_
  f_status_t fake_make_operate_process_type_top(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    {
      f_status_t status = F_none;

      status = f_path_change_at(data_make->path.top.id);

      if (F_status_is_error(status)) {
        fake_print_message_section_operation_path_stack_max(data_make->main, data_make->error, F_status_set_fine(status), "f_path_change", arguments.array[0].string);

        return status;
      }
    }

    if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
      fll_print_format("Changed to project path ''.%c", data_make->main->output.to.stream, f_string_eol_s[0]);
    }

    // Clear stack, except for the project root.
    for (f_array_length_t i = 1; i < data_make->path.stack.used; ++i) {
      f_string_dynamic_resize(0, &data_make->path.stack.array[i]);
    } // for

    data_make->path.stack.used = 1;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_top_

#ifndef _di_fake_make_operate_process_type_touch_
  f_status_t fake_make_operate_process_type_touch(fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, data_make->main->umask);

    for (f_array_length_t i = 1; i < arguments.used; ++i) {

      if (fl_string_dynamic_compare_string(fake_make_operation_argument_file_s, arguments.array[0], fake_make_operation_argument_file_s_length) == F_equal_to) {
        status = f_file_touch(arguments.array[i].string, mode.regular, F_false);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_touch", F_true, data_make->path_cache.string, "touch", fll_error_file_type_file_e);
          }
          else {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_touch", F_true, arguments.array[i].string, "touch", fll_error_file_type_file_e);
          }

          break;
        }
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory_s, arguments.array[0], fake_make_operation_argument_directory_s_length) == F_equal_to) {
        status = f_directory_touch(arguments.array[i].string, mode.directory);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_touch", F_true, data_make->path_cache.string, "touch", fll_error_file_type_directory_e);
          }
          else {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_touch", F_true, arguments.array[i].string, "touch", fll_error_file_type_directory_e);
          }

          break;
        }
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("Touched '%[%Q%]'.%c", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.array[i], data_make->main->context.set.notable, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_touch_

#ifdef __cplusplus
} // extern "C"
#endif
