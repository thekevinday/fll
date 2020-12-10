#include "init.h"
#include "private-init.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_init_print_help_
  f_return_status init_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, init_name_long, init_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fll_program_print_help_usage(output, context, init_name, f_string_empty_s);

    fl_color_print(output.stream, context.set.important, " Notes:");
    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  This program is intended to be directly called by the kernel during boot.%c", f_string_eol[0]);
    fprintf(output.stream, "%c", f_string_eol[0]);

    // @todo: this should still print the kernel command options.

    return F_none;
  }
#endif // _di_init_print_help_

#ifndef _di_init_main_
  f_return_status init_main(const f_console_arguments_t arguments, init_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, init_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { init_parameter_no_color, init_parameter_light, init_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          }

          init_delete_data(data);
          return F_status_set_error(status);
        }
      }

      status = F_none;
    }

    if (data->parameters[init_parameter_help].result == f_console_result_found) {
      init_print_help(data->output, data->context);

      init_delete_data(data);
      return F_none;
    }

    if (data->parameters[init_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, init_version);

      init_delete_data(data);
      return F_none;
    }

    // @todo

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol[0]);
      }
    }

    init_delete_data(data);
    return status;
  }
#endif // _di_init_main_

#ifndef _di_init_delete_data_
  f_return_status init_delete_data(init_data_t *data) {

    for (f_string_length_t i = 0; i < init_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.root);
    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.root_group);
    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.root_sub);
    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.run);
    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.settings);
    f_macro_string_dynamic_t_delete_simple(data->setting_kernel.settings_name);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_init_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
