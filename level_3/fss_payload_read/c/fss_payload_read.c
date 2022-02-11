#include "fss_payload_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_read_program_version_
  const f_string_static_t fss_payload_read_program_version_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_READ_program_version_s, 0, FSS_PAYLOAD_READ_program_version_s_length);
#endif // _di_fss_payload_read_program_version_

#ifndef _di_fss_payload_read_program_name_
  const f_string_static_t fss_payload_read_program_name_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_READ_program_name_s, 0, FSS_PAYLOAD_READ_program_name_s_length);
  const f_string_static_t fss_payload_read_program_name_long_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_READ_program_name_long_s, 0, FSS_PAYLOAD_READ_program_name_long_s_length);
#endif // _di_fss_payload_read_program_name_

#ifndef _di_fss_payload_read_print_help_
  f_status_t fss_payload_read_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_payload_read_program_name_long_s, fss_payload_read_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_payload_read_short_at_s, fss_payload_read_long_at_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Select Object at this numeric index.");
    fll_program_print_help_option(file, context, fss_payload_read_short_content_s, fss_payload_read_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Content (default).");
    fll_program_print_help_option(file, context, fss_payload_read_short_columns_s, fss_payload_read_long_columns_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the total number of columns.");
    fll_program_print_help_option(file, context, fss_payload_read_short_delimit_s, fss_payload_read_long_delimit_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(file, context, fss_payload_read_short_depth_s, fss_payload_read_long_depth_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select Object at this numeric depth.");
    fll_program_print_help_option(file, context, fss_payload_read_short_empty_s, fss_payload_read_long_empty_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Include empty Content when processing.");
    fll_program_print_help_option(file, context, fss_payload_read_short_line_s, fss_payload_read_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print only the Content at the given line.");
    fll_program_print_help_option(file, context, fss_payload_read_short_name_s, fss_payload_read_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Select Object with this name.");
    fll_program_print_help_option(file, context, fss_payload_read_short_object_s, fss_payload_read_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the Object.");
    fll_program_print_help_option(file, context, fss_payload_read_short_pipe_s, fss_payload_read_long_pipe_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print using the special pipe format.");
    fll_program_print_help_option(file, context, fss_payload_read_short_raw_s, fss_payload_read_long_raw_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print with the original quotes and escapes.");
    fll_program_print_help_option(file, context, fss_payload_read_short_select_s, fss_payload_read_long_select_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Select sub-Content at this index.");
    fll_program_print_help_option(file, context, fss_payload_read_short_total_s, fss_payload_read_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print the total number of lines.");
    fll_program_print_help_option(file, context, fss_payload_read_short_trim_s, fss_payload_read_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Trim Object names on select or print.");

    fll_program_print_help_usage(file, context, fss_payload_read_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format(" %[Notes:%]%r", file.stream, context.set.important, context.set.important, f_string_eol_s);

    fl_print_format("  This program will print the Content associated with the given Object and Content main based on the FSS-000E Payload standard.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  All numeric positions (indexes) start at 0 instead of 1.%r", file.stream, f_string_eol_s);
    fl_print_format("  For example, a file of 17 lines would range from 0 to 16.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the %[%r%r%] option, an order of operations is enforced on the parameters.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable, f_string_eol_s);

    fl_print_format("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%r", file.stream, f_string_eol_s);

    fl_print_format("    %[%r%r%]: An Object index at the specified depth.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_at_s, context.set.notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: A new depth within the specified depth, indexed from the root.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: An Object name at the specified depth.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_name_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] must be in numeric order, but values in between may be skipped.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable, f_string_eol_s);
    fl_print_format("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%r", file.stream, f_string_eol_s);
    fl_print_format("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] selects a Content column.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_select_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Specify both %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_object_s, context.set.notable);
    fl_print_format(" and the %[%r%r%] parameters to get the total objects.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_total_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When both %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_at_s, context.set.notable);
    fl_print_format(" and %[%r%r%] parameters are specified (at the same depth),", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_name_s, context.set.notable);
    fl_print_format(" the %[%r%r%] parameter value will be treated as a position relative to the specified", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_at_s, context.set.notable);
    fl_print_format(" %[%r%r%] parameter value.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_name_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program may support parameters, such as %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable);
    fl_print_format(" or %[%r%r%], even if not supported by the standard.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_select_s, context.set.notable, f_string_eol_s);
    fl_print_format("  This is done to help ensure consistency for scripting.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable);
    fl_print_format(" if the standard doesn't support nested Content, then only a depth of 0 would be valid.%r", file.stream, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_select_s, context.set.notable);
    fl_print_format(" if the standard doesn't support multiple Content groups, then only a select of 0 would be valid.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_trim_s, context.set.notable);
    fl_print_format(" will remove leading and trailing whitespaces when selecting objects or when printing objects.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying both the %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_object_s, context.set.notable);
    fl_print_format(" parameter and the %[%r%r%] parameter, the entire Object and Content are printed, including the formatting.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_content_s, context.set.notable, f_string_eol_s);
    fl_print_format("  Both the Object and Content printed are already escaped.%r", file.stream, f_string_eol_s);
    fl_print_format("  Both the Object and Content are separated by an EOL.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] accepts the following:%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_delimit_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Do not apply delimits.%r", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_none_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: (default) Apply all delimits.%r", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_all_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Apply delimits for Objects.%r", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_object_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - A number, 0 or greater: apply delimits for Content at the specified depth.%r", file.stream, f_string_eol_s);
    fl_print_format("  - A number, 0 or greater, followed by a %[%r%]: (such as '1+') apply delimits for Content at the specified depth and any greater depth (numerically).%r", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_greater_s, context.set.notable, f_string_eol_s, f_string_eol_s);
    fl_print_format("  - A number, 0 or lesser, followed by a %[%r%]: (such as '1-') apply delimits for Content at the specified depth and any lesser depth (numerically).%r%r", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_lesser_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] parameter may be specified multiple times to customize the delimit behavior.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_delimit_s, context.set.notable, f_string_eol_s);

    fl_print_format("  The %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_delimit_s, context.set.notable);
    fl_print_format(" values %[%r%]", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_none_s, context.set.notable);
    fl_print_format(" and %[%r%],", file.stream, context.set.notable, fss_payload_read_delimit_mode_name_all_s, context.set.notable);
    fl_print_format(" overrule all other delimit values.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameters %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_columns_s, context.set.notable);
    fl_print_format(" and %[%r%r%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_select_s, context.set.notable);
    fl_print_format(" refer to a Content column.%r", file.stream, f_string_eol_s);
    fl_print_format("  The word \"column\" is being loosely defined to refer to a specific Content.%r", file.stream, f_string_eol_s);
    fl_print_format("  This is not to be confused with a depth.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  As an exceptional case, a %[%r%r%] of", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_depth_s, context.set.notable);
    fl_print_format(" %[1%] applies only to the explicit Object of", file.stream, context.set.notable, context.set.notable);
    fl_print_format(" '%[%r%]'.%r", file.stream, context.set.notable, f_fss_string_header_s, context.set.notable, f_string_eol_s);
    fl_print_format("  Content at this depth is processed as FSS-0001 Extended.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The Content of the explicit Object of", file.stream);
    fl_print_format(" '%[%r%]'", file.stream, context.set.notable, f_fss_string_payload_s, context.set.notable, f_string_eol_s);
    fl_print_format(" will not contain any Content close pipe control codes when using", file.stream);
    fl_print_format(" %[%r%r%].%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_payload_read_long_pipe_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_payload_read_print_help_

#ifndef _di_fss_payload_read_main_
  f_status_t fss_payload_read_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = fss_payload_read_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = fss_payload_read_total_parameters_d;

    {
      f_console_parameter_id_t ids[3] = { fss_payload_read_parameter_no_color_e, fss_payload_read_parameter_light_e, fss_payload_read_parameter_dark_e };
      const f_console_parameter_ids_t choices = { ids, 3 };

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->context);

      main->output.set = &main->context.set;
      main->error.set = &main->context.set;
      main->warning.set = &main->context.set;

      if (main->context.set.error.before) {
        main->output.context = f_color_set_empty_s;
        main->output.notable = main->context.set.notable;

        main->error.context = main->context.set.error;
        main->error.notable = main->context.set.notable;

        main->warning.context = main->context.set.warning;
        main->warning.notable = main->context.set.notable;
      }
      else {
        f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

        fll_program_parameter_process_empty(&main->context, sets);
      }

      if (F_status_is_error(status)) {
        fss_payload_read_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { fss_payload_read_parameter_verbosity_quiet_e, fss_payload_read_parameter_verbosity_normal_e, fss_payload_read_parameter_verbosity_verbose_e, fss_payload_read_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fss_payload_read_main_delete(main);

        return status;
      }

      if (choice == fss_payload_read_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fss_payload_read_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fss_payload_read_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fss_payload_read_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    status = F_none;

    if (main->parameters.array[fss_payload_read_parameter_help_e].result == f_console_result_found_e) {
      fss_payload_read_print_help(main->output.to, main->context);

      fss_payload_read_main_delete(main);

      return status;
    }

    if (main->parameters.array[fss_payload_read_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_payload_read_program_version_s);

      fss_payload_read_main_delete(main);

      return status;
    }

    // Provide a range designating where within the buffer a particular file exists, using a statically allocated array.
    fss_payload_read_file_t files_array[main->parameters.remaining.used + 1];
    fss_payload_read_data_t data = fss_payload_read_data_t_initialize;

    data.argv = main->parameters.arguments.array;
    data.files.array = files_array;
    data.files.used = 1;
    data.files.size = main->parameters.remaining.used + 1;
    data.files.array[0].name = fss_payload_read_pipe_name_s;
    data.files.array[0].range.start = 1;
    data.files.array[0].range.stop = 0;

    if (main->parameters.remaining.used || main->process_pipe) {
      {
        const f_array_length_t parameter_code[] = {
          fss_payload_read_parameter_at_e,
          fss_payload_read_parameter_depth_e,
          fss_payload_read_parameter_line_e,
          fss_payload_read_parameter_select_e,
          fss_payload_read_parameter_name_e,
          fss_payload_read_parameter_delimit_e,
        };

        const f_string_static_t parameter_name[] = {
          fss_payload_read_long_at_s,
          fss_payload_read_long_depth_s,
          fss_payload_read_long_line_s,
          fss_payload_read_long_select_s,
          fss_payload_read_long_name_s,
          fss_payload_read_long_delimit_s,
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

          if (main->parameters.array[parameter_code[i]].result == f_console_result_found_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameter_name[i], main->error.notable);
            fl_print_format("%[' requires a %s.%]%r", main->error.to.stream, main->error.context, parameter_message[i], main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);

            status = F_status_set_error(F_parameter);
            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_payload_read_parameter_columns_e].result == f_console_result_found_e) {
        const f_array_length_t parameter_code[] = {
          fss_payload_read_parameter_depth_e,
          fss_payload_read_parameter_line_e,
          fss_payload_read_parameter_pipe_e,
          fss_payload_read_parameter_select_e,
          fss_payload_read_parameter_total_e,
        };

        const f_string_static_t parameter_name[] = {
          fss_payload_read_long_depth_s,
          fss_payload_read_long_line_s,
          fss_payload_read_long_pipe_s,
          fss_payload_read_long_select_s,
          fss_payload_read_long_total_s,
        };

        const uint8_t parameter_match[] = {
          f_console_result_additional_e,
          f_console_result_additional_e,
          f_console_result_found_e,
          f_console_result_additional_e,
          f_console_result_found_e,
        };

        for (f_array_length_t i = 0; i < 5; ++i) {

          if (main->parameters.array[parameter_code[i]].result == parameter_match[i]) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_columns_s, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, parameter_name[i], main->error.notable);
            fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);

            status = F_status_set_error(F_parameter);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_payload_read_parameter_total_e].result == f_console_result_found_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_pipe_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_total_s, main->error.notable);
          fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters.array[fss_payload_read_parameter_line_e].result == f_console_result_additional_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_pipe_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_line_s, main->error.notable);
          fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_payload_read_parameter_delimit_e].result == f_console_result_additional_e) {
        f_array_length_t index = 0;
        f_array_length_t length = 0;
        uint16_t signal_check = 0;

        // Set the value to 0 to allow for detecting mode based on what is provided.
        data.delimit_mode = 0;

        for (f_array_length_t i = 0; i < main->parameters.array[fss_payload_read_parameter_delimit_e].values.used; ++i) {

          if (!((++signal_check) % fss_payload_read_signal_check_d)) {
            if (fss_payload_read_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            signal_check = 0;
          }

          index = main->parameters.array[fss_payload_read_parameter_delimit_e].values.array[i];
          length = data.argv[index].used;

          if (!length) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_delimit_s, main->error.notable);
            fl_print_format("%[' must not be empty.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);

            status = F_status_set_error(F_parameter);

            break;
          }
          else if (fl_string_dynamic_compare(data.argv[index], fss_payload_read_delimit_mode_name_none_s) == F_equal_to) {
            data.delimit_mode = fss_payload_read_delimit_mode_none_e;
          }
          else if (fl_string_dynamic_compare(data.argv[index], fss_payload_read_delimit_mode_name_all_s) == F_equal_to) {
            data.delimit_mode = fss_payload_read_delimit_mode_all_e;
          }
          else if (fl_string_dynamic_compare(data.argv[index], fss_payload_read_delimit_mode_name_object_s) == F_equal_to) {
            switch (data.delimit_mode) {
              case 0:
                data.delimit_mode = fss_payload_read_delimit_mode_object_e;
                break;

              case fss_payload_read_delimit_mode_none_e:
              case fss_payload_read_delimit_mode_all_e:
              case fss_payload_read_delimit_mode_content_greater_object_e:
              case fss_payload_read_delimit_mode_content_lesser_object_e:
              case fss_payload_read_delimit_mode_object_e:
                break;

              case fss_payload_read_delimit_mode_content_e:
                data.delimit_mode = fss_payload_read_delimit_mode_content_object_e;
                break;

              case fss_payload_read_delimit_mode_content_greater_e:
                data.delimit_mode = fss_payload_read_delimit_mode_content_greater_object_e;
                break;

              case fss_payload_read_delimit_mode_content_lesser_e:
                data.delimit_mode = fss_payload_read_delimit_mode_content_lesser_object_e;
                break;

              default:
                break;
            }
          }
          else {
            if (!data.delimit_mode) {
              data.delimit_mode = fss_payload_read_delimit_mode_content_e;
            }
            else if (data.delimit_mode == fss_payload_read_delimit_mode_object_e) {
              data.delimit_mode = fss_payload_read_delimit_mode_content_object_e;
            }

            if (data.argv[index].string[length - 1] == fss_payload_read_delimit_mode_name_greater_s.string[0]) {
              if (!(data.delimit_mode == fss_payload_read_delimit_mode_none_e || data.delimit_mode == fss_payload_read_delimit_mode_all_e)) {
                if (data.delimit_mode == fss_payload_read_delimit_mode_content_object_e) {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_greater_object_e;
                }
                else {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_greater_e;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }
            else if (data.argv[index].string[length - 1] == fss_payload_read_delimit_mode_name_lesser_s.string[0]) {
              if (!(data.delimit_mode == fss_payload_read_delimit_mode_none_e || data.delimit_mode == fss_payload_read_delimit_mode_all_e)) {
                if (data.delimit_mode == fss_payload_read_delimit_mode_content_object_e) {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_lesser_object_e;
                }
                else {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_lesser_e;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }

            f_string_range_t range = macro_f_string_range_t_initialize(length);

            // Ignore leading plus sign.
            if (data.argv[index].string[0] == f_string_ascii_plus_s.string[0]) {
              ++range.start;
            }

            status = fl_conversion_string_to_number_unsigned(data.argv[index].string, range, &data.delimit_depth);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_payload_read_long_delimit_s, data.argv[index]);

              break;
            }

            // There can be nothing smaller than 0, so replace '0-' logic with just '0' logic.
            if (data.delimit_mode == fss_payload_read_delimit_mode_content_lesser_e || data.delimit_mode == fss_payload_read_delimit_mode_content_lesser_object_e) {
              if (!data.delimit_depth) {
                if (data.delimit_mode == fss_payload_read_delimit_mode_content_lesser_e) {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_e;
                }
                else {
                  data.delimit_mode = fss_payload_read_delimit_mode_content_object_e;
                }
              }
            }
          }
        } // for

        // Guarantee the default value is "all".
        if (F_status_is_error_not(status) && !data.delimit_mode) {
          data.delimit_mode = fss_payload_read_delimit_mode_all_e;
        }
      }

      if (F_status_is_error_not(status)) {
        status = fss_payload_read_depth_process(main, &data);
      }

      // This standard only partially supports nesting, so any depth greater than 1 can be predicted without processing the file.
      if (F_status_is_error_not(status)) {
        for (f_array_length_t i = 0; i < data.depths.used; ++i) {

          if (data.depths.array[i].depth == 1) {
            data.option |= fss_payload_read_data_option_extended_d;
          }

          if (data.depth_max < data.depths.array[i].depth) {
            data.depth_max = data.depths.array[i].depth;
          }
        } // for

        if (data.depth_max > 1) {
          if (main->parameters.array[fss_payload_read_parameter_total_e].result == f_console_result_found_e) {
            fss_payload_read_print_zero(main);
          }

          fss_payload_read_data_delete_simple(&data);
          fss_payload_read_main_delete(main);

          return F_none;
        }
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_payload_read_parameter_select_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_payload_read_long_select_s, main->error.notable);
        fl_print_format("%[' parameter requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        fss_payload_read_depths_resize(0, &data.depths);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status)) {
        for (f_array_length_t i = 0; i < data.files.used; ++i) {
          macro_f_string_range_t_clear(data.files.array[i].range);
        } // for
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        data.files.array[0].range.start = 0;

        status = f_file_stream_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
        }
        else if (data.buffer.used) {
          data.files.array[0].range.stop = data.buffer.used - 1;

          // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
          // Guarantee that a newline exists at the end of the buffer.
          status = f_string_dynamic_append_assure(f_string_eol_s, &data.buffer);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
          }
        }
        else {
          data.files.array[0].range.start = 1;
        }
      }

      if (F_status_is_error_not(status) && main->parameters.remaining.used > 0) {
        f_file_t file = f_file_t_initialize;
        f_array_length_t size_file = 0;
        const f_array_length_t buffer_used = data.buffer.used;
        uint16_t signal_check = 0;

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++signal_check) % fss_payload_read_signal_check_d)) {
            if (fss_payload_read_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            signal_check = 0;
          }

          data.files.array[data.files.used].range.start = data.buffer.used;
          file.stream = 0;
          file.id = -1;

          status = f_file_stream_open(data.argv[main->parameters.remaining.array[i]], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          size_file = 0;
          status = f_file_size_by_id(file.id, &size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);

            break;
          }

          if (size_file) {
            file.size_read = size_file + 1;

            // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
            // Guarantee that a newline exists at the end of the buffer.
            // This is done as a pre-process on the next file because the "payload" must always be last and must not have a newline appended.
            if (buffer_used != data.buffer.used) {
              status = f_string_dynamic_append_assure(f_string_eol_s, &data.buffer);

              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
              }
            }

            status = f_file_stream_read(file, &data.buffer);

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);

              break;
            }
            else if (data.buffer.used > data.files.array[data.files.used].range.start) {
              data.files.array[data.files.used].name = data.argv[main->parameters.remaining.array[i]];
              data.files.array[data.files.used++].range.stop = data.buffer.used - 1;
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
        status = fss_payload_read_process(main, &data);
      }

      fss_payload_read_data_delete_simple(&data);
    }
    else {
      fll_print_format("%r%[%QYou failed to specify one or more files.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      status = F_status_set_error(F_parameter);
    }

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    fss_payload_read_data_delete_simple(&data);
    fss_payload_read_main_delete(main);

    return status;
  }
#endif // _di_fss_payload_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
