#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

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
        fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_basic_list_read", data.file_data_build_fakefile.string, range, F_true);

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
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_fss_nameds_new", F_true);

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
              fake_print_warning_fakefile_object_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, "list", name_settings.string);
              continue;
            }

            content_range = list_contents.array[i].array[0];

            *status = fll_fss_extended_read(&data_make->buffer, &content_range, &settings.objects, &settings.contents, 0, 0);
            if (F_status_is_error(*status)) {
              fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

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
              fake_print_warning_fakefile_object_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, "list", name_main.string);
              continue;
            }

            missing_main = F_false;
            data_make->main = data_make->fakefile.used;
          }

          data_make->fakefile.array[data_make->fakefile.used].name = list_objects.array[i];

          content_range = list_contents.array[i].array[0];

          *status = fll_fss_extended_read(&data_make->buffer, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotedss);
          if (F_status_is_error(*status)) {
            fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

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
          fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: the fakefile '");
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
          fake_print_error(data.context, data.verbosity, *status, function_name, F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_true;

      if (settings.objects.used) {
        bool unmatched_load = F_true;

        for (f_array_length i = 0; i < settings.objects.used; i++) {
          if (fl_string_dynamic_partial_compare_string(fake_make_setting_load_build, data_make->buffer, fake_make_setting_load_build_length, settings.objects.array[i]) == F_equal_to) {
            if (unmatched_load) {
              if (settings.contents.array[i].used) {
                if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_yes, data_make->buffer, fake_common_setting_bool_yes_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_true;
                }
                else if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_no, data_make->buffer, fake_common_setting_bool_no_length, settings.contents.array[i].array[0]) == F_equal_to) {
                  data_make->setting_make.load_build = F_false;
                }
                else {
                  fake_print_error_fakefile_settings_content_invalid(data.context, data.verbosity, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings);
                }

                unmatched_load = F_false;
              }

              if (settings.contents.array[i].used > 1) {
                fake_print_warning_settings_content_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, fake_make_setting_load_build);
              }
            }
            else {
              fake_print_warning_settings_content_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, fake_make_setting_load_build);
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
                      fake_print_error(data.context, data.verbosity, *status, function_name, F_true);

                      f_macro_fss_set_delete_simple(settings);
                      return;
                    }
                  } // for
                }
              }
            }
          }
        } // for
      }

      if (data_make->setting_make.load_build) {
        fake_build_load_setting(data, &data_make->setting_build, status);
      }

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
          &data_make->setting_make.define,
          &data_make->setting_make.parameter,
        };

        *status = fll_fss_snatch_map_apart(data_make->buffer, settings.objects, settings.contents, settings_name, settings_length, 2, settings_value, 0);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_fss_snatch_map_apart", F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      if (data_make->setting_make.define.used) {
        f_status status_validate = F_none;

        for (f_array_length i = 0; i < data_make->setting_make.define.used; i++) {
          status_validate = fake_make_operate_validate_define_name(data_make->setting_make.define.array[i].name);

          if (status_validate == F_false) {
            if (data.verbosity != fake_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data.context.error, data.context.reset, "ERROR: invalid characters in the define setting name '");

              fl_color_print_code(f_type_error, data.context.notable);
              f_print_string_dynamic(f_type_error, data_make->setting_make.define.array[i].name);
              fl_color_print_code(f_type_error, data.context.reset);

              fl_color_print_line(f_type_error, data.context.error, data.context.reset, "', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.");
            }

            *status = F_status_set_error(F_failure);
          }
        } // for
      }

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

    f_string_lengths list_stack = f_string_lengths_initialize;
    fake_make_data data_make = fake_make_data_initialize;

    f_macro_string_dynamics_new(status, data_make.path.stack, f_memory_default_allocation_step);
    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_macro_string_dynamics_new", F_true);
      return status;
    }

    status = f_path_current(F_true, &data_make.path.stack.array[0]);
    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_path_current", F_true);

      fake_macro_make_data_delete_simple(data_make);
      return status;
    }

    status = f_directory_open(data_make.path.stack.array[0].string, F_false, &data_make.path.top);
    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_directory_open", F_true);

      fake_macro_make_data_delete_simple(data_make);
      return status;
    }

    f_macro_mode_set_default_umask(mode, data.umask);

    data_make.fail = fake_make_operation_fail_type_exit;

    fake_make_load_fakefile(data, &data_make, &status);

    fake_make_operate_section(data, data_make.main, &data_make, &list_stack, &status);

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

    f_macro_string_lengths_delete_simple(list_stack);
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
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true);
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

    f_string_map_multis *map_multis = 0;

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
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_iki_read", F_true);
        break;
      }

      if (arguments->used == arguments->size) {
        if (arguments->used + f_memory_default_allocation_step <= F_buffer_too_large) {
          f_macro_string_dynamics_resize((*status), (*arguments), arguments->used + f_memory_default_allocation_step);
        }
        else if (arguments->used + 1 <= F_buffer_too_large) {
          f_macro_string_dynamics_resize((*status), (*arguments), arguments->used + 1);
        }
        else {
          *status = F_status_set_error(F_buffer_too_large);
        }

        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true);
          return;
        }
      }

      if (iki_variable.used) {
        if (iki_variable.array[0].start > 0 && content.array[i].start < iki_variable.array[0].start) {
          range.start = content.array[i].start;
          range.stop = iki_variable.array[0].start - 1;

          *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true);
            break;
          }
        }

        for (j = 0, previous = iki_variable.array[0].start; j < iki_variable.used; j++) {

          if (previous + 1 < iki_variable.array[j].start) {
            range.start = previous + 1;
            range.stop = iki_variable.array[j].start - 1;

            *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
            if (F_status_is_error(*status)) {
              fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true);
              break;
            }
          }

          *status = fl_string_dynamic_partial_compare(vocabulary_define, data_make->buffer, range_define, iki_vocabulary.array[j]);

          if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_compare(vocabulary_parameter, data_make->buffer, range_parameter, iki_vocabulary.array[j]);

            if (*status == F_equal_to) {
              map_multis = &data_make->setting_make.parameter;
            }
          }
          else if (*status == F_equal_to) {
            map_multis = &data_make->setting_make.define;
          }

          if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, iki_variable.array[j], &arguments->array[arguments->used]);
            if (F_status_is_error(*status)) {
              fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true);
              break;
            }

            previous = iki_variable.array[j].stop;
            continue;
          }
          else if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_partial_compare", F_true);
            break;
          }

          if (map_multis->used) {
            for (k = 0; k < map_multis->used; k++) {
              *status = fl_string_dynamic_partial_compare_dynamic(map_multis->array[k].name, data_make->buffer, iki_content.array[j]);

              if (*status == F_equal_to) {
                if (map_multis->array[k].value.used) {
                  if (quoteds.array[i]) {
                    for (l = 0; l < map_multis->array[k].value.used; l++) {
                      if (l > 0) {
                        *status = fl_string_append(" ", 1, &arguments->array[arguments->used]);
                        if (F_status_is_error(*status)) {
                          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append", F_true);
                          break;
                        }
                      }

                      *status = fl_string_dynamic_append_nulless(map_multis->array[k].value.array[l], &arguments->array[arguments->used]);
                      if (F_status_is_error(*status)) {
                        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
                        break;
                      }
                    } // for
                  }
                  else {
                    if (arguments->used + map_multis->array[k].value.used > arguments->size) {
                      if (arguments->used + map_multis->array[k].value.used > F_buffer_too_large) {
                        *status = F_status_set_error(F_buffer_too_large);

                        fake_print_error(data.context, data.verbosity, F_buffer_too_large, "f_macro_string_dynamics_resize", F_true);
                        break;
                      }

                      f_macro_string_dynamics_resize((*status), (*arguments), arguments->used + map_multis->array[k].value.used);
                      if (F_status_is_error(*status)) {
                        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "f_macro_string_dynamics_resize", F_true);
                        break;
                      }
                    }

                    for (l = 0; l < map_multis->array[k].value.used; l++) {
                      *status = fl_string_dynamic_append_nulless(map_multis->array[k].value.array[l], &arguments->array[arguments->used]);
                      if (F_status_is_error(*status)) {
                        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_append_nulless", F_true);
                        break;
                      }

                      *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);
                      if (F_status_is_error(*status)) {
                        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_terminate_after", F_true);
                        break;
                      }

                      arguments->used++;
                    } // for
                  }
                }

                break;
              }
              else if (F_status_is_error(*status)) {
                fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_compare", F_true);
                break;
              }
            } // for

            if (F_status_is_error(*status)) break;
          }

          previous = iki_variable.array[j].stop;
        } // for

        if (F_status_is_error(*status)) break;

        if (iki_variable.array[iki_variable.used - 1].stop < content.array[i].stop) {
          range.start = iki_variable.array[iki_variable.used - 1].stop + 1;
          range.stop = content.array[i].stop;

          *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
          if (F_status_is_error(*status)) {
            fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_dynamic_partial_append_nulless", F_true);
            break;
          }
        }
      }
      else {
        *status = fl_string_dynamic_partial_append_nulless(data_make->buffer, content.array[i], &arguments->array[arguments->used]);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_append_nulless", F_true);
          break;
        }
      }

      // if iki variable did not match (results in empty string) or iki variable is inside quotes, then increment.
      if (used_arguments == arguments->used) {
        *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_terminate_after", F_true);
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

#ifndef _di_fake_make_operate_section_
  void fake_make_operate_section(const fake_data data, const f_array_length section_id, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (section_id > data_make->fakefile.used) {
      *status = F_status_set_error(F_parameter);

      fake_print_error(data.context, data.verbosity, F_parameter, "fake_make_operate_section", F_true);
      return;
    }

    const f_fss_named *section = &data_make->fakefile.array[section_id];

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);

      fl_color_print(f_type_output, data.context.important, data.context.reset, "Processing Section '");

      fl_color_print_code(f_type_output, data.context.notable);
      f_print_string_dynamic_partial(f_type_output, data_make->buffer, section->name);
      fl_color_print_code(f_type_output, data.context.reset);

      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "'.");
    }

    if (!section->objects.used) {
      return;
    }

    const f_string_static operations_name[] = {
      f_macro_string_static_initialize(fake_make_operation_archive, fake_make_operation_archive_length),
      f_macro_string_static_initialize(fake_make_operation_build, fake_make_operation_build_length),
      f_macro_string_static_initialize(fake_make_operation_clean, fake_make_operation_clean_length),
      f_macro_string_static_initialize(fake_make_operation_compile, fake_make_operation_compile_length),
      f_macro_string_static_initialize(fake_make_operation_create, fake_make_operation_create_length),
      f_macro_string_static_initialize(fake_make_operation_define, fake_make_operation_define_length),
      f_macro_string_static_initialize(fake_make_operation_delete, fake_make_operation_delete_length),
      f_macro_string_static_initialize(fake_make_operation_else, fake_make_operation_else_length),
      f_macro_string_static_initialize(fake_make_operation_fail, fake_make_operation_fail_length),
      f_macro_string_static_initialize(fake_make_operation_group, fake_make_operation_group_length),
      f_macro_string_static_initialize(fake_make_operation_if, fake_make_operation_if_length),
      f_macro_string_static_initialize(fake_make_operation_link, fake_make_operation_link_length),
      f_macro_string_static_initialize(fake_make_operation_mode, fake_make_operation_mode_length),
      f_macro_string_static_initialize(fake_make_operation_operate, fake_make_operation_operate_length),
      f_macro_string_static_initialize(fake_make_operation_owner, fake_make_operation_owner_length),
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
      f_macro_string_range_initialize(fake_make_operation_build_length),
      f_macro_string_range_initialize(fake_make_operation_clean_length),
      f_macro_string_range_initialize(fake_make_operation_compile_length),
      f_macro_string_range_initialize(fake_make_operation_create_length),
      f_macro_string_range_initialize(fake_make_operation_define_length),
      f_macro_string_range_initialize(fake_make_operation_delete_length),
      f_macro_string_range_initialize(fake_make_operation_else_length),
      f_macro_string_range_initialize(fake_make_operation_fail_length),
      f_macro_string_range_initialize(fake_make_operation_group_length),
      f_macro_string_range_initialize(fake_make_operation_if_length),
      f_macro_string_range_initialize(fake_make_operation_link_length),
      f_macro_string_range_initialize(fake_make_operation_mode_length),
      f_macro_string_range_initialize(fake_make_operation_operate_length),
      f_macro_string_range_initialize(fake_make_operation_owner_length),
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
      fake_make_operation_type_build,
      fake_make_operation_type_clean,
      fake_make_operation_type_compile,
      fake_make_operation_type_create,
      fake_make_operation_type_define,
      fake_make_operation_type_delete,
      fake_make_operation_type_else,
      fake_make_operation_type_fail,
      fake_make_operation_type_group,
      fake_make_operation_type_if,
      fake_make_operation_type_link,
      fake_make_operation_type_mode,
      fake_make_operation_type_operate,
      fake_make_operation_type_owner,
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

    const f_string_static *operation_name = 0;

    f_string_dynamics arguments[section->objects.used];

    f_array_length i = 0;
    f_array_length j = 0;

    memset(operations, 0, sizeof(uint8_t) * section->objects.used);
    memset(arguments, 0, sizeof(f_string_dynamics) * section->objects.used);

    bool error_none = F_true;
    bool process = F_true;

    do {
      // pre-process the list to identify invalid commands so that nothing is processed if any operation can be detected as invalid by the pre-process validation.
      process = !process;

      for (i = 0; i < section->objects.used; i++) {
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
          fake_print_error_fakefile_section_operation_unknown(data.context, data.verbosity, data_make->buffer, section->name, section->objects.array[i]);

          *status = F_status_set_error(F_invalid);
        }
        else if (operation == fake_make_operation_type_operate) {
          if (section_stack->used == fake_make_section_stack_max) {
            fake_print_error_fakefile_section_operation_stack_max(data.context, data.verbosity, data_make->buffer, section->name, section->objects.array[i], fake_make_section_stack_max);

            *status = F_status_set_error(F_recurse);
          }
        }

        // find and report all unknown operations before exiting.
        if (F_status_is_error(*status)) {
          error_none = F_false;
          *status = F_none;
          continue;
        }

        operations[i] = operation;

        if (process) {
          fake_make_operate_expand(data, section->name, operation, *operation_name, section->contents.array[i], section->quotedss.array[i], data_make, &arguments[i], status);
          if (F_status_is_error(*status)) {
            error_none = F_false;
            continue;
          }
        }

        fake_make_operate_validate(data, section->name, operation, *operation_name, *data_make, arguments[i], operation_if, process, status);

        if (operation_if) {
          if (operation_if == fake_make_operation_if_type_if) {
            operation_if = fake_make_operation_if_type_else;
          }
          else if (operation_if == fake_make_operation_if_type_else) {
            if (operation == fake_make_operation_type_if) {
              operation_if = fake_make_operation_if_type_if;
            }
            else {
              operation_if = 0;
            }
          }
          else {
            operation_if = 0;
          }
        }
        else if (operation == fake_make_operation_type_if) {
          operation_if = fake_make_operation_if_type_if;
        }

        if (F_status_is_error(*status)) {
          error_none = F_false;
          *status = F_none;
          continue;
        }

        if (error_none && process) {
          fake_make_operate_perform(data, section->name, operation, *operation_name, arguments[i], operation_if, data_make, status);

          if (F_status_is_error(*status)) {
            fake_print_error_fakefile_section_operation_failed(data.context, data.verbosity, data_make->buffer, section->name, section->objects.array[i]);
            break;
          }
        }
      } // for
    } while (error_none && !process);

    if (!error_none && F_status_is_fine(*status)) {
      *status = F_status_set_error(F_failure);
    }

    for (i = 0; i < section->objects.used; i++) {
      f_macro_string_dynamics_delete_simple(arguments[i]);
    } // for
  }
#endif // _di_fake_make_operate_section_

#ifndef _di_fake_make_operate_perform_
  void fake_make_operate_perform(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_string_dynamics arguments, const uint8_t operation_if, fake_make_data *data_make, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (operation == fake_make_operation_type_archive) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);

      return;
    }

    if (operation == fake_make_operation_type_build) {
      *status = fake_build_operate(data);

      fake_make_operate_perform_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_clean) {
      *status = fake_clean_operate(data);

      fake_make_operate_perform_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_compile) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_create) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_define) {
      // @todo: walk through each existing define to see if it already exists and replace it, otherwise create a new one.
      return;
    }

    if (operation == fake_make_operation_type_delete) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_else) {
      // @todo: need to manage the condition result for the if condition to decide if the else was or was not triggered.
      return;
    }

    if (operation == fake_make_operation_type_fail) {
      return;
    }

    if (operation == fake_make_operation_type_group) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_if) {
      // @todo: walk through each condition and save success/failure state.
      return;
    }

    if (operation == fake_make_operation_type_link) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_mode) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_operate) {
      // @todo: call other list, adding it to the stack.
      return;
    }

    if (operation == fake_make_operation_type_owner) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_pop) {
      // @todo: change directory.
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
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_shell) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }

    if (operation == fake_make_operation_type_skeleton) {
      *status = fake_skeleton_operate(data);

      fake_make_operate_perform_process_return(data, 0, data_make, status);
      return;
    }

    if (operation == fake_make_operation_type_to) {
      // @todo: change directory.
      return;
    }

    if (operation == fake_make_operation_type_top) {
      // @todo: change directory.
      return;
    }

    if (operation == fake_make_operation_type_touch) {
      // *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
      //fake_build_arguments_standard_add(data, data_build, F_true, F_true, &arguments, status);
      //fake_build_execute(data, data_build, data_build.setting.build_compiler, arguments, status);
      return;
    }
  }
#endif // _di_fake_make_operate_perform_

#ifndef _di_fake_make_operate_perform_process_return_
  void fake_make_operate_perform_process_return(const fake_data data, const f_number_signed return_code, fake_make_data *data_make, f_status *status) {
    f_status status2 = F_none;

    // @todo: assiging the return status should be moved to a function.
    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (F_status_is_error(*status)) {
      // @todo: convert F_status_set_fine(*status) to a string and assign that instead of 1. (need a convert function from llu to string.)
      status2 = fl_string_append("1", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
    }
    else {
      // @todo: convert return_code to a string and assign that instead of 0. (need a convert function from llu to string.)
      status2 = fl_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      if (F_status_is_error(status2)) {
        *status = status2;
        // @todo print error.
      }
    }

    if (F_status_is_fine(status2)) {
      status2 = fl_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);
      if (F_status_is_error(status2)) {
        *status = status2;
        // @todo print error.
      }
    }
  }
#endif // _di_fake_make_operate_perform_process_return_

#ifndef _di_fake_make_operate_validate_
  void fake_make_operate_validate(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const fake_make_data data_make, const f_string_dynamics arguments, const uint8_t operation_if, const bool process, f_status *status) {
    if (F_status_is_error(*status)) return;

    if (operation == fake_make_operation_type_archive || operation == fake_make_operation_type_run || operation == fake_make_operation_type_shell || operation == fake_make_operation_type_touch) {
      if (arguments.used == 0) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_build) {
      if (arguments.used > 1) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used && process) {
        if (arguments.array[0].used) {
          f_status status_file = f_file_is(arguments.array[0].string, f_file_type_regular);

          if (F_status_is_error(status_file)) {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "failed to find file '%s'", arguments.array[0].string);
            *status = status_file;
          }

          if (!status_file) {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "the file '%s' must be a regular file", arguments.array[0].string);
            *status = F_status_set_error(F_failure);
          }
        }
        else {
          fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "filename argument must not be an empty string");
        }
      }
    }
    else if (operation == fake_make_operation_type_clean || operation == fake_make_operation_type_pop || operation == fake_make_operation_type_top || operation == fake_make_operation_type_skeleton) {
      if (arguments.used) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_compile) {
      if (arguments.used == 0) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_create || operation == fake_make_operation_type_delete) {
      if (arguments.used) {
        if (process) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_file, arguments.array[0], fake_make_operation_argument_file_length) == F_equal_to) {
            if (arguments.used > 2) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
              *status = F_status_set_error(F_failure);
            }
          }
          else if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory, arguments.array[0], fake_make_operation_argument_directory_length) == F_equal_to) {
            if (arguments.used > 3) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
              *status = F_status_set_error(F_failure);
            }
            else if (arguments.used == 3) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_recursive, arguments.array[0], fake_make_operation_argument_recursive_length) == F_equal_to_not) {
                fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "third argument must be either '%s' or not provided at all", fake_make_operation_argument_recursive);
                *status = F_status_set_error(F_failure);
              }
            }
          }
          else {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "unsupported file type '%s'", arguments.array[0].string);
            *status = F_status_set_error(F_failure);
          }
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_define) {
      if (arguments.used) {
        if (process) {
          // @todo: validate that first argument is a valid define name.
          // @todo: if arguments.used is 1, then value is assigned to null.
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_else) {
      if (operation_if == fake_make_operation_if_type_else) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "must not be used after another else condition");
        *status = F_status_set_error(F_failure);
      }
      else if (!operation_if) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has no preceding if condition");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_fail) {
      if (arguments.used) {
        if (process) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_error, arguments.array[0], fake_make_operation_argument_error_length) == F_equal_to_not) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn, arguments.array[0], fake_make_operation_argument_warn_length) == F_equal_to_not) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_ignore, arguments.array[0], fake_make_operation_argument_ignore_length) == F_equal_to_not) {
                fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "unsupported fail type '%s'", arguments.array[0].string);
                *status = F_status_set_error(F_failure);
              }
            }
          }
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_group || operation == fake_make_operation_type_mode || operation == fake_make_operation_type_owner) {
      if (arguments.used > 3) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used > 1) {
        if (process) {
          f_status status_file = f_file_is(arguments.array[1].string, f_file_type_regular);

          if (F_status_is_error(status_file)) {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "failed to find file '%s'", arguments.array[1].string);
            *status = status_file;
          }

          if (!status_file) {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "the file '%s' must be a regular file", arguments.array[1].string);
            *status = F_status_set_error(F_failure);
          }

          if (arguments.used == 3) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_recursive, arguments.array[2], fake_make_operation_argument_recursive_length) == F_equal_to_not) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "third argument must be either '%s' or not provided at all", fake_make_operation_argument_recursive);
              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_if) {
      if (operation_if == fake_make_operation_if_type_if) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "must not be used after another if condition");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_link) {
      // @todo validate link is outside that the link is or is not outside the project directory.
      if (arguments.used > 2) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 2) {
        if (process) {
          f_status status_file = F_none;

          if (arguments.array[0].used) {
            status_file = f_file_exists(arguments.array[0].string);

            if (F_status_is_error(status_file) || !status_file) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "failed to find file '%s'", arguments.array[0].string);

              if (status_file == F_false) {
                *status = F_status_set_error(F_failure);
              }
              else {
                *status = status_file;
              }
            }
          }
          else {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "%s filename argument must not be an empty string", fake_make_operation_argument_target);
            *status = F_status_set_error(F_failure);
          }

          if (arguments.array[1].used) {
            status_file = f_file_exists(arguments.array[1].string);

            if (F_status_is_error(status_file) || !status_file) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "failed to find file '%s'", arguments.array[1].string);

              if (status_file == F_false) {
                *status = F_status_set_error(F_failure);
              }
              else {
                *status = status_file;
              }
            }
          }
          else {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "%s filename argument must not be an empty string", fake_make_operation_argument_point);
            *status = F_status_set_error(F_failure);
          }
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }
    else if (operation == fake_make_operation_type_operate) {
      // @todo: validate if list name exists (and is not reserved, such as 'settings' and 'main').
      // @todo: should recursion be checked here as well?
    }
    else if (operation == fake_make_operation_type_to) {
      if (arguments.used > 1) {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "has too many arguments");
        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (process) {
          if (arguments.array[0].used) {
            f_status status_file = f_file_is(arguments.array[0].string, f_file_type_directory);

            if (F_status_is_error(status_file)) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "failed to find file '%s'", arguments.array[0].string);
              *status = status_file;
            }

            if (!status_file) {
              fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "the file '%s' must be a directory file", arguments.array[0].string);
              *status = F_status_set_error(F_failure);
            }
          }
          else {
            fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "filename argument must not be an empty string");
          }
        }
      }
      else {
        fake_print_error_section_operation(data, data_make.buffer,section_name, operation_name, "requires arguments");
        *status = F_status_set_error(F_failure);
      }
    }

    // note: there is nothing to validate for fake_make_operation_type_print.
  }
#endif // _di_fake_make_operate_validate_

#ifndef _di_fake_make_operate_validate_define_name_
  f_return_status fake_make_operate_validate_define_name(const f_string_static name) {
    if (!name.used) return F_none;

    if (!(isascii(name.string[0]) || name.string[0] == '_')) {
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

#ifdef __cplusplus
} // extern "C"
#endif
