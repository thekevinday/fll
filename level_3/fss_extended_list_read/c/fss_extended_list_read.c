#include <level_3/fss_extended_list_read.h>
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_print_help_
  f_return_status fss_extended_list_read_print_help(const fl_color_context context) {
    fll_program_print_help_header(context, fss_extended_list_read_name_long, fss_extended_list_read_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, fss_extended_list_read_short_at, fss_extended_list_read_long_at, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Select object at this numeric index.");
    fll_program_print_help_option(context, fss_extended_list_read_short_depth, fss_extended_list_read_long_depth, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Select object at this numeric depth.");
    fll_program_print_help_option(context, fss_extended_list_read_short_empty, fss_extended_list_read_long_empty, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Include empty content when processing.");
    fll_program_print_help_option(context, fss_extended_list_read_short_line, fss_extended_list_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print only the content at the given line.");
    fll_program_print_help_option(context, fss_extended_list_read_short_name, fss_extended_list_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Select object with this name.");
    fll_program_print_help_option(context, fss_extended_list_read_short_object, fss_extended_list_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the object instead of the content.");
    fll_program_print_help_option(context, fss_extended_list_read_short_select, fss_extended_list_read_long_select, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Select sub-content at this index.");
    fll_program_print_help_option(context, fss_extended_list_read_short_total, fss_extended_list_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print the total number of lines.");
    fll_program_print_help_option(context, fss_extended_list_read_short_trim, fss_extended_list_read_long_trim, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Trim object names on select or print.");

    fll_program_print_help_usage(context, fss_extended_list_read_name, "filename(s)");

    fl_color_print(f_type_output, context.important, context.reset, " Notes:");

    printf("%c", f_string_eol[0], f_string_eol[0]);

    printf("  This program will print the content associated with the given object and content data based on the FSS-0002 Basic List standard.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  When using the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
    printf(" option, an order of operations is enforced on the parameters.%c", f_string_eol[0]);

    printf("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", f_string_eol[0]);

    printf("    ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_at);
    printf(": An object index at the specified depth.%c", f_string_eol[0]);

    printf("    ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
    printf(": A new depth within the specified depth, indexed from the root.%c", f_string_eol[0]);

    printf("    ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
    printf(": An object name at the specified depth.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The parameter ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
    printf(" must be in numeric order, but values in between may be skipped.%c", f_string_eol[0]);
    printf("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", f_string_eol[0]);
    printf("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The parameter ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
    printf(" selects a content index at a given depth.%c", f_string_eol[0]);
    printf("    (This parameter is not synonymous with the depth parameter and does not relate to nested content).%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  Specify both ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_object);
    printf(" and the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_total);
    printf(" parameters to get the total objects.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  When both ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_at);
    printf(" and ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
    printf(" parameters are specified (at the same depth), the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_at);
    printf(" parameter value will be treated as a position relative to the specified ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
    printf(" parameter value.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  This program may support parameters, such as ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
    printf(" or ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
    printf(", even if not supported by the standard.%c", f_string_eol[0]);
    printf("  This is done to help ensure consistency for scripting.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  For parameters like ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
    printf(", if the standard doesn't support nested content, then only a depth of 0 would be valid.%c", f_string_eol[0]);

    printf("  For parameters like ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
    printf(", if the standard doesn't support multiple content groups, then only a select of 0 would be valid.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The parameter ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_trim);
    printf(" will remove leading and trailing whitespaces when selecting objects or when printing objects.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_fss_extended_list_read_print_help_

#ifndef _di_fss_extended_list_read_main_
  f_return_status fss_extended_list_read_main(const f_console_arguments arguments, fss_extended_list_read_data *data) {
    f_status status = F_none;

    {
      f_console_parameters parameters = { data->parameters, fss_extended_list_read_total_parameters };
      f_console_parameter_id ids[3] = { fss_extended_list_read_parameter_no_color, fss_extended_list_read_parameter_light, fss_extended_list_read_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

      if (F_status_is_error(status)) {
        fss_extended_list_read_delete_data(data);
        return F_status_set_error(status);
      }

      status = F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_help].result == f_console_result_found) {
      fss_extended_list_read_print_help(data->context);
    }
    else if (data->parameters[fss_extended_list_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_extended_list_read_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[fss_extended_list_read_parameter_at].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_at);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_extended_list_read_parameter_depth].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_line);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_extended_list_read_parameter_name].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a string.");

        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[fss_extended_list_read_parameter_object].result == f_console_result_found) {
        if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_object);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_line);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");

          fss_extended_list_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_additional) {
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_object);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");

          fss_extended_list_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }
      }

      if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
        if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_line);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_total);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");

          fss_extended_list_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }
      }

      fss_extended_list_read_depths depths = fss_extended_list_read_depths_initialize;

      f_string_length counter = 0;
      f_string_length original_size = data->quantity.total;

      status = fss_extended_list_read_main_preprocess_depth(arguments, *data, &depths);
      if (F_status_is_error(status)) {
        macro_fss_extended_list_read_depths_delete_simple(depths);
        fss_extended_list_read_delete_data(data);
        return status;
      }

      if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_found) {
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: the '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_select);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter requires a positive number.");

        macro_fss_extended_list_read_depths_delete_simple(depths);
        fss_extended_list_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.id = f_type_descriptor_input;

        status = f_file_read(file, &data->buffer);
        if (F_status_is_error(status)) {
          fss_extended_list_read_print_file_error(data->context, "f_file_read", "-", F_status_set_fine(status));

          macro_fss_extended_list_read_depths_delete_simple(depths);
          fss_extended_list_read_delete_data(data);
          return status;
        }

        status = fss_extended_list_read_main_process_file(arguments, data, "-", depths);
        if (F_status_is_error(status)) {
          macro_fss_extended_list_read_depths_delete_simple(depths);
          fss_extended_list_read_delete_data(data);
          return status;
        }

        // Clear buffers before continuing.
        f_macro_fss_nest_delete_simple(data->nest);
        f_macro_string_dynamic_delete_simple(data->buffer);
      }

      if (data->remaining.used > 0) {
        for (; counter < data->remaining.used; counter++) {
          f_file file = f_file_initialize;

          status = f_file_open(arguments.argv[data->remaining.array[counter]], 0, &file);

          data->quantity.total = original_size;

          if (F_status_is_error(status)) {
            fss_extended_list_read_print_file_error(data->context, "f_file_open", arguments.argv[data->remaining.array[counter]], F_status_set_fine(status));

            macro_fss_extended_list_read_depths_delete_simple(depths);
            fss_extended_list_read_delete_data(data);
            return status;
          }

          if (data->quantity.total == 0) {
            status = f_file_size_by_id(file.id, &data->quantity.total);
            if (F_status_is_error(status)) {
              fss_extended_list_read_print_file_error(data->context, "f_file_size_by_id", arguments.argv[data->remaining.array[counter]], F_status_set_fine(status));

              f_file_close(&file.id);

              macro_fss_extended_list_read_depths_delete_simple(depths);
              fss_extended_list_read_delete_data(data);
              return status;
            }

            // Skip past empty files.
            if (data->quantity.total == 0) {
              f_file_close(&file.id);
              continue;
            }
          }

          status = f_file_read_until(file, &data->buffer, data->quantity.total);

          f_file_close(&file.id);

          if (F_status_is_error(status)) {
            fss_extended_list_read_print_file_error(data->context, "f_file_read_until", arguments.argv[data->remaining.array[counter]], F_status_set_fine(status));

            macro_fss_extended_list_read_depths_delete_simple(depths);
            fss_extended_list_read_delete_data(data);
            return status;
          }

          status = fss_extended_list_read_main_process_file(arguments, data, arguments.argv[data->remaining.array[counter]], depths);

          if (F_status_is_error(status)) {
            macro_fss_extended_list_read_depths_delete_simple(depths);
            fss_extended_list_read_delete_data(data);
            return status;
          }

          // Clear buffers before repeating the loop.
          f_macro_fss_nest_delete_simple(data->nest);
          f_macro_string_dynamic_delete_simple(data->buffer);
        } // for
      }

      macro_fss_extended_list_read_depths_delete_simple(depths);
    }
    else {
      fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files.");
      status = F_status_set_error(F_parameter);
    }

    fss_extended_list_read_delete_data(data);
    return status;
  }
#endif // _di_fss_extended_list_read_main_

#ifndef _di_fss_extended_list_read_delete_data_
  f_return_status fss_extended_list_read_delete_data(fss_extended_list_read_data *data) {
    f_status status = F_none;
    f_string_length i = 0;

    while (i < fss_extended_list_read_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_fss_nest_delete_simple(data->nest);

    f_macro_string_dynamic_delete_simple(data->buffer);
    f_macro_string_lengths_delete_simple(data->remaining);

    fl_macro_color_context_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_extended_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
