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

            f_fss_quotedss quoted_contents = f_fss_quotedss_initialize;

            content_range = list_contents.array[i].array[0];

            *status = fll_fss_extended_read(&data_make->buffer, &content_range, &settings.objects, &settings.contents, 0, &quoted_contents);
            if (F_status_is_error(*status)) {
              fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

              f_macro_fss_quotedss_delete_simple(quoted_contents);
              f_macro_fss_set_delete_simple(settings);
              f_macro_fss_objects_delete_simple(list_objects);
              f_macro_fss_contents_delete_simple(list_contents);
              return;
            }

            if (quoted_contents.used) {
              // @todo
            }

            f_macro_fss_quotedss_delete_simple(quoted_contents);

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

          *status = fll_fss_extended_read(&data_make->buffer, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, 0);
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

      data_make->setting_make.load_build = F_true;

      if (settings.objects.used) {
        // look for load_build to determine if settings from the build settings file should be loaded.
        const f_string_range range_load_build = f_macro_string_range_initialize(fake_make_setting_load_build_length);

        const f_string_range range_yes = f_macro_string_range_initialize(fake_common_setting_bool_yes_length);
        const f_string_range range_no = f_macro_string_range_initialize(fake_common_setting_bool_no_length);

        const f_string_static name_settings_load_build = f_macro_string_static_initialize(fake_make_setting_load_build, fake_make_setting_load_build_length);
        const f_string_static value_settings_load_build_yes = f_macro_string_static_initialize(fake_common_setting_bool_yes, fake_common_setting_bool_yes_length);
        const f_string_static value_settings_load_build_no = f_macro_string_static_initialize(fake_common_setting_bool_no, fake_common_setting_bool_no_length);

        for (f_array_length i = 0; i < settings.objects.used; i++) {
          if (fl_string_dynamic_partial_compare(name_settings_load_build, data_make->buffer, range_load_build, settings.objects.array[i]) == F_equal_to) {
            if (settings.contents.array[i].used) {
              if (fl_string_dynamic_partial_compare(value_settings_load_build_yes, data_make->buffer, range_yes, settings.contents.array[i].array[0]) == F_equal_to) {
                data_make->setting_make.load_build = F_true;
              }
              else if (fl_string_dynamic_partial_compare(value_settings_load_build_no, data_make->buffer, range_no, settings.contents.array[i].array[0]) == F_equal_to) {
                data_make->setting_make.load_build = F_false;
              }
              else {
                fake_print_error_fakefile_settings_content_invalid(data.context, data.verbosity, data.file_data_build_fakefile.string, data_make->buffer, settings.objects.array[i], settings.contents.array[i].array[0], fake_make_section_settings);
              }
            }

            if (settings.contents.array[i].used > 1) {
              fake_print_warning_settings_content_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, fake_make_setting_load_build);
            }

            break;
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

        *status = fll_fss_snatch_map_mash_apart(data_make->buffer, settings.objects, settings.contents, settings_name, settings_length, 2, " ", 1, settings_value, 0);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_fss_snatch_map_mash_apart", F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      f_macro_fss_set_delete_simple(settings);
    }
  }
#endif // _di_fake_make_load_fakefile_

#ifndef _di_fake_make_operate_
  f_return_status fake_make_operate(const fake_data data) {
    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.color_section_set, data.color_section_reset, "Making project.");
    }

    f_status status = F_none;
    f_mode mode = f_mode_initialize;

    f_string_lengths list_stack = f_string_lengths_initialize;
    fake_make_data data_make = fake_make_data_initialize;

    f_macro_mode_set_default_umask(mode, data.umask);

    fake_make_load_fakefile(data, &data_make, &status);

    fake_make_operate_section(data, data_make.main, &data_make, &list_stack, &status);

    f_macro_string_lengths_delete_simple(list_stack);
    fake_macro_make_data_delete_simple(data_make);

    return status;
  }
#endif // _di_fake_make_operate_

#ifndef _di_fake_make_operation_expand_
  void fake_make_operation_expand(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_fss_content content, fake_make_data *data_make, f_string_dynamics *arguments, f_status *status) {
    if (F_status_is_error(*status)) return;
    if (content.used == 0) return;

    if (data.verbosity == fake_verbosity_verbose) {
      fl_color_print(f_type_output, data.context.standout, data.context.reset, "Expanding content values for section operation '");

      fl_color_print_code(f_type_output, data.context.notable);
      f_print_string_dynamic(f_type_output, operation_name);
      fl_color_print_code(f_type_output, data.context.reset);

      fl_color_print_line(f_type_output, data.context.standout, data.context.reset, "'.");
    }

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

    f_string_length previous = 0;

    for (; i < content.used; i++) {
      if (content.array[i].start > content.array[i].stop) {
        continue;
      }

      range = content.array[i];

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

          // @todo: consider designing a way to designate appending map as a single value string or multiple separate strings.
          //        this could potential be done by considering single vs double quotes.
          //        then arguments->used would have to be incremented based on this number.
          if (map_multis->used) {
            for (k = 0; k < map_multis->used; k++) {
              *status = fl_string_dynamic_partial_compare_dynamic(map_multis->array[k].name, data_make->buffer, iki_content.array[j]);

              if (*status == F_equal_to) {
                if (map_multis->array[k].value.used) {
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

      *status = fl_string_dynamic_terminate_after(&arguments->array[arguments->used]);
      if (F_status_is_error(*status)) {
        fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fl_string_terminate_after", F_true);
        break;
      }

      arguments->used++;

      f_macro_iki_variable_delete_simple(iki_variable);
      f_macro_iki_vocabulary_delete_simple(iki_vocabulary);
      f_macro_iki_content_delete_simple(iki_content);
    } // for

    f_macro_iki_variable_delete_simple(iki_variable);
    f_macro_iki_vocabulary_delete_simple(iki_vocabulary);
    f_macro_iki_content_delete_simple(iki_content);
  }
#endif // _di_fake_make_operation_expand_

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

      fl_color_print(f_type_output, data.color_section_set, data.color_section_reset, "Processing Section '");

      fl_color_print_code(f_type_output, data.context.notable);
      f_print_string_dynamic_partial(f_type_output, data_make->buffer, section->name);
      fl_color_print_code(f_type_output, data.context.reset);

      fl_color_print_line(f_type_output, data.color_section_set, data.color_section_reset, "'.");
    }

    const f_string_static operations_name[] = {
      f_macro_string_static_initialize(fake_make_operation_archive, fake_make_operation_archive_length),
      f_macro_string_static_initialize(fake_make_operation_build, fake_make_operation_build_length),
      f_macro_string_static_initialize(fake_make_operation_clean, fake_make_operation_clean_length),
      f_macro_string_static_initialize(fake_make_operation_compile, fake_make_operation_compile_length),
      f_macro_string_static_initialize(fake_make_operation_create, fake_make_operation_create_length),
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

    const f_array_length operations_type[] = {
      fake_make_operation_type_archive ,
      fake_make_operation_type_build,
      fake_make_operation_type_clean,
      fake_make_operation_type_compile,
      fake_make_operation_type_create,
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

    f_array_length operation = 0;
    f_array_length operations[section->objects.used];

    const f_string_static *operation_name = 0;

    f_string_dynamics arguments[section->objects.used];

    f_array_length i = 0;
    f_array_length j = 0;

    memset(operations, 0, sizeof(f_array_length) * section->objects.used);
    memset(arguments, 0, sizeof(f_string_dynamics) * section->objects.used);

    bool has_error = F_false;

    // pre-process the list to identify invalid commands so that nothing is processed if any operation is invalid.
    for (; i < section->objects.used; i++) {
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
        has_error = F_true;
        *status = F_none;
        continue;
      }

      operations[i] = operation;

      fake_make_operation_expand(data, section->name, operation, *operation_name, section->contents.array[i], data_make, &arguments[i], status);
      if (F_status_is_error(*status)) {
        has_error = F_true;
        *status = F_none;
        continue;
      }

      //fake_make_operation_validate();
    } // for

    if (F_status_is_fine(*status) && has_error) {
      *status = F_none;
    }

    if (F_status_is_error(*status)) {
      for (i = 0; i < section->objects.used; i++) {
        f_macro_string_dynamics_delete_simple(arguments[i]);
      } // for

      return;
    }

    for (; i < section->objects.used; i++) {
      // 3: expand the operation content into dynamic strings.
      // 4: process any variables and then re-validate any operations with replacements.
      // 5: perform the operation.
    } // for

    for (i = 0; i < section->objects.used; i++) {
      f_macro_string_dynamics_delete_simple(arguments[i]);
    } // for
  }
#endif // _di_fake_make_operate_section_

#ifdef __cplusplus
} // extern "C"
#endif
