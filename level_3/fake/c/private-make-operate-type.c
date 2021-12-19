#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-load_parameters.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate.h"
#include "private-make-operate-type.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_type_clone_
  f_status_t fake_make_operate_process_type_clone(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type__

#ifndef _di_fake_make_operate_process_type_copy_
  f_status_t fake_make_operate_process_type_copy(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_copy_

#ifndef _di_fake_make_operate_process_type_deletes_
  f_status_t fake_make_operate_process_type_deletes(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_deletes_

#ifndef _di_fake_make_operate_process_type_exit_
  f_status_t fake_make_operate_process_type_exit(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_exit_

#ifndef _di_fake_make_operate_process_type_fail_
  f_status_t fake_make_operate_process_type_fail(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_fail_

#ifndef _di_fake_make_operate_process_type_group_
  f_status_t fake_make_operate_process_type_group(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_group_

#ifndef _di_fake_make_operate_process_type_groups_
  f_status_t fake_make_operate_process_type_groups(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_groups_

#ifndef _di_fake_make_operate_process_type_if_group_
  f_status_t fake_make_operate_process_type_if_group(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_group(main, data_make->error, arguments.array[1], &id);
    if (F_status_is_error(status)) return status;

    uid_t id_file = 0;

    *operation_if = fake_make_operation_if_type_true_next;

    for (f_array_length_t i = 2; i < arguments.used; ++i, id_file = 0) {

      status = f_file_group_read(arguments.array[i].string, &id_file);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_group_read", F_true, arguments.array[i].string, "get group of", fll_error_file_type_file);

        break;
      }

      if (id != id_file) {
        *operation_if = fake_make_operation_if_type_false_next;

        break;
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_group_

#ifndef _di_fake_make_operate_process_type_if_mode_
  f_status_t fake_make_operate_process_type_if_mode(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

    f_status_t status = F_none;
    f_file_mode_t mode_rule = 0;
    mode_t mode_match = 0;
    bool is = F_false;

    if (fl_string_dynamic_compare_string(fake_make_operation_argument_is_s, arguments.array[1], fake_make_operation_argument_is_s_length) == F_equal_to) {
      is = F_true;
    }

    {
      uint8_t mode_replace = 0;

      status = fake_make_get_id_mode(main, data_make->error, arguments.array[2], &mode_rule, &mode_replace);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        return status;
      }

      status = f_file_mode_to_mode(mode_rule, &mode_match);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        fll_error_print(data_make->error, F_status_set_fine(status), "f_file_mode_to_mode", F_true);

        return status;
      }
    }

    mode_t mode_file = 0;

    *operation_if = fake_make_operation_if_type_true_next;

    for (f_array_length_t i = 3; i < arguments.used; ++i, mode_file = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "get mode of", fll_error_file_type_file);

        break;
      }

      if (is) {
        if (mode_match != (mode_file & F_file_mode_all_d)) {
          *operation_if = fake_make_operation_if_type_false_next;

          break;
        }
      }
      else {
        if (!(mode_match & mode_file)) {
          *operation_if = fake_make_operation_if_type_false_next;

          break;
        }
      }
    } // for

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_mode_

#ifndef _di_fake_make_operate_process_type_if_owner_
  f_status_t fake_make_operate_process_type_if_owner(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_owner(main, data_make->error, arguments.array[1], &id);
    if (F_status_is_error(status)) return status;

    uid_t id_file = 0;

    *operation_if = fake_make_operation_if_type_true_next;

    for (f_array_length_t i = 2; i < arguments.used; ++i, id_file = 0) {

      status = f_file_owner_read(arguments.array[i].string, &id_file);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_owner_read", F_true, arguments.array[i].string, "get owner of", fll_error_file_type_file);

        break;
      }

      if (id != id_file) {
        *operation_if = fake_make_operation_if_type_false_next;

        break;
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_owner_

#ifndef _di_fake_make_operate_process_type_if_is_
  f_status_t fake_make_operate_process_type_if_is(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

    f_status_t status = F_none;

    // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
    // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
    // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
    // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
    uint8_t type = 0;

    f_array_length_t i = 1;

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

    *operation_if = fake_make_operation_if_type_true_next;

    for (; i < arguments.used; ++i, mode_file = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        *operation_if = fake_make_operation_if_type_false_always_next;

        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "get mode of", fll_error_file_type_file);

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

      if (!(type & type_file)) {
        *operation_if = fake_make_operation_if_type_false_next;

        break;
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_if_is_

#ifndef _di_fake_make_operate_process_type_if_defined_
  void fake_make_operate_process_type_if_defined(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

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
      main->path_build.used,
      F_true,
      main->path_data.used,
      main->define.used,
      main->fakefile.used,
      main->mode.used,
      main->process.used,
      main->settings.used,
      main->path_sources.used,
      F_true,
      main->path_work.used,
      main->parameters[fake_parameter_path_build].result == f_console_result_additional,
      main->parameters[fake_parameter_light].result == f_console_result_found || main->parameters[fake_parameter_dark].result == f_console_result_found || main->parameters[fake_parameter_no_color].result == f_console_result_found,
      main->parameters[fake_parameter_path_data].result == f_console_result_additional,
      main->parameters[fake_parameter_define].result == f_console_result_additional,
      main->parameters[fake_parameter_fakefile].result == f_console_result_additional,
      main->parameters[fake_parameter_mode].result == f_console_result_additional,
      main->parameters[fake_parameter_process].result == f_console_result_additional,
      main->parameters[fake_parameter_settings].result == f_console_result_additional,
      main->parameters[fake_parameter_path_sources].result == f_console_result_additional,
      main->parameters[fake_parameter_verbosity_quiet].result == f_console_result_found || main->parameters[fake_parameter_verbosity_normal].result == f_console_result_found || main->parameters[fake_parameter_verbosity_verbose].result == f_console_result_found || main->parameters[fake_parameter_verbosity_debug].result == f_console_result_found,
      main->parameters[fake_parameter_path_work].result == f_console_result_additional,
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

    if (fl_string_dynamic_compare_string(fake_make_operation_argument_environment_s, arguments.array[1], fake_make_operation_argument_environment_s_length) == F_equal_to) {
      *operation_if = fake_make_operation_if_type_true_next;

      for (f_array_length_t i = 2; i < arguments.used; ++i) {

        if (f_environment_exists(arguments.array[i].string) != F_true) {
          *operation_if = fake_make_operation_if_type_false_next;

          break;
        }
      } // for
    }
    else if (fl_string_dynamic_compare_string(fake_make_operation_argument_parameter_s, arguments.array[1], fake_make_operation_argument_parameter_s_length) == F_equal_to) {

      f_array_length_t i = 2;
      f_array_length_t j = 0;

      // 0 = unknown, 1 = fail, 2 = pass.
      uint8_t result = 0;

      *operation_if = fake_make_operation_if_type_true_next;

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

      if (result < 2) {
        *operation_if = fake_make_operation_if_type_false_next;
      }
    }
  }
#endif // _di_fake_make_operate_process_type_if_defined_

#ifndef _di_fake_make_operate_process_type_if_greater_if_lesser_
  f_status_t fake_make_operate_process_type_if_greater_if_lesser(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) {

    f_status_t status = F_none;

    f_string_range_t range = f_string_range_t_initialize;
    f_number_unsigned_t number_left = 0;
    f_number_unsigned_t number_right = 0;

    bool is_negative_left = F_false;
    bool is_negative_right = F_false;

    f_array_length_t i = 1;

    const uint8_t type_if = *operation_if;

    *operation_if = fake_make_operation_if_type_true_next;

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

        if (type_if == fake_make_operation_if_type_if_greater) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left > number_right)) {
              *operation_if = fake_make_operation_if_type_false_next;

              break;
            }
          }
          else if (!is_negative_left && is_negative_right) {
            *operation_if = fake_make_operation_if_type_false_next;

            break;
          }
        }
        else if (type_if == fake_make_operation_if_type_if_greater_equal) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left >= number_right)) {
              *operation_if = fake_make_operation_if_type_false_next;

              break;
            }
          }
          else if (!is_negative_left && is_negative_right) {
            *operation_if = fake_make_operation_if_type_false_next;

            break;
          }
        }
        else if (type_if == fake_make_operation_if_type_if_less) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left < number_right)) {
              *operation_if = fake_make_operation_if_type_false_next;

              break;
            }
          }
          else if (is_negative_left && !is_negative_right) {
            *operation_if = fake_make_operation_if_type_false_next;

            break;
          }
        }
        else if (type_if == fake_make_operation_if_type_if_less_equal) {

          if (is_negative_left == is_negative_right) {
            if (!(number_left <= number_right)) {
              *operation_if = fake_make_operation_if_type_false_next;

              break;
            }
          }
          else if (is_negative_left && !is_negative_right) {
            *operation_if = fake_make_operation_if_type_false_next;

            break;
          }
        }
      } // for
    }

    if (F_status_is_error(status)) {
      *operation_if = fake_make_operation_if_type_false_always_next;

      if (main->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
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

#ifndef _di_fake_make_operate_process_type_modes_
  f_status_t fake_make_operate_process_type_modes(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;

    f_file_mode_t mode_rule = 0;
    uint8_t replace = 0;

    status = fake_make_get_id_mode(main, data_make->error, arguments.array[0], &mode_rule, &replace);
    if (F_status_is_error(status)) return 0;

    mode_t mode = 0;
    mode_t mode_file = 0;

    for (f_array_length_t i = 1; i < arguments.used; ++i, mode = 0) {

      status = f_file_mode_read(arguments.array[i].string, &mode_file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_read", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file);

        break;
      }

      status = f_file_mode_determine(mode_file, mode_rule, replace, macro_f_file_type_is_directory(mode_file), &mode);

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_mode_determine", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file);

        break;
      }

      if (all) {
        status = fll_file_mode_set_all(arguments.array[i].string, mode, fake_make_operation_recursion_depth_max_d);
      }
      else {
        status = f_file_mode_set(arguments.array[i].string, mode);
      }

      if (F_status_is_error(status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), all ? "fll_file_mode_set_all" : "f_file_mode_set", F_true, arguments.array[i].string, "change mode of", fll_error_file_type_file);

        break;
      }

      if (main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Changed mode of '%Q' to %#@u.%c", main->output.to.stream, arguments.array[i], mode, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_modes_

#ifndef _di_fake_make_operate_process_type_move_
  f_status_t fake_make_operate_process_type_move(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;
    f_status_t status_file = F_none;

    const f_array_length_t total = arguments.used -1;

    fl_directory_recurse_t recurse = fl_directory_recurse_t_initialize;

    f_array_length_t destination_length = 0;

    if (main->error.verbosity == f_console_verbosity_verbose) {
      recurse.output = main->output.to;
      recurse.verbose = fake_verbose_print_move;
    }

    bool existing = F_true;

    // In this case, the destination could be a file, so confirm this.
    if (arguments.used == 2) {
      status_file = f_directory_is(arguments.array[1].string);

      if (F_status_is_error(status_file)) {
        fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_is", F_true, arguments.array[1].string, "identify", fll_error_file_type_directory);

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
        fll_error_file_print(data_make->error, F_status_set_fine(status), "fll_file_move", F_true, arguments.array[i].string, "move", fll_error_file_type_directory);

        status = F_status_set_error(F_failure);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_move_

#ifndef _di_fake_make_operate_process_type_owners_
  f_status_t fake_make_operate_process_type_owners(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) {

    f_status_t status = F_none;
    uid_t id = 0;

    status = fake_make_get_id_owner(main, data_make->error, arguments.array[0], &id);
    if (F_status_is_error(status)) return status;

    f_status_t status_file = F_none;

    for (f_array_length_t i = 1; i < arguments.used; ++i) {

      status_file = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

      if (F_status_is_error(status_file)) {
        status = status_file;

        fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

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

        fll_error_file_print(data_make->error, F_status_set_fine(status), all ? "fll_file_role_change_all" : "f_file_role_change", F_true, arguments.array[i].string, "change owner of", fll_error_file_type_file);
      }
      else if (main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("%s owner of '%Q' to %u.%c", main->output.to.stream, all ? "Recursively changed" : "Changed", arguments.array[i], id, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_owners_

#ifndef _di_fake_make_operate_process_type_pop_
  f_status_t fake_make_operate_process_type_pop(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    f_string_dynamic_resize(0, &data_make->path.stack.array[data_make->path.stack.used - 1]);

    --data_make->path.stack.used;

    status = f_path_change(data_make->path.stack.array[data_make->path.stack.used - 1].string);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_stack_max(main, data_make->error, F_status_set_fine(status), "f_path_change", data_make->path.stack.array[data_make->path.stack.used - 1].string);

      return 0;
    }

    if (main->error.verbosity == f_console_verbosity_verbose) {
      status = fake_make_path_relative(main, data_make, data_make->path.stack.array[data_make->path.stack.used - 1]);

      // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "fake_make_path_relative", F_true);
        fll_print_format("Changed to project path '%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, data_make->path.stack.array[data_make->path.stack.used - 1], main->context.set.notable, f_string_eol_s[0]);
      }
      else {
        fll_print_format("Changed to project path '%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, data_make->path_cache, main->context.set.notable, f_string_eol_s[0]);
      }
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_pop_

#ifndef _di_fake_make_operate_process_type_to_
  f_status_t fake_make_operate_process_type_to(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;

    status = fake_make_assure_inside_project(main, data_make, arguments.array[0]);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string);

      if (F_status_set_fine(status) == F_false) {
        status = F_status_set_error(F_failure);
      }

      return status;
    }

    status = f_path_change(arguments.array[0].string);

    if (F_status_is_error(status)) {
      fake_print_message_section_operation_path_stack_max(main, data_make->error, F_status_set_fine(status), "f_path_change", arguments.array[0].string);
    }
    else {
      status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, &data_make->path.stack);

      if (F_status_set_fine(status) == F_array_too_large) {
        fake_print_message_section_operation_path_stack_max(main, data_make->error, F_array_too_large, "f_string_dynamics_increase_by", "path stack");

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

      if (main->error.verbosity == f_console_verbosity_verbose) {
        status = fake_make_path_relative(main, data_make, data_make->path.stack.array[data_make->path.stack.used]);

        // The created relative path is for verbosity purposes and as such its failure to be processed should not be treated as a failure of the function.
        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "fake_make_path_relative", F_true);
          fll_print_format("Changed to project path '%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, data_make->path.stack.array[data_make->path.stack.used], main->context.set.notable, f_string_eol_s[0]);
        }
        else {
          fll_print_format("Changed to project path '%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, data_make->path_cache, main->context.set.notable, f_string_eol_s[0]);
        }
      }

      ++data_make->path.stack.used;
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_to_

#ifndef _di_fake_make_operate_process_type_top_
  f_status_t fake_make_operate_process_type_top(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    {
      f_status_t status = F_none;

      status = f_path_change_at(data_make->path.top.id);

      if (F_status_is_error(status)) {
        fake_print_message_section_operation_path_stack_max(main, data_make->error, F_status_set_fine(status), "f_path_change", arguments.array[0].string);

        return status;
      }
    }

    if (main->error.verbosity == f_console_verbosity_verbose) {
      fll_print_format("Changed to project path ''.%c", main->output.to.stream, f_string_eol_s[0]);
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
  f_status_t fake_make_operate_process_type_touch(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) {

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    macro_f_mode_t_set_default_umask(mode, main->umask);

    for (f_array_length_t i = 1; i < arguments.used; ++i) {

      if (fl_string_dynamic_compare_string(fake_make_operation_argument_file_s, arguments.array[0], fake_make_operation_argument_file_s_length) == F_equal_to) {
        status = f_file_touch(arguments.array[i].string, mode.regular, F_false);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_touch", F_true, data_make->path_cache.string, "touch", fll_error_file_type_file);
          }
          else {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_file_touch", F_true, arguments.array[i].string, "touch", fll_error_file_type_file);
          }

          break;
        }
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory_s, arguments.array[0], fake_make_operation_argument_directory_s_length) == F_equal_to) {
        status = f_directory_touch(arguments.array[i].string, mode.directory);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_touch", F_true, data_make->path_cache.string, "touch", fll_error_file_type_directory);
          }
          else {
            fll_error_file_print(data_make->error, F_status_set_fine(status), "f_directory_touch", F_true, arguments.array[i].string, "touch", fll_error_file_type_directory);
          }

          break;
        }
      }

      if (main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("Touched '%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, arguments.array[i], main->context.set.notable, f_string_eol_s[0]);
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_type_touch_

#ifdef __cplusplus
} // extern "C"
#endif
