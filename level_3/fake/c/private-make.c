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

#ifndef _di_fake_make_load_setting_
  void fake_make_load_setting(const fake_data data, fake_make_data *data_make, f_status *status) {
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

            *status = fll_fss_extended_read(&data_make->buffer, &content_range, &settings.objects, &settings.contents);
            if (F_status_is_error(*status)) {
              fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_extended_read", data.file_data_build_fakefile.string, content_range, F_true);

              f_macro_fss_set_delete_simple(settings);
              f_macro_fss_objects_delete_simple(list_objects);
              f_macro_fss_contents_delete_simple(list_contents);
              return;
            }

            missing_settings = F_false;
          }
          else if (fl_string_dynamic_partial_compare(name_main, data_make->buffer, name_main_range, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_print_warning_fakefile_object_multiple(data.context, data.verbosity, data.file_data_build_fakefile.string, "list", name_main.string);
              continue;
            }

            missing_main = F_false;
            data_make->main = i;
          }
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

      // look for load_build to determine if settings from the build settings file should be loaded.
      const f_string_range range_load_build = f_macro_string_range_initialize(fake_make_setting_load_build_length);

      data_make->setting_make.load_build = F_true;

      if (settings.objects.used) {
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

        *status = fll_fss_snatch_map_mash_apart(data_make->buffer, settings.objects, settings.contents, settings_name, settings_length, 2, " ", 1, settings_value);
        if (F_status_is_error(*status)) {
          fake_print_error(data.context, data.verbosity, F_status_set_fine(*status), "fll_fss_snatch_map_mash_apart", F_true);

          //@todo fake_print_error_fss(data.context, data.verbosity, *status, "fll_fss_snatch_map", data.file_data_build_fakefile.string, content_range, F_true);

          f_macro_fss_set_delete_simple(settings);
          return;
        }
      }

      // @todo load any defaults for unassigned values.

      f_macro_fss_set_delete_simple(settings);
    }
  }
#endif // _di_fake_make_load_setting_

#ifndef _di_fake_make_operate_
  f_return_status fake_make_operate(const fake_data data) {
    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print_line(f_type_output, data.color_section_set, data.color_section_reset, "Making project.");
    }

    f_status status = F_none;
    f_mode mode = f_mode_initialize;

    fake_make_data data_make = fake_make_data_initialize;

    f_macro_mode_set_default_umask(mode, data.umask);

    fake_make_load_setting(data, &data_make, &status);

    // @todo

    fake_macro_make_data_delete_simple(data_make);

    return status;
  }
#endif // _di_fake_make_operate_

#ifdef __cplusplus
} // extern "C"
#endif
