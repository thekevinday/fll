#include "fss_extended_read.h"
#include "private-common.h"
#include "private-fss_extended_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_read_print_help_
  f_status_t fss_extended_read_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_extended_read_name_long, fss_extended_read_version);

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

    fll_program_print_help_option(output, context, fss_extended_read_short_at, fss_extended_read_long_at, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Select Object at this numeric index.");
    fll_program_print_help_option(output, context, fss_extended_read_short_content, fss_extended_read_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Content (default).");
    fll_program_print_help_option(output, context, fss_extended_read_short_delimit, fss_extended_read_long_delimit, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(output, context, fss_extended_read_short_depth, fss_extended_read_long_depth, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select Object at this numeric depth.");
    fll_program_print_help_option(output, context, fss_extended_read_short_empty, fss_extended_read_long_empty, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Include empty Content when processing.");
    fll_program_print_help_option(output, context, fss_extended_read_short_line, fss_extended_read_long_line, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print only the Content at the given line.");
    fll_program_print_help_option(output, context, fss_extended_read_short_name, fss_extended_read_long_name, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Select Object with this name.");
    fll_program_print_help_option(output, context, fss_extended_read_short_object, fss_extended_read_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the Object.");
    fll_program_print_help_option(output, context, fss_extended_read_short_pipe, fss_extended_read_long_pipe, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print using the special pipe format.");
    fll_program_print_help_option(output, context, fss_extended_read_short_select, fss_extended_read_long_select, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Select sub-Content at this index.");
    fll_program_print_help_option(output, context, fss_extended_read_short_total, fss_extended_read_long_total, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print the total number of lines.");
    fll_program_print_help_option(output, context, fss_extended_read_short_trim, fss_extended_read_long_trim, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Trim Object names on select or print.");

    fll_program_print_help_usage(output, context, fss_extended_read_name, "filename(s)");

    f_color_print(output.stream, context.set.important, " Notes:");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program will print the Content associated with the given Object and Content main based on the FSS-0001 Extended standard.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  All numeric positions (indexes) start at 0 instead of 1.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  For example, a file of 17 lines would range from 0 to 16.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When using the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_depth);
    fprintf(output.stream, " option, an order of operations is enforced on the parameters.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_at);
    fprintf(output.stream, ": An Object index at the specified depth.%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_depth);
    fprintf(output.stream, ": A new depth within the specified depth, indexed from the root.%c", f_string_eol_s[0]);

    fprintf(output.stream, "    ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_name);
    fprintf(output.stream, ": An Object name at the specified depth.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_depth);
    fprintf(output.stream, " must be in numeric order, but values in between may be skipped.%c", f_string_eol_s[0]);
    fprintf(output.stream, "    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", f_string_eol_s[0]);
    fprintf(output.stream, "    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_select);
    fprintf(output.stream, " selects a Content index at a given depth.%c", f_string_eol_s[0]);
    fprintf(output.stream, "    (This parameter is not synonymous with the depth parameter and does not relate to nested Content).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  Specify both ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_object);
    fprintf(output.stream, " and the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_total);
    fprintf(output.stream, " parameters to get the total objects.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When both ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_at);
    fprintf(output.stream, " and ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_name);
    fprintf(output.stream, " parameters are specified (at the same depth), the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_at);
    fprintf(output.stream, " parameter value will be treated as a position relative to the specified ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_name);
    fprintf(output.stream, " parameter value.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program may support parameters, such as ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_depth);
    fprintf(output.stream, " or ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_select);
    fprintf(output.stream, ", even if not supported by the standard.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  This is done to help ensure consistency for scripting.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  For parameters like ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_depth);
    fprintf(output.stream, ", if the standard doesn't support nested Content, then only a depth of 0 would be valid.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  For parameters like ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_select);
    fprintf(output.stream, ", if the standard doesn't support multiple Content groups, then only a select of 0 would be valid.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_trim);
    fprintf(output.stream, " will remove leading and trailing whitespaces when selecting objects or when printing objects.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When specifying both the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_object);
    fprintf(output.stream, " parameter and the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_content);
    fprintf(output.stream, " parameter, the entire Object and Content are printed, including the formatting.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Both the Object and Content printed are already escaped.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Both the Object and Content are separated by a space.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The parameter ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_delimit);
    fprintf(output.stream, " accepts the following:%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_none);
    fprintf(output.stream, ": Do not apply delimits.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_all);
    fprintf(output.stream, ": (default) Apply all delimits.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_object);
    fprintf(output.stream, ": Apply delimits for Objects.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - A number, 0 or greater: apply delimits for Content at the specified depth.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - A number, 0 or greater, followed by a ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_greater);
    fprintf(output.stream, ": (such as '1+') apply delimits for Content at the specified depth and any greater depth (numerically).%c", f_string_eol_s[0]);
    fprintf(output.stream, "  - A number, 0 or greater, followed by a ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_lesser);
    fprintf(output.stream, ": (such as '1-') apply delimits for Content at the specified depth and any lesser depth (numerically).%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_delimit);
    fprintf(output.stream, " parameter may be specified multiple times to customize the delimit behavior.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_delimit);
    fprintf(output.stream, " values ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_none);
    fprintf(output.stream, " and ");
    f_color_print(output.stream, context.set.notable, "%s", fss_extended_read_delimit_mode_name_all);
    fprintf(output.stream, ", overrule all other delimit values.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fss_extended_read_print_help_

#ifndef _di_fss_extended_read_main_
  f_status_t fss_extended_read_main(f_console_arguments_t * const arguments, fss_extended_read_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_extended_read_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_extended_read_parameter_no_color, fss_extended_read_parameter_light, fss_extended_read_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(*arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          fss_extended_read_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_extended_read_parameter_verbosity_quiet, fss_extended_read_parameter_verbosity_normal, fss_extended_read_parameter_verbosity_verbose, fss_extended_read_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_extended_read_main_delete(main);

          return status;
        }

        if (choice == fss_extended_read_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_extended_read_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_extended_read_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_extended_read_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_extended_read_parameter_help].result == f_console_result_found) {
      fss_extended_read_print_help(main->output, main->context);

      fss_extended_read_main_delete(main);
      return status;
    }

    if (main->parameters[fss_extended_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, fss_extended_read_version);

      fss_extended_read_main_delete(main);
      return status;
    }

    // Provide a range designating where within the buffer a particular file exists, using a statically allocated array.
    fss_extended_read_file_t files_array[main->remaining.used + 1];
    fss_extended_read_data_t data = fss_extended_read_data_t_initialize;

    data.files.array = files_array;
    data.files.used = 1;
    data.files.size = main->remaining.used + 1;

    if (main->remaining.used || main->process_pipe) {
      {
        const f_array_length_t parameter_code[] = {
          fss_extended_read_parameter_at,
          fss_extended_read_parameter_depth,
          fss_extended_read_parameter_line,
          fss_extended_read_parameter_select,
          fss_extended_read_parameter_name,
          fss_extended_read_parameter_delimit,
        };

        const f_string_t parameter_name[] = {
          fss_extended_read_long_at,
          fss_extended_read_long_depth,
          fss_extended_read_long_line,
          fss_extended_read_long_select,
          fss_extended_read_long_name,
          fss_extended_read_long_delimit,
        };

        const f_string_t message_positive_number = "positive number";
        const f_string_t message_string = "string";
        const f_string_t message_value = "value";

        const f_string_t parameter_message[] = {
          message_positive_number,
          message_positive_number,
          message_positive_number,
          message_positive_number,
          message_string,
          message_value,
        };

        for (f_array_length_t i = 0; i < 6; ++i) {

          if (main->parameters[parameter_code[i]].result == f_console_result_found) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
            f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, parameter_name[i]);
            f_color_print(main->error.to.stream, main->context.set.error, "' requires a %s.%c", parameter_message[i], f_string_eol_s[0]);

            status = F_status_set_error(F_parameter);
            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && main->parameters[fss_extended_read_parameter_pipe].result == f_console_result_found) {
        if (main->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sCannot specify the '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_pipe);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter with the '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_total);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters[fss_extended_read_parameter_line].result == f_console_result_found) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sCannot specify the '", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_pipe);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter with the '");
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_line);
          f_color_print(main->error.to.stream, main->context.set.error, "' parameter.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status) && main->parameters[fss_extended_read_parameter_delimit].result == f_console_result_additional) {
        f_array_length_t location = 0;
        f_array_length_t length = 0;

        // Set the value to 0 to allow for detecting mode based on what is provided.
        data.delimit_mode = 0;

        for (f_array_length_t i = 0; i < main->parameters[fss_extended_read_parameter_delimit].values.used; ++i) {

          location = main->parameters[fss_extended_read_parameter_delimit].values.array[i];
          length = strnlen(arguments->argv[location], f_console_parameter_size);

          if (!length) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
            f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_delimit);
            f_color_print(main->error.to.stream, main->context.set.error, "' must not be empty.%c", f_string_eol_s[0]);

            status = F_status_set_error(F_parameter);
            break;
          }
          else if (fl_string_compare(arguments->argv[location], fss_extended_read_delimit_mode_name_none, length, fss_extended_read_delimit_mode_name_none_length) == F_equal_to) {
            data.delimit_mode = fss_extended_read_delimit_mode_none;
          }
          else if (fl_string_compare(arguments->argv[location], fss_extended_read_delimit_mode_name_all, length, fss_extended_read_delimit_mode_name_all_length) == F_equal_to) {
            data.delimit_mode = fss_extended_read_delimit_mode_all;
          }
          else if (fl_string_compare(arguments->argv[location], fss_extended_read_delimit_mode_name_object, length, fss_extended_read_delimit_mode_name_object_length) == F_equal_to) {
            switch (data.delimit_mode) {
              case 0:
                data.delimit_mode = fss_extended_read_delimit_mode_object;
                break;

              case fss_extended_read_delimit_mode_none:
              case fss_extended_read_delimit_mode_all:
              case fss_extended_read_delimit_mode_content_greater_object:
              case fss_extended_read_delimit_mode_content_lesser_object:
              case fss_extended_read_delimit_mode_object:
                break;

              case fss_extended_read_delimit_mode_content:
                data.delimit_mode = fss_extended_read_delimit_mode_content_object;
                break;

              case fss_extended_read_delimit_mode_content_greater:
                data.delimit_mode = fss_extended_read_delimit_mode_content_greater_object;
                break;

              case fss_extended_read_delimit_mode_content_lesser:
                data.delimit_mode = fss_extended_read_delimit_mode_content_lesser_object;
                break;

              default:
                break;
            }
          }
          else {
            if (!data.delimit_mode) {
              data.delimit_mode = fss_extended_read_delimit_mode_content;
            }
            else if (data.delimit_mode == fss_extended_read_delimit_mode_object) {
              data.delimit_mode = fss_extended_read_delimit_mode_content_object;
            }

            if (arguments->argv[location][length - 1] == fss_extended_read_delimit_mode_name_greater[0]) {
              if (!(data.delimit_mode == fss_extended_read_delimit_mode_none || data.delimit_mode == fss_extended_read_delimit_mode_all)) {
                if (data.delimit_mode == fss_extended_read_delimit_mode_content_object) {
                  data.delimit_mode = fss_extended_read_delimit_mode_content_greater_object;
                }
                else {
                  data.delimit_mode = fss_extended_read_delimit_mode_content_greater;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }
            else if (arguments->argv[location][length - 1] == fss_extended_read_delimit_mode_name_lesser[0]) {
              if (!(data.delimit_mode == fss_extended_read_delimit_mode_none || data.delimit_mode == fss_extended_read_delimit_mode_all)) {
                if (data.delimit_mode == fss_extended_read_delimit_mode_content_object) {
                  data.delimit_mode = fss_extended_read_delimit_mode_content_lesser_object;
                }
                else {
                  data.delimit_mode = fss_extended_read_delimit_mode_content_lesser;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }

            f_string_range_t range = macro_f_string_range_t_initialize(length);

            // Ignore leading plus sign.
            if (arguments->argv[location][0] == '+') {
              ++range.start;
            }

            status = fl_conversion_string_to_number_unsigned(arguments->argv[location], range, &data.delimit_depth);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_read_long_delimit, arguments->argv[location]);
              break;
            }

            // There can be nothing smaller than 0, so replace '0-' logic with just '0' logic.
            if (data.delimit_mode == fss_extended_read_delimit_mode_content_lesser || data.delimit_mode == fss_extended_read_delimit_mode_content_lesser_object) {
              if (!data.delimit_depth) {
                if (data.delimit_mode == fss_extended_read_delimit_mode_content_lesser) {
                  data.delimit_mode = fss_extended_read_delimit_mode_content;
                }
                else {
                  data.delimit_mode = fss_extended_read_delimit_mode_content_object;
                }
              }
            }
          }
        } // for

        // Guarantee the default value is "all".
        if (!data.delimit_mode) {
          data.delimit_mode = fss_extended_read_delimit_mode_all;
        }
      }

      if (F_status_is_error_not(status)) {
        status = fss_extended_read_depth_process(arguments, main, &data);
      }

      // This standard does not support nesting, so any depth greater than 0 can be predicted without processing the file.
      if (F_status_is_error_not(status) && data.depths.array[0].depth > 0) {
        if (main->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
          fss_extended_read_print_zero(main);
        }

        fss_extended_read_data_delete_simple(&data);
        fss_extended_read_main_delete(main);

        return F_none;
      }

      if (F_status_is_error_not(status) && main->parameters[fss_extended_read_parameter_select].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_read_long_select);
        f_color_print(main->error.to.stream, main->context.set.error, "' parameter requires a positive number.%c", f_string_eol_s[0]);

        fss_extended_read_depths_resize(0, &data.depths);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status)) {
        for (f_array_length_t i = 0; i < data.files.used; ++i) {
          macro_f_string_range_t_clear(data.files.array[i].range);
        } // for
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;
        file.stream = f_type_input;

        data.files.array[0].name = 0;
        data.files.array[0].range.start = 0;

        status = f_file_stream_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, "-", "read", fll_error_file_type_pipe);
        }
        else if (data.buffer.used) {
          data.files.array[0].range.stop = data.buffer.used - 1;

          // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
          // Guarantee that a newline exists at the end of the buffer.
          status = f_string_append_assure(f_string_eol_s, 1, &data.buffer);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true, "-", "read", fll_error_file_type_pipe);
          }
        }
        else {
          data.files.array[0].range.start = 1;
        }
      }

      if (F_status_is_error_not(status) && main->remaining.used > 0) {
        f_file_t file = f_file_t_initialize;
        f_array_length_t size_file = 0;

        for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

          data.files.array[data.files.used].range.start = data.buffer.used;
          file.stream = 0;
          file.id = -1;

          status = f_file_stream_open(arguments->argv[main->remaining.array[i]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments->argv[main->remaining.array[i]], "open", fll_error_file_type_file);

            break;
          }

          size_file = 0;
          status = f_file_size_by_id(file.id, &size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, arguments->argv[main->remaining.array[i]], "read", fll_error_file_type_file);

            break;
          }

          if (size_file) {
            status = f_string_dynamic_resize(data.buffer.size + size_file, &data.buffer);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true, arguments->argv[main->remaining.array[i]], "read", fll_error_file_type_file);

              break;
            }

            status = f_file_stream_read(file, &data.buffer);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, arguments->argv[main->remaining.array[i]], "read", fll_error_file_type_file);

              break;
            }
            else if (data.buffer.used > data.files.array[data.files.used].range.start) {
              data.files.array[data.files.used].name = arguments->argv[main->remaining.array[i]];
              data.files.array[data.files.used++].range.stop = data.buffer.used - 1;

              // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
              // Guarantee that a newline exists at the end of the buffer.
              status = f_string_append_assure(f_string_eol_s, 1, &data.buffer);

              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true, "-", "read", fll_error_file_type_pipe);
              }
            }
          }
          else {
            data.files.array[data.files.used].range.start = 1;
          }

          f_file_stream_close(F_true, &file);
        } // for

        f_file_stream_close(F_true, &file);
      }

      if (F_status_is_error_not(status)) {
        status = fss_extended_read_process(arguments, main, &data);
      }

      fss_extended_read_data_delete_simple(&data);
    }
    else {
      f_color_print(main->error.to.stream, main->context.set.error, "%sYou failed to specify one or more files.%c", fll_error_print_error, f_string_eol_s[0]);
      status = F_status_set_error(F_parameter);
    }

    fss_extended_read_data_delete_simple(&data);
    fss_extended_read_main_delete(main);

    return status;
  }
#endif // _di_fss_extended_read_main_

#ifndef _di_fss_extended_read_main_delete_
  f_status_t fss_extended_read_main_delete(fss_extended_read_main_t *main) {

    for (f_array_length_t i = 0; i < fss_extended_read_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);
    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_extended_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
