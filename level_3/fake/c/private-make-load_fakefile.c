#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-load.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_load_fakefile_
  void fake_make_load_fakefile(fake_main_t * const main, fake_make_data_t *data_make, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (fake_signal_received(main)) {
      *status = F_status_set_error(F_interrupt);

      return;
    }

    data_make->fakefile.used = 0;

    *status = fake_file_buffer(main, main->file_data_build_fakefile.string, &data_make->buffer);
    if (F_status_is_error(*status)) return;

    if (!data_make->buffer.used) {
      if (main->error.verbosity == f_console_verbosity_verbose) {
        flockfile(main->warning.to.stream);

        fl_print_format("%c%[%SThe fakefile '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
        fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, main->file_data_build_fakefile, main->warning.notable);
        fl_print_format("%[' is empty.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

        funlockfile(main->warning.to.stream);
      }

      return;
    }

    f_fss_objects_t list_objects = f_fss_objects_t_initialize;
    f_fss_contents_t list_contents = f_fss_contents_t_initialize;

    {
      f_string_range_t range = macro_f_string_range_t_initialize(data_make->buffer.used);
      f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      {
        f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_fss, 0, (void *) &main, 0);

        *status = fll_fss_basic_list_read(data_make->buffer, state, &range, &list_objects, &list_contents, &delimits, 0, &comments);
      }

      if (F_status_is_error(*status)) {
        fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_basic_list_read", main->file_data_build_fakefile.string, range, F_true);
      }
      else {
        *status = fl_fss_apply_delimit(delimits, &data_make->buffer);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);
        }
      }

      macro_f_fss_delimits_t_delete_simple(delimits);
      macro_f_fss_comments_t_delete_simple(comments);

      if (F_status_is_error(*status)) {
        macro_f_fss_objects_t_delete_simple(list_objects);
        macro_f_fss_contents_t_delete_simple(list_contents);

        return;
      }
    }

    {
      bool missing_main = F_true;
      bool missing_settings = F_true;

      f_fss_set_t settings = f_fss_set_t_initialize;

      f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_fss, 0, (void *) &main, 0);

      const f_string_static_t name_settings = macro_f_string_static_t_initialize(fake_make_section_settings_s, fake_make_section_settings_s_length);
      const f_string_static_t name_main = macro_f_string_static_t_initialize(fake_make_section_main_s, fake_make_section_main_s_length);

      const f_string_range_t name_settings_range = macro_f_string_range_t_initialize(fake_make_section_settings_s_length);
      const f_string_range_t name_main_range = macro_f_string_range_t_initialize(fake_make_section_main_s_length);

      if (list_objects.used > data_make->fakefile.size) {
        macro_f_fss_nameds_t_resize((*status), data_make->fakefile, list_objects.used);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "macro_f_fss_nameds_t_resize", F_true);

        macro_f_fss_set_t_delete_simple(settings);
        macro_f_fss_objects_t_delete_simple(list_objects);
        macro_f_fss_contents_t_delete_simple(list_contents);

        return;
      }

      {
        f_string_range_t content_range = f_string_range_t_initialize;
        f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

        for (f_array_length_t i = 0; i < list_objects.used; ++i) {

          if (!(i % fake_signal_check_short_d) && fake_signal_received(main)) {
            *status = F_status_set_error(F_interrupt);

            break;
          }

          if (fl_string_dynamic_partial_compare(name_settings, data_make->buffer, name_settings_range, list_objects.array[i]) == F_equal_to) {
            if (!missing_settings) {
              fake_print_warning_settings_object_multiple(main, main->file_data_build_fakefile.string, "list", name_settings.string);

              continue;
            }

            delimits.used = 0;
            content_range = list_contents.array[i].array[0];

            *status = fll_fss_extended_read(data_make->buffer, state, &content_range, &settings.objects, &settings.contents, 0, 0, &delimits, 0);

            if (F_status_is_error(*status)) {
              fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_extended_read", main->file_data_build_fakefile.string, content_range, F_true);

              break;
            }

            *status = fl_fss_apply_delimit(delimits, &data_make->buffer);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);

              break;
            }

            missing_settings = F_false;

            continue;
          }
          else if (fl_string_dynamic_partial_compare(name_main, data_make->buffer, name_main_range, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_print_warning_settings_object_multiple(main, main->file_data_build_fakefile.string, "list", name_main.string);

              continue;
            }

            missing_main = F_false;
            data_make->main = data_make->fakefile.used;
          }

          data_make->fakefile.array[data_make->fakefile.used].name = list_objects.array[i];

          delimits.used = 0;
          content_range = list_contents.array[i].array[0];

          *status = fll_fss_extended_read(data_make->buffer, state, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotess, &delimits, 0);

          if (F_status_is_error(*status)) {
            fake_print_error_fss(main, F_status_set_fine(*status), "fll_fss_extended_read", main->file_data_build_fakefile.string, content_range, F_true);

            break;
          }

          *status = fl_fss_apply_delimit(delimits, &data_make->buffer);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fl_fss_apply_delimit", F_true);

            break;
          }

          ++data_make->fakefile.used;
        } // for

        macro_f_fss_delimits_t_delete_simple(delimits);
      }

      macro_f_fss_objects_t_delete_simple(list_objects);
      macro_f_fss_contents_t_delete_simple(list_contents);

      if (F_status_is_error(*status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      if (missing_main) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%SThe fakefile '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, main->file_data_build_fakefile, main->error.notable);
          fl_print_format("%[' is missing the required '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, fake_make_section_main_s, main->error.notable);
          fl_print_format("%[' object.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        *status = F_status_set_error(F_failure);

        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // Always have the parameter variable "return" map at index 0 and be pre-initialized.
      {
        f_string_t function_name = "macro_f_string_map_multis_t_resize";

        macro_f_string_map_multis_t_resize(*status, data_make->setting_make.parameter, F_memory_default_allocation_small_d);

        if (F_status_is_error_not(*status)) {
          data_make->setting_make.parameter.used = 1;

          function_name = "f_string_append";
          *status = f_string_append(fake_make_setting_return_s, fake_make_setting_return_s_length, &data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_error_not(*status)) {
          function_name = "f_string_dynamic_terminate_after";
          *status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_error_not(*status)) {
          function_name = "f_string_dynamics_resize";
          *status = f_string_dynamics_resize(1, &data_make->setting_make.parameter.array[0].value);
        }

        if (F_status_is_error_not(*status)) {
          function_name = "f_string_dynamic_terminate_after";
          *status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
        }

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), function_name, F_true);

          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      f_string_range_t *range_compiler = 0;
      f_string_range_t *range_indexer = 0;

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_true;
      data_make->setting_make.fail = fake_make_operation_fail_type_exit;

      if (settings.objects.used) {
        bool unmatched_fail = F_true;
        bool unmatched_load = F_true;

        for (f_array_length_t i = 0; i < settings.objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(fake_make_setting_compiler_s, data_make->buffer, fake_make_setting_compiler_s_length, settings.objects.array[i]) == F_equal_to) {
            if (range_compiler) {
              fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_compiler_s);
            }
            else {
              if (settings.contents.array[i].used) {
                range_compiler = &settings.contents.array[i].array[0];

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_compiler_s);
                }
              }
              else {
                fake_print_warning_settings_content_empty(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings_s);
              }
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_environment_s, data_make->buffer, fake_make_setting_environment_s_length, settings.objects.array[i]) == F_equal_to) {
            f_string_dynamic_t name_define = f_string_dynamic_t_initialize;

            f_array_length_t j = 0;
            f_array_length_t k = 0;

            for (; j < settings.contents.array[i].used; ++j) {

              *status = f_string_dynamic_partial_append_nulless(data_make->buffer, settings.contents.array[i].array[j], &name_define);

              if (F_status_is_error(*status)) {
                fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);
                break;
              }

              *status = f_string_dynamic_terminate_after(&name_define);

              if (F_status_is_error(*status)) {
                fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
                break;
              }

              // The environment settings are stored in the build settings rathe than the make settings.
              if (fake_make_operate_validate_define_name(name_define) == F_true) {
                for (k = 0; k < data_make->setting_build.environment.used; ++k) {
                  if (fl_string_dynamic_compare(name_define, data_make->setting_build.environment.array[k]) == F_equal_to) {
                    break;
                  }
                } // for

                if (k == data_make->setting_build.environment.used) {
                  *status = f_string_dynamics_increase(F_memory_default_allocation_small_d, &data_make->setting_build.environment);

                  if (F_status_is_error(*status)) {
                    fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);
                    break;
                  }

                  // Include the terminating NULL when copying.
                  ++name_define.used;

                  *status = f_string_dynamic_append(name_define, &data_make->setting_build.environment.array[data_make->setting_build.environment.used]);

                  if (F_status_is_error(*status)) {
                    fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                    break;
                  }

                  // Ensure that the terminating NULL is after the end of the string used size.
                  --data_make->setting_build.environment.array[data_make->setting_build.environment.used++].used;
                }
                else if (main->warning.verbosity == f_console_verbosity_verbose) {
                  flockfile(main->warning.to.stream);

                  fl_print_format("%c%[%SThe environment name '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
                  fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, name_define, main->warning.notable);
                  fl_print_format("%[' is already added.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

                  funlockfile(main->warning.to.stream);
                }
              }
              else if (main->warning.verbosity == f_console_verbosity_verbose) {
                flockfile(main->warning.to.stream);

                fl_print_format("%c%[%SThe environment name '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
                fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, name_define, main->warning.notable);
                fl_print_format("%[' is invalid, ignoring.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

                funlockfile(main->warning.to.stream);
              }

              name_define.used = 0;
            } // for

            if (F_status_is_error(*status)) {
              macro_f_string_dynamic_t_delete_simple(name_define);

              break;
            }

            *status = F_none;
            macro_f_string_dynamic_t_delete_simple(name_define);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_fail_s, data_make->buffer, fake_make_setting_fail_s_length, settings.objects.array[i]) == F_equal_to) {
            if (unmatched_fail) {
              if (settings.contents.array[i].used) {
                if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_exit_s, data_make->buffer, fake_make_operation_argument_exit_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_exit;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_warn_s, data_make->buffer, fake_make_operation_argument_warn_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_warn;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_ignore_s, data_make->buffer, fake_make_operation_argument_ignore_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_ignore;
                }
                else {
                  fake_print_warning_settings_content_invalid(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings_s);
                }

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_fail_s);
                }

                unmatched_fail = F_false;
              }
              else {
                fake_print_warning_settings_content_empty(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings_s);
              }
            }
            else {
              fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_fail_s);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_indexer_s, data_make->buffer, fake_make_setting_indexer_s_length, settings.objects.array[i]) == F_equal_to) {
            if (range_indexer) {
              fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_indexer_s);
            }
            else {
              if (settings.contents.array[i].used) {
                range_indexer = &settings.contents.array[i].array[0];

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_indexer_s);
                }
              }
              else {
                fake_print_warning_settings_content_empty(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings_s);
              }
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_load_build_s, data_make->buffer, fake_make_setting_load_build_s_length, settings.objects.array[i]) == F_equal_to) {
            if (unmatched_load) {
              if (settings.contents.array[i].used) {
                if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_yes_s, data_make->buffer, fake_common_setting_bool_yes_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_true;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_no_s, data_make->buffer, fake_common_setting_bool_no_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_false;
                }
                else {
                  fake_print_warning_settings_content_invalid(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings_s);
                }

                unmatched_load = F_false;

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_load_build_s);
                }
              }
              else {
                fake_print_warning_settings_content_empty(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings_s);
              }
            }
            else {
              fake_print_warning_settings_content_multiple(main, main->file_data_build_fakefile.string, fake_make_setting_load_build_s);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_parameter_s, data_make->buffer, fake_make_setting_parameter_s_length, settings.objects.array[i]) == F_equal_to) {
            if (settings.contents.array[i].used) {
              if (fl_string_dynamic_partial_compare_string(fake_make_setting_return_s, data_make->buffer, fake_make_setting_return_s_length, settings.contents.array[i].array[0]) == F_equal_to) {
                if (settings.contents.array[i].used > 1) {
                  f_string_t function_name = 0;

                  // Each define replaces the previous define.
                  data_make->setting_make.parameter.array[0].value.array[0].used = 0;

                  for (f_array_length_t j = 1; j < settings.contents.array[i].used; ++j) {

                    function_name = "f_string_dynamic_partial_append_nulless";
                    *status = f_string_dynamic_partial_append_nulless(data_make->buffer, settings.contents.array[i].array[j], &data_make->setting_make.parameter.array[0].value.array[0]);

                    if (F_status_is_error_not(*status)) {
                      function_name = "f_string_dynamic_terminate_after";
                      *status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
                    }

                    if (F_status_is_error_not(*status) && j + 1 < settings.contents.array[i].used) {
                      function_name = "f_string_append_assure";
                      *status = f_string_append_assure(f_string_space_s, 1, &data_make->setting_make.parameter.array[0].value.array[0]);
                    }

                    if (F_status_is_error(*status)) {
                      fll_error_print(main->error, F_status_set_fine(*status), function_name, F_true);

                      break;
                    }
                  } // for

                  if (F_status_is_error(*status)) break;
                }
              }
            }
            else {
              fake_print_warning_settings_content_empty(main, main->file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings_s);
            }
          }
        } // for

        if (F_status_is_error(*status)) {
          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      if (F_status_is_error_not(*status) && data_make->setting_make.load_build) {
        f_string_static_t stub = f_string_static_t_initialize;

        fake_build_load_setting(main, stub, &data_make->setting_build, status);

        if (F_status_is_error(*status) && *status != F_status_set_error(F_interrupt)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fake_build_load_setting", F_true);
        }
      }

      if (F_status_is_error(*status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // If either compiler or indexer is specified, each will replace any existing build_compiler or build_indexer, respectively.
      if (range_compiler) {
        data_make->setting_build.build_compiler.used = 0;

        *status = f_string_dynamic_partial_append(data_make->buffer, *range_compiler, &data_make->setting_build.build_compiler);
      }

      if (F_status_is_error_not(*status) && range_indexer) {
        data_make->setting_build.build_indexer.used = 0;

        *status = f_string_dynamic_partial_append(data_make->buffer, *range_indexer, &data_make->setting_build.build_indexer);
      }

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) != F_interrupt) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_partial_append", F_true);
        }

        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      f_string_map_multis_t define = f_string_map_multis_t_initialize;

      // Load the fakefile "settings" as if they are build "settings".
      fake_build_load_setting_process(main, F_false, main->file_data_build_fakefile.string, data_make->buffer, settings.objects, settings.contents, &data_make->setting_build, status);

      if (F_status_is_error_not(*status) && settings.objects.used) {
        const f_string_t settings_name[] = {
          fake_make_setting_define_s,
          fake_make_setting_parameter_s,
        };

        const f_array_length_t settings_length[] = {
          fake_make_setting_define_s_length,
          fake_make_setting_parameter_s_length,
        };

        f_string_map_multis_t *settings_value[] = {
          &define,
          &data_make->setting_make.parameter,
        };

        *status = fll_fss_snatch_map_apart(data_make->buffer, settings.objects, settings.contents, settings_name, settings_length, 2, settings_value, 0, 0);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fll_fss_snatch_map_apart", F_true);

          macro_f_string_map_multis_t_delete_simple(define);
          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      if (define.used) {
        f_status_t status_validate = F_none;
        f_string_dynamic_t combined = f_string_dynamic_t_initialize;

        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < define.used; ++i) {

          status_validate = fake_make_operate_validate_define_name(define.array[i].name);

          if (status_validate) {
            combined.used = 0;

            for (j = 0; j < define.array[i].value.used; ++j) {

              *status = f_string_dynamic_mash(f_string_space_s, 1, define.array[i].value.array[j], &combined);

              if (F_status_is_error(*status)) {
                fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_mash_nulless", F_true);

                break;
              }
            } // for

            if (F_status_is_error(*status)) break;

            *status = f_string_dynamic_terminate_after(&combined);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);
              break;
            }

            *status = f_environment_set(define.array[i].name.string, combined.string, F_true);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_environment_set", F_true);

              break;
            }
          }
          else {
            if (main->error.verbosity != f_console_verbosity_quiet) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%SInvalid characters in the define setting name '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, define.array[i].name, main->error.notable);
              fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) are allowed.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);
            }

            *status = F_status_set_error(F_failure);

            break;
          }
        } // for

        macro_f_string_dynamic_t_delete_simple(combined);
      }

      macro_f_string_map_multis_t_delete_simple(define);
      macro_f_fss_set_t_delete_simple(settings);
    }
  }
#endif // _di_fake_make_load_fakefile_

#ifdef __cplusplus
} // extern "C"
#endif
