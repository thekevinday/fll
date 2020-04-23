#include <level_3/fss_basic_list_read.h>
#include "private-fss_basic_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_print_help_
  f_return_status fss_basic_list_read_print_help(const fss_basic_list_read_data data) {
    fll_program_print_help_header(data.context, fss_basic_list_read_name_long, fss_basic_list_read_version);

    fll_program_print_help_option(data.context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(data.context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(data.context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(data.context, fss_basic_list_read_short_at, fss_basic_list_read_long_at, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Select object at this numeric index.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_depth, fss_basic_list_read_long_depth, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Select object at this numeric depth.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_empty, fss_basic_list_read_long_empty, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Include empty content when processing.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_line, fss_basic_list_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print only the content at the given line.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_name, fss_basic_list_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Select object with this name.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_object, fss_basic_list_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the object instead of the content.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_select, fss_basic_list_read_long_select, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Select sub-content at this index.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_total, fss_basic_list_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print the total number of lines.");
    fll_program_print_help_option(data.context, fss_basic_list_read_short_trim, fss_basic_list_read_long_trim, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Trim object names on select or print.");

    fll_program_print_help_usage(data.context, fss_basic_list_read_name, "filename(s)");

    fl_color_print(f_standard_output, data.context.important, data.context.reset, " Notes:");

    printf("%c", f_string_eol, f_string_eol);

    printf("  This program will print the content associated with the given object and content data based on the FSS-0002 Basic List standard.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  When using the ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
    printf(" option, an order of operations is enforced on the parameters.%c", f_string_eol);

    printf("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", f_string_eol);

    printf("    ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_at);
    printf(": An object index at the specified depth.%c", f_string_eol);

    printf("    ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
    printf(": A new depth within the specified depth, indexed from the root.%c", f_string_eol);

    printf("    ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_name);
    printf(": An object name at the specified depth.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  The parameter ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
    printf(" must be in numeric order, but values in between may be skipped.%c", f_string_eol);
    printf("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", f_string_eol);
    printf("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  The parameter ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_select);
    printf(" selects a content index at a given depth.%c", f_string_eol);
    printf("    (This parameter is not synonymous with the depth parameter and does not relate to nested content).%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  Specify both ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_object);
    printf(" and the ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_total);
    printf(" parameters to get the total objects.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  When both ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_at);
    printf(" and ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_name);
    printf(" parameters are specified (at the same depth), the ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_at);
    printf(" parameter value will be treated as a position relative to the specified ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_name);
    printf(" parameter value.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  This program may support parameters, such as ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
    printf(" or ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_select);
    printf(", even if not supported by the standard.%c", f_string_eol);
    printf("  This is done to help ensure consistency for scripting.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  For parameters like ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
    printf(", if the standard doesn't support nested content, then only a depth of 0 would be valid.%c", f_string_eol);

    printf("  For parameters like ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_select);
    printf(", if the standard doesn't support multiple content groups, then only a select of 0 would be valid.%c", f_string_eol);

    printf("%c", f_string_eol);

    printf("  The parameter ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_trim);
    printf(" will remove leading and trailing whitespaces when selecting objects or when printing objects.%c", f_string_eol);

    printf("%c", f_string_eol);

    return f_none;
  }
#endif // _di_fss_basic_list_read_print_help_

#ifndef _di_fss_basic_list_read_main_
  f_return_status fss_basic_list_read_main(const f_console_arguments arguments, fss_basic_list_read_data *data) {
    f_status status = f_none;

    {
      f_console_parameters parameters = { data->parameters, fss_basic_list_read_total_parameters };
      f_console_parameter_id ids[3] = { fss_basic_list_read_parameter_no_color, fss_basic_list_read_parameter_light, fss_basic_list_read_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_process_parameters(arguments, parameters, choices, &data->remaining, &data->context);

      if (f_status_is_error(status)) {
        fss_basic_list_read_delete_data(data);
        return f_status_set_error(status);
      }

      status = f_none;
    }

    if (data->parameters[fss_basic_list_read_parameter_help].result == f_console_result_found) {
      fss_basic_list_read_print_help(*data);
    }
    else if (data->parameters[fss_basic_list_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_basic_list_read_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_at);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->parameters[fss_basic_list_read_parameter_depth].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_depth);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_line);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_name);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' requires a string.");

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->parameters[fss_basic_list_read_parameter_select].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: The parameter '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_select);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' requires a positive number.");

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_found) {
        if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_object);
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_line);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' parameter.");

          fss_basic_list_read_delete_data(data);
          return f_status_set_error(f_invalid_parameter);
        }

        if (data->parameters[fss_basic_list_read_parameter_select].result == f_console_result_additional) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_object);
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_select);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' parameter.");

          fss_basic_list_read_delete_data(data);
          return f_status_set_error(f_invalid_parameter);
        }
      }

      if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
        if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_line);
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "' parameter with the '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_total);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' parameter.");

          fss_basic_list_read_delete_data(data);
          return f_status_set_error(f_invalid_parameter);
        }
      }

      fss_basic_list_read_depths depths = fss_basic_list_read_depths_initialize;

      f_string_length counter = 0;
      f_string_length original_size = data->file_position.total_elements;

      status = fss_basic_list_read_main_preprocess_depth(arguments, *data, &depths);
      if (f_status_is_error(status)) {
        macro_fss_basic_list_read_depths_delete_simple(depths);
        fss_basic_list_read_delete_data(data);
        return status;
      }

      // This standard does not support nesting, so any depth greater than 0 can be predicted without processing the file.
      if (depths.array[0].depth > 0) {
        macro_fss_basic_list_read_depths_delete_simple(depths);

        if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
          fprintf(f_standard_output, "0%c", f_string_eol);

          fss_basic_list_read_delete_data(data);
          return f_none;
        }

        fss_basic_list_read_delete_data(data);
        return f_none;
      }

      if (data->parameters[fss_basic_list_read_parameter_select].result == f_console_result_found) {
        fl_color_print(f_standard_error, data->context.error, data->context.reset, "ERROR: the '");
        fl_color_print(f_standard_error, data->context.notable, data->context.reset, "--%s", fss_basic_list_read_long_select);
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "' parameter requires a positive number.");

        macro_fss_basic_list_read_depths_delete_simple(depths);
        fss_basic_list_read_delete_data(data);
        return f_status_set_error(f_invalid_parameter);
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.address = f_pipe;

        status = fl_file_read_fifo(file, &data->buffer);

        if (f_status_is_error(status)) {
          fss_basic_list_read_print_file_error(data->context, "fl_file_read_fifo", "-", f_status_set_fine(status));

          macro_fss_basic_list_read_depths_delete_simple(depths);
          fss_basic_list_read_delete_data(data);
          return status;
        }

        status = fss_basic_list_read_main_process_file(arguments, data, "-", depths);

        if (f_status_is_error(status)) {
          macro_fss_basic_list_read_depths_delete_simple(depths);
          fss_basic_list_read_delete_data(data);
          return status;
        }

        // Clear buffers before continuing.
        f_macro_fss_contents_delete_simple(data->contents);
        f_macro_fss_objects_delete_simple(data->objects);
        f_macro_string_dynamic_delete_simple(data->buffer);
      }

      if (data->remaining.used > 0) {
        for (; counter < data->remaining.used; counter++) {
          f_file file = f_file_initialize;

          status = f_file_open(&file, arguments.argv[data->remaining.array[counter]]);

          data->file_position.total_elements = original_size;

          if (f_status_is_error(status)) {
            fss_basic_list_read_print_file_error(data->context, "f_file_open", arguments.argv[data->remaining.array[counter]], f_status_set_fine(status));
            macro_fss_basic_list_read_depths_delete_simple(depths);
            fss_basic_list_read_delete_data(data);
            return status;
          }

          if (data->file_position.total_elements == 0) {
            fseek(file.address, 0, SEEK_END);

            data->file_position.total_elements = ftell(file.address);

            // Sskip past empty files.
            if (data->file_position.total_elements == 0) {
              f_file_close(&file);
              continue;
            }

            fseek(file.address, 0, SEEK_SET);
          }

          status = fl_file_read(file, data->file_position, &data->buffer);

          f_file_close(&file);

          if (f_status_is_error(status)) {
            fss_basic_list_read_print_file_error(data->context, "fl_file_read", arguments.argv[data->remaining.array[counter]], f_status_set_fine(status));
            macro_fss_basic_list_read_depths_delete_simple(depths);
            fss_basic_list_read_delete_data(data);
            return status;
          }

          status = fss_basic_list_read_main_process_file(arguments, data, arguments.argv[data->remaining.array[counter]], depths);

          if (f_status_is_error(status)) {
            macro_fss_basic_list_read_depths_delete_simple(depths);
            fss_basic_list_read_delete_data(data);
            return status;
          }

          // Clear buffers before repeating the loop.
          f_macro_fss_contents_delete_simple(data->contents);
          f_macro_fss_objects_delete_simple(data->objects);
          f_macro_string_dynamic_delete_simple(data->buffer);
        } // for
      }

      macro_fss_basic_list_read_depths_delete_simple(depths);
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files.");
      status = f_status_set_error(f_invalid_parameter);
    }

    fss_basic_list_read_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_list_read_main_

#ifndef _di_fss_basic_list_read_delete_data_
  f_return_status fss_basic_list_read_delete_data(fss_basic_list_read_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_basic_list_read_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_fss_contents_delete_simple(data->contents);
    f_macro_fss_objects_delete_simple(data->objects);
    f_macro_string_dynamic_delete_simple(data->buffer);
    f_macro_string_lengths_delete_simple(data->remaining);

    fl_macro_color_context_delete_simple(data->context);

    return f_none;
  }
#endif // _di_fss_basic_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
