#include "fake.h"
#include "private-common.h"
#include "private-make.h"
#include "private-make-operate_validate.h"
#include "private-make-operate_validate_type.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_validate_type_break_
  f_status_t fake_make_operate_validate_type_break(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used) {
      if (fl_string_dynamic_compare(fake_make_operation_argument_success_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_failure_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {

          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QUnsupported break type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      }
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_break_

#ifndef _di_fake_make_operate_validate_type_build_
  f_status_t fake_make_operate_validate_type_build(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      if (data_make->cache_arguments.array[0].used) {
        f_string_static_t path_file = f_string_static_t_initialize;
        path_file.used = data_make->data->path_data_build.used + data_make->cache_arguments.array[0].used;

        f_char_t path_file_string[path_file.used + 1];
        path_file.string = path_file_string;
        path_file_string[path_file.used] = 0;

        memcpy(path_file_string, data_make->data->path_data_build.string, sizeof(f_char_t) * data_make->data->path_data_build.used);
        memcpy(path_file_string + data_make->data->path_data_build.used, data_make->cache_arguments.array[0].string, sizeof(f_char_t) * data_make->cache_arguments.array[0].used);

        const f_status_t status = f_file_is(path_file, F_file_type_regular_d, F_false);

        if (status == F_file_found_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        if (F_status_is_error(status)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_is", F_true, path_file, f_file_operation_find_s, fll_error_file_type_file_e);

          return F_status_set_error(F_failure);
        }

        if (!status) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
            fl_print_format("%[' must be a regular file.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          fll_print_format("%r%[QFilename argument must not be an empty string.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
        }

        return F_status_set_error(F_failure);
      }
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_build_

#ifndef _di_fake_make_operate_validate_type_clean_top_skeleton_
  f_status_t fake_make_operate_validate_type_clean_top_skeleton(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_clean_top_skeleton_

#ifndef _di_fake_make_operate_validate_type_clone_
  f_status_t fake_make_operate_validate_type_clone(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      f_status_t status = F_none;
      f_status_t status_file = F_none;

      for (f_array_length_t i = 0; i < data_make->cache_arguments.used; ++i) {

        status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

        if (F_status_is_error(status_file)) {
          fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

          status = F_status_set_error(F_failure);
        }
      } // for

      for (f_array_length_t i = 0; i < data_make->cache_arguments.used - 1; ++i) {

        if (f_file_exists(data_make->cache_arguments.array[i], F_true) != F_true) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          status = F_status_set_error(F_failure);
        }
      } // for

      if (data_make->cache_arguments.used > 2) {

        // The last file must be a directory.
        status_file = f_directory_is(data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

        if (status_file == F_false || status_file == F_file_found_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe last file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], data_make->error.notable);
            fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          status = F_status_set_error(F_failure);
        }

        if (F_status_is_error(status_file)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], f_file_operation_find_s, fll_error_file_type_directory_e);

          status = F_status_set_error(F_failure);
        }
      }
      else {

        // When the first file is a directory, then the second, if it exists, must also be a directory.
        status_file = f_directory_is(data_make->cache_arguments.array[0]);

        if (status_file == F_true) {
          status_file = f_directory_is(data_make->cache_arguments.array[1]);

          if (status_file == F_false) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%r%[%QThe second file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

              funlockfile(data_make->error.to.stream);
            }

            status = F_status_set_error(F_failure);
          }
        }
      }

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_clone_

#ifndef _di_fake_make_operate_validate_type_compile_
  f_status_t fake_make_operate_validate_type_compile(fake_make_data_t * const data_make) {

    if (!data_make->cache_arguments.used) {
      fake_print_error_requires_more_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->setting_build.build_compiler.used) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QNo compiler has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_compile_s, data_make->error.notable);
        fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_compile_

#ifndef _di_fake_make_operate_validate_type_condition_
  f_status_t fake_make_operate_validate_type_condition(fake_make_data_t * const data_make, fake_state_process_t * const state_process) {

    if (state_process->operation == fake_make_operation_type_if_e) {
      if (state_process->operation_previous == fake_make_operation_type_if_e) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%r%[%QMust not be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
          fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
          fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

          funlockfile(data_make->error.to.stream);
        }

        return F_status_set_error(F_failure);
      }
    }
    else {
      if (!(state_process->operation_previous == fake_make_operation_type_if_e || state_process->operation_previous == fake_make_operation_type_and_e || state_process->operation_previous == fake_make_operation_type_or_e)) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%r%[%QMay only be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
          fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
          fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

          funlockfile(data_make->error.to.stream);
        }

        return F_status_set_error(F_failure);
      }
    }

    if (data_make->cache_arguments.used) {
      const f_string_static_t if_type_strings[] = {
        fake_make_operation_argument_if_define_s,
        fake_make_operation_argument_if_equal_s,
        fake_make_operation_argument_if_equal_not_s,
        fake_make_operation_argument_if_exist_s,
        fake_make_operation_argument_if_failure_s,
        fake_make_operation_argument_if_greater_s,
        fake_make_operation_argument_if_greater_equal_s,
        fake_make_operation_argument_if_group_s,
        fake_make_operation_argument_if_is_s,
        fake_make_operation_argument_if_less_s,
        fake_make_operation_argument_if_less_equal_s,
        fake_make_operation_argument_if_mode_s,
        fake_make_operation_argument_if_not_s,
        fake_make_operation_argument_if_define_s,    // If not define, represented by just "define".
        fake_make_operation_argument_if_exist_s,     // If not exist, represented by just "exist".
        fake_make_operation_argument_if_group_s,     // If not group, represented by just "group".
        fake_make_operation_argument_if_is_s,        // If not is, represented by just "is".
        fake_make_operation_argument_if_mode_s,      // If not mode, represented by just "mode".
        fake_make_operation_argument_if_owner_s,     // If not owner, represented by just "owner".
        fake_make_operation_argument_if_parameter_s, // If not parameter, represented by just "parameter".
        fake_make_operation_argument_if_owner_s,
        fake_make_operation_argument_if_parameter_s,
        fake_make_operation_argument_if_success_s,
      };

      const uint8_t if_type_codes[] = {
        fake_make_operation_if_type_if_define_e,
        fake_make_operation_if_type_if_equal_e,
        fake_make_operation_if_type_if_equal_not_e,
        fake_make_operation_if_type_if_exist_e,
        fake_make_operation_if_type_if_failure_e,
        fake_make_operation_if_type_if_greater_e,
        fake_make_operation_if_type_if_greater_equal_e,
        fake_make_operation_if_type_if_group_e,
        fake_make_operation_if_type_if_is_e,
        fake_make_operation_if_type_if_less_e,
        fake_make_operation_if_type_if_less_equal_e,
        fake_make_operation_if_type_if_mode_e,
        fake_make_operation_if_type_if_not_e,
        fake_make_operation_if_type_if_not_define_e,
        fake_make_operation_if_type_if_not_exist_e,
        fake_make_operation_if_type_if_not_group_e,
        fake_make_operation_if_type_if_not_is_e,
        fake_make_operation_if_type_if_not_mode_e,
        fake_make_operation_if_type_if_not_owner_e,
        fake_make_operation_if_type_if_not_parameter_e,
        fake_make_operation_if_type_if_owner_e,
        fake_make_operation_if_type_if_parameter_e,
        fake_make_operation_if_type_if_success_e,
      };

      const f_string_static_t if_not_type_strings[] = {
        fake_make_operation_argument_if_define_s,
        fake_make_operation_argument_if_exist_s,
        fake_make_operation_argument_if_group_s,
        fake_make_operation_argument_if_is_s,
        fake_make_operation_argument_if_mode_s,
        fake_make_operation_argument_if_owner_s,
        fake_make_operation_argument_if_parameter_s,
      };

      const uint8_t if_not_type_codes[] = {
        fake_make_operation_if_type_if_not_define_e,
        fake_make_operation_if_type_if_not_exist_e,
        fake_make_operation_if_type_if_not_group_e,
        fake_make_operation_if_type_if_not_is_e,
        fake_make_operation_if_type_if_not_mode_e,
        fake_make_operation_if_type_if_not_owner_e,
        fake_make_operation_if_type_if_not_parameter_e,
      };

      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_string_static_t if_and_or;
      bool dereference = F_true;

      if (state_process->operation == fake_make_operation_type_and_e) {
        if_and_or = fake_make_operation_and_s;
      }
      else if (state_process->operation == fake_make_operation_type_or_e) {
        if_and_or = fake_make_operation_or_s;
      }
      else {
        if_and_or = fake_make_operation_if_s;
      }

      if (fl_string_dynamic_compare(fake_make_operation_argument_no_dereference_s, data_make->cache_arguments.array[k]) == F_equal_to) {
        ++k;
        dereference = F_false;
      }

      const uint8_t if_type_minimum[] = {
        dereference ? 3 : 4, // If define.
        dereference ? 2 : 3, // If equal (==).
        dereference ? 2 : 3, // If equal not (<>).
        dereference ? 2 : 3, // If exist.
        dereference ? 1 : 2, // If failure.
        dereference ? 2 : 3, // If greater (>).
        dereference ? 2 : 3, // If greater equal (>=).
        dereference ? 3 : 4, // If group.
        dereference ? 3 : 4, // If is.
        dereference ? 2 : 3, // If less (<).
        dereference ? 2 : 3, // If less equal (<=).
        dereference ? 4 : 5, // If mode.
        dereference ? 3 : 4, // If not.
        dereference ? 5 : 6, // If not define.
        dereference ? 3 : 4, // If not exist.
        dereference ? 4 : 5, // If not group.
        dereference ? 4 : 5, // If not is.
        dereference ? 5 : 6, // If not mode.
        dereference ? 4 : 5, // If not owner.
        dereference ? 5 : 6, // If not parameter.
        dereference ? 3 : 4, // If parameter.
        dereference ? 3 : 4, // If owner.
        dereference ? 1 : 2, // If success.
      };

      const uint8_t if_not_type_minimum[] = {
        dereference ? 4 : 5, // If not define.
        dereference ? 3 : 4, // If not exist.
        dereference ? 4 : 5, // If not group.
        dereference ? 4 : 5, // If not is.
        dereference ? 5 : 6, // If not mode.
        dereference ? 4 : 5, // If not owner.
        dereference ? 4 : 5, // If not parameter.
      };

      for (; i < 23; ++i) {

        // Skip the "if not XXX" types as they are determined later on.
        if (i > 12 && i < 21) continue;

        if (fl_string_dynamic_compare(if_type_strings[i], data_make->cache_arguments.array[k]) == F_equal_to) {
          state_process->condition = if_type_codes[i];

          break;
        }
      } // for

      if (i == 23) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%r%[%QUnsupported '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, if_and_or, data_make->error.notable);
          fl_print_format("%[' type '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[k], data_make->error.notable);
          fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

          funlockfile(data_make->error.to.stream);
        }

        return F_status_set_error(F_failure);
      }

      state_process->condition_result = fake_condition_result_true_e;

      ++k;

      // Identify and convert to the appropriate if not condition.
      if (state_process->condition == fake_make_operation_if_type_if_not_e) {
        if (data_make->cache_arguments.used < 1 + k) {
          fake_print_error_requires_more_arguments(data_make);

          return F_status_set_error(F_failure);
        }

        for (; j < 7; ++j) {

          if (fl_string_dynamic_compare(if_not_type_strings[j], data_make->cache_arguments.array[k]) == F_equal_to) {
            state_process->condition = if_not_type_codes[j];

            break;
          }
        } // for

        if (j == 7) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QUnsupported '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, if_and_or, data_make->error.notable);
            fl_print_format("%[' not type '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[k], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      }
      else {
        j = 7;
      }

      if (j == 7 && data_make->cache_arguments.used >= if_type_minimum[i] || j < 7 && data_make->cache_arguments.used >= if_not_type_minimum[j]) {
        if (state_process->condition == fake_make_operation_if_type_if_success_e || state_process->condition == fake_make_operation_if_type_if_failure_e) {

          // The success and failure operations minimum is also the maximum.
          if (data_make->cache_arguments.used > if_type_minimum[i]) {
            fake_print_error_too_many_arguments(data_make);

            return F_status_set_error(F_failure);
          }

          return F_none;
        }

        if (state_process->condition == fake_make_operation_if_type_if_equal_e || state_process->condition == fake_make_operation_if_type_if_equal_not_e) {
          if (data_make->cache_arguments.used < 2 + k) {
            fake_print_error_requires_more_arguments(data_make);

            return F_status_set_error(F_failure);
          }

          return F_none;
        }

        if (state_process->condition == fake_make_operation_if_type_if_exist_e || state_process->condition == fake_make_operation_if_type_if_not_exist_e) {
          return F_none;
        }

        if (state_process->condition == fake_make_operation_if_type_if_group_e || state_process->condition == fake_make_operation_if_type_if_is_e || state_process->condition == fake_make_operation_if_type_if_mode_e || state_process->condition > fake_make_operation_if_type_if_not_exist_e && state_process->condition < fake_make_operation_if_type_if_success_e) {

          if (state_process->condition == fake_make_operation_if_type_if_mode_e || state_process->condition == fake_make_operation_if_type_if_not_mode_e) {
            if (fl_string_dynamic_compare(fake_make_operation_argument_is_s, data_make->cache_arguments.array[k]) == F_equal_to_not) {
              if (fl_string_dynamic_compare(fake_make_operation_argument_has_s, data_make->cache_arguments.array[k]) == F_equal_to_not) {
                if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  fl_print_format("%r%[%QUnsupported %smode type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, j == 6 ? "" : "not ", data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[k], data_make->error.notable);
                  fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

                  funlockfile(data_make->error.to.stream);
                }

                return F_status_set_error(F_failure);
              }
            }

            f_file_mode_t mode_rule = 0;
            uint8_t replace = 0;

            if (F_status_is_error(fake_make_get_id_mode(data_make->data, data_make->error, data_make->cache_arguments.array[++k], &mode_rule, &replace))) {
              return F_status_set_error(F_failure);
            }

            i = ++k;
          }
          else if (state_process->condition == fake_make_operation_if_type_if_group_e || state_process->condition == fake_make_operation_if_type_if_not_group_e) {
            gid_t id = 0;

            if (F_status_is_error(fake_make_get_id_group(data_make->data, data_make->error, data_make->cache_arguments.array[k++], &id))) {
              return F_status_set_error(F_failure);
            }

            i = k;
          }
          else if (state_process->condition == fake_make_operation_if_type_if_is_e || state_process->condition == fake_make_operation_if_type_if_not_is_e) {

            // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
            // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
            // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
            // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
            uint8_t type_file = 0;

            for (i = k; i < data_make->cache_arguments.used; ++i) {

              if (fl_string_dynamic_compare(fake_make_operation_argument_if_is_for_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                ++i;

                break;
              }

              if (fl_string_dynamic_compare(f_file_type_name_block_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x1;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_character_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x2;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_directory_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x4;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_fifo_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x8;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_link_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x10;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_regular_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x20;
              }
              else if (fl_string_dynamic_compare(f_file_type_name_socket_s, data_make->cache_arguments.array[i]) == F_equal_to) {
                type_file |= 0x40;
              }
              else {
                if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  fl_print_format("%r%[%QUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
                  fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

                  funlockfile(data_make->error.to.stream);
                }

                type_file |= 0x80;
              }
            } // for

            if (type_file & 0x80) return F_status_set_error(F_failure);
          }
          else if (state_process->condition == fake_make_operation_if_type_if_owner_e || state_process->condition == fake_make_operation_if_type_if_not_owner_e) {
            uid_t id = 0;

            if (F_status_is_error(fake_make_get_id_owner(data_make->data, data_make->error, data_make->cache_arguments.array[k++], &id))) {
              return F_status_set_error(F_failure);
            }

            i = k;
          }

          if (i < data_make->cache_arguments.used) {
            f_status_t status = F_none;
            f_status_t status_file = F_none;

            for (; i < data_make->cache_arguments.used; ++i) {

              status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

              if (F_status_is_error(status_file)) {
                fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

                status = F_status_set_error(F_failure);
              }
              else if (state_process->condition != fake_make_operation_if_type_if_exist_e && state_process->condition != fake_make_operation_if_type_if_is_e) {

                // The existence tests do not need to happen here for *_if_exists and *_if_is as those two types will handle performing them during the process stage.
                status_file = f_file_exists(data_make->cache_arguments.array[i], dereference);

                if (status_file == F_false) {
                  status_file = F_status_set_error(F_file_found_not);
                }

                if (F_status_is_error(status_file)) {
                  fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_exists", F_true, data_make->cache_arguments.array[i], f_file_operation_find_s, fll_error_file_type_file_e);

                  status = F_status_set_error(F_failure);
                }
              }
            } // for

            return status;
          }

          return F_none;
        }

        if (state_process->condition == fake_make_operation_if_type_if_greater_e || state_process->condition == fake_make_operation_if_type_if_greater_equal_e || state_process->condition == fake_make_operation_if_type_if_less_e || state_process->condition == fake_make_operation_if_type_if_less_equal_e) {
          if (data_make->cache_arguments.used < 2 + k) {
            fake_print_error_requires_more_arguments(data_make);

            return F_status_set_error(F_failure);
          }

          f_status_t status = F_none;
          f_status_t status_number = F_none;
          f_string_range_t range = f_string_range_t_initialize;
          f_number_unsigned_t number = 0;

          for (i = k; i < data_make->cache_arguments.used; ++i, status_number = F_none) {

            if (data_make->cache_arguments.array[i].used) {
              range.start = 0;
              range.stop = data_make->cache_arguments.array[i].used - 1;

              if (data_make->cache_arguments.array[i].string[0] == f_string_ascii_plus_s.string[0]) {
                range.start = 1;
              }
              else if (data_make->cache_arguments.array[i].string[0] == f_string_ascii_minus_s.string[0]) {
                range.start = 1;
              }

              if (range.start > range.stop) {
                status_number = F_status_set_error(F_failure);
              }
              else {
                status_number = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, data_make->cache_arguments.array[i], range, &number);
              }
            }
            else {
              status_number = F_status_set_error(F_failure);
            }

            if (F_status_is_error(status_number)) {
              status = F_status_set_error(F_failure);

              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                if (number > F_number_t_size_unsigned_d) {
                  fl_print_format("%r%[%QThe number '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
                  fl_print_format("%[' may only be between the ranges -%un to %un.%]%r", data_make->error.to.stream, data_make->error.context, F_number_t_size_unsigned_d, F_number_t_size_unsigned_d, data_make->error.context, f_string_eol_s);
                }
                else {
                  fl_print_format("%r%[%QInvalid or unsupported number provided '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
                  fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);
                }

                funlockfile(data_make->error.to.stream);
              }
            }
          } // for

          return status;
        }
      }

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_condition_

#ifndef _di_fake_make_operate_validate_type_copy_
  f_status_t fake_make_operate_validate_type_copy(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      f_status_t status = F_none;
      f_status_t status_file = F_none;

      for (f_array_length_t i = 0; i < data_make->cache_arguments.used; ++i) {

        status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

        if (F_status_is_error(status_file)) {
          fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

          status = F_status_set_error(F_failure);
        }
      } // for

      for (f_array_length_t i = 0; i < data_make->cache_arguments.used - 1; ++i) {

        if (f_file_exists(data_make->cache_arguments.array[i], F_true) != F_true) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          status = F_status_set_error(F_failure);
        }
      } // for

      if (data_make->cache_arguments.used > 2) {

        // The last file must be a directory.
        status_file = f_directory_is(data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

        if (status_file == F_false || status_file == F_file_found_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe last file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], data_make->error.notable);
            fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          status = F_status_set_error(F_failure);
        }

        if (F_status_is_error(status_file)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], f_file_operation_identify_s, fll_error_file_type_directory_e);

          status = F_status_set_error(F_failure);
        }
      }
      else {

        // When the first file is a directory, then the second, if it exists, must also be a directory.
        status_file = f_directory_is(data_make->cache_arguments.array[0]);

        if (status_file == F_true) {
          status_file = f_directory_is(data_make->cache_arguments.array[1]);

          if (status_file == F_false) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%r%[%QThe second file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

              funlockfile(data_make->error.to.stream);
            }

            status = F_status_set_error(F_failure);
          }
        }
      }

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_copy_

#ifndef _di_fake_make_operate_validate_type_define_
  f_status_t fake_make_operate_validate_type_define(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      const f_status_t status = fake_make_operate_validate_define_name(data_make->cache_arguments.array[0]);

      if (status == F_none) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          fll_print_format("%r%[%QDefine name must not be an empty string.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
        }

        return F_status_set_error(F_failure);
      }

      if (status == F_false) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%r%[%QInvalid characters in the define setting name '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
          fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

          funlockfile(data_make->error.to.stream);
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_define_

#ifndef _di_fake_make_operate_validate_type_delete_
  f_status_t fake_make_operate_validate_type_delete(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      f_status_t status = F_none;
      f_status_t status_file = F_none;

      for (f_array_length_t i = 0; i < data_make->cache_arguments.used; ++i) {

        status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

        if (F_status_is_error(status_file)) {
          fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

          status = F_status_set_error(F_failure);
        }
      } // for

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_delete_

#ifndef _di_fake_make_operate_validate_type_else_
  f_status_t fake_make_operate_validate_type_else(fake_make_data_t * const data_make, fake_state_process_t * const state_process) {

    if (state_process->operation_previous == fake_make_operation_type_else_e) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QMust not be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_else_s, data_make->error.notable);
        fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    if (state_process->operation_previous == fake_make_operation_type_if_e || state_process->operation_previous == fake_make_operation_type_and_e || state_process->operation_previous == fake_make_operation_type_or_e) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QMust not be used immediately after an '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
        fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
        fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
        fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    if (!state_process->block) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        fl_print_format("%r%[%QHas no preceding '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
        fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
        fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
        fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);
      }

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_else_

#ifndef _di_fake_make_operate_validate_type_exit_
  f_status_t fake_make_operate_validate_type_exit(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used) {
      if (fl_string_dynamic_compare(fake_make_operation_argument_success_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_failure_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QUnsupported exit type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      }
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_exit_

#ifndef _di_fake_make_operate_validate_type_fail_
  f_status_t fake_make_operate_validate_type_fail(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      if (fl_string_dynamic_compare(fake_make_operation_argument_exit_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_warn_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
          if (fl_string_dynamic_compare(fake_make_operation_argument_ignore_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%r%[%QUnsupported fail type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

              funlockfile(data_make->error.to.stream);
            }

            return F_status_set_error(F_failure);
          }
        }
      }

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_fail_

#ifndef _di_fake_make_operate_validate_type_index_
  f_status_t fake_make_operate_validate_type_index(fake_make_data_t * const data_make) {

    if (!data_make->cache_arguments.used) {
      fake_print_error_requires_more_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (!data_make->setting_build.build_indexer.used) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QNo indexer has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_index_s, data_make->error.notable);
        fl_print_format("%[' section operation.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_index_

#ifndef _di_fake_make_operate_validate_type_link_
  f_status_t fake_make_operate_validate_type_link(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 4) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used > 1) {
      f_status_t status = F_none;
      f_status_t status_file = F_none;

      // 0x1 = force, 0x2 = strict.
      uint8_t flag = 0;

      if (data_make->cache_arguments.used > 2) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_force_s, data_make->cache_arguments.array[0]) == F_equal_to) {
          flag |= 0x1;
        }
        else if (fl_string_dynamic_compare(fake_make_operation_argument_strict_s, data_make->cache_arguments.array[0]) == F_equal_to) {
          flag |= 0x2;
        }
        else {
          fake_print_message_section_operation_link_argument_unknown(data_make->data, data_make->error, data_make->cache_arguments.array[0]);

          status = F_status_set_error(F_failure);
        }

        if (data_make->cache_arguments.used > 3) {
          if (fl_string_dynamic_compare(fake_make_operation_argument_force_s, data_make->cache_arguments.array[1]) == F_equal_to) {
            flag |= 0x1;
          }
          else if (fl_string_dynamic_compare(fake_make_operation_argument_strict_s, data_make->cache_arguments.array[1]) == F_equal_to) {
            flag |= 0x2;
          }
          else {
            fake_print_message_section_operation_link_argument_unknown(data_make->data, data_make->error, data_make->cache_arguments.array[1]);

            status = F_status_set_error(F_failure);
          }
        }
      }

      status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

      if (F_status_is_error(status_file)) {
        fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

        status = F_status_set_error(F_failure);
      }
      else {
        if (!(flag & 0x1)) {
          if (!data_make->cache_path.used || f_file_exists(data_make->cache_path, F_false) == F_true) {
            fake_print_message_section_operation_link_point_exists(data_make->data, data_make->error, data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

            status = F_status_set_error(F_failure);
          }
        }

        if (f_path_is_absolute(data_make->cache_arguments.array[data_make->cache_arguments.used - 2]) == F_true) {
          status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[data_make->cache_arguments.used - 2]);

          if (F_status_is_error(status_file)) {
            fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_arguments.array[data_make->cache_arguments.used - 2]);

            status = F_status_set_error(F_failure);
          }

          if ((flag & 0x2) && F_status_is_error_not(status_file)) {
            if (f_file_exists(data_make->cache_arguments.array[data_make->cache_arguments.used - 2], F_false) != F_true) {
              fake_print_message_section_operation_link_target_exists_not(data_make->data, data_make->error, data_make->cache_arguments.array[data_make->cache_arguments.used - 2]);

              status = F_status_set_error(F_failure);
            }
          }
        }

        // The target path is relative to the point path so construct the path for performing checks.
        else if (data_make->cache_arguments.array[data_make->cache_arguments.used - 2].used) {

          // The cache_path contains the full path to the point file, save this so that the cache_path can be re-used.
          f_char_t full_string[data_make->cache_path.used + 1];
          f_string_static_t full = macro_f_string_static_t_initialize(full_string, 0, data_make->cache_path.used);

          memcpy(full_string, data_make->cache_path.string, sizeof(f_char_t) * data_make->cache_path.used);
          full_string[data_make->cache_path.used] = 0;

          data_make->cache_path.used = 0;

          status_file = f_file_name_directory(full, &data_make->cache_path);

          if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_name_directory", F_true, full, f_file_operation_analyze_s, fll_error_file_type_path_e);

            status = F_status_set_error(F_failure);
          }

          if (F_status_is_error_not(status_file)) {
            status_file = f_string_dynamic_append_assure(f_path_separator_s, &data_make->cache_path);

            if (F_status_is_error(status_file)) {
              fll_error_print(data_make->error, F_status_set_fine(status_file), "f_string_dynamic_append_assure", F_true);

              status = F_status_set_error(F_failure);
            }
            else {
              status_file = f_string_dynamic_append(data_make->cache_arguments.array[data_make->cache_arguments.used - 2], &data_make->cache_path);

              if (F_status_is_error(status_file)) {
                fll_error_print(data_make->error, F_status_set_fine(status_file), "f_string_dynamic_append", F_true);

                status = F_status_set_error(F_failure);
              }
            }

            if (F_status_is_error_not(status_file)) {

              // The cache_path is used by fake_make_assure_inside_project(), so copy the contents into another buffer.
              f_char_t target_string[data_make->cache_path.used + 1];
              f_string_static_t target = macro_f_string_static_t_initialize(target_string, 0, data_make->cache_path.used);

              memcpy(target_string, data_make->cache_path.string, sizeof(f_char_t) * data_make->cache_path.used);
              target_string[data_make->cache_path.used] = 0;

              status_file = fake_make_assure_inside_project(data_make, target);

              if (F_status_is_error(status_file)) {
                fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", target);

                status = F_status_set_error(F_failure);
              }

              if ((flag & 0x2) && F_status_is_error_not(status_file)) {
                if (f_file_exists(target, F_false) != F_true) {
                  fake_print_message_section_operation_link_target_exists_not(data_make->data, data_make->error, target);

                  status = F_status_set_error(F_failure);
                }
              }
            }
          }
        }
        else {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_print_format("%r%[%QTarget filename argument must not be an empty string.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
          }
        }
      }

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_link_

#ifndef _di_fake_make_operate_validate_type_move_
  f_status_t fake_make_operate_validate_type_move(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      f_status_t status = F_none;

      {
        f_status_t status_file = F_none;

        for (f_array_length_t i = 0; i < data_make->cache_arguments.used; ++i) {

          status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

          if (F_status_is_error(status_file)) {
            fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

            status = F_status_set_error(F_failure);
          }
        } // for

        if (F_status_is_error_not(status)) {
          for (f_array_length_t i = 0; i < data_make->cache_arguments.used - 1; ++i) {

            if (f_file_exists(data_make->cache_arguments.array[i], F_true) != F_true) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
                fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

                funlockfile(data_make->error.to.stream);
              }

              status = F_status_set_error(F_failure);
            }
          } // for
        }

        if (F_status_is_error(status)) return status;
      }

      if (data_make->cache_arguments.used > 2) {

        // The last file must be a directory.
        status = f_directory_is(data_make->cache_arguments.array[data_make->cache_arguments.used - 1]);

        if (status == F_false || status == F_file_found_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe last file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], data_make->error.notable);
            fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        if (F_status_is_error(status)) {
          fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_is", F_true, data_make->cache_arguments.array[data_make->cache_arguments.used - 1], f_file_operation_identify_s, fll_error_file_type_directory_e);

          return F_status_set_error(F_failure);
        }
      }
      else {

        // When the first file is a directory, then the second, if it exists, must also be a directory.
        status = f_directory_is(data_make->cache_arguments.array[0]);

        if (status == F_true) {
          status = f_directory_is(data_make->cache_arguments.array[1]);

          if (status == F_false) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%r%[%QThe second file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

              funlockfile(data_make->error.to.stream);
            }

            return F_status_set_error(F_failure);
          }
        }
      }

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_move_

#ifndef _di_fake_make_operate_validate_type_operate_
  f_status_t fake_make_operate_validate_type_operate(fake_make_data_t * const data_make, f_array_lengths_t * const section_stack) {

    if (data_make->cache_arguments.used > 1) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used == 1) {
      f_array_length_t id_section = 0;

      for (; id_section < data_make->fakefile.used; ++id_section) {

        if (fl_string_dynamic_partial_compare_string(data_make->cache_arguments.array[0].string, data_make->buffer, data_make->cache_arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
          break;
        }
      } // for

      if (id_section == data_make->fakefile.used) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QNo operation section named '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
        fl_print_format("%[' is found.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);

        return F_status_set_error(F_failure);
      }

      for (f_array_length_t i = 0; i < section_stack->used; ++i) {

        if (section_stack->array[i] == id_section) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe section operation '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->fakefile.array[id_section].name, data_make->error.notable);
            fl_print_format("%[' is already in the operation stack, recursion is not allowed.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      } // for

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_operate_

#ifndef _di_fake_make_operate_validate_type_parameter_
  f_status_t fake_make_operate_validate_type_parameter(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
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

      f_status_t status = F_none;

      for (f_array_length_t i = 0; i < 33; ++i) {

        if (fl_string_dynamic_compare(reserved_name[i], data_make->cache_arguments.array[0]) == F_equal_to) {
          fll_print_format("%r%[%QCannot assign a value to the parameter name '%r' because it is a reserved parameter name.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, reserved_name[i], data_make->error.context, f_string_eol_s);

          status = F_status_set_error(F_failure);
        }
      } // for

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_parameter_

#ifndef _di_fake_make_operate_validate_type_permission_
  f_status_t fake_make_operate_validate_type_permission(fake_make_data_t * const data_make, fake_state_process_t * const state_process) {

    if (data_make->cache_arguments.used) {
      f_array_length_t i = 1;

      if (state_process->operation == fake_make_operation_type_group_e || state_process->operation == fake_make_operation_type_groups_e || state_process->operation == fake_make_operation_type_owner_e || state_process->operation == fake_make_operation_type_owners_e) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_no_dereference_s, data_make->cache_arguments.array[i]) == F_equal_to) {
          i = 2;
        }
      }

      if (data_make->cache_arguments.used > i) {
        f_status_t status = F_none;
        f_status_t status_file = F_none;

        for (; i < data_make->cache_arguments.used; ++i) {

          status_file = f_file_is(data_make->cache_arguments.array[i], F_file_type_regular_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

              funlockfile(data_make->error.to.stream);
            }

            status = F_status_set_error(F_failure);
          }

          if (F_status_is_error(status_file)) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_is", F_true, data_make->cache_arguments.array[i], f_file_operation_find_s, fll_error_file_type_directory_e);
            }

            status = F_status_set_error(F_failure);
          }
        }

        return status;
      }
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_permission_

#ifndef _di_fake_make_operate_validate_type_pop_
  f_status_t fake_make_operate_validate_type_pop(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->path.stack.used == 1) {
      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        fll_print_format("%r%[%QMust not attempt to pop project root off of path stack.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_pop_

#ifndef _di_fake_make_operate_validate_type_run_
  f_status_t fake_make_operate_validate_type_run(fake_make_data_t * const data_make) {

    if (!data_make->cache_arguments.used) {
      fake_print_error_requires_more_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_validate_type_run_

#ifndef _di_fake_make_operate_validate_type_to_
  f_status_t fake_make_operate_validate_type_to(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      fake_print_error_too_many_arguments(data_make);

      return F_status_set_error(F_failure);
    }

    if (data_make->cache_arguments.used) {
      if (data_make->cache_arguments.array[0].used) {
        const f_status_t status = f_file_is(data_make->cache_arguments.array[0], F_file_type_directory_d, F_false);

        if (status == F_file_found_not) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QFailed to find file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        if (F_status_is_error(status)) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_is", F_true, data_make->data->file_data_build_fakefile, f_file_operation_find_s, fll_error_file_type_file_e);
          }

          return F_status_set_error(F_failure);
        }

        if (!status) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QThe file '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
            fl_print_format("%[' must be a directory file.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        return F_none;
      }

      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        fll_print_format("%r%[%QFilename argument must not be an empty string.%]%r", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s);
      }

      return F_status_set_error(F_failure);
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_to_

#ifndef _di_fake_make_operate_validate_type_touch_
  f_status_t fake_make_operate_validate_type_touch(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used > 1) {
      if (fl_string_dynamic_compare(fake_make_operation_argument_file_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {
        if (fl_string_dynamic_compare(fake_make_operation_argument_directory_s, data_make->cache_arguments.array[0]) == F_equal_to_not) {

          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%r%[%QUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->cache_arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

            funlockfile(data_make->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }
      }

      f_status_t status = F_none;
      f_status_t status_file = F_none;

      for (f_array_length_t i = 1; i < data_make->cache_arguments.used; ++i) {

        status_file = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[i]);

        if (F_status_is_error(status_file)) {
          fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[i]);

          status = F_status_set_error(F_failure);
        }
      } // for

      return status;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_touch_

#ifndef _di_fake_make_operate_validate_type_write_
  f_status_t fake_make_operate_validate_type_write(fake_make_data_t * const data_make) {

    if (data_make->cache_arguments.used) {
      if (!data_make->cache_arguments.array[0].used) {
        fake_print_error_argument_empty(data_make, 1);

        return F_status_set_error(F_failure);
      }

      const f_status_t status = fake_make_assure_inside_project(data_make, data_make->cache_arguments.array[0]);

      if (F_status_is_error(status)) {
        fake_print_message_section_operation_path_outside(data_make->data, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->cache_path.used ? data_make->cache_path : data_make->cache_arguments.array[0]);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    fake_print_error_requires_more_arguments(data_make);

    return F_status_set_error(F_failure);
  }
#endif // _di_fake_make_operate_validate_type_write_

#ifdef __cplusplus
} // extern "C"
#endif
