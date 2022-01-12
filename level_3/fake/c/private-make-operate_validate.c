#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-operate.h"
#include "private-make-operate_validate.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_validate_
  void fake_make_operate_validate(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (state_process->operation == fake_make_operation_type_index_e || state_process->operation == fake_make_operation_type_run_e || state_process->operation == fake_make_operation_type_shell_e) {
      if (!arguments.used) {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (state_process->operation == fake_make_operation_type_index_e) {
        if (!data_make->setting_build.build_indexer.used) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SNo indexer has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_index_s, data_make->error.notable);
            fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_break_e) {
      if (arguments.used > 1) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to_not) {

            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported break type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_build_e) {
      if (arguments.used > 1) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          char path_file[data_make->main->path_data_build.used + arguments.array[0].used + 1];

          memcpy(path_file, data_make->main->path_data_build.string, data_make->main->path_data_build.used);
          memcpy(path_file + data_make->main->path_data_build.used, arguments.array[0].string, arguments.array[0].used);

          path_file[data_make->main->path_data_build.used + arguments.array[0].used] = 0;

          f_status_t status_file = f_file_is(path_file, F_file_type_regular_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%S%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_is", F_true, path_file, "find", fll_error_file_type_file_e);
            *status = status_file;
          }
          else if (!status_file) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
              fl_print_format("%[' must be a regular file.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_print_format("%c%[%SFilename argument must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_clean_e || state_process->operation == fake_make_operation_type_pop_e || state_process->operation == fake_make_operation_type_top_e || state_process->operation == fake_make_operation_type_skeleton_e) {
      if (arguments.used) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (state_process->operation == fake_make_operation_type_pop_e) {
        if (data_make->path.stack.used == 1) {

          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_print_format("%c%[%SMust not attempt to pop project root off of path stack.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_clone_e) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // The last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "find", fll_error_file_type_directory_e);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // When the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_compile_e) {
      if (!arguments.used) {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (data_make->setting_build.build_compiler.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SNo compiler has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_compile_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_copy_e) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // The last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "identify", fll_error_file_type_directory_e);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // When the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_define_e) {
      if (arguments.used) {
        *status = fake_make_operate_validate_define_name(arguments.array[0]);

        if (*status == F_none) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_print_format("%c%[%SDefine name must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
        else if (*status == F_false) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SInvalid characters in the define setting name '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
            fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_delete_e || state_process->operation == fake_make_operation_type_deletes_e) {
      if (arguments.used) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_else_e) {
      if (state_process->block == fake_make_operation_if_type_else_e) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SMust not be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_else_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);

        return;
      }

      if (state_process->operation_previous == fake_make_operation_type_if_e || state_process->operation_previous == fake_make_operation_type_and_e || state_process->operation_previous == fake_make_operation_type_or_e) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SMust not be used immediately after an '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
          fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
          fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);

        return;
      }

      if (!state_process->block) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          fl_print_format("%c%[%SHas no preceding '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
          fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
          fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);

        return;
      }

      if (arguments.used) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_exit_e) {
      if (arguments.used > 1) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported exit type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_fail_e) {
      if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_exit_s, arguments.array[0], fake_make_operation_argument_exit_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn_s, arguments.array[0], fake_make_operation_argument_warn_s_length) == F_equal_to_not) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_ignore_s, arguments.array[0], fake_make_operation_argument_ignore_s_length) == F_equal_to_not) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SUnsupported fail type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
                fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_group_e || state_process->operation == fake_make_operation_type_groups_e || state_process->operation == fake_make_operation_type_mode_e || state_process->operation == fake_make_operation_type_modes_e || state_process->operation == fake_make_operation_type_owner_e || state_process->operation == fake_make_operation_type_owners_e) {
      if (arguments.used > 1) {
        f_status_t status_file = F_none;

        for (f_array_length_t i = 1; i < arguments.used; ++i) {

          status_file = f_file_is(arguments.array[i].string, F_file_type_regular_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_is", F_true, arguments.array[i].string, "find", fll_error_file_type_directory_e);
            }

            *status = status_file;
          }
        }

        return;
      }

      fake_print_error_requires_more_arguments(data_make);

      *status = F_status_set_error(F_failure);

      return;
    }

    if (state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e) {
      if (state_process->operation == fake_make_operation_type_if_e) {
        if (state_process->operation_previous == fake_make_operation_type_if_e) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SMust not be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
            fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
            fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
            fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);

          return;
        }
      }
      else {
        if (!(state_process->operation_previous == fake_make_operation_type_if_e || state_process->operation_previous == fake_make_operation_type_and_e || state_process->operation_previous == fake_make_operation_type_or_e)) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SMay only be used immediately after another '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
            fl_print_format("%[', '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
            fl_print_format("%[', or '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
            fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);

          return;
        }
      }

      if (arguments.used) {
        const f_string_t if_type_strings[] = {
          fake_make_operation_argument_if_defined_s,
          fake_make_operation_argument_if_equal_s,
          fake_make_operation_argument_if_equal_not_s,
          fake_make_operation_argument_if_exists_s,
          fake_make_operation_argument_if_failure_s,
          fake_make_operation_argument_if_greater_s,
          fake_make_operation_argument_if_greater_equal_s,
          fake_make_operation_argument_if_group_s,
          fake_make_operation_argument_if_is_s,
          fake_make_operation_argument_if_less_s,
          fake_make_operation_argument_if_less_equal_s,
          fake_make_operation_argument_if_mode_s,
          fake_make_operation_argument_if_not_s,
          fake_make_operation_argument_if_defined_s, // If not defined, represented by just "defined".
          fake_make_operation_argument_if_exists_s,  // If not exists, represented by just "exists".
          fake_make_operation_argument_if_group_s,   // If not group, represented by just "group".
          fake_make_operation_argument_if_is_s,      // If not is, represented by just "is".
          fake_make_operation_argument_if_mode_s,    // If not mode, represented by just "mode".
          fake_make_operation_argument_if_owner_s,   // If not owner, represented by just "owner".
          fake_make_operation_argument_if_owner_s,
          fake_make_operation_argument_if_success_s,
        };

        const f_array_length_t if_type_lengths[] = {
          fake_make_operation_argument_if_defined_s_length,
          fake_make_operation_argument_if_equal_s_length,
          fake_make_operation_argument_if_equal_not_s_length,
          fake_make_operation_argument_if_exists_s_length,
          fake_make_operation_argument_if_failure_s_length,
          fake_make_operation_argument_if_greater_s_length,
          fake_make_operation_argument_if_greater_equal_s_length,
          fake_make_operation_argument_if_group_s_length,
          fake_make_operation_argument_if_is_s_length,
          fake_make_operation_argument_if_less_s_length,
          fake_make_operation_argument_if_less_equal_s_length,
          fake_make_operation_argument_if_mode_s_length,
          fake_make_operation_argument_if_not_s_length,
          fake_make_operation_argument_if_defined_s_length, // if not defined, represented by just "defined".
          fake_make_operation_argument_if_exists_s_length,  // if not exists, represented by just "exists".
          fake_make_operation_argument_if_group_s_length,   // if not group, represented by just "group".
          fake_make_operation_argument_if_is_s_length,      // if not is, represented by just "is".
          fake_make_operation_argument_if_mode_s_length,    // if not mode, represented by just "mode".
          fake_make_operation_argument_if_owner_s_length,   // if not owner, represented by just "owner".
          fake_make_operation_argument_if_owner_s_length,
          fake_make_operation_argument_if_success_s_length,
        };

        const uint8_t if_type_codes[] = {
          fake_make_operation_if_type_if_defined_e,
          fake_make_operation_if_type_if_equal_e,
          fake_make_operation_if_type_if_equal_not_e,
          fake_make_operation_if_type_if_exists_e,
          fake_make_operation_if_type_if_failure_e,
          fake_make_operation_if_type_if_greater_e,
          fake_make_operation_if_type_if_greater_equal_e,
          fake_make_operation_if_type_if_group_e,
          fake_make_operation_if_type_if_is_e,
          fake_make_operation_if_type_if_less_e,
          fake_make_operation_if_type_if_less_equal_e,
          fake_make_operation_if_type_if_mode_e,
          fake_make_operation_if_type_if_not_e,
          fake_make_operation_if_type_if_not_defined_e,
          fake_make_operation_if_type_if_not_exists_e,
          fake_make_operation_if_type_if_not_group_e,
          fake_make_operation_if_type_if_not_is_e,
          fake_make_operation_if_type_if_not_mode_e,
          fake_make_operation_if_type_if_not_owner_e,
          fake_make_operation_if_type_if_owner_e,
          fake_make_operation_if_type_if_success_e,
        };

        const uint8_t if_type_minimum[] = {
          3, // If defined.
          2, // If equal (==).
          2, // If equal not (<>).
          2, // If exists.
          1, // If failure.
          2, // If greater (>).
          2, // If greater equal (>=).
          3, // If group.
          3, // If is.
          2, // If less (<).
          2, // If less equal (<=).
          4, // If mode.
          3, // If not.
          5, // If not defined.
          3, // If not exists.
          4, // If not group.
          4, // If not is.
          5, // If not mode.
          4, // If not owner.
          3, // If owner.
          1, // If success.
        };

        const f_string_t if_not_type_strings[] = {
          fake_make_operation_argument_if_defined_s,
          fake_make_operation_argument_if_exists_s,
          fake_make_operation_argument_if_group_s,
          fake_make_operation_argument_if_is_s,
          fake_make_operation_argument_if_mode_s,
          fake_make_operation_argument_if_owner_s,
        };

        const f_array_length_t if_not_type_lengths[] = {
          fake_make_operation_argument_if_defined_s_length,
          fake_make_operation_argument_if_exists_s_length,
          fake_make_operation_argument_if_group_s_length,
          fake_make_operation_argument_if_is_s_length,
          fake_make_operation_argument_if_mode_s_length,
          fake_make_operation_argument_if_owner_s_length,
        };

        const uint8_t if_not_type_codes[] = {
          fake_make_operation_if_type_if_not_defined_e,
          fake_make_operation_if_type_if_not_exists_e,
          fake_make_operation_if_type_if_not_group_e,
          fake_make_operation_if_type_if_not_is_e,
          fake_make_operation_if_type_if_not_mode_e,
          fake_make_operation_if_type_if_not_owner_e,
        };

        const uint8_t if_not_type_minimum[] = {
          4, // If not defined.
          3, // If not exists.
          4, // If not group.
          4, // If not is.
          5, // If not mode.
          4, // If not owner.
        };

        f_array_length_t i = 0;
        f_array_length_t j = 0;
        f_string_t if_and_or;

        if (state_process->operation == fake_make_operation_type_and_e) {
          if_and_or = fake_make_operation_and_s;
        }
        else if (state_process->operation == fake_make_operation_type_or_e) {
          if_and_or = fake_make_operation_or_s;
        }
        else {
          if_and_or = fake_make_operation_if_s;
        }

        for (; i < 21; ++i) {

          // Skip the "if not XXX" types as they are determined later on.
          if (i > 12 && i < 19) continue;

          if (fl_string_dynamic_compare_string(if_type_strings[i], arguments.array[0], if_type_lengths[i]) == F_equal_to) {
            state_process->condition = if_type_codes[i];

            break;
          }
        } // for

        if (i == 21) {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SUnsupported '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, if_and_or, data_make->error.notable);
            fl_print_format("%[' type '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);

          return;
        }

        // Identify and convert to the appropriate if not condition.
        if (state_process->condition == fake_make_operation_if_type_if_not_e) {
          if (arguments.used < 2) {
            fake_print_error_requires_more_arguments(data_make);

            *status = F_status_set_error(F_failure);

            return;
          }

          for (; j < 6; ++j) {

            if (fl_string_dynamic_compare_string(if_not_type_strings[j], arguments.array[1], if_not_type_lengths[j]) == F_equal_to) {
              state_process->condition = if_not_type_codes[j];

              break;
            }
          } // for

          if (j == 6) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, if_and_or, data_make->error.notable);
              fl_print_format("%[' not type '%]", data_make->error.to.stream, data_make->error.context, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);

            return;
          }
        }
        else {
          j = 6;
        }

        if (j == 6 && arguments.used >= if_type_minimum[i] || arguments.used >= if_not_type_minimum[j]) {
          if (state_process->condition == fake_make_operation_if_type_if_success_e || state_process->condition == fake_make_operation_if_type_if_failure_e) {

            // The success and failure operations minimum is also the maximum.
            if (arguments.used > if_type_minimum[i]) {
              fake_print_error_too_many_arguments(data_make);

              *status = F_status_set_error(F_failure);
            }

            return;
          }

          if (state_process->condition == fake_make_operation_if_type_if_defined_e || state_process->condition == fake_make_operation_if_type_if_not_defined_e) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_environment_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_environment_s_length) == F_equal_to_not) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_parameter_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_parameter_s_length) == F_equal_to_not) {
                if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  fl_print_format("%c%[%SUnsupported define type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, j == 6 ? arguments.array[1] : arguments.array[2], data_make->error.notable);
                  fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                  funlockfile(data_make->error.to.stream);
                }

                *status = F_status_set_error(F_failure);
              }
            }

            return;
          }
          else if (state_process->condition == fake_make_operation_if_type_if_equal_e || state_process->condition == fake_make_operation_if_type_if_equal_not_e) {
            if (arguments.used < 3) {
              fake_print_error_requires_more_arguments(data_make);

              *status = F_status_set_error(F_failure);
            }

            return;
          }
          else if (state_process->condition == fake_make_operation_if_type_if_exists_e || state_process->condition == fake_make_operation_if_type_if_not_exists_e) {
            return;
          }
          else if (state_process->condition == fake_make_operation_if_type_if_group_e || state_process->condition == fake_make_operation_if_type_if_is_e || state_process->condition == fake_make_operation_if_type_if_mode_e || state_process->condition > fake_make_operation_if_type_if_not_exists_e && state_process->condition < fake_make_operation_if_type_if_success_e) {

            if (state_process->condition == fake_make_operation_if_type_if_mode_e || state_process->condition == fake_make_operation_if_type_if_not_mode_e) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_is_s, arguments.array[1], fake_make_operation_argument_is_s_length) == F_equal_to_not) {
                if (fl_string_dynamic_compare_string(fake_make_operation_argument_has_s, arguments.array[1], fake_make_operation_argument_has_s_length) == F_equal_to_not) {
                  if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                    flockfile(data_make->error.to.stream);

                    fl_print_format("%c%[%SUnsupported %smode type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, j == 6 ? "" : "not ", data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                    funlockfile(data_make->error.to.stream);
                  }

                  *status = F_status_set_error(F_failure);

                  return;
                }
              }

              f_file_mode_t mode_rule = 0;
              uint8_t replace = 0;

              *status = fake_make_get_id_mode(data_make->main, data_make->error, j == 6 ? arguments.array[2] : arguments.array[3], &mode_rule, &replace);
              if (F_status_is_error(*status)) return;

              i = j == 6 ? 3 : 4;
            }
            else if (state_process->condition == fake_make_operation_if_type_if_group_e || state_process->condition == fake_make_operation_if_type_if_not_group_e) {
              gid_t id = 0;

              *status = fake_make_get_id_group(data_make->main, data_make->error, j == 6 ? arguments.array[1] : arguments.array[2], &id);
              if (F_status_is_error(*status)) return;

              i = j == 6 ? 2 : 3;
            }
            else if (state_process->condition == fake_make_operation_if_type_if_is_e || state_process->condition == fake_make_operation_if_type_if_not_is_e) {

              // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
              // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
              // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
              // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
              uint8_t type_file = 0;

              for (i = j == 6 ? 1 : 2; i < arguments.used; ++i) {

                if (fl_string_dynamic_compare_string(fake_make_operation_argument_if_is_for_s, arguments.array[i], fake_make_operation_argument_if_is_for_s_length) == F_equal_to) {
                  ++i;

                  break;
                }

                if (fl_string_dynamic_compare_string(F_file_type_name_block_s, arguments.array[i], F_file_type_name_block_s_length) == F_equal_to) {
                  type_file |= 0x1;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_character_s, arguments.array[i], F_file_type_name_character_s_length) == F_equal_to) {
                  type_file |= 0x2;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_directory_s, arguments.array[i], F_file_type_name_directory_s_length) == F_equal_to) {
                  type_file |= 0x4;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_fifo_s, arguments.array[i], F_file_type_name_fifo_s_length) == F_equal_to) {
                  type_file |= 0x8;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_link_s, arguments.array[i], F_file_type_name_link_s_length) == F_equal_to) {
                  type_file |= 0x10;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_regular_s, arguments.array[i], F_file_type_name_regular_s_length) == F_equal_to) {
                  type_file |= 0x20;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_socket_s, arguments.array[i], F_file_type_name_socket_s_length) == F_equal_to) {
                  type_file |= 0x40;
                }
                else {
                  if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                    flockfile(data_make->error.to.stream);

                    fl_print_format("%c%[%SUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                    funlockfile(data_make->error.to.stream);
                  }

                  type_file |= 0x80;
                }
              } // for

              if (type_file & 0x80) {
                *status = F_status_set_error(F_failure);

                return;
              }
            }
            else if (state_process->condition == fake_make_operation_if_type_if_owner_e || state_process->condition == fake_make_operation_if_type_if_not_owner_e) {
              uid_t id = 0;

              *status = fake_make_get_id_owner(data_make->main, data_make->error, arguments.array[1], &id);
              if (F_status_is_error(*status)) return;

              i = j == 6 ? 2 : 3;
            }

            if (i < arguments.used) {
              for (f_status_t status_file = F_none; i < arguments.used; ++i) {

                status_file = fake_make_assure_inside_project(data_make, arguments.array[i]);

                if (F_status_is_error(status_file)) {
                  fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

                  if (F_status_is_error_not(*status)) {
                    if (F_status_set_fine(status_file) == F_false) {
                      *status = F_status_set_error(F_failure);
                    }
                    else {
                      *status = status_file;
                    }
                  }
                }
                else if (state_process->condition != fake_make_operation_if_type_if_exists_e && state_process->condition != fake_make_operation_if_type_if_is_e) {

                  // The existence tests do not need to happen here for *_if_exists and *_if_is as those two types will handle performing them during the process stage.
                  status_file = f_file_exists(arguments.array[i].string);

                  if (status_file == F_false) {
                    status_file = F_status_set_error(F_file_found_not);
                  }

                  if (F_status_is_error(status_file)) {
                    fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_exists", F_true, arguments.array[i].string, "find", fll_error_file_type_file_e);

                    if (F_status_is_error_not(*status)) {
                      *status = F_status_set_error(status_file);
                    }
                  }
                }
              } // for
            }
          }
          else if (state_process->condition == fake_make_operation_if_type_if_greater_e || state_process->condition == fake_make_operation_if_type_if_greater_equal_e || state_process->condition == fake_make_operation_if_type_if_less_e || state_process->condition == fake_make_operation_if_type_if_less_equal_e) {
            if (arguments.used < 3) {
              fake_print_error_requires_more_arguments(data_make);

              *status = F_status_set_error(F_failure);

              return;
            }

            f_status_t status_number = F_none;
            f_string_range_t range = f_string_range_t_initialize;
            f_number_unsigned_t number = 0;
            bool is_negative = F_false;

            // @fixme there needs to handle converting numbers with decimals (like 1.01), perhaps operate on them as strings or provide a special processor.
            for (i = 1; i < arguments.used; ++i, status_number = F_none) {

              if (arguments.array[i].used) {
                range.start = 0;
                range.stop = arguments.array[i].used - 1;

                if (arguments.array[i].string[0] == '+') {
                  range.start = 1;
                }
                else if (arguments.array[i].string[0] == '-') {
                  range.start = 1;
                  is_negative = F_true;
                }

                if (range.start > range.stop) {
                  status_number = F_status_set_error(F_failure);
                }
                else {
                  status_number = fl_conversion_string_to_number_unsigned(arguments.array[i].string, range, &number);
                }
              }
              else {
                status_number = F_status_set_error(F_failure);
              }

              if (F_status_is_error(status_number)) {
                *status = F_status_set_error(F_failure);

                if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  if (number > F_number_t_size_unsigned_d) {
                    fl_print_format("%c%[%SThe number '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%[' may only be between the ranges -%un to %un.%]%c", data_make->error.to.stream, data_make->error.context, F_number_t_size_unsigned_d, F_number_t_size_unsigned_d, data_make->error.context, f_string_eol_s[0]);
                  }
                  else {
                    fl_print_format("%c%[%SInvalid or unsupported number provided '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);
                  }

                  funlockfile(data_make->error.to.stream);
                }
              }
            } // for
          }
        }

        return;
      }

      fake_print_error_requires_more_arguments(data_make);

      *status = F_status_set_error(F_failure);

      return;
    }

    if (state_process->operation == fake_make_operation_type_link_e) {
      if (arguments.used > 2) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 2) {
        *status = fake_make_assure_inside_project(data_make, arguments.array[0]);

        if (F_status_is_error(*status)) {
          fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }

        *status = fake_make_assure_inside_project(data_make, arguments.array[1]);

        if (F_status_is_error(*status)) {
          fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[1].string);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_move_e) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // The last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "identify", fll_error_file_type_directory_e);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // When the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_operate_e) {
      if (arguments.used > 1) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 1) {
        f_array_length_t id_section = 0;

        for (; id_section < data_make->fakefile.used; ++id_section) {

          if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
            break;
          }
        } // for

        if (id_section == data_make->fakefile.used) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SNo operation section named '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
          fl_print_format("%[' was found.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }
        else {
          for (f_array_length_t i = 0; i < section_stack->used; ++i) {

            if (section_stack->array[i] == id_section) {
              if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe section operation '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->fakefile.array[id_section].name, data_make->error.notable);
                fl_print_format("%[' is already in the operation stack, recursion is not allowed.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
              break;
            }
          } // for
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_parameter_e) {
      if (arguments.used) {
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

        for (f_array_length_t i = 0; i < 33; ++i) {

          if (fl_string_dynamic_compare_string(reserved_name[i], arguments.array[0], reserved_length[i]) == F_equal_to) {
            fll_print_format("%c%[%SCannot assign a value to the parameter name '%s' because it is a reserved parameter name.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);

            *status = F_status_set_error(F_failure);

            return;
          }
        } // for
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_to_e) {
      if (arguments.used > 1) {
        fake_print_error_too_many_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          f_status_t status_file = f_file_is(arguments.array[0].string, F_file_type_directory_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_is", F_true, data_make->main->file_data_build_fakefile.string, "find", fll_error_file_type_file_e);
            }

            *status = status_file;
          }
          else if (!status_file) {
            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%[' must be a directory file.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
            fll_print_format("%c%[%SFilename argument must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }
        }
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (state_process->operation == fake_make_operation_type_touch_e) {
      if (arguments.used > 1) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_file_s, arguments.array[0], fake_make_operation_argument_file_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory_s, arguments.array[0], fake_make_operation_argument_directory_s_length) == F_equal_to_not) {

            if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }

        for (f_array_length_t i = 1; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data_make->main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        fake_print_error_requires_more_arguments(data_make);

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    // Note: there is nothing to validate for fake_make_operation_type_print_e.
    return;
  }
#endif // _di_fake_make_operate_validate_

#ifndef _di_fake_make_operate_validate_define_name_
  f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    if (!(isalpha(name.string[0]) || name.string[0] == '_')) {
      return F_false;
    }

    for (f_array_length_t i = 0; i < name.used; ++i) {

      if (!(isalnum(name.string[i]) || name.string[i] == '_')) {
        return F_false;
      }
    } // for

    return F_true;
  }
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif
