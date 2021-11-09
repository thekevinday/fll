#include "fss_embedded_list_read.h"
#include "private-common.h"
#include "private-fss_embedded_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_print_help_
  f_status_t fss_embedded_list_read_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_embedded_list_read_program_name_long_s, fss_embedded_list_read_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, fss_embedded_list_read_short_at_s, fss_embedded_list_read_long_at_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Select Object at this numeric index.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_content_s, fss_embedded_list_read_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Content (default).");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_columns_s, fss_embedded_list_read_long_columns_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the total number of columns.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_delimit_s, fss_embedded_list_read_long_delimit_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_depth_s, fss_embedded_list_read_long_depth_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select Object at this numeric depth.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_empty_s, fss_embedded_list_read_long_empty_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Include empty Content when processing.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_line_s, fss_embedded_list_read_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print only the Content at the given line.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_name_s, fss_embedded_list_read_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Select Object with this name.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_object_s, fss_embedded_list_read_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the Object.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_pipe_s, fss_embedded_list_read_long_pipe_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print using the special pipe format.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_raw_s, fss_embedded_list_read_long_raw_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print with the original quotes and escapes.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_select_s, fss_embedded_list_read_long_select_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Select sub-Content at this index.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_total_s, fss_embedded_list_read_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print the total number of lines.");
    fll_program_print_help_option(file, context, fss_embedded_list_read_short_trim_s, fss_embedded_list_read_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Trim Object names on select or print.");

    fll_program_print_help_usage(file, context, fss_embedded_list_read_program_name_s, "filename(s)");

    fl_print_format(" %[Notes:%]%c", file.stream, context.set.important, context.set.important, f_string_eol_s[0]);

    fl_print_format("  This program will print the Content associated with the given Object and Content main based on the FSS-0008 Embedded List standard.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  All numeric positions (indexes) start at 0 instead of 1.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  For example, a file of 17 lines would range from 0 to 16.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When using the %[%s%s%] option, an order of operations is enforced on the parameters.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, context.set.notable, f_string_eol_s[0]);

    fl_print_format("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%c", file.stream, f_string_eol_s[0]);

    fl_print_format("    %[%s%s%]: An Object index at the specified depth.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_at_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("    %[%s%s%]: A new depth within the specified depth, indexed from the root.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("    %[%s%s%]: An Object name at the specified depth.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_name_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The parameter %[%s%s%] must be in numeric order, but values in between may be skipped.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%c", file.stream, f_string_eol_s[0]);
    fl_print_format("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The parameter %[%s%s%] selects a Content column.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  Specify both %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_object_s, context.set.notable);
    fl_print_format(" and the %[%s%s%] parameters to get the total objects.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_total_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When both %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_at_s, context.set.notable);
    fl_print_format(" and %[%s%s%] parameters are specified (at the same depth),", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_name_s, context.set.notable);
    fl_print_format(" the %[%s%s%] parameter value will be treated as a position relative to the specified", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_at_s, context.set.notable);
    fl_print_format(" %[%s%s%] parameter value.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_name_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  This program may support parameters, such as %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, context.set.notable);
    fl_print_format(" or %[%s%s%], even if not supported by the standard.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("  This is done to help ensure consistency for scripting.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  For parameters like %[%s%s%],", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, context.set.notable);
    fl_print_format(" if the standard doesn't support nested Content, then only a depth of 0 would be valid.%c", file.stream, f_string_eol_s[0]);

    fl_print_format("  For parameters like %[%s%s%],", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, context.set.notable);
    fl_print_format(" if the standard doesn't support multiple Content groups, then only a select of 0 would be valid.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The parameter %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_trim_s, context.set.notable);
    fl_print_format(" will remove leading and trailing whitespaces when selecting objects or when printing objects.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When specifying both the %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_object_s, context.set.notable);
    fl_print_format(" parameter and the %[%s%s%] parameter, the entire Object and Content are printed, including the formatting.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_content_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("  Both the Object and Content printed are already escaped.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  Both the Object and Content are separated by an EOL.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The parameter %[%s%s%] accepts the following:%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_delimit_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("  - %[%s%]: Do not apply delimits.%c", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_none_s, context.set.notable, f_string_eol_s[0]);
    fl_print_format("  - %[%s%]: (default) Apply all delimits.%c", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_all_s, context.set.notable, f_string_eol_s[0]);
    // @todo
    //fl_print_format("  - %[%s%]: Apply delimits for Objects.%c", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_object, context.set.notable, f_string_eol_s[0]);
    fl_print_format("  - A number, 0 or greater: apply delimits for Content at the specified depth.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  - A number, 0 or greater, followed by a %[%s%]: (such as '1+') apply delimits for Content at the specified depth and any greater depth (numerically).%c", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_greater_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);
    fl_print_format("  - A number, 0 or lesser, followed by a %[%s%]: (such as '1-') apply delimits for Content at the specified depth and any lesser depth (numerically).%c%c", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_lesser_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The %[%s%s%] parameter may be specified multiple times to customize the delimit behavior.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_delimit_s, context.set.notable, f_string_eol_s[0]);

    fl_print_format("  The %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_delimit_s, context.set.notable);
    fl_print_format(" values %[%s%]", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_none_s, context.set.notable);
    fl_print_format(" and %[%s%],", file.stream, context.set.notable, fss_embedded_list_read_delimit_mode_name_all_s, context.set.notable);
    fl_print_format(" overrule all other delimit values.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The parameters %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_columns_s, context.set.notable);
    fl_print_format(" and %[%s%s%]", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, context.set.notable);
    fl_print_format(" refer to a Content column.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  The word \"column\" is being loosely defined to refer to a specific Content.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  This is not to be confused with a depth.%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_print_help_

#ifndef _di_fss_embedded_list_read_main_
  f_status_t fss_embedded_list_read_main(const f_console_arguments_t arguments, fss_embedded_list_read_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_embedded_list_read_total_parameters_d);

      {
        f_console_parameter_id_t ids[3] = { fss_embedded_list_read_parameter_no_color, fss_embedded_list_read_parameter_light, fss_embedded_list_read_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

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
          fss_embedded_list_read_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_embedded_list_read_parameter_verbosity_quiet, fss_embedded_list_read_parameter_verbosity_normal, fss_embedded_list_read_parameter_verbosity_verbose, fss_embedded_list_read_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_embedded_list_read_main_delete(main);
          return status;
        }

        if (choice == fss_embedded_list_read_parameter_verbosity_quiet) {
          main->output.verbosity = f_console_verbosity_quiet;
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_embedded_list_read_parameter_verbosity_normal) {
          main->output.verbosity = f_console_verbosity_normal;
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_embedded_list_read_parameter_verbosity_verbose) {
          main->output.verbosity = f_console_verbosity_verbose;
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_embedded_list_read_parameter_verbosity_debug) {
          main->output.verbosity = f_console_verbosity_debug;
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_embedded_list_read_parameter_help].result == f_console_result_found) {
      fss_embedded_list_read_print_help(main->output.to, main->context);

      fss_embedded_list_read_main_delete(main);
      return F_none;
    }

    if (main->parameters[fss_embedded_list_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output.to, fss_embedded_list_read_program_version_s);

      fss_embedded_list_read_main_delete(main);
      return F_none;
    }

    if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
      if (main->parameters[fss_embedded_list_read_parameter_columns].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_total_s, main->error.notable);
        fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_columns_s, main->error.notable);
        fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
    }

    if (main->remaining.used > 0 || main->process_pipe) {
      if (main->parameters[fss_embedded_list_read_parameter_at].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_at_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_depth].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_line].result == f_console_result_additional) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_line_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_name].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_name_s, main->error.notable);
        fl_print_format("%[' requires a string.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_select].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters[fss_embedded_list_read_parameter_line].result == f_console_result_additional) {
        if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_line_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_total_s, main->error.notable);
          fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters[fss_embedded_list_read_parameter_pipe].result == f_console_result_found) {
        if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_pipe_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_total_s, main->error.notable);
          fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters[fss_embedded_list_read_parameter_delimit].result == f_console_result_found) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_delimit_s, main->error.notable);
          fl_print_format("%[' requires a value.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters[fss_embedded_list_read_parameter_delimit].result == f_console_result_additional) {
          const f_array_length_t location = main->parameters[fss_embedded_list_read_parameter_delimit].values.array[0];
          f_array_length_t length = strnlen(arguments.argv[location], f_console_parameter_size);

          if (length == 0) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sThe value for the parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_delimit_s, main->error.notable);
            fl_print_format("%[' must not be empty.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);

            status = F_status_set_error(F_parameter);
          }
          else if (fl_string_compare(arguments.argv[location], fss_embedded_list_read_delimit_mode_name_none_s, length, fss_embedded_list_read_delimit_mode_name_none_s_length) == F_equal_to) {
            main->delimit_mode = fss_embedded_list_read_delimit_mode_none;
          }
          else if (fl_string_compare(arguments.argv[location], fss_embedded_list_read_delimit_mode_name_all_s, length, fss_embedded_list_read_delimit_mode_name_all_s_length) == F_equal_to) {
            main->delimit_mode = fss_embedded_list_read_delimit_mode_all;
          }
          else {
            main->delimit_mode = fss_embedded_list_read_delimit_mode_depth;

            if (arguments.argv[location][length - 1] == fss_embedded_list_read_delimit_mode_name_greater_s[0]) {
              main->delimit_mode = fss_embedded_list_read_delimit_mode_depth_greater;

              // shorten the length to better convert the remainder to a number.
              --length;
            }
            else if (arguments.argv[location][length - 1] == fss_embedded_list_read_delimit_mode_name_lesser_s[0]) {
              main->delimit_mode = fss_embedded_list_read_delimit_mode_depth_lesser;

              // shorten the length to better convert the remainder to a number.
              --length;
            }

            f_string_range_t range = macro_f_string_range_t_initialize(length);

            // ignore leading plus sign.
            if (arguments.argv[location][0] == '+') {
              ++range.start;
            }

            status = fl_conversion_string_to_number_unsigned(arguments.argv[location], range, &main->delimit_depth);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_read_long_delimit_s, arguments.argv[location]);
            }
          }
        }
      }

      fss_embedded_list_read_depths_t depths = fss_embedded_list_read_depths_t_initialize;

      f_fss_delimits_t objects_delimits = f_fss_delimits_t_initialize;
      f_fss_delimits_t contents_delimits = f_fss_delimits_t_initialize;
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      f_array_length_t original_size = main->quantity.total;

      if (F_status_is_error_not(status)) {
        status = fss_embedded_list_read_main_preprocess_depth(arguments, *main, &depths);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_preprocess_depth", F_true);
        }
      }

      if (F_status_is_error_not(status) && main->parameters[fss_embedded_list_read_parameter_select].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_select_s, main->error.notable);
        fl_print_format("%[' parameter requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;

        status = f_file_read(file, &main->buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, "-", "read", fll_error_file_type_pipe);
        }
        else {
          status = fss_embedded_list_read_main_process_file(arguments, main, "-", depths, &objects_delimits, &contents_delimits, &comments);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_process_file", F_true, "-", "read", fll_error_file_type_pipe);
          }
        }

        // Clear buffers before continuing.
        macro_f_fss_nest_t_delete_simple(main->nest);
        macro_f_string_dynamic_t_delete_simple(main->buffer);
      }

      if (F_status_is_error_not(status) && main->remaining.used > 0) {
        for (f_array_length_t i = 0; i < main->remaining.used; ++i) {
          f_file_t file = f_file_t_initialize;

          status = f_file_open(arguments.argv[main->remaining.array[i]], 0, &file);

          main->quantity.total = original_size;

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, arguments.argv[main->remaining.array[i]], "open", fll_error_file_type_file);
            break;
          }

          if (!main->quantity.total) {
            status = f_file_size_by_id(file.id, &main->quantity.total);
            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, arguments.argv[main->remaining.array[i]], "read", fll_error_file_type_file);

              f_file_stream_close(F_true, &file);
              break;
            }

            // Skip past empty files.
            if (!main->quantity.total) {
              if (main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
                fll_print_format("0%c", main->output.to.stream, f_string_eol_s[0]);
              }

              f_file_stream_close(F_true, &file);
              continue;
            }
          }

          status = f_file_read_until(file, main->quantity.total, &main->buffer);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read_until", F_true, arguments.argv[main->remaining.array[i]], "read", fll_error_file_type_file);
            break;
          }

          status = fss_embedded_list_read_main_process_file(arguments, main, arguments.argv[main->remaining.array[i]], depths, &objects_delimits, &contents_delimits, &comments);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_process_file", F_true, arguments.argv[main->remaining.array[i]], "read", fll_error_file_type_file);
            break;
          }

          // Clear buffers before repeating the loop.
          macro_f_fss_nest_t_delete_simple(main->nest);
          macro_f_string_dynamic_t_delete_simple(main->buffer);
        } // for

        if (F_status_is_error(status)) {
          macro_f_fss_nest_t_delete_simple(main->nest);
          macro_f_string_dynamic_t_delete_simple(main->buffer);
        }
      }

      macro_fss_embedded_list_read_depths_t_delete_simple(depths);
      macro_f_fss_delimits_t_delete_simple(objects_delimits);
      macro_f_fss_delimits_t_delete_simple(contents_delimits);
      macro_f_fss_comments_t_delete_simple(comments);
    }
    else {
      fll_print_format("%c%[%sYou failed to specify one or more files.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
      status = F_status_set_error(F_parameter);
    }

    fss_embedded_list_read_main_delete(main);
    return status;
  }
#endif // _di_fss_embedded_list_read_main_

#ifndef _di_fss_embedded_list_read_main_delete_
  f_status_t fss_embedded_list_read_main_delete(fss_embedded_list_read_main_t *main) {

    for (f_array_length_t i = 0; i < fss_embedded_list_read_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_fss_nest_t_delete_simple(main->nest);

    macro_f_string_dynamic_t_delete_simple(main->buffer);
    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
