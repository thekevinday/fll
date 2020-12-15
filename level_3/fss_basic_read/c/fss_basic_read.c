#include "fss_basic_read.h"
#include "private-fss_basic_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_print_help_
  f_return_status fss_basic_read_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_basic_read_name_long, fss_basic_read_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol[0]);

    fll_program_print_help_option(output, context, fss_basic_read_short_at, fss_basic_read_long_at, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Select object at this numeric index.");
    fll_program_print_help_option(output, context, fss_basic_read_short_content, fss_basic_read_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, " Print the content (default).");
    fll_program_print_help_option(output, context, fss_basic_read_short_delimit, fss_basic_read_long_delimit, f_console_symbol_short_enable, f_console_symbol_long_enable, " Designate how to handle applying delimits.");
    fll_program_print_help_option(output, context, fss_basic_read_short_depth, fss_basic_read_long_depth, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Select object at this numeric depth.");
    fll_program_print_help_option(output, context, fss_basic_read_short_empty, fss_basic_read_long_empty, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Include empty content when processing.");
    fll_program_print_help_option(output, context, fss_basic_read_short_line, fss_basic_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print only the content at the given line.");
    fll_program_print_help_option(output, context, fss_basic_read_short_name, fss_basic_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Select object with this name.");
    fll_program_print_help_option(output, context, fss_basic_read_short_object, fss_basic_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the object.");
    fll_program_print_help_option(output, context, fss_basic_read_short_pipe, fss_basic_read_long_pipe, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print using the special pipe format.");
    fll_program_print_help_option(output, context, fss_basic_read_short_select, fss_basic_read_long_select, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Select sub-content at this index.");
    fll_program_print_help_option(output, context, fss_basic_read_short_total, fss_basic_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print the total number of lines.");
    fll_program_print_help_option(output, context, fss_basic_read_short_trim, fss_basic_read_long_trim, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Trim object names on select or print.");

    fll_program_print_help_usage(output, context, fss_basic_read_name, "filename(s)");

    fl_color_print(output.stream, context.set.important, " Notes:");

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  This program will print the content associated with the given object and content data based on the FSS-0000 Basic standard.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  When using the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
    fprintf(output.stream, " option, an order of operations is enforced on the parameters.%c", f_string_eol[0]);

    fprintf(output.stream, "  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", f_string_eol[0]);

    fprintf(output.stream, "    ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_at);
    fprintf(output.stream, ": An object index at the specified depth.%c", f_string_eol[0]);

    fprintf(output.stream, "    ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
    fprintf(output.stream, ": A new depth within the specified depth, indexed from the root.%c", f_string_eol[0]);

    fprintf(output.stream, "    ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_name);
    fprintf(output.stream, ": An object name at the specified depth.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  The parameter ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
    fprintf(output.stream, " must be in numeric order, but values in between may be skipped.%c", f_string_eol[0]);
    fprintf(output.stream, "    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", f_string_eol[0]);
    fprintf(output.stream, "    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  The parameter ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
    fprintf(output.stream, " selects a content index at a given depth.%c", f_string_eol[0]);
    fprintf(output.stream, "    (This parameter is not synonymous with the depth parameter and does not relate to nested content).%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  Specify both ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_object);
    fprintf(output.stream, " and the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_total);
    fprintf(output.stream, " parameters to get the total objects.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  When both ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_at);
    fprintf(output.stream, " and ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_name);
    fprintf(output.stream, " parameters are specified (at the same depth), the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_at);
    fprintf(output.stream, " parameter value will be treated as a position relative to the specified ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_name);
    fprintf(output.stream, " parameter value.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  This program may support parameters, such as ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
    fprintf(output.stream, " or ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
    fprintf(output.stream, ", even if not supported by the standard.%c", f_string_eol[0]);
    fprintf(output.stream, "  This is done to help ensure consistency for scripting.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  For parameters like ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
    fprintf(output.stream, ", if the standard doesn't support nested content, then only a depth of 0 would be valid.%c", f_string_eol[0]);

    fprintf(output.stream, "  For parameters like ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
    fprintf(output.stream, ", if the standard doesn't support multiple content groups, then only a select of 0 would be valid.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  The parameter ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_trim);
    fprintf(output.stream, " will remove leading and trailing whitespaces when selecting objects or when printing objects.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  When specifying both the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_object);
    fprintf(output.stream, " parameter and the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_content);
    fprintf(output.stream, " parameter, the entire object and content are printed, including the formatting.%c", f_string_eol[0]);
    fprintf(output.stream, "  Both the object and content printed are already escaped.%c", f_string_eol[0]);
    fprintf(output.stream, "  Both the object and content are separated by a space.%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    fprintf(output.stream, "  The parameter ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_delimit);
    fprintf(output.stream, " accepts the following:%c", f_string_eol[0]);
    fprintf(output.stream, "  - ");
    fl_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_none);
    fprintf(output.stream, ": Do not apply delimits.%c", f_string_eol[0]);
    fprintf(output.stream, "  - ");
    fl_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_all);
    fprintf(output.stream, ": (default) apply all delimits.%c", f_string_eol[0]);
    fprintf(output.stream, "  - a number, 0 or greater: apply delimits for the specified depth.%c", f_string_eol[0]);
    fprintf(output.stream, "  - a number, 0 or greater, followed by a ");
    fl_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_greater);
    fprintf(output.stream, ": (such as '1+') apply delimits for the specified depth and any greater depth (numerically).%c", f_string_eol[0]);
    fprintf(output.stream, "  - a number, 0 or greater, followed by a ");
    fl_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_lesser);
    fprintf(output.stream, ": (such as '1-') apply delimits for the specified depth and any lesser depth (numerically).%c", f_string_eol[0]);

    fprintf(output.stream, "%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_fss_basic_read_print_help_

#ifndef _di_fss_basic_read_main_
  f_return_status fss_basic_read_main(const f_console_arguments_t arguments, fss_basic_read_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, fss_basic_read_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_basic_read_parameter_no_color, fss_basic_read_parameter_light, fss_basic_read_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          fss_basic_read_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_basic_read_parameter_verbosity_quiet, fss_basic_read_parameter_verbosity_normal, fss_basic_read_parameter_verbosity_verbose, fss_basic_read_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_basic_read_delete_data(data);
          return status;
        }

        if (choice == fss_basic_read_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_basic_read_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_basic_read_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_basic_read_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_read_parameter_help].result == f_console_result_found) {
      fss_basic_read_print_help(data->output, data->context);

      fss_basic_read_delete_data(data);
      return status;
    }

    if (data->parameters[fss_basic_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, fss_basic_read_version);

      fss_basic_read_delete_data(data);
      return status;
    }

    if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[fss_basic_read_parameter_at].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_at);
        fl_color_print(data->error.to.stream, data->context.set.error, "' requires a positive number.%c", f_string_eol[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_depth].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_depth);
        fl_color_print(data->error.to.stream, data->context.set.error, "' requires a positive number.%c", f_string_eol[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_line].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_line);
        fl_color_print(data->error.to.stream, data->context.set.error, "' requires a positive number.%c", f_string_eol[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_name].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_name);
        fl_color_print(data->error.to.stream, data->context.set.error, "' requires a string.%c", f_string_eol[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_select].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
        fl_color_print(data->error.to.stream, data->context.set.error, "' requires a positive number.%c", f_string_eol[0]);

        status = F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_basic_read_parameter_object].result == f_console_result_found) {
        if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sCannot specify the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_line);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.");

          status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_select].result == f_console_result_additional) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sCannot specify the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);

          status = F_status_set_error(F_parameter);
        }

        if (data->parameters[fss_basic_read_parameter_content].result == f_console_result_found) {
          if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
            fl_color_print(data->error.to.stream, data->context.set.error, "%sCannot specify both the '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_object);
            fl_color_print(data->error.to.stream, data->context.set.error, "' and the '");
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_content);
            fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_total);
            fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);

            status = F_status_set_error(F_parameter);
          }
        }
      }

      if (data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
        if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sCannot specify the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_line);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_total);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);

          status = F_status_set_error(F_parameter);
        }
      }

      if (data->parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
        if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sCannot specify the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_pipe);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_total);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        if (data->parameters[fss_basic_read_parameter_delimit].result == f_console_result_found) {
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_delimit);
          fl_color_print(data->error.to.stream, data->context.set.error, "' requires a value.%c", f_string_eol[0]);

          status = F_status_set_error(F_parameter);
        }
        else if (data->parameters[fss_basic_read_parameter_delimit].result == f_console_result_additional) {
          const f_string_length_t location = data->parameters[fss_basic_read_parameter_delimit].values.array[0];
          f_string_length_t length = strnlen(arguments.argv[location], f_console_length_size);

          if (length == 0) {
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_delimit);
            fl_color_print(data->error.to.stream, data->context.set.error, "' must not be empty.%c", f_string_eol[0]);

            status = F_status_set_error(F_parameter);
          }
          else if (fl_string_compare(arguments.argv[location], fss_basic_read_delimit_mode_name_none, length, fss_basic_read_delimit_mode_name_none_length) == F_equal_to) {
            data->delimit_mode = fss_basic_read_delimit_mode_none;
          }
          else if (fl_string_compare(arguments.argv[location], fss_basic_read_delimit_mode_name_all, length, fss_basic_read_delimit_mode_name_all_length) == F_equal_to) {
            data->delimit_mode = fss_basic_read_delimit_mode_all;
          }
          else {
            data->delimit_mode = fss_basic_read_delimit_mode_depth;

            if (arguments.argv[location][length - 1] == fss_basic_read_delimit_mode_name_greater[0]) {
              data->delimit_mode = fss_basic_read_delimit_mode_depth_greater;

              // shorten the length to better convert the remainder to a number.
              length--;
            }
            else if (arguments.argv[location][length - 1] == fss_basic_read_delimit_mode_name_lesser[0]) {
              data->delimit_mode = fss_basic_read_delimit_mode_depth_lesser;

              // shorten the length to better convert the remainder to a number.
              length--;
            }

            f_string_range_t range = f_macro_string_range_t_initialize(length);

            // ignore leading plus sign.
            if (arguments.argv[location][0] == '+') {
              range.start++;
            }

            status = fl_conversion_string_to_number_unsigned(arguments.argv[location], &data->delimit_depth, range);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(data->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_delimit, arguments.argv[location]);
            }
          }
        }
      }

      fss_basic_read_depths_t depths = fss_basic_read_depths_t_initialize;

      f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

      f_string_length_t original_size = data->quantity.total;

      if (F_status_is_error_not(status)) {
        status = fss_basic_read_main_preprocess_depth(arguments, *data, &depths);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fss_basic_read_main_preprocess_depth", F_true);
        }
      }

      // This standard does not support nesting, so any depth greater than 0 can be predicted without processing the file.
      if (F_status_is_error_not(status) && depths.array[0].depth > 0) {
        fss_basic_read_macro_depths_t_delete_simple(depths);
        f_macro_fss_delimits_t_delete_simple(delimits);

        if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fprintf(data->output.stream, "0%c", f_string_eol[0]);
        }

        fss_basic_read_delete_data(data);
        return F_none;
      }

      if (F_status_is_error_not(status) && data->parameters[fss_basic_read_parameter_select].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_read_long_select);
        fl_color_print(data->error.to.stream, data->context.set.error, "' parameter requires a positive number.%c", f_string_eol[0]);

        fss_basic_read_macro_depths_t_delete_simple(depths);
        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;

        status = f_file_read(file, &data->buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "f_file_read", F_true, "-", "read", fll_error_file_type_pipe);
        }
        else {
          status = fss_basic_read_main_process_file(arguments, data, "-", depths, &delimits);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "fss_basic_read_main_process_file", F_true, "-", "read", fll_error_file_type_pipe);
          }
        }

        // Clear buffers before continuing.
        f_macro_fss_contents_t_delete_simple(data->contents);
        f_macro_fss_objects_t_delete_simple(data->objects);
        fl_string_dynamic_delete(&data->buffer);
      }

      if (F_status_is_error_not(status) && data->remaining.used > 0) {
        for (f_array_length_t i = 0; i < data->remaining.used; i++) {
          f_file_t file = f_file_t_initialize;

          status = f_file_open(arguments.argv[data->remaining.array[i]], 0, &file);

          data->quantity.total = original_size;

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_open", F_true, arguments.argv[data->remaining.array[i]], "open", fll_error_file_type_file);
            break;
          }

          if (!data->quantity.total) {
            status = f_file_size_by_id(file.id, &data->quantity.total);

            if (F_status_is_error(status)) {
              fll_error_file_print(data->error, F_status_set_fine(status), "f_file_size_by_id", F_true, arguments.argv[data->remaining.array[i]], "read", fll_error_file_type_file);

              f_file_stream_close(F_true, &file);
              break;
            }

            // Skip past empty files.
            if (!data->quantity.total) {
              if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
                fprintf(data->output.stream, "0%c", f_string_eol[0]);
              }

              f_file_stream_close(F_true, &file);
              continue;
            }
          }

          status = f_file_read_until(file, data->quantity.total, &data->buffer);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_read_until", F_true, arguments.argv[data->remaining.array[i]], "read", fll_error_file_type_file);
            break;
          }

          status = fss_basic_read_main_process_file(arguments, data, arguments.argv[data->remaining.array[i]], depths, &delimits);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "fss_basic_read_main_process_file", F_true, arguments.argv[data->remaining.array[i]], "read", fll_error_file_type_file);
            break;
          }

          // Clear buffers before repeating the loop.
          f_macro_fss_contents_t_delete_simple(data->contents);
          f_macro_fss_objects_t_delete_simple(data->objects);
          fl_string_dynamic_delete(&data->buffer);
        } // for

        if (F_status_is_error(status)) {
          f_macro_fss_contents_t_delete_simple(data->contents);
          f_macro_fss_objects_t_delete_simple(data->objects);
          fl_string_dynamic_delete(&data->buffer);
        }
      }

      fss_basic_read_macro_depths_t_delete_simple(depths);
      f_macro_fss_delimits_t_delete_simple(delimits);
    }
    else {
      fl_color_print(data->error.to.stream, data->context.set.error, "%sYou failed to specify one or more files.%c", fll_error_print_error, f_string_eol[0]);
      status = F_status_set_error(F_parameter);
    }

    fss_basic_read_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_read_main_

#ifndef _di_fss_basic_read_delete_data_
  f_return_status fss_basic_read_delete_data(fss_basic_read_data_t *data) {

    for (f_string_length_t i = 0; i < fss_basic_read_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_fss_contents_t_delete_simple(data->contents);
    f_macro_fss_objects_t_delete_simple(data->objects);
    fl_string_dynamic_delete(&data->buffer);
    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_basic_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
