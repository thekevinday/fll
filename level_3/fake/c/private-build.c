#include <level_3/fake.h>
#include "private-fake.h"
#include "private-build.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_execute_process_script_
  f_return_status fake_build_execute_process_script(const fake_data data, const f_string_dynamic process_script) {
    if (process_script.used == 0) return f_none;

    f_status status = f_none;

    const f_string parameter_prefixs[] = {
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
      f_console_symbol_short_enable,
    };

    const f_string_length parameter_prefixs_length[] = {
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
       f_console_symbol_short_enable_length,
    };

    const f_string parameter_names[] = {
      fake_short_defines,
      fake_short_process,
      fake_short_settings,
      fake_short_path_build,
      fake_short_path_work,
      fake_short_path_source_build,
      fake_short_path_source_common,
      fake_short_path_source_data,
      fake_short_path_source_documents,
      fake_short_path_source_codes,
      fake_short_path_source_licenses,
      fake_short_path_source_settings,
    };

    const f_string_length parameter_names_length[] = {
       fake_short_defines_length,
       fake_short_process_length,
       fake_short_settings_length,
       fake_short_path_build_length,
       fake_short_path_work_length,
       fake_short_path_source_build_length,
       fake_short_path_source_common_length,
       fake_short_path_source_data_length,
       fake_short_path_source_documents_length,
       fake_short_path_source_codes_length,
       fake_short_path_source_licenses_length,
       fake_short_path_source_settings_length,
    };

    const f_string parameter_values[] = {
      data.defines.string,
      data.process.string,
      data.settings.string,
      data.path_build.string,
      data.path_work.string,
      data.path_source_build.string,
      data.path_source_common.string,
      data.path_source_data.string,
      data.path_source_documents.string,
      data.path_source_codes.string,
      data.path_source_licenses.string,
      data.path_source_settings.string,
    };

    const f_string_length parameter_values_length[] = {
      data.defines.used,
      data.process.used,
      data.settings.used,
      data.path_build.used,
      data.path_work.used,
      data.path_source_build.used,
      data.path_source_common.used,
      data.path_source_data.used,
      data.path_source_documents.used,
      data.path_source_codes.used,
      data.path_source_licenses.used,
      data.path_source_settings.used,
    };

    const uint8_t parameters_total = 12;

    f_string_dynamics arguments = f_string_dynamics_initialize;

    status = fll_execute_arguments_add(fake_other_operation_build, fake_other_operation_build_length, &arguments);

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fll_execute_arguments_add", f_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return status;
    }

    status = fll_execute_arguments_add_parameter_set(parameter_prefixs, parameter_prefixs_length, parameter_names, parameter_names_length, parameter_values, parameter_values_length, parameters_total, &arguments);

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fll_execute_arguments_add_parameter_set", f_true);

      f_macro_string_dynamics_delete_simple(arguments);
      return status;
    }

    f_string_dynamic path = f_string_dynamic_initialize;

    if (process_script.string[0] != '/') {
      status = fl_string_dynamic_append(data.path_source_settings, &path);
    }

    if (!f_status_is_error(status)) {
      status = fl_string_dynamic_append(process_script, &path);
    }

    if (f_status_is_error(status)) {
      fake_print_error(data.context, f_status_set_fine(status), "fl_string_dynamic_append", f_true);

      f_macro_string_dynamic_delete_simple(path);
      return status;
    }

    int results = 0;

    status = fll_execute_path(path.string, arguments, &results);

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_failure) {
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to execute script: ");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, ".");
      }
      else {
        fake_print_error(data.context, f_status_set_fine(status), "fll_execute_path", f_true);
      }
    }

    f_macro_string_dynamic_delete_simple(path);
    f_macro_string_dynamics_delete_simple(arguments);

    return status;
  }
#endif // _di_fake_execute_process_pre_

#ifdef __cplusplus
} // extern "C"
#endif
