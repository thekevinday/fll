#include "fss_basic_read.h"
#include "private-common.h"
#include "private-fss_basic_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_print_help_
  f_status_t fss_basic_read_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_basic_read_name_long, fss_basic_read_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, fss_basic_read_short_at, fss_basic_read_long_at, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Select object at this numeric index.");
    fll_program_print_help_option(output, context, fss_basic_read_short_content, fss_basic_read_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the content (default).");
    fll_program_print_help_option(output, context, fss_basic_read_short_delimit, fss_basic_read_long_delimit, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(output, context, fss_basic_read_short_depth, fss_basic_read_long_depth, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select object at this numeric depth.");
    fll_program_print_help_option(output, context, fss_basic_read_short_empty, fss_basic_read_long_empty, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Include empty content when processing.");
    fll_program_print_help_option(output, context, fss_basic_read_short_line, fss_basic_read_long_line, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print only the content at the given line.");
    fll_program_print_help_option(output, context, fss_basic_read_short_name, fss_basic_read_long_name, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Select object with this name.");
    fll_program_print_help_option(output, context, fss_basic_read_short_object, fss_basic_read_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the object.");
    fll_program_print_help_option(output, context, fss_basic_read_short_pipe, fss_basic_read_long_pipe, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print using the special pipe format.");
    fll_program_print_help_option(output, context, fss_basic_read_short_select, fss_basic_read_long_select, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Select sub-content at this index.");
    fll_program_print_help_option(output, context, fss_basic_read_short_total, fss_basic_read_long_total, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print the total number of lines.");
    fll_program_print_help_option(output, context, fss_basic_read_short_trim, fss_basic_read_long_trim, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Trim object names on select or print.");

    fll_program_print_help_usage(output, context, fss_basic_read_name, "filename(s)");

    f_color_print(output.stream, context.set.important, " Notes:");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program will print the content associated with the given object and content main based on the FSS-0000 Basic standard.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When using the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
    fprintf(output.stream, " option, an order of operations is enforced on the parameters.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_at);
    fprintf(output.stream, ": An object index at the specified depth.%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
    fprintf(output.stream, ": A new depth within the specified depth, indexed from the root.%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
    fprintf(output.stream, ": An object name at the specified depth.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
    fprintf(output.stream, " must be in numeric order, but values in between may be skipped.%c", f_string_eol_s[0]);
    fprintf(output.stream, "    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", f_string_eol_s[0]);
    fprintf(output.stream, "    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_select);
    fprintf(output.stream, " selects a content index at a given depth.%c", f_string_eol_s[0]);
    fprintf(output.stream, "    (This parameter is not synonymous with the depth parameter and does not relate to nested content).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  Specify both ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_object);
    fprintf(output.stream, " and the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_total);
    fprintf(output.stream, " parameters to get the total objects.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When both ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_at);
    fprintf(output.stream, " and ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
    fprintf(output.stream, " parameters are specified (at the same depth), the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_at);
    fprintf(output.stream, " parameter value will be treated as a position relative to the specified ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
    fprintf(output.stream, " parameter value.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program may support parameters, such as ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
    fprintf(output.stream, " or ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_select);
    fprintf(output.stream, ", even if not supported by the standard.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  This is done to help ensure consistency for scripting.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  For parameters like ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
    fprintf(output.stream, ", if the standard doesn't support nested content, then only a depth of 0 would be valid.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  For parameters like ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_select);
    fprintf(output.stream, ", if the standard doesn't support multiple content groups, then only a select of 0 would be valid.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_trim);
    fprintf(output.stream, " will remove leading and trailing whitespaces when selecting objects or when printing objects.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When specifying both the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_object);
    fprintf(output.stream, " parameter and the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_content);
    fprintf(output.stream, " parameter, the entire object and content are printed, including the formatting.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Both the object and content printed are already escaped.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Both the object and content are separated by a space.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_delimit);
    fprintf(output.stream, " accepts the following:%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - ");
    f_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_none);
    fprintf(output.stream, ": Do not apply delimits.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - ");
    f_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_all);
    fprintf(output.stream, ": (default) apply all delimits.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - a number, 0 or greater: apply delimits for the specified depth.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - a number, 0 or greater, followed by a ");
    f_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_greater);
    fprintf(output.stream, ": (such as '1+') apply delimits for the specified depth and any greater depth (numerically).%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - a number, 0 or greater, followed by a ");
    f_color_print(output.stream, context.set.notable, "%s", fss_basic_read_delimit_mode_name_lesser);
    fprintf(output.stream, ": (such as '1-') apply delimits for the specified depth and any lesser depth (numerically).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fss_basic_read_print_help_

#ifndef _di_fss_basic_read_main_
  f_status_t fss_basic_read_main(const f_console_arguments_t arguments, fss_basic_read_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_basic_read_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_basic_read_parameter_no_color, fss_basic_read_parameter_light, fss_basic_read_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          fss_basic_read_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_basic_read_parameter_verbosity_quiet, fss_basic_read_parameter_verbosity_normal, fss_basic_read_parameter_verbosity_verbose, fss_basic_read_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_basic_read_main_delete(main);
          return status;
        }

        if (choice == fss_basic_read_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_basic_read_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_basic_read_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_basic_read_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_basic_read_parameter_help].result == f_console_result_found) {
      fss_basic_read_print_help(main->output, main->context);

      fss_basic_read_main_delete(main);
      return status;
    }

    if (main->parameters[fss_basic_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, fss_basic_read_version);

      fss_basic_read_main_delete(main);
      return status;
    }

    if (main->remaining.used > 0 || main->process_pipe) {
      if (main->parameters[fss_basic_read_parameter_at].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_at);
        f_color_print(main->error.to.stream, main->context.set.error, "' requires a positive number.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_depth].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
        f_color_print(main->error.to.stream, main->context.set.error, "' requires a positive number.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_line].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_line);
        f_color_print(main->error.to.stream, main->context.set.error, "' requires a positive number.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_name].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
        f_color_print(main->error.to.stream, main->context.set.error, "' requires a string.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_select].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_select);
        f_color_print(main->error.to.stream, main->context.set.error, "' requires a positive number.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
        if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sCannot specify the '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_pipe);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter with the '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_total);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters[fss_basic_read_parameter_delimit].result == f_console_result_found) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_delimit);
          f_color_print(main->error.to.stream, main->context.set.error, "' requires a value.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters[fss_basic_read_parameter_delimit].result == f_console_result_additional) {
          const f_array_length_t location = main->parameters[fss_basic_read_parameter_delimit].values.array[0];
          f_array_length_t length = strnlen(arguments.argv[location], f_console_parameter_size);

          if (length == 0) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
            f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_delimit);
            f_color_print(main->error.to.stream, main->context.set.error, "' must not be empty.%c", f_string_eol_s[0]);

            status = F_status_set_error(F_parameter);
          }
          else if (fl_string_compare(arguments.argv[location], fss_basic_read_delimit_mode_name_none, length, fss_basic_read_delimit_mode_name_none_length) == F_equal_to) {
            main->delimit_mode = fss_basic_read_delimit_mode_none;
          }
          else if (fl_string_compare(arguments.argv[location], fss_basic_read_delimit_mode_name_all, length, fss_basic_read_delimit_mode_name_all_length) == F_equal_to) {
            main->delimit_mode = fss_basic_read_delimit_mode_all;
          }
          else {
            main->delimit_mode = fss_basic_read_delimit_mode_depth;

            if (arguments.argv[location][length - 1] == fss_basic_read_delimit_mode_name_greater[0]) {
              main->delimit_mode = fss_basic_read_delimit_mode_depth_greater;

              // shorten the length to better convert the remainder to a number.
              length--;
            }
            else if (arguments.argv[location][length - 1] == fss_basic_read_delimit_mode_name_lesser[0]) {
              main->delimit_mode = fss_basic_read_delimit_mode_depth_lesser;

              // shorten the length to better convert the remainder to a number.
              length--;
            }

            f_string_range_t range = macro_f_string_range_t_initialize(length);

            // ignore leading plus sign.
            if (arguments.argv[location][0] == '+') {
              range.start++;
            }

            status = fl_conversion_string_to_number_unsigned(arguments.argv[location], range, &main->delimit_depth);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_delimit, arguments.argv[location]);
            }
          }
        }
      }

      f_file_t file = f_file_t_initialize;
      fss_basic_read_depths_t depths = fss_basic_read_depths_t_initialize;
      f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

      if (F_status_is_error_not(status)) {
        status = fss_basic_read_depth_process(arguments, *main, &depths);
      }

      // This standard does not support nesting, so any depth greater than 0 can be predicted without processing the file.
      if (F_status_is_error_not(status) && depths.array[0].depth > 0) {
        if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fprintf(main->output.stream, "0%c", f_string_eol_s[0]);
        }

        fss_basic_read_depths_resize(0, &depths);
        macro_f_fss_delimits_t_delete_simple(delimits);
        fss_basic_read_main_delete(main);

        return F_none;
      }

      if (F_status_is_error_not(status) && main->parameters[fss_basic_read_parameter_select].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_select);
        f_color_print(main->error.to.stream, main->context.set.error, "' parameter requires a positive number.%c", f_string_eol_s[0]);

        fss_basic_read_depths_resize(0, &depths);

        status = F_status_set_error(F_parameter);
      }

      // Provide a range designating where within the buffer a particular file exists, using a statically allocated array. @fixme make this a structure with
      fss_basic_read_file_t files_array[main->remaining.used + 1];
      fss_basic_read_files_t files = fss_basic_read_files_t_initialize;

      if (F_status_is_error_not(status)) {
        files.array = files_array;
        files.size += main->remaining.used;

        for (f_array_length_t i = 0; i < files.used; ++i) {
          macro_f_string_range_t_clear(files.array[i].range);
        } // for
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        file.id = f_type_descriptor_input;
        file.stream = f_type_input;

        files.array[0].name = 0;
        files.array[0].range.start = 0;

        status = f_file_stream_read(file, 1, &main->buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, "-", "read", fll_error_file_type_pipe);
        }
        else if (main->buffer.used) {
          files.array[0].range.stop = main->buffer.used - 1;

          // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
          // Guarantee that a newline exists at the end of the buffer.
          status = f_string_append_assure(f_string_eol_s, 1, &main->buffer);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true, "-", "read", fll_error_file_type_pipe);
          }
        }
        else {
          files.array[0].range.start = 1;
        }
      }

      if (F_status_is_error_not(status) && main->remaining.used > 0) {
        for (f_array_length_t i = 0; i < main->remaining.used; i++) {

          files.array[files.used].range.start = main->buffer.used;
          file.stream = 0;
          file.id = -1;

          status = f_file_stream_open(arguments.argv[main->remaining.array[i]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[main->remaining.array[i]], "open", fll_error_file_type_file);

            f_file_stream_close(F_true, &file);
            break;
          }

          status = f_file_stream_read(file, 1, &main->buffer);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, arguments.argv[main->remaining.array[i]], "read", fll_error_file_type_file);

            break;
          }
          else if (main->buffer.used > files.array[files.used].range.start) {
            files.array[files.used].name = arguments.argv[main->remaining.array[i]];
            files.array[files.used++].range.stop = main->buffer.used - 1;

            // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
            // Guarantee that a newline exists at the end of the buffer.
            status = f_string_append_assure(f_string_eol_s, 1, &main->buffer);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true, "-", "read", fll_error_file_type_pipe);
            }
          }
          else {
            files.array[files.used].range.start = 1;
          }
        } // for
      }

      if (F_status_is_error_not(status)) {
        status = fss_basic_read_process(arguments, files, depths, main, &delimits);
      }

      macro_f_fss_contents_t_delete_simple(main->contents);
      macro_f_fss_objects_t_delete_simple(main->objects);
      macro_f_string_dynamic_t_delete_simple(main->buffer);

      fss_basic_read_depths_resize(0, &depths);
      macro_f_fss_delimits_t_delete_simple(delimits);
    }
    else {
      f_color_print(main->error.to.stream, main->context.set.error, "%sYou failed to specify one or more files.%c", fll_error_print_error, f_string_eol_s[0]);
      status = F_status_set_error(F_parameter);
    }

    fss_basic_read_main_delete(main);
    return status;
  }
#endif // _di_fss_basic_read_main_

#ifndef _di_fss_basic_read_main_delete_
  f_status_t fss_basic_read_main_delete(fss_basic_read_main_t *main) {

    for (f_array_length_t i = 0; i < fss_basic_read_total_parameters; i++) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_fss_contents_t_delete_simple(main->contents);
    macro_f_fss_objects_t_delete_simple(main->objects);
    macro_f_string_dynamic_t_delete_simple(main->buffer);
    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_basic_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
