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

    // @todo: add all arguments and possibly fss settings.
    f_string_dynamics arguments = f_string_dynamics_initialize;
    f_string_dynamic argument[1] = f_string_dynamic_initialize;
    int results = 0;

    argument[0].string = (f_string) fake_other_operation_build;
    argument[0].size = fake_other_operation_build_length;
    argument[0].used = fake_other_operation_build_length;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    status = fll_execute_path(path.string, arguments, &results);

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_failure) {
        fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to execute script: ");
        fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", path.string);
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, ".");
      }
      else {
        fake_print_error(data.context, status, "fll_execute_program", f_true);
      }
    }

    f_macro_string_dynamic_delete_simple(path);

    return status;
  }
#endif // _di_fake_execute_process_pre_

#ifdef __cplusplus
} // extern "C"
#endif
