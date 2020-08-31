#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_assure_inside_project_
  f_return_status fake_make_assure_inside_project(const fake_data data, const f_string_static path, fake_make_data *data_make) {

    data_make->path_cache.used = 0;

    f_status status = fll_path_canonical(path.string, &data_make->path_cache);
    if (F_status_is_error(status)) return status;

    if (data_make->path_cache.used < data_make->path.stack.array[0].used) {
      return F_status_set_error(F_false);
    }

    const f_string_range range = f_macro_string_range_initialize(data_make->path.stack.array[0].used);

    if (range.start <= range.stop) {
      status = fl_string_dynamic_partial_compare(data_make->path.stack.array[0], data_make->path_cache, range, range);
      if (F_status_is_error(status)) return status;

      if (status) {
        if (data_make->path_cache.used == data_make->path.stack.array[0].used) {
          return F_true;
        }

        if (data_make->path_cache.string[data_make->path.stack.array[0].used] == f_path_separator[0]) {
          return F_true;
        }
      }
    }

    return F_status_set_error(F_false);
  }
#endif // _di_fake_make_assure_inside_project_

#ifndef _di_fake_make_get_id_group_
  f_return_status fake_make_get_id_group(const fake_data data, const fake_make_print print, const f_string_static buffer, gid_t *id) {
    const f_string_range range = f_macro_string_range_initialize(buffer.used);

    f_number_unsigned number = 0;

    f_status status = fl_conversion_string_to_number_unsigned(buffer.string, &number, range);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        status = f_account_id_group_by_name(buffer.string, id);

        if (F_status_is_error(status)) {
          fake_print_message(data, status, "f_account_id_group_by_name", F_true, print);
          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(print.to, "%c", f_string_eol[0]);
            fl_color_print(print.to, print.context, data.context.reset, "%s: The group name '", print.prefix);
            fl_color_print(print.to, data.context.notable, data.context.reset, "%s", buffer.string);
            fl_color_print_line(print.to, print.context, data.context.reset, "' was not found.");
          }

          return F_status_set_error(F_failure);
        }

        return F_none;
      }

      fake_print_message(data, status, "fl_conversion_string_to_number_unsigned", F_true, print);
      return F_status_set_error(status);
    }
    else if (number > f_type_size_32_unsigned) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: The number '", print.prefix);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", number);
        fl_color_print_line(print.to, print.context, data.context.reset, "' is too large.");
      }
    }

    *id = (gid_t) number;
    return status;
  }
#endif // _di_fake_make_get_id_group_

#ifndef _di_fake_make_get_id_mode_
  f_return_status fake_make_get_id_mode(const fake_data data, const fake_make_print print, const f_string_static buffer, f_file_mode *mode, uint8_t *replace) {
    if (!buffer.used) {
      fake_print_message(data, F_parameter, "fake_make_get_id_mode", F_true, print);
      return F_status_set_error(F_parameter);
    }

    f_status status = f_file_mode_from_string(buffer.string, data.umask, mode, replace);

    if (F_status_is_error(status)) {
      if (data.verbosity != fake_verbosity_quiet) {
        if (F_status_set_fine(status) == F_syntax) {
          fprintf(print.to, "%c", f_string_eol[0]);
          fl_color_print(print.to, print.context, data.context.reset, "%s: The mode '", print.prefix);
          fl_color_print(print.to, data.context.notable, data.context.reset, "%s", buffer.string);
          fl_color_print_line(print.to, print.context, data.context.reset, "' is invalid.");
        }
        else {
          fake_print_message(data, status, "f_file_mode_from_string", F_true, print);
        }
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fake_make_get_id_mode_

#ifndef _di_fake_make_get_id_owner_
  f_return_status fake_make_get_id_owner(const fake_data data, const fake_make_print print, const f_string_static buffer, uid_t *id) {
    const f_string_range range = f_macro_string_range_initialize(buffer.used);

    f_number_unsigned number = 0;

    f_status status = fl_conversion_string_to_number_unsigned(buffer.string, &number, range);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        status = f_account_id_user_by_name(buffer.string, id);

        if (F_status_is_error(status)) {
          fake_print_message(data, status, "f_account_id_user_by_name", F_true, print);
          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          if (data.verbosity != fake_verbosity_quiet) {
            fprintf(print.to, "%c", f_string_eol[0]);
            fl_color_print(print.to, print.context, data.context.reset, "%s: The user name '", print.prefix);
            fl_color_print(print.to, data.context.notable, data.context.reset, "%s", buffer.string);
            fl_color_print_line(print.to, print.context, data.context.reset, "' was not found.");
          }

          return F_status_set_error(F_failure);
        }

        return F_none;
      }

      fake_print_message(data, status, "fl_conversion_string_to_number_unsigned", F_true, print);
      return F_status_set_error(status);
    }
    else if (number > f_type_size_32_unsigned) {
      if (data.verbosity != fake_verbosity_quiet) {
        fprintf(print.to, "%c", f_string_eol[0]);
        fl_color_print(print.to, print.context, data.context.reset, "%s: The number '", print.prefix);
        fl_color_print(print.to, data.context.notable, data.context.reset, "%llu", number);
        fl_color_print_line(print.to, print.context, data.context.reset, "' is too large.");
      }
    }

    *id = (uid_t) number;
    return status;
  }
#endif // _di_fake_make_get_id_owner_

#ifndef _di_fake_make_load_fakefile_
  void fake_make_load_fakefile(const fake_data data, fake_make_data *data_make, f_status *status) {
    if (F_status_is_error(*status)) return;

    *status = fake_file_buffer(data, data.file_data_build_fakefile.string, &data_make->buffer);
    if (F_status_is_error(*status)) return;

    if (!data_make->buffer.used) {
      if (data.verbosity == fake_verbosity_verbose) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the fakefile '");
        fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", data.file_data_build_fakefile.string);
        fl_color_print(f_type_warning, data.context.warning, data.context.reset, "' is empty.");
      }

      return;
    }

    f_fss_objects list_objects = f_fss_objects_initialize;
    f_fss_contents list_contents = f_fss_contents_initialize;

    {
      f_string_range range = f_macro_string_range_initialize(data_make->buffer.used);

      *status = fll_fss_basic_list_read(&data_make->buffer, &range, &list_objects, &list_contents);
      if (F_status_is_error(*status)) {
        fake_print_error_fss(data, *status, "fll_fss_basic_list_read", data.file_data_build_fakefile.string, range, F_true);

        f_macro_fss_objects_delete_simple(list_objects);
        f_macro_fss_contents_delete_simple(list_contents);
        return;
      }
    }

    {
      bool missing_main = F_true;
      bool missing_settings = F_true;

      f_fss_set settings = f_fss_set_initialize;

      const f_string_static name_settings = f_macro_string_static_initialize(fake_make_section_settings, fake_make_section_settings_length);
      const f_string_static name_main = f_macro_string_static_initialize(fake_make_section_main, fake_make_section_main_length);

      const f_string_range name_settings_range = f_macro_string_range_initialize(fake_make_section_settings_length);
      const f_string_range name_main_range = f_macro_string_range_initialize(fake_make_section_main_length);

      f_macro_fss_nameds_new((*status), data_make->fakefile, list_objects.used);
      if (F_status_is_error(*status)) {
        fake_print_error(data, F_status_set_fine(*status), "f_macro_fss_nameds_new", F_true);

        f_macro_fss_set_delete_simple(settings);
        f_macro_fss_objects_delete_simple(list_objects);
        f_macro_fss_contents_delete_simple(list_contents);
        return;
      }

      {
        f_string_range content_range = f_string_range_initialize;

        for (f_array_length i = 0; i < list_objects.used; i++) {
          if (fl_string_dynamic_partial_compare(name_settings, data_make->buffer, name_settings_range, list_objects.array[i]) == F_equal_to) {
            if (!missing_settings) {
              fake_print_warning_settings_object_multiple(data, data.file_data_build_fakefile.string, "list", name_settings.string);
              continue;
            }

            content_range = list_contents.array[i].array[0];

            *status = fll_fss_extended_read(&data_make->buffer, &content_range, &settings.objects, &settings.contents, 0, 0);
            if (F_status_is_error(*status)) {
              fake_print_error_fss(data, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

              f_macro_fss_set_delete_simple(settings);
              f_macro_fss_objects_delete_simple(list_objects);
              f_macro_fss_contents_delete_simple(list_contents);
              return;
            }

            missing_settings = F_false;
            continue;
          }
          else if (fl_string_dynamic_partial_compare(name_main, data_make->buffer, name_main_range, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_print_warning_settings_object_multiple(data, data.file_data_build_fakefile.string, "list", name_main.string);
              continue;
            }

            missing_main = F_false;
            data_make->main = data_make->fakefile.used;
          }

          data_make->fakefile.array[data_make->fakefile.used].name = list_objects.array[i];

          content_range = list_contents.array[i].array[0];

          *status = fll_fss_extended_read(&data_make->buffer, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotedss);
          if (F_status_is_error(*status)) {
            fake_print_error_fss(data, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

            f_macro_fss_set_delete_simple(settings);
            f_macro_fss_objects_delete_simple(list_objects);
            f_macro_fss_contents_delete_simple(list_contents);
            return;
          }

          data_make->fakefile.used++;
        } // for
      }

      f_macro_fss_objects_delete_simple(list_objects);
      f_macro_fss_contents_delete_simple(list_contents);

      if (missing_main) {
        if (data.verbosity != fake_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: The fakefile '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", data.file_data_build_fakefile.string);
          fl_color_print(f_type_error, data.context.error, data.context.reset, "' is missing the required '");
          fl_color_print(f_type_error, data.context.notable, data.context.reset, "%s", fake_make_section_main);
          fl_color_print_line(f_type_error, data.context.error, data.context.reset, "' object.");
        }

        *status = F_status_set_error(F_failure);

        f_macro_fss_set_delete_simple(settings);
        return;
      }

      // always have the parameter variable "return" map at index 0 and pre-initialized.
      {
        f_string function_name = "f_macro_string_map_multis_new";

        f_macro_string_map_multis_new(*status, data_make->setting_make.parameter, f_memory_default_allocation_step);

        if (F_status_is_fine(*status)) {
          data_make->setting_make.parameter.used = 1;

          function_name = "fl_string_append";
          *status = fl_string_append(fake_make_setting_return, fake_make_setting_return_length, &data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_fine(*status)) {
          function_name = "fl_string_dynamic_terminate_after";
          *status = fl_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_fine(*status)) {
          function_name = "f_macro_string_dynamics_new";
          f_macro_string_dynamics_new(*status, data_make->setting_make.parameter.array[0].value, 1);
        }

        if (F_status_is_fine(*status)) {
          function_name = "fl_string_dynamic_terminate_after";
          *status = fl_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
        }

        if (F_status_is_error(*status)) {
          fake_print_error(data, *status, function_name, F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      f_string_range *range_compiler = 0;
      f_string_range *range_linker = 0;

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_true;
      data_make->setting_make.fail = fake_make_operation_fail_type_exit;

      if (settings.objects.used) {
        bool unmatched_fail = F_true;
        bool unmatched_load = F_true;

        for (f_array_length i = 0; i < settings.objects.used; i++) {
          if (fl_string_dynamic_partial_compare_string(fake_make_setting_compiler, data_make->buffer, fake_make_setting_compiler_length, settings.objects.array[i]) == F_equal_to) {
            if (range_compiler) {
              fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_compiler);
            }
            else {
              if (settings.contents.array[i].used) {
                range_compiler = &settings.contents.array[i].array[0];

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_compiler);
                }
              }
              else {
                fake_print_warning_settings_content_empty(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings);
              }
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_environment, data_make->buffer, fake_make_setting_environment_length, settings.objects.array[i]) == F_equal_to) {
            f_string_dynamic name_define = f_string_dynamic_initialize;

            f_array_length j = 0;
            f_array_length k = 0;

            for (; j < settings.contents.array[i].used; j++) {

              *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, settings.contents.array[i].array[j], &name_define);
              if (F_status_is_error(*status)) {
                fake_print_error(data, *status, "fl_string_dynamic_partial_append_nulless", F_true);

                f_macro_string_dynamic_delete_simple(name_define);
                f_macro_fss_set_delete_simple(settings);
                return;
              }

              *status = fl_string_dynamic_terminate_after(&name_define);
              if (F_status_is_error(*status)) {
                fake_print_error(data, *status, "fl_string_dynamic_terminate_after", F_true);

                f_macro_string_dynamic_delete_simple(name_define);
                f_macro_fss_set_delete_simple(settings);
                return;
              }

              if (fake_make_operate_validate_define_name(name_define) == F_true) {
                for (k = 0; k < data_make->setting_build.environment.used; k++) {
                  if (fl_string_dynamic_compare(name_define, data_make->setting_build.environment.array[k]) == F_equal_to) {
                    break;
                  }
                } // for

                if (k == data_make->setting_build.environment.used) {
                  if (data_make->setting_build.environment.used + 1 > data_make->setting_build.environment.size) {
                    *status = fl_string_dynamics_size_increase(f_memory_default_allocation_step, &data_make->setting_build.environment);

                    if (F_status_is_error(*status)) {
                      fake_print_error(data, *status, "fl_string_lengths_size_increase", F_true);

                      f_macro_string_dynamic_delete_simple(name_define);
                      f_macro_fss_set_delete_simple(settings);
                      return;
                    }
                  }

                  // Include the terminating NULL when copying.
                  name_define.used++;

                  *status = fl_string_dynamic_append(name_define, &data_make->setting_build.environment.array[data_make->setting_build.environment.used]);
                  if (F_status_is_error(*status)) {
                    fake_print_error(data, *status, "fl_string_dynamic_append", F_true);

                    f_macro_string_dynamic_delete_simple(name_define);
                    f_macro_fss_set_delete_simple(settings);
                    return;
                  }

                  // Ensure that the terminating NULL is after the end of the string used size.
                  data_make->setting_build.environment.array[data_make->setting_build.environment.used].used--;
                  data_make->setting_build.environment.used++;
                }
                else if (data.verbosity == fake_verbosity_verbose) {
                  fprintf(f_type_warning, "%c", f_string_eol[0]);
                  fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: The environment name '");
                  fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", name_define.string);
                  fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' is already added.");
                }
              }
              else if (data.verbosity == fake_verbosity_verbose) {
                fprintf(f_type_warning, "%c", f_string_eol[0]);
                fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: The environment name '");
                fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", name_define.string);
                fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' is invalid, ignoring.");
              }

              name_define.used = 0;
            } // for

            *status = F_none;
            f_macro_string_dynamic_delete_simple(name_define);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_fail, data_make->buffer, fake_make_setting_fail_length, settings.objects.array[i]) == F_equal_to) {
            if (unmatched_fail) {
              if (settings.contents.array[i].used) {
                if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_exit, data_make->buffer, fake_make_operation_argument_exit_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_exit;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_warn, data_make->buffer, fake_make_operation_argument_warn_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_warn;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_ignore, data_make->buffer, fake_make_operation_argument_ignore_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.fail = fake_make_operation_fail_type_ignore;
                }
                else {
                  fake_print_warning_settings_content_invalid(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings);
                }

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_fail);
                }

                unmatched_fail = F_false;
              }
              else {
                fake_print_warning_settings_content_empty(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings);
              }
            }
            else {
              fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_fail);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_linker, data_make->buffer, fake_make_setting_linker_length, settings.objects.array[i]) == F_equal_to) {
            if (range_linker) {
              fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_linker);
            }
            else {
              if (settings.contents.array[i].used) {
                range_linker = &settings.contents.array[i].array[0];

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_linker);
                }
              }
              else {
                fake_print_warning_settings_content_empty(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings);
              }
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_load_build, data_make->buffer, fake_make_setting_load_build_length, settings.objects.array[i]) == F_equal_to) {
            if (unmatched_load) {
              if (settings.contents.array[i].used) {
                if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_yes, data_make->buffer, fake_common_setting_bool_yes_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_true;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_no, data_make->buffer, fake_common_setting_bool_no_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_false;
                }
                else {
                  fake_print_warning_settings_content_invalid(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings);
                }

                unmatched_load = F_false;

                if (settings.contents.array[i].used > 1) {
                  fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_load_build);
                }
              }
              else {
                fake_print_warning_settings_content_empty(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings);
              }
            }
            else {
              fake_print_warning_settings_content_multiple(data, data.file_data_build_fakefile.string, fake_make_setting_load_build);
            }
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_parameter, data_make->buffer, fake_make_setting_parameter_length, settings.objects.array[i]) == F_equal_to) {
            if (settings.contents.array[i].used) {
              if (fl_string_dynamic_partial_compare_string(fake_make_setting_return, data_make->buffer, fake_make_setting_return_length, settings.contents.array[i].array[0]) == F_equal_to) {
                if (settings.contents.array[i].used > 1) {
                  f_string function_name = 0;

                  // each define replaces the previous define.
                  data_make->setting_make.parameter.array[0].value.array[0].used = 0;

                  for (f_array_length j = 1; j < settings.contents.array[i].used; j++) {
                    function_name = "fl_string_dynamic_partial_append_nulless";
                    *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, settings.contents.array[i].array[j], &data_make->setting_make.parameter.array[0].value.array[0]);

                    if (F_status_is_fine(*status)) {
                      function_name = "fl_string_dynamic_terminate_after";
                      *status = fl_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
                    }

                    if (F_status_is_fine(*status) && j + 1 < settings.contents.array[i].used) {
                      function_name = "fl_string_append_assure";
                      *status = fl_string_append_assure(" ", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
                    }

                    if (F_status_is_error(*status)) {
                      fake_print_error(data, *status, function_name, F_true);

                      f_macro_fss_set_delete_simple(settings);
                      return;
                    }
                  } // for
                }
              }
            }
            else {
              fake_print_warning_settings_content_empty(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], fake_make_section_settings);
            }
          }
        } // for
      }

      if (data_make->setting_make.load_build) {
        fake_build_load_setting(data, &data_make->setting_build, status);

        if (F_status_is_error(*status)) {
          fake_print_error(data, *status, "fake_build_load_setting", F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      // if either compiler or linker is specified, each will replace any existing build_compiler or build_linker, respectively.
      if (range_compiler) {
        data_make->setting_build.build_compiler.used = 0;
        *status = fl_string_dynamic_partial_append(data_make->buffer, *range_compiler, &data_make->setting_build.build_compiler);
      }

      if (F_status_is_fine(*status) && range_linker) {
        data_make->setting_build.build_linker.used = 0;
        *status = fl_string_dynamic_partial_append(data_make->buffer, *range_linker, &data_make->setting_build.build_linker);
      }

      if (F_status_is_error(*status)) {
        fake_print_error(data, *status, "fl_string_dynamic_partial_append", F_true);

        f_macro_fss_set_delete_simple(settings);
        return;
      }

      f_string_map_multis define = f_string_map_multis_initialize;

      fake_build_load_setting_process(data, data.file_data_build_fakefile.string, data_make->buffer, settings.objects, settings.contents, &data_make->setting_build, status);

      if (F_status_is_not_error(*status) && settings.objects.used) {
        const f_string settings_name[] = {
          fake_make_setting_define,
          fake_make_setting_parameter,
        };

        const f_string_length settings_length[] = {
          fake_make_setting_define_length,
          fake_make_setting_parameter_length,
        };

        f_string_map_multis *settings_value[] = {
          &define,
          &data_make->setting_make.parameter,
        };

        *status = fll_fss_snatch_map_apart(data_make->buffer, settings.objects, settings.contents, settings_name, settings_length, 2, settings_value, 0);
        if (F_status_is_error(*status)) {
          fake_print_error(data, F_status_set_fine(*status), "fll_fss_snatch_map_apart", F_true);

          f_macro_string_map_multis_delete_simple(define);
          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      if (define.used) {
        f_status status_validate = F_none;
        f_string_dynamic combined = f_string_dynamic_initialize;

        for (f_array_length i = 0; i < define.used; i++) {
          status_validate = fake_make_operate_validate_define_name(define.array[i].name);

          if (status_validate) {
            combined.used = 0;

            for (f_array_length j = 0; j < define.array[i].value.used; j++) {
              *status = fl_string_dynamic_mash(" ", 1, define.array[i].value.array[j], &combined);
              if (F_status_is_error(*status)) {
                fake_print_error(data, *status, "fl_string_dynamic_mash_nulless", F_true);
                break;
              }
            } // for

            if (F_status_is_error(*status)) break;

            *status = fl_string_dynamic_terminate_after(&combined);
            if (F_status_is_error(*status)) {
              fake_print_error(data, *status, "fl_string_dynamic_terminate_after", F_true);
              break;
            }

            *status = f_environment_set(define.array[i].name.string, combined.string, F_true);
            if (F_status_is_error(*status)) {
              fake_print_error(data, F_status_set_fine(*status), "f_environment_set", F_true);
              break;
            }
          }
          else {
            if (data.verbosity != fake_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: Invalid characters in the define setting name '");

              fl_color_print_code(f_type_error, data.context.notable);
              f_print_string_dynamic(f_type_error, define.array[i].name);
              fl_color_print_code(f_type_error, data.context.reset);

              fl_color_print_line(f_type_error, data.context.error, data.context.reset, "', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.");
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        f_macro_string_dynamic_delete_simple(combined);
      }

      f_macro_string_map_multis_delete_simple(define);
      f_macro_fss_set_delete_simple(settings);
    }
  }
#endif // _di_fake_make_load_fakefile_

#ifndef _di_fake_make_operate_
  f_return_status fake_make_operate(const fake_data data) {
    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "Making project.");
    }

    f_status status = F_none;
    f_mode mode = f_mode_initialize;

    f_string_lengths section_stack = f_string_lengths_initialize;
    fake_make_data data_make = fake_make_data_initialize;

    f_macro_string_dynamics_new(status, data_make.path.stack, f_memory_default_allocation_step);
    if (F_status_is_error(status)) {
      fake_print_error(data, F_status_set_fine(status), "f_macro_string_dynamics_new", F_true);
      return status;
    }

    status = f_path_current(F_true, &data_make.path.stack.array[0]);
    if (F_status_is_error(status)) {
      fake_print_error(data, F_status_set_fine(status), "f_path_current", F_true);

      fake_macro_make_data_delete_simple(data_make);
      return status;
    }

    status = f_directory_open(data_make.path.stack.array[0].string, F_false, &data_make.path.top);
    if (F_status_is_error(status)) {
      fake_print_error(data, F_status_set_fine(status), "f_directory_open", F_true);

      fake_macro_make_data_delete_simple(data_make);
      return status;
    }

    data_make.path.stack.used = 1;

    f_macro_mode_set_default_umask(mode, data.umask);

    fake_make_load_fakefile(data, &data_make, &status);

    if (data_make.setting_make.fail == fake_make_operation_fail_type_exit) {
      data_make.print.prefix = fake_make_print_error;
      data_make.print.context = data.context.error;
      data_make.print.to = f_type_error;
    }
    else if (data_make.setting_make.fail == fake_make_operation_fail_type_warn) {
      data_make.print.prefix = fake_make_print_warning;
      data_make.print.context = data.context.warning;
      data_make.print.to = f_type_warning;
    }
    else {
      data_make.print.to = 0;
    }

    fake_make_operate_section(data, data_make.main, &data_make, &section_stack, &status);

    if (data_make.path.current > 0) {
      f_file_close(&data_make.path.current);
    }

    {
      f_status status_path = f_path_change_at(data_make.path.top);

      if (F_status_is_error(status_path) && data.verbosity == fake_verbosity_verbose) {
        fprintf(f_type_warning, "%c", f_string_eol[0]);
        fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: Failed change back to orignal path '");
        fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", data_make.path.stack.array[0].string);
        fl_color_print(f_type_warning, data.context.warning, data.context.reset, "', status code = ");
        fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%llu", F_status_set_fine(status_path));
        fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, ".");
      }
    }

    f_file_close(&data_make.path.top);

    f_macro_string_lengths_delete_simple(section_stack);
    fake_macro_make_data_delete_simple(data_make);

    return status;
  }
#endif // _di_fake_make_operate_

#ifndef _di_fake_make_operate_expand_
  void fake_make_operate_expand(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_fss_content content, const f_fss_quoteds quoteds, fake_make_data *data_make, f_string_dynamics *arguments, f_status *status) {
    if (F_status_is_error(*status)) return;
    if (content.used == 0) return;

    // pre-allocate the known arguments size.
    if (arguments->used + content.used > arguments->size) {
      if (arguments->used + content.used > F_buffer_too_large) {
        *status = F_status_set_error(F_buffer_too_large);
      }
      else {
        f_macro_string_dynamics_resize((*status), (*arguments), arguments->used + content.used);
      }

      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true, data_make->print);
        return;
      }
    }

    const f_string_static vocabulary_define = f_macro_string_static_initialize(iki_vocabulary_0002_define, iki_vocabulary_0002_define_length);
    const f_string_static vocabulary_parameter = f_macro_string_static_initialize(iki_vocabulary_0002_parameter, iki_vocabulary_0002_parameter_length);

    const f_string_range range_define = f_macro_string_range_initialize(iki_vocabulary_0002_define_length);
    const f_string_range range_parameter = f_macro_string_range_initialize(iki_vocabulary_0002_parameter_length);

    f_iki_variable iki_variable = f_iki_variable_initialize;
    f_iki_vocabulary iki_vocabulary = f_iki_vocabulary_initialize;
    f_iki_content iki_content = f_iki_content_initialize;

    f_string_range range = f_string_range_initialize;
    f_string_map_multis *parameter = &data_make->setting_make.parameter;

    bool unmatched = F_true;
    bool parameter_is = F_false;
    bool define_is = F_false;

    f_array_length i = 0;
    f_array_length j = 0;
    f_array_length k = 0;
    f_array_length l = 0;

    f_array_length used_arguments = 0;

    f_string_length previous = 0;

    for (; i < content.used; i++) {

      if (content.array[i].start > content.array[i].stop) {
        continue;
      }

      range = content.array[i];

      used_arguments = arguments->used;

      *status = fl_iki_read(&data_make->buffer, &range, &iki_variable, &iki_vocabulary, &iki_content);
      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "fl_iki_read", F_true, data_make->print);
        break;
      }

      if (arguments->used == arguments->size) {
        *status = fl_string_dynamics_size_increase(f_memory_default_allocation_step, arguments);
        if (F_status_is_error(*status)) {
          fake_print_message(data, F_status_set_fine(*status), "fl_string_lengths_size_increase", F_true, data_make->print);
          return;
        }
      }

      if (iki_variable.used) {
        if (iki_variable.array[0].start > 0 && content.array[i].start < iki_variable.array[0].start) {
          range.start = content.array[i].start;
          range.stop = iki_variable.array[0].start - 1;

          *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
          if (F_status_is_error(*status)) {
            fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true, data_make->print);
            break;
          }
        }

        for (j = 0, previous = iki_variable.array[0].start; j < iki_variable.used; j++) {
          parameter_is = F_false;
          define_is = F_false;

          if (previous + 1 < iki_variable.array[j].start) {
            range.start = previous + 1;
            range.stop = iki_variable.array[j].start - 1;

            *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
            if (F_status_is_error(*status)) {
              fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true, data_make->print);
              break;
            }
          }

          *status = fl_string_dynamic_partial_compare(vocabulary_define, data_make->buffer, range_define, iki_vocabulary.array[j]);

          if (*status == F_equal_to) {
            define_is = F_true;
          }
          else if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_compare(vocabulary_parameter, data_make->buffer, range_parameter, iki_vocabulary.array[j]);

            if (*status == F_equal_to) {
              parameter_is = F_true;
            }
          }

          if (F_status_is_error(*status)) {
            fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_partial_compare", F_true, data_make->print);
            break;
          }

          if (parameter_is) {
            unmatched = F_true;

            if (parameter->used) {
              for (k = 0; k < parameter->used; k++) {
                *status = fl_string_dynamic_partial_compare_dynamic(parameter->array[k].name, data_make->buffer, iki_content.array[j]);

                if (*status == F_equal_to) {
                  unmatched = F_false;

                  if (parameter->array[k].value.used) {
                    if (quoteds.array[i]) {
                      for (l = 0; l < parameter->array[k].value.used; l++) {
                        if (l > 0) {
                          *status = fl_string_append(" ", 1, &arguments->array[arguments->used]);
                          if (F_status_is_error(*status)) {
                            fake_print_message(data, F_status_set_fine(*status), "fl_string_append", F_true, data_make->print);
                            break;
                          }
                        }

                        *status = fl_string_dynamic_append_nulless(parameter->array[k].value.array[l], &arguments->array[arguments->used]);
                        if (F_status_is_error(*status)) {
                          fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true, data_make->print);
                          break;
                        }
                      } // for
                    }
                    else {
                      if (arguments->used + parameter->array[k].value.used > arguments->size) {
                        if (arguments->used + parameter->array[k].value.used > F_buffer_too_large) {
                          *status = F_status_set_error(F_buffer_too_large);

                          fake_print_message(data, F_buffer_too_large, "f_macro_string_dynamics_resize", F_true, data_make->print);
                          break;
                        }

                        f_macro_string_dynamics_resize((*status), (*arguments), arguments->used + parameter->array[k].value.used);
                        if (F_status_is_error(*status)) {
                          fake_print_message(data, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true, data_make->print);
                          break;
                        }
                      }

                      for (l = 0; l < parameter->array[k].value.used; l++) {
                        *status = fl_string_dynamic_append_nulless(parameter->array[k].value.array[l], &arguments->array[arguments->used]);
                        if (F_status_is_error(*status)) {
                          fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true, data_make->print);
                          break;
                        }

                        *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);
                        if (F_status_is_error(*status)) {
                          fake_print_message(data, F_status_set_fine(*status), "fl_string_terminate_after", F_true, data_make->print);
                          break;
                        }

                        arguments->used++;
                      } // for
                    }
                  }

                  break;
                }
                else if (F_status_is_error(*status)) {
                  fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_compare", F_true, data_make->print);
                  break;
                }
              } // for
            }

            if (F_status_is_error(*status)) break;

            if (unmatched) {
              *status = fake_make_operate_expand_build(data, quoteds.array[i], iki_content.array[j], data_make, arguments);
              if (F_status_is_error(*status)) {
                fake_print_message(data, F_status_set_fine(*status), "fake_make_operate_expand_build", F_true, data_make->print);
                break;
              }
            }
          }
          else if (define_is && data_make->setting_make.load_build) {
            *status = fake_make_operate_expand_environment(data, quoteds.array[i], iki_content.array[j], data_make, arguments);
            if (F_status_is_error(*status)) {
              fake_print_message(data, F_status_set_fine(*status), "fake_make_operate_expand_environment", F_true, data_make->print);
              break;
            }
          }

          previous = iki_variable.array[j].stop;
        } // for

        if (F_status_is_error(*status)) break;

        if (iki_variable.array[iki_variable.used - 1].stop < content.array[i].stop) {
          range.start = iki_variable.array[iki_variable.used - 1].stop + 1;
          range.stop = content.array[i].stop;

          // if arguments.used was not incremented, then use the value, otherwise arguments.used is past the value to append to, so subtract 1.
          if (used_arguments == arguments->used) {
            *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
          }
          else {
            *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used - 1]);

            if (F_status_is_fine(*status)) {
              *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used - 1]);
              if (F_status_is_error(*status)) {
                fake_print_message(data, F_status_set_fine(*status), "fl_string_terminate_after", F_true, data_make->print);
                break;
              }
            }
          }

          if (F_status_is_error(*status)) {
            fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true, data_make->print);
            break;
          }
        }
      }
      else {
        *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, content.array[i], &arguments->array[arguments->used]);
        if (F_status_is_error(*status)) {
          fake_print_message(data, F_status_set_fine(*status), "fl_string_append_nulless", F_true, data_make->print);
          break;
        }
      }

      // if iki variable did not match (results in empty string) or iki variable is inside quotes, then increment.
      if (used_arguments == arguments->used) {
        *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);
        if (F_status_is_error(*status)) {
          fake_print_message(data, F_status_set_fine(*status), "fl_string_terminate_after", F_true, data_make->print);
          break;
        }

        arguments->used++;
      }

      f_macro_iki_variable_delete_simple(iki_variable);
      f_macro_iki_vocabulary_delete_simple(iki_vocabulary);
      f_macro_iki_content_delete_simple(iki_content);
    } // for

    f_macro_iki_variable_delete_simple(iki_variable);
    f_macro_iki_vocabulary_delete_simple(iki_vocabulary);
    f_macro_iki_content_delete_simple(iki_content);
  }
#endif // _di_fake_make_operate_expand_

#ifndef _di_fake_make_operate_expand_build_
  f_return_status fake_make_operate_expand_build(const fake_data data, const f_fss_quoted quoted, const f_string_range range_name, fake_make_data *data_make, f_string_dynamics *arguments) {
    f_status status = F_none;
    f_string_dynamic value = f_string_dynamic_initialize;

    bool unmatched = F_true;

    {
      const f_string uint8_name[] = {
        fake_build_setting_name_build_language,
        fake_build_setting_name_version_target,
      };

      const f_string_length uint8_length[] = {
        fake_build_setting_name_build_language_length,
        fake_build_setting_name_version_target_length,
      };

      const uint8_t uint8_value[] = {
        data_make->setting_build.build_language,
        data_make->setting_build.version_target,
      };

      for (uint8_t i = 0; i < 2; i++) {
        status = fl_string_dynamic_partial_compare_string(uint8_name[i], data_make->buffer, uint8_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = f_conversion_number_unsigned_to_string(uint8_value[i], 10, &value);
          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string bool_name[] = {
        fake_build_setting_name_build_script,
        fake_build_setting_name_build_shared,
        fake_build_setting_name_build_static,
        fake_build_setting_name_search_exclusive,
        fake_build_setting_name_search_shared,
        fake_build_setting_name_search_static,
      };

      const f_string_length bool_length[] = {
        fake_build_setting_name_build_script_length,
        fake_build_setting_name_build_shared_length,
        fake_build_setting_name_build_static_length,
        fake_build_setting_name_search_exclusive_length,
        fake_build_setting_name_search_shared_length,
        fake_build_setting_name_search_static_length,
      };

      const bool bool_value[] = {
        data_make->setting_build.build_script,
        data_make->setting_build.build_shared,
        data_make->setting_build.build_static,
        data_make->setting_build.search_exclusive,
        data_make->setting_build.search_shared,
        data_make->setting_build.search_static,
      };

      for (uint8_t i = 0; i < 6; i++) {
        status = fl_string_dynamic_partial_compare_string(bool_name[i], data_make->buffer, bool_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          if (bool_value[i]) {
            status = fl_string_append(fake_common_setting_bool_yes, fake_common_setting_bool_yes_length, &value);
          }
          else {
            status = fl_string_append(fake_common_setting_bool_no, fake_common_setting_bool_no_length, &value);
          }

          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string dynamic_name[] = {
        fake_build_setting_name_build_compiler,
        fake_build_setting_name_build_linker,
        fake_build_setting_name_path_headers,
        fake_build_setting_name_path_language,
        fake_build_setting_name_path_library_script,
        fake_build_setting_name_path_library_shared,
        fake_build_setting_name_path_library_static,
        fake_build_setting_name_path_program_script,
        fake_build_setting_name_path_program_shared,
        fake_build_setting_name_path_program_static,
        fake_build_setting_name_process_post,
        fake_build_setting_name_process_pre,
        fake_build_setting_name_project_name,
        fake_build_setting_name_version_major,
        fake_build_setting_name_version_micro,
        fake_build_setting_name_version_minor,
      };

      const f_string_length dynamic_length[] = {
        fake_build_setting_name_build_compiler_length,
        fake_build_setting_name_build_linker_length,
        fake_build_setting_name_path_headers_length,
        fake_build_setting_name_path_language_length,
        fake_build_setting_name_path_library_script_length,
        fake_build_setting_name_path_library_shared_length,
        fake_build_setting_name_path_library_static_length,
        fake_build_setting_name_path_program_script_length,
        fake_build_setting_name_path_program_shared_length,
        fake_build_setting_name_path_program_static_length,
        fake_build_setting_name_process_post_length,
        fake_build_setting_name_process_pre_length,
        fake_build_setting_name_project_name_length,
        fake_build_setting_name_version_major_length,
        fake_build_setting_name_version_micro_length,
        fake_build_setting_name_version_minor_length,
      };

      const f_string_dynamic dynamic_value[] = {
        data_make->setting_build.build_compiler,
        data_make->setting_build.build_linker,
        data_make->setting_build.path_headers,
        data_make->setting_build.path_language,
        data_make->setting_build.path_library_script,
        data_make->setting_build.path_library_shared,
        data_make->setting_build.path_library_static,
        data_make->setting_build.path_program_script,
        data_make->setting_build.path_program_shared,
        data_make->setting_build.path_program_static,
        data_make->setting_build.process_post,
        data_make->setting_build.process_pre,
        data_make->setting_build.project_name,
        data_make->setting_build.version_major,
        data_make->setting_build.version_micro,
        data_make->setting_build.version_minor,
      };

      for (uint8_t i = 0; i < 16; i++) {
        status = fl_string_dynamic_partial_compare_string(dynamic_name[i], data_make->buffer, dynamic_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = fl_string_dynamic_append(dynamic_value[i], &value);
          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string dynamics_name[] = {
        fake_build_setting_name_build_libraries,
        fake_build_setting_name_build_sources_headers,
        fake_build_setting_name_build_sources_library,
        fake_build_setting_name_build_sources_program,
        fake_build_setting_name_build_sources_settings,
        fake_build_setting_name_build_sources_script,
        fake_build_setting_name_defines_all,
        fake_build_setting_name_defines_shared,
        fake_build_setting_name_defines_static,
        fake_build_setting_name_environment,
        fake_build_setting_name_flags_all,
        fake_build_setting_name_flags_library,
        fake_build_setting_name_flags_program,
        fake_build_setting_name_flags_shared,
        fake_build_setting_name_flags_static,
        fake_build_setting_name_modes,
        fake_build_setting_name_modes_default,
      };

      const f_string_length dynamics_length[] = {
        fake_build_setting_name_build_libraries_length,
        fake_build_setting_name_build_sources_headers_length,
        fake_build_setting_name_build_sources_library_length,
        fake_build_setting_name_build_sources_program_length,
        fake_build_setting_name_build_sources_settings_length,
        fake_build_setting_name_build_sources_script_length,
        fake_build_setting_name_defines_all_length,
        fake_build_setting_name_defines_shared_length,
        fake_build_setting_name_defines_static_length,
        fake_build_setting_name_environment_length,
        fake_build_setting_name_flags_all_length,
        fake_build_setting_name_flags_library_length,
        fake_build_setting_name_flags_program_length,
        fake_build_setting_name_flags_shared_length,
        fake_build_setting_name_flags_static_length,
        fake_build_setting_name_modes_length,
        fake_build_setting_name_modes_default_length,
      };

      const f_string_dynamics dynamics_value[] = {
        data_make->setting_build.build_libraries,
        data_make->setting_build.build_sources_headers,
        data_make->setting_build.build_sources_library,
        data_make->setting_build.build_sources_program,
        data_make->setting_build.build_sources_setting,
        data_make->setting_build.build_sources_script,
        data_make->setting_build.defines_all,
        data_make->setting_build.defines_shared,
        data_make->setting_build.defines_static,
        data_make->setting_build.environment,
        data_make->setting_build.flags_all,
        data_make->setting_build.flags_library,
        data_make->setting_build.flags_program,
        data_make->setting_build.flags_shared,
        data_make->setting_build.flags_static,
        data_make->setting_build.modes,
        data_make->setting_build.modes_default,
      };

      for (uint8_t i = 0; i < 17; i++) {
        status = fl_string_dynamic_partial_compare_string(dynamics_name[i], data_make->buffer, dynamics_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          for (f_array_length j = 0; j < dynamics_value[i].used; j++) {
            status = fl_string_dynamic_mash(" ", 1, dynamics_value[i].array[j], &value);
            if (F_status_is_error(status)) {
              break;
            }
          } // for

          break;
        }
      } // for
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(value);
      return status;
    }

    if (unmatched) {
      f_macro_string_dynamic_delete_simple(value);
      return F_false;
    }

    if (quoted) {
      status = fl_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);
    }
    else {
      status = fl_string_dynamics_size_increase(f_memory_default_allocation_step, arguments);

      if (F_status_is_fine(status)) {
        status = fl_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);

        if (F_status_is_fine(status)) {
          status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);

          if (F_status_is_fine(status)) {
            arguments->used++;
          }
        }
      }
    }

    f_macro_string_dynamic_delete_simple(value);

    if (F_status_is_fine(status)) {
      return F_true;
    }

    return status;
  }
#endif // _di_fake_make_operate_expand_build_

#ifndef _di_fake_make_operate_expand_environment_
  f_return_status fake_make_operate_expand_environment(const fake_data data, const f_fss_quoted quoted, const f_string_range range_name, fake_make_data *data_make, f_string_dynamics *arguments) {
    f_status status = F_none;
    f_string_dynamic value = f_string_dynamic_initialize;

    bool unmatched = F_false;

    {
      f_string_dynamic name = f_string_dynamic_initialize;

      status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range_name, &name);
      if (F_status_is_error(status)) return status;

      status = f_environment_get(name.string, &value);

      f_macro_string_dynamic_delete_simple(name);
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(value);
      return status;
    }
    else if (status == F_exist_not) {
      f_macro_string_dynamic_delete_simple(value);
      return F_false;
    }

    if (quoted) {
      status = fl_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);
    }
    else {
      status = fl_string_dynamics_size_increase(f_memory_default_allocation_step, arguments);

      if (F_status_is_fine(status)) {
        status = fl_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);

        if (F_status_is_fine(status)) {
          status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);

          if (F_status_is_fine(status)) {
            arguments->used++;
          }
        }
      }
    }

    f_macro_string_dynamic_delete_simple(value);

    if (F_status_is_fine(status)) {
      return F_true;
    }

    return status;
  }
#endif // _di_fake_make_operate_expand_environment_

#ifndef _di_fake_make_operate_section_
  void fake_make_operate_section(const fake_data data, const f_array_length id_section, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (id_section > data_make->fakefile.used) {
      *status = F_status_set_error(F_parameter);

      fake_print_message(data, F_parameter, "fake_make_operate_section", F_true, data_make->print);
      return;
    }

    // add the operation id to the operation stack.
    if (section_stack->used + 1 > section_stack->size) {
      *status = fl_string_lengths_size_increase(f_memory_default_allocation_step, section_stack);

      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "fl_string_lengths_size_increase", F_true, data_make->print);
        return;
      }
    }


    section_stack->array[section_stack->used] = id_section;
    section_stack->used++;

    const f_fss_named *section = &data_make->fakefile.array[id_section];

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);

      fl_color_print(f_type_output, data.context.important, data.context.reset, "Processing Section '");

      fl_color_print_code(f_type_output, data.context.notable);
      f_print_string_dynamic_partial(f_type_output, data_make->buffer, section->name);
      fl_color_print_code(f_type_output, data.context.reset);

      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "'.");
    }

    if (!section->objects.used) {
      section_stack->used--;
      return;
    }

    const f_string_static operations_name[] = {
      f_macro_string_static_initialize(fake_make_operation_archive, fake_make_operation_archive_length),
      f_macro_string_static_initialize(fake_make_operation_break, fake_make_operation_break_length),
      f_macro_string_static_initialize(fake_make_operation_build, fake_make_operation_build_length),
      f_macro_string_static_initialize(fake_make_operation_clean, fake_make_operation_clean_length),
      f_macro_string_static_initialize(fake_make_operation_compile, fake_make_operation_compile_length),
      f_macro_string_static_initialize(fake_make_operation_define, fake_make_operation_define_length),
      f_macro_string_static_initialize(fake_make_operation_delete, fake_make_operation_delete_length),
      f_macro_string_static_initialize(fake_make_operation_deletes, fake_make_operation_deletes_length),
      f_macro_string_static_initialize(fake_make_operation_else, fake_make_operation_else_length),
      f_macro_string_static_initialize(fake_make_operation_exit, fake_make_operation_exit_length),
      f_macro_string_static_initialize(fake_make_operation_fail, fake_make_operation_fail_length),
      f_macro_string_static_initialize(fake_make_operation_group, fake_make_operation_group_length),
      f_macro_string_static_initialize(fake_make_operation_groups, fake_make_operation_groups_length),
      f_macro_string_static_initialize(fake_make_operation_if, fake_make_operation_if_length),
      f_macro_string_static_initialize(fake_make_operation_link, fake_make_operation_link_length),
      f_macro_string_static_initialize(fake_make_operation_mode, fake_make_operation_mode_length),
      f_macro_string_static_initialize(fake_make_operation_modes, fake_make_operation_modes_length),
      f_macro_string_static_initialize(fake_make_operation_operate, fake_make_operation_operate_length),
      f_macro_string_static_initialize(fake_make_operation_owner, fake_make_operation_owner_length),
      f_macro_string_static_initialize(fake_make_operation_owners, fake_make_operation_owners_length),
      f_macro_string_static_initialize(fake_make_operation_pop, fake_make_operation_pop_length),
      f_macro_string_static_initialize(fake_make_operation_print, fake_make_operation_print_length),
      f_macro_string_static_initialize(fake_make_operation_run, fake_make_operation_run_length),
      f_macro_string_static_initialize(fake_make_operation_shell, fake_make_operation_shell_length),
      f_macro_string_static_initialize(fake_make_operation_skeleton, fake_make_operation_skeleton_length),
      f_macro_string_static_initialize(fake_make_operation_to, fake_make_operation_to_length),
      f_macro_string_static_initialize(fake_make_operation_top, fake_make_operation_top_length),
      f_macro_string_static_initialize(fake_make_operation_touch, fake_make_operation_touch_length),
    };

    const f_string_range operations_range[] = {
      f_macro_string_range_initialize(fake_make_operation_archive_length),
      f_macro_string_range_initialize(fake_make_operation_break_length),
      f_macro_string_range_initialize(fake_make_operation_build_length),
      f_macro_string_range_initialize(fake_make_operation_clean_length),
      f_macro_string_range_initialize(fake_make_operation_compile_length),
      f_macro_string_range_initialize(fake_make_operation_define_length),
      f_macro_string_range_initialize(fake_make_operation_delete_length),
      f_macro_string_range_initialize(fake_make_operation_deletes_length),
      f_macro_string_range_initialize(fake_make_operation_else_length),
      f_macro_string_range_initialize(fake_make_operation_exit_length),
      f_macro_string_range_initialize(fake_make_operation_fail_length),
      f_macro_string_range_initialize(fake_make_operation_group_length),
      f_macro_string_range_initialize(fake_make_operation_groups_length),
      f_macro_string_range_initialize(fake_make_operation_if_length),
      f_macro_string_range_initialize(fake_make_operation_link_length),
      f_macro_string_range_initialize(fake_make_operation_mode_length),
      f_macro_string_range_initialize(fake_make_operation_modes_length),
      f_macro_string_range_initialize(fake_make_operation_operate_length),
      f_macro_string_range_initialize(fake_make_operation_owner_length),
      f_macro_string_range_initialize(fake_make_operation_owners_length),
      f_macro_string_range_initialize(fake_make_operation_pop_length),
      f_macro_string_range_initialize(fake_make_operation_print_length),
      f_macro_string_range_initialize(fake_make_operation_run_length),
      f_macro_string_range_initialize(fake_make_operation_shell_length),
      f_macro_string_range_initialize(fake_make_operation_skeleton_length),
      f_macro_string_range_initialize(fake_make_operation_to_length),
      f_macro_string_range_initialize(fake_make_operation_top_length),
      f_macro_string_range_initialize(fake_make_operation_touch_length),
    };

    const uint8_t operations_type[] = {
      fake_make_operation_type_archive,
      fake_make_operation_type_break,
      fake_make_operation_type_build,
      fake_make_operation_type_clean,
      fake_make_operation_type_compile,
      fake_make_operation_type_define,
      fake_make_operation_type_delete,
      fake_make_operation_type_deletes,
      fake_make_operation_type_else,
      fake_make_operation_type_exit,
      fake_make_operation_type_fail,
      fake_make_operation_type_group,
      fake_make_operation_type_groups,
      fake_make_operation_type_if,
      fake_make_operation_type_link,
      fake_make_operation_type_mode,
      fake_make_operation_type_modes,
      fake_make_operation_type_operate,
      fake_make_operation_type_owner,
      fake_make_operation_type_owners,
      fake_make_operation_type_pop,
      fake_make_operation_type_print,
      fake_make_operation_type_run,
      fake_make_operation_type_shell,
      fake_make_operation_type_skeleton,
      fake_make_operation_type_to,
      fake_make_operation_type_top,
      fake_make_operation_type_touch,
    };

    uint8_t operation = 0;
    uint8_t operations[section->objects.used];
    uint8_t operation_if = 0;

    bool success = F_true;

    const f_string_static *operation_name = 0;

    f_string_dynamics arguments[section->objects.used];

    f_array_length i = 0;
    f_array_length j = 0;

    memset(operations, 0, sizeof(uint8_t) * section->objects.used);
    memset(arguments, 0, sizeof(f_string_dynamics) * section->objects.used);

    for (i = 0; i < section->objects.used; i++, *status = F_none) {
      operation = 0;
      operation_name = 0;

      for (j = 0; j < fake_make_operation_total; j++) {
        if (fl_string_dynamic_partial_compare(operations_name[j], data_make->buffer, operations_range[j], section->objects.array[i]) == F_equal_to) {
          operation = operations_type[j];
          operation_name = &operations_name[j];
          break;
        }
      } // for

      if (operation == 0) {
        fake_print_message_section_operation_unknown(data, data_make->buffer, section->name, section->objects.array[i], data_make->print);

        *status = F_status_set_error(F_invalid);
      }
      else if (operation == fake_make_operation_type_operate) {
        if (section_stack->used == fake_make_section_stack_max) {
          fake_print_message_section_operation_stack_max(data, data_make->buffer, section->name, section->objects.array[i], fake_make_section_stack_max, data_make->print);

          *status = F_status_set_error(F_recurse);
        }
      }

      if (F_status_is_fine(*status)) {
        operations[i] = operation;

        fake_make_operate_expand(data, section->name, operation, *operation_name, section->contents.array[i], section->quotedss.array[i], data_make, &arguments[i], status);
      }

      if (operation_if == fake_make_operation_if_type_true_next) {
        operation_if = fake_make_operation_if_type_true;
      }
      else if (operation_if == fake_make_operation_if_type_false_next) {
        operation_if = fake_make_operation_if_type_false;
      }
      else if (operation_if == fake_make_operation_if_type_false_always_next) {
        operation_if = fake_make_operation_if_type_false_always;
      }

      fake_make_operate_validate(data, section->name, operation, *operation_name, arguments[i], &operation_if, data_make, section_stack, status);

      if (F_status_is_fine(*status)) {

        if (operation_if == fake_make_operation_if_type_false) {
          operation_if = fake_make_operation_if_type_else_true_next;
          continue;
        }
        else if (operation_if == fake_make_operation_if_type_false_always) {
          operation_if = fake_make_operation_if_type_else_false_next_always;
          continue;
        }
        else if (operation_if == fake_make_operation_if_type_else_false) {
          operation_if = 0;
          continue;
        }

        fake_make_operate_process(data, section->name, operation, *operation_name, arguments[i], success, &operation_if, data_make, section_stack, status);
      }
      else {

        if (operation == fake_make_operation_type_if) {
          switch (operation_if) {
            case fake_make_operation_if_type_if_defined:
            case fake_make_operation_if_type_if_equal:
            case fake_make_operation_if_type_if_equal_not:
            case fake_make_operation_if_type_if_exists:
            case fake_make_operation_if_type_if_failure:
            case fake_make_operation_if_type_if_greater:
            case fake_make_operation_if_type_if_greater_equal:
            case fake_make_operation_if_type_if_group:
            case fake_make_operation_if_type_if_is:
            case fake_make_operation_if_type_if_less:
            case fake_make_operation_if_type_if_less_equal:
            case fake_make_operation_if_type_if_mode:
            case fake_make_operation_if_type_if_owner:
            case fake_make_operation_if_type_if_success:
              operation_if = 0;
              break;
          }
        }

        if (operation_if == fake_make_operation_if_type_false) {
          operation_if = fake_make_operation_if_type_else_true_next;
        }
        else if (operation_if == fake_make_operation_if_type_false_always) {
          operation_if = fake_make_operation_if_type_else_false_next_always;
        }
        else if (operation_if == fake_make_operation_if_type_else_false) {
          operation_if = 0;
        }
      }

      if (operation_if == fake_make_operation_if_type_else_true || operation_if == fake_make_operation_if_type_else_false) {
        // No else condition provided, so clear the operation_if state.
        if (operation != fake_make_operation_type_else) {
          operation_if = 0;
        }
      }
      else if (operation_if == fake_make_operation_if_type_true) {
        operation_if = fake_make_operation_if_type_else_false_next;
      }
      else if (operation_if == fake_make_operation_if_type_false_always) {
        operation_if = fake_make_operation_if_type_else_false_next_always;
      }

      if (F_status_is_error(*status)) {
        success = F_false;

        // break acts identical to fail when at the top of the stack.
        if (F_status_set_fine(*status) == F_signal_abort && section_stack->used == 0) {
          data_make->setting_make.fail = fake_make_operation_fail_type_exit;
          data_make->print.prefix = fake_make_print_error;
          data_make->print.context = data.context.error;
          data_make->print.to = f_type_error;
        }

        fake_print_message_section_operation_failed(data, data_make->buffer, section->name, section->objects.array[i], data_make->print);

        // F_signal_abort is used by the break section operation.
        if (F_status_set_fine(*status) == F_signal_abort) {
          break;
        }

        // F_signal_abort is used by the exit section operation.
        if (F_status_set_fine(*status) == F_signal_quit) {
          if (section_stack->used == 0) {
            *status = F_status_set_error(F_failure);
          }

          break;
        }

        if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
          operation_if = 0;
          break;
        }
      }
      else if (*status == F_signal_abort) {
        success = F_true;

        // F_signal_abort is used by the break section operation.
        break;
      }
      else if (*status == F_signal_quit) {
        success = F_true;

        // F_signal_abort is used by the exit section operation.
        if (section_stack->used == 0) {
          *status = F_none;
        }

        break;
      }
      else {
        success = F_true;
      }
    } // for

    if (i == section->objects.used && (operation_if == fake_make_operation_if_type_true_next || operation_if == fake_make_operation_if_type_false_next || operation_if == fake_make_operation_if_type_else_true || operation_if == fake_make_operation_if_type_else_false)) {
      if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
        const char *type_name = 0;

        if (operation_if == fake_make_operation_if_type_true_next || operation_if == fake_make_operation_if_type_false_next) {
          type_name = fake_make_operation_if;
        }
        else {
          type_name = fake_make_operation_else;
        }

        fprintf(data_make->print.to, "%c", f_string_eol[0]);
        fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Incomplete '", data_make->print.prefix);
        fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", type_name);
        fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' at end of section.");
      }

      fake_print_message_section_operation_failed(data, data_make->buffer, section->name, section->objects.array[section->objects.used - 1], data_make->print);

      *status = F_status_set_error(F_failure);
    }

    // ensure an error is returned during recursion if the last known section operation failed, except for the main operation.
    if (success == F_false && F_status_is_fine(*status) && section_stack->used > 1) {
      *status = F_status_set_error(F_failure);
    }

    for (i = 0; i < section->objects.used; i++) {
      f_macro_string_dynamics_delete_simple(arguments[i]);
    } // for

    section_stack->used--;
  }
#endif // _di_fake_make_operate_section_

#ifndef _di_fake_make_operate_process_
  void fake_make_operate_process(const fake_data data, const f_string_range section_name, const uint8_t operation, const f_string_static operation_name, const f_string_dynamics arguments, const bool success, uint8_t *operation_if, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) {

    if (operation == fake_make_operation_type_archive) {
      if (!arguments.used) {
        return;
      }

      fake_execute(data, data_make->environment, data_make->setting_build.build_linker, arguments, status);

      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "fake_execute", F_true, data_make->print);
      }

      return;
    }

    if (operation == fake_make_operation_type_break) {
      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success, arguments.array[0], fake_make_operation_argument_success_length) == F_equal_to) {
        *status = F_signal_abort;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure, arguments.array[0], fake_make_operation_argument_failure_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_abort);
      }
      else {
        return;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Breaking as '%s'.", arguments.used ? arguments.array[0].string : fake_make_operation_argument_success);
      }

      return;
    }

    if (operation == fake_make_operation_type_build) {
      *status = fake_build_operate(data);

      fake_make_operate_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_clean) {
      *status = fake_clean_operate(data);

      fake_make_operate_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_compile) {
      if (!arguments.used) {
        return;
      }

      fake_execute(data, data_make->environment, data_make->setting_build.build_compiler, arguments, status);

      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "fake_execute", F_true, data_make->print);
      }

      return;
    }

    if (operation == fake_make_operation_type_define) {
      if (!arguments.used) {
        return;
      }

      if (arguments.used > 1) {
        *status = f_environment_set(arguments.array[0].string, arguments.array[1].string, F_true);
      }
      else {
        *status = f_environment_set(arguments.array[0].string, "", F_true);
      }

      if (F_status_is_error(*status)) {
        fake_print_message(data, F_status_set_fine(*status), "f_environment_set", F_true, data_make->print);
      }
      else if (data.verbosity == fake_verbosity_verbose) {
        printf("Defined environment variable '%s'.%c", arguments.array[0].string, f_string_eol[0]);
      }

      return;
    }

    if (operation == fake_make_operation_type_delete || operation == fake_make_operation_type_deletes) {
      const int recursion_max = operation == fake_make_operation_type_delete ? 0 : f_directory_descriptors_max;
      struct stat file_stat;

      for (f_array_length i = 0; i < arguments.used; i++) {
        memset(&file_stat, 0, sizeof(struct stat));

        *status = f_file_stat(arguments.array[i].string, F_false, &file_stat);

        if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_file_found_not) {
            if (data.verbosity == fake_verbosity_verbose) {
              fprintf(f_type_warning, "%c", f_string_eol[0]);
              fl_color_print(f_type_warning, data.context.warning, data.context.reset, "WARNING: the file '");
              fl_color_print(f_type_warning, data.context.notable, data.context.reset, "%s", arguments.array[i].string);
              fl_color_print_line(f_type_warning, data.context.warning, data.context.reset, "' was not found.");
            }

            *status = F_none;
          }
          else {
            fake_print_message_file(data, F_status_set_fine(*status), "f_file_stat", arguments.array[i].string, "delete", F_true, F_true, data_make->print);
            return;
          }
        }
        else if (f_macro_file_type_is_directory(file_stat.st_mode)) {
          if (data.verbosity == fake_verbosity_verbose) {
            *status = f_directory_remove_custom(arguments.array[i].string, recursion_max, F_false, fake_clean_remove_recursively_verbosely);
          }
          else {
            *status = f_directory_remove(arguments.array[i].string, recursion_max, F_false);
          }

          if (F_status_set_fine(*status) == F_file_found_not) {
            if (data.verbosity == fake_verbosity_verbose) {
              printf("The directory '%s' does not exist.%c", arguments.array[i].string, f_string_eol[0]);
            }

            *status = F_none;
          }

          if (F_status_is_error(*status)) {
            fake_print_message_file(data, F_status_set_fine(*status), "f_directory_remove", arguments.array[i].string, "delete", F_false, F_true, data_make->print);
            return;
          }
          else if (data.verbosity == fake_verbosity_verbose) {
            printf("Removed '%s'.%c", arguments.array[i].string, f_string_eol[0]);
          }
        }
        else {
          *status = f_file_remove(arguments.array[i].string);

          if (F_status_is_error(*status)) {
            fake_print_message_file(data, F_status_set_fine(*status), "f_file_remove", arguments.array[i].string, "delete", F_true, F_true, data_make->print);
            return;
          }
          else if (data.verbosity == fake_verbosity_verbose) {
            printf("Removed '%s'.%c", arguments.array[i].string, f_string_eol[0]);
          }
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_else) {
      if (*operation_if == fake_make_operation_if_type_else_false_next || *operation_if == fake_make_operation_if_type_else_false_next_always) {
        *operation_if = fake_make_operation_if_type_else_false;
      }
      else if (*operation_if != fake_make_operation_if_type_else_true_next) {
        *operation_if = fake_make_operation_if_type_else_true;
      }

      return;
    }

    if (operation == fake_make_operation_type_exit) {
      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success, arguments.array[0], fake_make_operation_argument_success_length) == F_equal_to) {
        *status = F_signal_quit;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure, arguments.array[0], fake_make_operation_argument_failure_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_quit);

        // forcing exit forces fail mode.
        data_make->setting_make.fail = fake_make_operation_fail_type_exit;
        data_make->print.prefix = fake_make_print_error;
        data_make->print.context = data.context.error;
        data_make->print.to = f_type_error;
      }
      else {
        return;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Exiting as '%s'.", arguments.used ? arguments.array[0].string : fake_make_operation_argument_success);
      }

      return;
    }

    if (operation == fake_make_operation_type_fail) {
      if (!arguments.used) {
        return;
      }

      if (fl_string_dynamic_compare_string(fake_make_operation_argument_exit, arguments.array[0], fake_make_operation_argument_exit_length) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_exit;
        data_make->print.prefix = fake_make_print_error;
        data_make->print.context = data.context.error;
        data_make->print.to = f_type_error;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn, arguments.array[0], fake_make_operation_argument_warn_length) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_warn;
        data_make->print.prefix = fake_make_print_warning;
        data_make->print.context = data.context.warning;
        data_make->print.to = f_type_warning;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_ignore, arguments.array[0], fake_make_operation_argument_ignore_length) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_ignore;
        data_make->print.to = 0;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Set failure state to '");

        if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
          printf(fake_make_operation_argument_exit);
        }
        else if (data_make->setting_make.fail == fake_make_operation_fail_type_warn) {
          printf(fake_make_operation_argument_warn);
        }
        else if (data_make->setting_make.fail == fake_make_operation_fail_type_ignore) {
          printf(fake_make_operation_argument_ignore);
        }

        printf("'.%c", f_string_eol[0]);
      }

      return;
    }

    if (operation == fake_make_operation_type_group) {
      if (!arguments.used) {
        return;
      }

      gid_t id = 0;

      *status = fake_make_get_id_group(data, data_make->print, arguments.array[0], &id);
      if (F_status_is_error(*status)) return;

      for (f_array_length i = 1; i < arguments.used; i++) {
        *status = f_file_role_change(arguments.array[i].string, -1, id, F_false);

        if (F_status_is_error(*status)) {
          fake_print_message_file(data, *status, "f_file_role_change", arguments.array[i].string, "change group of", F_true, F_true, data_make->print);
        }
        else if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed group of '%s' to %llu.%c", arguments.array[i].string, id, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_groups) {
      if (!arguments.used) {
        return;
      }

      gid_t id = 0;

      *status = fake_make_get_id_group(data, data_make->print, arguments.array[0], &id);
      if (F_status_is_error(*status)) return;

      for (f_array_length i = 1; i < arguments.used; i++) {
        // @todo: recursive.
        *status = f_file_role_change(arguments.array[i].string, -1, id, F_false);

        if (F_status_is_error(*status)) {
          fake_print_message_file(data, *status, "f_file_role_change", arguments.array[i].string, "change group of", F_true, F_true, data_make->print);
        }
        else if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed group of '%s' to %llu.%c", arguments.array[i].string, id, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_if) {
      if (!arguments.used) {
        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_success) {
        if (success) {
          *operation_if = fake_make_operation_if_type_true_next;
        }
        else {
          *operation_if = fake_make_operation_if_type_false_next;
        }

        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_failure) {
        if (success) {
          *operation_if = fake_make_operation_if_type_false_next;
        }
        else {
          *operation_if = fake_make_operation_if_type_true_next;
        }

        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_mode) {
        *operation_if = fake_make_operation_if_type_false_next;

        bool is = F_false;

        if (fl_string_dynamic_compare_string(fake_make_operation_argument_is, arguments.array[1], fake_make_operation_argument_is_length) == F_equal_to) {
          is = F_true;
        }

        f_file_mode mode_rule = 0;
        mode_t mode_match = 0;
        uint8_t replace = 0;

        // @fixme: mode_rule needs to be converted to a mode_t.
        *status = fake_make_get_id_mode(data, data_make->print, arguments.array[1], &mode_rule, &replace);
        if (F_status_is_error(*status)) return;

        mode_t mode_file = 0;

        for (f_array_length i = 2; i < arguments.used; i++, mode_file = 0) {

          *status = f_file_mode_read(arguments.array[i].string, &mode_file);
          if (F_status_is_error(*status)) {
            fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_read", arguments.array[i].string, "get mode of", F_true, F_true, data_make->print);
            break;
          }

          if (is) {
            if (mode_match == mode_file) {
              // @todo success
            }
            else {
              // @todo failure
            }
          }
          else {
            if (mode_match & mode_file) {
              // @todo success
            }
            else {
              // @todo failure
            }
          }
        } // for

        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_owner || *operation_if == fake_make_operation_if_type_if_group) {
        *operation_if = fake_make_operation_if_type_false_next;
        // @todo: handle first owner/group parameter and then filepath parameters.
        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_is) {
        *operation_if = fake_make_operation_if_type_false_next;
        // @todo: handle first file type parameter and then filepath parameters.
        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_exists) {
        *operation_if = fake_make_operation_if_type_false_next;
        // @todo: handle file type filepath parameters.
        return;
      }

      if (*operation_if == fake_make_operation_if_type_if_defined) {
        *operation_if = fake_make_operation_if_type_false_next;
        // @todo: handle first parameter/environment parameter and then define name parameters.
        return;
      }

      // @todo: for each of these, handle converting all arguments to integers/numbers and then processing conditions in order.
      //fake_make_operation_if_type_if_equal
      //fake_make_operation_if_type_if_equal_not (needs to be applied to all, so use separate logic block.)
      //fake_make_operation_if_type_if_greater
      //fake_make_operation_if_type_if_greater_equal
      //fake_make_operation_if_type_if_less
      //fake_make_operation_if_type_if_less_equal

      *operation_if = fake_make_operation_if_type_false_next;

      return;
    }

    if (operation == fake_make_operation_type_link) {
      if (!arguments.used) {
        return;
      }

      *status = f_file_link(arguments.array[0].string, arguments.array[1].string);

      if (F_status_is_error(*status)) {
        fake_print_message_file(data, *status, "f_file_link", arguments.array[1].string, "create link", F_true, F_true, data_make->print);
      }
      else if (data.verbosity == fake_verbosity_verbose) {
        printf("Created symbolic link from '%s' to '%s'.%c", arguments.array[1].string, arguments.array[0].string, f_string_eol[0]);
      }

      return;
    }

    if (operation == fake_make_operation_type_mode) {
      if (!arguments.used) {
        return;
      }

      f_file_mode mode_rule = 0;
      uint8_t replace = 0;

      *status = fake_make_get_id_mode(data, data_make->print, arguments.array[0], &mode_rule, &replace);
      if (F_status_is_error(*status)) return;

      mode_t mode = 0;
      mode_t mode_file = 0;

      for (f_array_length i = 1; i < arguments.used; i++) {
        mode = 0;

        *status = f_file_mode_read(arguments.array[i].string, &mode_file);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_read", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        *status = f_file_mode_determine(mode_file, mode_rule, replace, f_macro_file_type_is_directory(mode_file), &mode);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_determine", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        *status = f_file_mode_set(arguments.array[i].string, mode);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_set", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed mode of '%s' to %#o.%c", arguments.array[i].string, mode, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_modes) {
      if (!arguments.used) {
        return;
      }

      f_file_mode mode_rule = 0;
      uint8_t replace = 0;

      *status = fake_make_get_id_mode(data, data_make->print, arguments.array[0], &mode_rule, &replace);
      if (F_status_is_error(*status)) return;

      mode_t mode = 0;
      mode_t mode_file = 0;

      for (f_array_length i = 1; i < arguments.used; i++) {
        // @todo recursive.
        mode = 0;

        *status = f_file_mode_read(arguments.array[i].string, &mode_file);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_read", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        *status = f_file_mode_determine(mode_file, mode_rule, replace, f_macro_file_type_is_directory(mode_file), &mode);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_determine", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        *status = f_file_mode_set(arguments.array[i].string, mode);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_mode_set", arguments.array[i].string, "change mode of", F_true, F_true, data_make->print);
          break;
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed mode of '%s' to %#o.%c", arguments.array[i].string, mode, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_operate) {
      if (!arguments.used) {
        return;
      }

      f_array_length id_section = 0;

      for (; id_section < data_make->fakefile.used; id_section++) {
        if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
          break;
        }
      } // for

      if (id_section == data_make->fakefile.used) {
        return;
      }

      fake_make_operate_section(data, id_section, data_make, section_stack, status);

      // Ensure that a break only happens within its active operation stack.
      if (*status == F_signal_abort) {
        *status = F_none;
      }
      else if (F_status_set_fine(*status) == F_signal_abort) {
        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_owner) {
      if (!arguments.used) {
        return;
      }

      uid_t id = 0;

      *status = fake_make_get_id_owner(data, data_make->print, arguments.array[0], &id);
      if (F_status_is_error(*status)) return;

      for (f_array_length i = 1; i < arguments.used; i++) {
        *status = f_file_role_change(arguments.array[i].string, id, -1, F_false);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_role_change", arguments.array[i].string, "change owner of", F_true, F_true, data_make->print);
          break;
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed owner of '%s' to %d.%c", arguments.array[i].string, id, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_owners) {
      if (!arguments.used) {
        return;
      }

      uid_t id = 0;

      *status = fake_make_get_id_owner(data, data_make->print, arguments.array[0], &id);
      if (F_status_is_error(*status)) return;

      for (f_array_length i = 1; i < arguments.used; i++) {
        // @todo recursive.
        *status = f_file_role_change(arguments.array[i].string, id, -1, F_false);
        if (F_status_is_error(*status)) {
          fake_print_message_file(data, F_status_set_fine(*status), "f_file_role_change", arguments.array[i].string, "change owner of", F_true, F_true, data_make->print);
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Changed owner of '%s' to %o.%c", arguments.array[i].string, id, f_string_eol[0]);
        }
      } // for

      return;
    }

    if (operation == fake_make_operation_type_pop) {
      f_macro_string_dynamic_delete_simple(data_make->path.stack.array[data_make->path.stack.used - 1]);

      data_make->path.stack.used--;

      *status = f_path_change(data_make->path.stack.array[data_make->path.stack.used - 1].string);
      if (F_status_is_error(*status)) {
        fake_print_message_section_operation_path_stack_max(data, F_status_set_fine(*status), "f_path_change", data_make->path.stack.array[data_make->path.stack.used - 1].string, data_make->print);
        return;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        *status = fake_make_path_relative(data, data_make->path.stack.array[data_make->path.stack.used - 1], data_make);
        if (F_status_is_error(*status)) {
          fake_print_message(data, F_status_set_fine(*status), "fake_make_path_relative", F_true, data_make->print);
          return;
        }

        printf("Changed to project path '");
        f_print_string_dynamic(f_type_output, data_make->path_cache);
        printf("'.%c", f_string_eol[0]);
      }

      return;
    }

    if (operation == fake_make_operation_type_print) {
      for (f_array_length i = 0; i < arguments.used; i++) {
        f_print_string_dynamic(f_type_output, arguments.array[i]);

        if (i + 1 < arguments.used) {
          printf(" ");
        }
      } // for

      printf("%c", f_string_eol[0]);
      return;
    }

    if (operation == fake_make_operation_type_run) {
      *status = fake_make_operate_process_run(data, arguments, F_false, data_make);
      return;
    }

    if (operation == fake_make_operation_type_shell) {
      *status = fake_make_operate_process_run(data, arguments, F_true, data_make);
      return;
    }

    if (operation == fake_make_operation_type_skeleton) {
      *status = fake_skeleton_operate(data);

      fake_make_operate_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_to) {
      if (!arguments.used) {
        return;
      }

      *status = fake_make_assure_inside_project(data, arguments.array[0], data_make);
      if (F_status_is_error(*status)) {
        fake_print_message_section_operation_path_outside(data, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string, data_make->print);

        if (F_status_set_fine(*status) == F_false) {
          *status = F_status_set_error(F_failure);
        }

        return;
      }

      *status = f_path_change(arguments.array[0].string);
      if (F_status_is_error(*status)) {
        fake_print_message_section_operation_path_stack_max(data, F_status_set_fine(*status), "f_path_change", arguments.array[0].string, data_make->print);
      }
      else {
        if (data_make->path.stack.used == data_make->path.stack.size) {
          *status = fl_string_dynamics_size_increase(f_memory_default_allocation_step, &data_make->path.stack);

          if (F_status_set_fine(*status) == F_buffer_too_large) {
            fake_print_message_section_operation_path_stack_max(data, F_buffer_too_large, "fl_string_lengths_size_increase", "path stack", data_make->print);
            return;
          }
          else if (F_status_is_error(*status)) {
            fake_print_message(data, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true, data_make->print);
            return;
          }
        }

        // copy the entire real path, including the trailing NULL.
        data_make->path_cache.used++;

        fl_string_dynamic_append(data_make->path_cache, &data_make->path.stack.array[data_make->path.stack.used]);

        if (F_status_is_error(*status)) {
          fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true, data_make->print);
          return;
        }

        if (data.verbosity == fake_verbosity_verbose) {
          *status = fake_make_path_relative(data, data_make->path.stack.array[data_make->path.stack.used], data_make);
          if (F_status_is_error(*status)) {
            fake_print_message(data, F_status_set_fine(*status), "fake_make_path_relative", F_true, data_make->print);
            return;
          }

          printf("Changed to project path '");
          f_print_string_dynamic(f_type_output, data_make->path_cache);
          printf("'.%c", f_string_eol[0]);
        }

        data_make->path.stack.used++;
      }

      return;
    }

    if (operation == fake_make_operation_type_top) {
      if (!arguments.used) {
        return;
      }

      *status = f_path_change_at(data_make->path.top);
      if (F_status_is_error(*status)) {
        fake_print_message_section_operation_path_stack_max(data, F_status_set_fine(*status), "f_path_change", arguments.array[0].string, data_make->print);
        return;
      }

      if (data.verbosity == fake_verbosity_verbose) {
        printf("Changed to project path ''.%c", f_string_eol[0]);
      }

      // clear stack, except for the project root.
      for (f_array_length i = 1; i < data_make->path.stack.used; i++) {
        f_macro_string_dynamic_delete_simple(data_make->path.stack.array[i]);
      } // for

      data_make->path.stack.used = 1;
      return;
    }

    if (operation == fake_make_operation_type_touch) {
      if (!arguments.used) {
        return;
      }

      f_mode mode = f_mode_initialize;

      f_macro_mode_set_default_umask(mode, data.umask);

      for (f_array_length i = 1; i < arguments.used; i++) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_file, arguments.array[0], fake_make_operation_argument_file_length) == F_equal_to) {
          *status = f_file_touch(arguments.array[i].string, mode.regular, F_false);

          if (F_status_is_error(*status)) {
            if (F_status_is_fine(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
              fake_print_message_file(data, F_status_set_fine(*status), "f_file_touch", data_make->path_cache.string, "touch", F_true, F_true, data_make->print);
            }
            else {
              fake_print_message_file(data, F_status_set_fine(*status), "f_file_touch", arguments.array[i].string, "touch", F_true, F_true, data_make->print);
            }

            break;
          }
        }
        else if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory, arguments.array[0], fake_make_operation_argument_directory_length) == F_equal_to) {
          *status = f_directory_touch(arguments.array[i].string, mode.directory);

          if (F_status_is_error(*status)) {
            if (F_status_is_fine(fll_path_canonical(arguments.array[i].string, &data_make->path_cache))) {
              fake_print_message_file(data, F_status_set_fine(*status), "f_directory_touch", data_make->path_cache.string, "touch", F_false, F_true, data_make->print);
            }
            else {
              fake_print_message_file(data, F_status_set_fine(*status), "f_directory_touch", arguments.array[i].string, "touch", F_false, F_true, data_make->print);
            }

            break;
          }
        }

        if (data.verbosity == fake_verbosity_verbose) {
          printf("Touched %s '", arguments.array[0].string);
          f_print_string_dynamic(f_type_output, arguments.array[i]);
          printf("'.%c", f_string_eol[0]);
        }

      } // for

      return;
    }
  }
#endif // _di_fake_make_operate_process_

#ifndef _di_fake_make_operate_process_execute_
  f_return_status fake_make_operate_process_execute(const fake_data data, const f_string_static program, const f_string_statics arguments, const bool as_shell, fake_make_data *data_make) {
    f_status status = F_none;

    // reset the environment.
    for (f_array_length i = 0; i < data_make->environment.names.used; i++) {
      data_make->environment.names.array[i].used = 0;
      data_make->environment.values.array[i].used = 0;
    } // for

    data_make->environment.names.used = 0;
    data_make->environment.values.used = 0;

    // load all environment variables found.
    for (f_array_length i = 0; i < data_make->setting_build.environment.used; i++) {

      // pre-allocate name and value if necessary.
      if (data_make->environment.names.used + 1 > data_make->environment.names.size) {
        f_macro_string_dynamics_resize(status, data_make->environment.names, data_make->environment.names.size + f_memory_default_allocation_step);

        if (F_status_is_not_error(status)) {
          f_macro_string_dynamics_resize(status, data_make->environment.values, data_make->environment.values.size + f_memory_default_allocation_step);
        }

        if (F_status_is_error(status)) {
          fake_print_message(data, F_status_set_fine(status), "f_macro_string_dynamics_resize", F_true, data_make->print);
          return status;
        }
      }

      status = f_environment_get(data_make->setting_build.environment.array[i].string, &data_make->environment.values.array[data_make->environment.values.used]);
      if (F_status_is_error(status)) {
        fake_print_message(data, F_status_set_fine(status), "f_environment_get", F_true, data_make->print);
        return status;
      }

      if (status == F_exist_not) continue;

      fl_string_dynamic_append(data_make->setting_build.environment.array[i], &data_make->environment.names.array[data_make->environment.names.used]);
      if (F_status_is_error(status)) {
        fake_print_message(data, F_status_set_fine(status), "f_environment_get", F_true, data_make->print);
        return status;
      }

      data_make->environment.names.used++;
      data_make->environment.values.used++;
    } // for

    if (data.verbosity == fake_verbosity_verbose) {
      printf("%s", program.string);

      for (f_array_length i = 0; i < arguments.used; i++) {
        if (arguments.array[i].used == 0) continue;

        printf(" %s", arguments.array[i].string);
      } // for

      printf("%c", f_string_eol[0]);

      // flush to stdout before executing command.
      fflush(f_type_output);
    }

    int result = 0;

    if (as_shell) {
      status = fll_execute_path_environment(program.string, arguments, data_make->environment.names, data_make->environment.values, &result);
    }
    else {
      status = fll_execute_program_environment(program.string, arguments, data_make->environment.names, data_make->environment.values, &result);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_file_found_not) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          fprintf(data_make->print.to, "%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Failed to find program '", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", program.string);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' for executing.");
        }
      }
      else if (F_status_set_fine(status) != F_failure) {
        fake_print_message(data, F_status_set_fine(status), "fll_execute_program_environment", F_true, data_make->print);
      }
    }

    fake_make_operate_process_return(data, result, data_make, &status);

    return status;
  }
#endif // _di_fake_make_operate_process_execute_

#ifndef _di_fake_make_operate_process_return_
  void fake_make_operate_process_return(const fake_data data, const int return_code, fake_make_data *data_make, f_status *status) {
    f_status status2 = F_none;

    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (return_code == 0) {
      if (F_status_is_error(*status)) {
        status2 = fl_string_append("1", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }
      else {
        status2 = fl_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }

      return;
    }
    else {
      if (return_code) {
        f_string_dynamic number = f_string_dynamic_initialize;

        status2 = f_conversion_number_signed_to_string(return_code, 10, &number);
        if (F_status_is_error(status2)) {
          *status = status2;

          fake_print_message(data, F_status_set_fine(*status), "f_conversion_number_signed_to_string", F_true, data_make->print);

          f_macro_string_dynamic_delete_simple(number);
          return;
        }

        status2 = fl_string_dynamic_append(number, &data_make->setting_make.parameter.array[0].value.array[0]);

        f_macro_string_dynamic_delete_simple(number);
      }
      else {
        status2 = fl_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }
    }

    if (F_status_is_error(status2)) {
      *status = status2;

      fake_print_message(data, F_status_set_fine(*status), "fl_string_append", F_true, data_make->print);
      return;
    }

    status2 = fl_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
    if (F_status_is_error(status2)) {
      *status = status2;

      fake_print_message(data, F_status_set_fine(*status), "fl_string_dynamic_terminate_after", F_true, data_make->print);
      return;
    }

    if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
      fprintf(data_make->print.to, "%c", f_string_eol[0]);
      fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Failed with return code '", data_make->print.prefix);
      fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", data_make->setting_make.parameter.array[0].value.array[0].string);
      fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
    }

    if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
      *status = F_status_set_error(F_failure);
    }
    else {
      *status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  f_return_status fake_make_operate_process_run(const fake_data data, const f_string_statics arguments, const bool as_shell, fake_make_data *data_make) {
    const f_string_static *program = &arguments.array[0];

    f_status status = F_none;
    f_string_dynamics args = f_string_dynamics_initialize;

    if (arguments.used > 1) {
      f_macro_string_dynamics_new(status, args, arguments.used - 1);
      if (F_status_is_error(status)) {
        fake_print_message(data, F_status_set_fine(status), "f_macro_string_dynamics_new", F_true, data_make->print);
        return status;
      }

      for (f_array_length i = 0; i < args.size; i++) {

        status = fl_string_dynamic_append(arguments.array[i + 1], &args.array[i]);
        if (F_status_is_error(status)) {
          fake_print_message(data, F_status_set_fine(status), "fl_string_dynamic_append", F_true, data_make->print);

          f_macro_string_dynamics_delete_simple(args);
          return status;
        }

        status = fl_string_dynamic_terminate(&args.array[i]);
        if (F_status_is_error(status)) {
          fake_print_message(data, F_status_set_fine(status), "fl_string_dynamic_terminate", F_true, data_make->print);

          f_macro_string_dynamics_delete_simple(args);
          return status;
        }

        args.used++;
      } // for
    }

    status = fake_make_operate_process_execute(data, *program, args, as_shell, data_make);

    f_macro_string_dynamics_delete_simple(args);
    return status;
  }
#endif // _di_fake_make_operate_process_run_

#ifndef _di_fake_make_operate_validate_
  void fake_make_operate_validate(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_string_dynamics arguments, uint8_t *operation_if, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (operation == fake_make_operation_type_archive || operation == fake_make_operation_type_run || operation == fake_make_operation_type_shell) {
      if (arguments.used == 0) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (operation == fake_make_operation_type_archive) {
        if (!data_make->setting_build.build_linker.used) {

          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            fprintf(data_make->print.to, "%c", f_string_eol[0]);
            fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: No linker has been specified, cannot perform '", data_make->print.prefix);
            fl_color_print(data_make->print.to, data.context.notable, data.context.reset, fake_make_operation_archive);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' section operation.");
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_break) {
      if (arguments.used > 1) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success, arguments.array[0], fake_make_operation_argument_success_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure, arguments.array[0], fake_make_operation_argument_failure_length) == F_equal_to_not) {

            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported break type '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_build) {
      if (arguments.used > 1) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          f_status status_file = f_file_is(arguments.array[0].string, f_file_type_regular);

          if (status_file == F_file_found_not) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Failed to find file '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            fake_print_message_file(data, *status, "f_file_is", data.file_data_build_fakefile.string, "find", F_true, F_true, data_make->print);
            *status = status_file;
          }
          else if (!status_file) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: The file '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' must be a regular file.");
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            printf("%c", f_string_eol[0]);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Filename argument must not be an empty string.", data_make->print.prefix);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_clean || operation == fake_make_operation_type_pop || operation == fake_make_operation_type_top || operation == fake_make_operation_type_skeleton) {
      if (arguments.used) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (operation == fake_make_operation_type_pop) {
        if (data_make->path.stack.used == 1) {

          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            printf("%c", f_string_eol[0]);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Must not attempt to pop project root off of path stack.", data_make->print.prefix);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_compile) {
      if (arguments.used == 0) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (data_make->setting_build.build_compiler.used) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          fprintf(data_make->print.to, "%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: No compiler has been specified, cannot perform '", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, fake_make_operation_compile);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' section operation.");
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_delete || operation == fake_make_operation_type_deletes) {
      if (arguments.used) {
        for (f_array_length i = 0; i < arguments.used; i++) {
          *status = fake_make_assure_inside_project(data, arguments.array[i], data_make);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(data, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string, data_make->print);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_define) {
      if (arguments.used) {
        *status = fake_make_operate_validate_define_name(arguments.array[0]);

        if (*status == F_none) {
          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            printf("%c", f_string_eol[0]);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Define name must not be an empty string.", data_make->print.prefix);
          }

          *status = F_status_set_error(F_failure);
        }
        else if (*status == F_false) {
          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            fprintf(data_make->print.to, "%c", f_string_eol[0]);
            fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Invalid characters in the define setting name '", data_make->print.prefix);

            fl_color_print_code(data_make->print.to, data.context.notable);
            f_print_string_dynamic(data_make->print.to, arguments.array[0]);
            fl_color_print_code(data_make->print.to, data.context.reset);

            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.");
          }

          *status = F_status_set_error(F_failure);
        }
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_else) {
      if (*operation_if == fake_make_operation_if_type_else_true || *operation_if == fake_make_operation_if_type_else_false) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Must not be used after another '", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "else");
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' section operation.");
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (*operation_if == fake_make_operation_if_type_true || *operation_if == fake_make_operation_if_type_false || *operation_if == fake_make_operation_if_type_false_always) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Must not be used inside an ", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "if");
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' section operation.");
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (*operation_if != fake_make_operation_if_type_else_true_next && *operation_if != fake_make_operation_if_type_else_false_next && *operation_if != fake_make_operation_if_type_else_false_next_always) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has no preceding if condition.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (arguments.used) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;
      }

      return;
    }

    if (operation == fake_make_operation_type_exit) {
      if (arguments.used > 1) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success, arguments.array[0], fake_make_operation_argument_success_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure, arguments.array[0], fake_make_operation_argument_failure_length) == F_equal_to_not) {

            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported exit type '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_fail) {
      if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_exit, arguments.array[0], fake_make_operation_argument_exit_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn, arguments.array[0], fake_make_operation_argument_warn_length) == F_equal_to_not) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_ignore, arguments.array[0], fake_make_operation_argument_ignore_length) == F_equal_to_not) {

              if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                printf("%c", f_string_eol[0]);
                fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported fail type '", data_make->print.prefix);
                fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
                fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_group || operation == fake_make_operation_type_groups || operation == fake_make_operation_type_mode || operation == fake_make_operation_type_modes || operation == fake_make_operation_type_owner || operation == fake_make_operation_type_owners) {
      if (arguments.used > 1) {
        f_status status_file = F_none;

        for (f_array_length i = 1; i < arguments.used; i++) {
          status_file = f_file_is(arguments.array[i].string, f_file_type_regular);

          if (status_file == F_file_found_not) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Failed to find file '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[i].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              fake_print_message_file(data, *status, "f_file_is", arguments.array[i].string, "find", F_true, F_true, data_make->print);
            }

            *status = status_file;
          }
        }

        return;
      }

      if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
        printf("%c", f_string_eol[0]);
        fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
      }

      *status = F_status_set_error(F_failure);

      return;
    }

    if (operation == fake_make_operation_type_if) {
      if (*operation_if == fake_make_operation_if_type_true || *operation_if == fake_make_operation_if_type_false || *operation_if == fake_make_operation_if_type_false_always) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Must not be used after another '", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "if");
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' section operation.");
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (arguments.used > 0) {
        const f_string if_type_strings[] = {
          fake_make_operation_argument_if_defined,
          fake_make_operation_argument_if_equal,
          fake_make_operation_argument_if_equal_not,
          fake_make_operation_argument_if_exists,
          fake_make_operation_argument_if_failure,
          fake_make_operation_argument_if_greater,
          fake_make_operation_argument_if_greater_equal,
          fake_make_operation_argument_if_group,
          fake_make_operation_argument_if_is,
          fake_make_operation_argument_if_less,
          fake_make_operation_argument_if_less_equal,
          fake_make_operation_argument_if_mode,
          fake_make_operation_argument_if_owner,
          fake_make_operation_argument_if_success,
        };

        const f_string_length if_type_lengths[] = {
          fake_make_operation_argument_if_defined_length,
          fake_make_operation_argument_if_equal_length,
          fake_make_operation_argument_if_equal_not_length,
          fake_make_operation_argument_if_exists_length,
          fake_make_operation_argument_if_failure_length,
          fake_make_operation_argument_if_greater_length,
          fake_make_operation_argument_if_greater_equal_length,
          fake_make_operation_argument_if_group_length,
          fake_make_operation_argument_if_is_length,
          fake_make_operation_argument_if_less_length,
          fake_make_operation_argument_if_less_equal_length,
          fake_make_operation_argument_if_mode_length,
          fake_make_operation_argument_if_owner_length,
          fake_make_operation_argument_if_success_length,
        };

        const uint8_t if_type_codes[] = {
          fake_make_operation_if_type_if_defined,
          fake_make_operation_if_type_if_equal,
          fake_make_operation_if_type_if_equal_not,
          fake_make_operation_if_type_if_exists,
          fake_make_operation_if_type_if_failure,
          fake_make_operation_if_type_if_greater,
          fake_make_operation_if_type_if_greater_equal,
          fake_make_operation_if_type_if_group,
          fake_make_operation_if_type_if_is,
          fake_make_operation_if_type_if_less,
          fake_make_operation_if_type_if_less_equal,
          fake_make_operation_if_type_if_mode,
          fake_make_operation_if_type_if_owner,
          fake_make_operation_if_type_if_success,
        };

        const uint8_t if_type_minimum[] = {
          2,
          2,
          2,
          2,
          1,
          2,
          2,
          3,
          3,
          2,
          2,
          4,
          3,
          1,
        };

        f_string_length i = 0;

        for (; i < 14; i++) {
          if (fl_string_dynamic_compare_string(if_type_strings[i], arguments.array[0], if_type_lengths[i]) == F_equal_to) {
            *operation_if = if_type_codes[i];
            break;
          }
        } // for

        if (i == 14) {
          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            printf("%c", f_string_eol[0]);
            fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported if type '", data_make->print.prefix);
            fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
          }

          *status = F_status_set_error(F_failure);
          *operation_if = fake_make_operation_if_type_false_always_next;

          return;
        }

        if (arguments.used >= if_type_minimum[i]) {
          if (*operation_if == fake_make_operation_if_type_if_success || *operation_if == fake_make_operation_if_type_if_failure) {
            if (arguments.used > if_type_minimum[i]) {
              if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                printf("%c", f_string_eol[0]);
                fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
              }

              *status = F_status_set_error(F_failure);
              *operation_if = fake_make_operation_if_type_false_always_next;
            }

            return;
          }

          if (*operation_if == fake_make_operation_if_type_if_mode || *operation_if == fake_make_operation_if_type_if_owner || *operation_if == fake_make_operation_if_type_if_group || *operation_if == fake_make_operation_if_type_if_is || *operation_if == fake_make_operation_if_type_if_exists) {
            if (*operation_if == fake_make_operation_if_type_if_mode) {

              if (fl_string_dynamic_compare_string(fake_make_operation_argument_is, arguments.array[1], fake_make_operation_argument_is_length) == F_equal_to_not) {
                if (fl_string_dynamic_compare_string(fake_make_operation_argument_has, arguments.array[1], fake_make_operation_argument_has_length) == F_equal_to_not) {
                  if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                    printf("%c", f_string_eol[0]);
                    fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported mode type '", data_make->print.prefix);
                    fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[1].string);
                    fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
                  }

                  *status = F_status_set_error(F_failure);
                  return;
                }
              }

              f_file_mode mode_rule = 0;
              uint8_t replace = 0;

              *status = fake_make_get_id_mode(data, data_make->print, arguments.array[2], &mode_rule, &replace);
              if (F_status_is_error(*status)) return;

              i = 3;
            }

            if (*operation_if == fake_make_operation_if_type_if_owner) {
              uid_t id = 0;

              *status = fake_make_get_id_owner(data, data_make->print, arguments.array[1], &id);
              if (F_status_is_error(*status)) return;

              i = 2;
            }

            if (*operation_if == fake_make_operation_if_type_if_group) {
              gid_t id = 0;

              *status = fake_make_get_id_group(data, data_make->print, arguments.array[1], &id);
              if (F_status_is_error(*status)) return;

              i = 2;
            }

            if (*operation_if == fake_make_operation_if_type_if_is) {
              // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
              // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
              // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
              // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
              uint8_t type_file = 0;

              for (i = 1; i < arguments.used; i++) {
                if (fl_string_dynamic_compare_string(fake_make_operation_argument_if_is_for, arguments.array[i], fake_make_operation_argument_if_is_for_length) == F_equal_to) {
                  i++;
                  break;
                }

                if (fl_string_dynamic_compare_string(f_file_type_name_block, arguments.array[i], f_file_type_name_block_length) == F_equal_to) {
                  type_file |= 0x1;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_character, arguments.array[i], f_file_type_name_character_length) == F_equal_to) {
                  type_file |= 0x2;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_directory, arguments.array[i], f_file_type_name_directory_length) == F_equal_to) {
                  type_file |= 0x4;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_fifo, arguments.array[i], f_file_type_name_fifo_length) == F_equal_to) {
                  type_file |= 0x8;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_link, arguments.array[i], f_file_type_name_link_length) == F_equal_to) {
                  type_file |= 0x10;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_regular, arguments.array[i], f_file_type_name_regular_length) == F_equal_to) {
                  type_file |= 0x20;
                }
                else if (fl_string_dynamic_compare_string(f_file_type_name_socket, arguments.array[i], f_file_type_name_socket_length) == F_equal_to) {
                  type_file |= 0x40;
                }
                else {
                  if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                    printf("%c", f_string_eol[0]);
                    fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported file type '", data_make->print.prefix);
                    fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[i].string);
                    fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
                  }

                  type_file |= 0x80;
                }
              } // for

              if (type_file & 0x80) {
                *status = F_status_set_error(F_failure);
                *operation_if = fake_make_operation_if_type_false_always_next;

                return;
              }
            }

            if (*operation_if == fake_make_operation_if_type_if_exists) {
              i = 1;
            }

            if (i < arguments.used) {
              for (f_status status_file = F_none; i < arguments.used; i++) {
                status_file = fake_make_assure_inside_project(data, arguments.array[i], data_make);

                if (F_status_is_error(status_file)) {
                  fake_print_message_section_operation_path_outside(data, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string, data_make->print);

                  *operation_if = fake_make_operation_if_type_false_always_next;

                  if (F_status_is_fine(*status)) {
                    if (F_status_set_fine(status_file) == F_false) {
                      *status = F_status_set_error(F_failure);
                    }
                    else {
                      *status = status_file;
                    }
                  }
                }
                else if (*operation_if != fake_make_operation_if_type_if_exists && *operation_if != fake_make_operation_if_type_if_is) {
                  // The existence tests do not need to happen here for *_if_exists and *_if_is as those two types will handle performing them during the process stage.
                  status_file = f_file_exists(arguments.array[i].string);

                  if (status_file == F_false) {
                    status_file = F_status_set_error(F_file_found_not);
                  }

                  if (F_status_is_error(status_file)) {
                    fake_print_message_file(data, F_status_set_fine(status_file), "f_file_exists", arguments.array[i].string, "find", F_true, F_true, data_make->print);

                    *operation_if = fake_make_operation_if_type_false_always_next;

                    if (F_status_is_fine(*status)) {
                      *status = F_status_set_error(status_file);
                    }
                  }
                }
              } // for

              return;
            }
          }

          if (*operation_if == fake_make_operation_if_type_if_defined) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_environment, arguments.array[1], fake_make_operation_argument_environment_length) == F_equal_to_not) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_parameter, arguments.array[1], fake_make_operation_argument_parameter_length) == F_equal_to_not) {
                if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                  printf("%c", f_string_eol[0]);
                  fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported define type '", data_make->print.prefix);
                  fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[1].string);
                  fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
                }

                *status = F_status_set_error(F_failure);
              }
            }

            return;
          }

          if (*operation_if == fake_make_operation_if_type_if_equal || *operation_if == fake_make_operation_if_type_if_equal_not) {
            // nothing to validate.
            return;
          }

          if (*operation_if == fake_make_operation_if_type_if_greater || *operation_if == fake_make_operation_if_type_if_greater_equal || *operation_if == fake_make_operation_if_type_if_less || *operation_if == fake_make_operation_if_type_if_less_equal) {
            f_status status_number = F_none;
            f_string_range range = f_string_range_initialize;
            f_number_unsigned number = 0;
            bool is_negative = F_false;

            // @fixme there needs to handle converting numbers with decimals (like 1.01), perhaps operate on them as strings or provide a special processor.
            for (i = 1; i < arguments.used; i++, status_number = F_none) {
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
                  status_number = fl_conversion_string_to_number_unsigned(arguments.array[i].string, &number, range);
                }
              }
              else {
                status_number = F_status_set_error(F_failure);
              }

              if (F_status_is_error(status_number)) {
                *status = F_status_set_error(F_failure);

                if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
                  printf("%c", f_string_eol[0]);

                  if (number > f_type_number_size_unsigned) {
                    fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: The number '", data_make->print.prefix);
                    fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%c%s", arguments.array[i].string);
                    fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' may only be between the ranges -%llu to %llu.", f_type_number_size_unsigned, f_type_number_size_unsigned);
                  }
                  else {
                    fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Invalid or unsupported number provided '", data_make->print.prefix);
                    fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[i].string);
                    fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
                  }
                }
              }
            } // for

            return;
          }
        }
      }

      if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
        printf("%c", f_string_eol[0]);
        fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
      }

      *status = F_status_set_error(F_failure);
      *operation_if = fake_make_operation_if_type_false_always_next;

      return;
    }

    if (operation == fake_make_operation_type_link) {
      if (arguments.used > 2) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 2) {
        *status = fake_make_assure_inside_project(data, arguments.array[0], data_make);
        if (F_status_is_error(*status)) {
          // @todo warning
          fake_print_message_section_operation_path_outside(data, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string, data_make->print);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }

        *status = fake_make_assure_inside_project(data, arguments.array[1], data_make);
        if (F_status_is_error(*status)) {
          // @todo warning
          fake_print_message_section_operation_path_outside(data, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[1].string, data_make->print);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_operate) {
      if (arguments.used > 1) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 1) {
        f_array_length id_section = 0;

        for (; id_section < data_make->fakefile.used; id_section++) {
          if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
            break;
          }
        } // for

        if (id_section == data_make->fakefile.used) {
          printf("%c", f_string_eol[0]);
          fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: No operation section named '", data_make->print.prefix);
          fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' was found.");
        }
        else {
          for (f_array_length i = 0; i < section_stack->used; i++) {
            if (section_stack->array[i] == id_section) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: The section operation '", data_make->print.prefix);

              fl_color_print_code(data_make->print.to, data.context.notable);
              f_print_string_dynamic_partial(data_make->print.to, data_make->buffer, data_make->fakefile.array[id_section].name);
              fl_color_print_code(data_make->print.to, data.context.reset);

              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' is already in the operation stack, recursion is not allowed.");

              *status = F_status_set_error(F_failure);
              break;
            }
          } // for
        }
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      return;
    }

    if (operation == fake_make_operation_type_to) {
      if (arguments.used > 1) {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Has too many arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          f_status status_file = f_file_is(arguments.array[0].string, f_file_type_directory);

          if (status_file == F_file_found_not) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Failed to find file '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              fake_print_message_file(data, *status, "f_file_is", data.file_data_build_fakefile.string, "find", F_true, F_true, data_make->print);
            }

            *status = status_file;
          }
          else if (!status_file) {
            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: The file '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "' must be a directory file.");
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
            printf("%c", f_string_eol[0]);
            fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Filename argument must not be an empty string.", data_make->print.prefix);
          }
        }
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_touch) {
      if (arguments.used > 1) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_file, arguments.array[0], fake_make_operation_argument_file_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory, arguments.array[0], fake_make_operation_argument_directory_length) == F_equal_to_not) {

            if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
              printf("%c", f_string_eol[0]);
              fl_color_print(data_make->print.to, data_make->print.context, data.context.reset, "%s: Unsupported file type '", data_make->print.prefix);
              fl_color_print(data_make->print.to, data.context.notable, data.context.reset, "%s", arguments.array[0].string);
              fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "'.");
            }

            *status = F_status_set_error(F_failure);
          }
        }

        for (f_array_length i = 1; i < arguments.used; i++) {
          *status = fake_make_assure_inside_project(data, arguments.array[i], data_make);
          if (F_status_is_error(*status)) {
            // @todo warning
            fake_print_message_section_operation_path_outside(data, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string, data_make->print);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        if (data.verbosity != fake_verbosity_quiet && data_make->print.to) {
          printf("%c", f_string_eol[0]);
          fl_color_print_line(data_make->print.to, data_make->print.context, data.context.reset, "%s: Requires more arguments.", data_make->print.prefix);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    // note: there is nothing to validate for fake_make_operation_type_print.
  }
#endif // _di_fake_make_operate_validate_

#ifndef _di_fake_make_operate_validate_define_name_
  f_return_status fake_make_operate_validate_define_name(const f_string_static name) {
    if (!name.used) return F_none;

    if (!(isalpha(name.string[0]) || name.string[0] == '_')) {
      return F_false;
    }

    for (f_string_length i = 0; i < name.used; i++) {
      if (!(isalnum(name.string[i]) || name.string[i] == '_')) {
        return F_false;
      }
    } // for

    return F_true;
  }
#endif // _di_fake_make_operate_validate_define_name_

#ifndef _di_fake_make_path_relative_
  f_return_status fake_make_path_relative(const fake_data data, const f_string_static path, fake_make_data *data_make) {
    data_make->path_cache.used = 0;

    if (!path.used || path.used == data_make->path.stack.array[0].used) {
      return F_none;
    }

    if (path.used < data_make->path.stack.array[0].used) {
      return F_status_set_error(F_failure);
    }

    f_string_range range = f_string_range_initialize;

    range.start = data_make->path.stack.array[0].used + 1;
    range.stop = range.start + (path.used - range.start) - 1;

    f_status status = fl_string_dynamic_partial_append(path, range, &data_make->path_cache);
    if (F_status_is_error(status)) return status;

    status = fl_string_dynamic_terminate(&data_make->path_cache);
    if (F_status_is_error(status)) return status;

    return status;
  }
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif
