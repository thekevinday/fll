#include "utf8.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_character_
  void utf8_print_character(utf8_data_t * const data, const f_string_static_t character, const f_color_set_t set) {

    if (data->main->parameters[utf8_parameter_strip_invalid].result == f_console_result_found || !character.used) {
      return;
    }

    if (data->mode & utf8_mode_to_binary_d) {
      fl_print_format("%s%[", data->file.stream, data->prepend, set);
      f_print_dynamic_raw(character, data->file.stream);
      fl_print_format("%s%]", data->file.stream, data->append, set);
    }
    else {
      fl_print_format("%s%[0x", data->file.stream, data->prepend, set);

      for (uint8_t i = 0; i < character.used; ++i) {
        fl_print_format("%04_uii", data->file.stream, (uint8_t) character.string[i]);
      } // for

      fl_print_format("%s%]", data->file.stream, data->append, set);
    }
  }
#endif // _di_utf8_print_character_

#ifndef _di_utf8_print_error_decode_
  void utf8_print_error_decode(utf8_data_t * const data, const f_status_t status, const f_string_static_t character) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    fl_print_format("%c%[%SFailed to decode character '%]", data->main->error.to.stream, f_string_eol_s[0], data->main->context.set.error, data->main->context.set.error);
    fl_print_format("%[%r%]", data->main->error.to.stream, data->main->context.set.notable, character, data->main->context.set.notable);
    fl_print_format("%[', error status code%] ", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s[0]);
    fl_print_format("%[%S%]", data->main->error.to.stream, data->main->context.set.notable, F_status_set_fine(status), data->main->context.set.notable);
    fl_print_format("%[.%]%c", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_error_decode_

#ifndef _di_utf8_print_error_no_from_
  void utf8_print_error_no_from(utf8_data_t * const data) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    fll_print_format("%c%[%sNo from sources are specified, please pipe data, designate a file, or add parameters.%]%c", data->main->error.to.stream, f_string_eol_s[0], data->main->error.context, data->main->error.prefix, data->main->error.context, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_no_value_
  void utf8_print_error_no_value(utf8_data_t * const data, const f_string_t parameter) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%c%[%SThe parameter '%]", data->main->error.to.stream, f_string_eol_s[0], data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
    fl_print_format("%[%s%S%]", data->main->error.to.stream, data->main->context.set.notable, f_console_symbol_long_enable_s, parameter, data->main->context.set.notable);
    fl_print_format("%[' is specified, but no value was given.%]%c", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s[0]);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_no_value_

#ifndef _di_utf8_print_error_parameter_conflict_
  void utf8_print_error_parameter_conflict(utf8_data_t * const data, const f_string_t first, const f_string_t second) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(data->main->output.to.stream);

    fl_print_format("%c%[%sThe parameter '%]", data->main->error.to.stream, f_string_eol_s[0], data->main->error.context, data->main->error.prefix, data->main->error.context);
    fl_print_format("%[%s%S%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, first, data->main->error.notable);
    fl_print_format("%[' cannot be used with the parameter '%]", data->main->error.to.stream, data->main->error.context, data->main->error.context);
    fl_print_format("%[%s%S%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, second, data->main->error.notable);
    fl_print_format("%['.%]%c", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s[0]);

    funlockfile(data->main->output.to.stream);
  }
#endif // _di_utf8_print_error_parameter_conflict_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  void utf8_print_error_parameter_file_name_empty(utf8_data_t * const data, const f_array_length_t index) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%c%[%SNo file specified at parameter index %]", data->main->error.to.stream, f_string_eol_s[0], data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
    fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->context.set.notable, index, data->main->context.set.notable);
    fl_print_format("%[.%]%c", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s[0]);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  void utf8_print_error_parameter_file_not_found(utf8_data_t * const data, const bool from, const f_string_t name) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%c%[%SFailed to find the %s file '%]", data->main->error.to.stream, f_string_eol_s[0], data->main->context.set.error, data->main->error.prefix, from ? utf8_string_from_s : utf8_string_to_s, data->main->context.set.error);
    fl_print_format("%[%S%]", data->main->error.to.stream, data->main->context.set.notable, name, data->main->context.set.notable);
    fl_print_format("%['.%]%c", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s[0]);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  void utf8_print_error_parameter_file_to_too_many(utf8_data_t * const data) {

    if (data->main->error.verbosity == f_console_verbosity_quiet) return;

    fll_print_format("%c%[%SToo many %s files specified, there may only be one to file.%]%c", data->main->error.to.stream, f_string_eol_s[0], data->main->context.set.error, data->main->error.prefix, utf8_string_to_s, data->main->context.set.error, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifndef _di_utf8_print_section_header_file_
  void utf8_print_section_header_file(utf8_data_t * const data, const f_string_t name) {

    if (data->main->output.verbosity == f_console_verbosity_quiet) return;
    if (data->main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    flockfile(data->main->output.to.stream);

    fl_print_format("%c%[File%] ", data->main->output.to.stream, f_string_eol_s[0], data->main->output.set->title, data->main->output.set->title);

    if (data->file.stream == data->main->output.to.stream) {
      fl_print_format("%[%S%]:%c", data->main->output.to.stream, data->main->output.set->notable, name, data->main->output.set->notable, f_string_eol_s[0]);
    }
    else {
      fl_print_format("%[%S%]: %S.%c", data->main->output.to.stream, data->main->output.set->notable, name, data->main->output.set->notable, data->file_name, f_string_eol_s[0]);
    }

    funlockfile(data->main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_file_

#ifndef _di_utf8_print_section_header_parameter_
  void utf8_print_section_header_parameter(utf8_data_t * const data, const f_array_length_t index) {

    if (data->main->output.verbosity == f_console_verbosity_quiet) return;
    if (data->main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    flockfile(data->main->output.to.stream);

    fl_print_format("%c%[Parameter%] ", data->main->output.to.stream, f_string_eol_s[0], data->main->output.set->title, data->main->output.set->title);
    fl_print_format("%[%ul%]:%c", data->main->output.to.stream, data->main->output.set->notable, index, data->main->output.set->notable, f_string_eol_s[0]);

    funlockfile(data->main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_parameter_

#ifndef _di_utf8_print_section_header_pipe_
  void utf8_print_section_header_pipe(utf8_data_t * const data) {

    if (data->main->output.verbosity == f_console_verbosity_quiet) return;
    if (data->main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    fll_print_format("%c%[Pipe%]:%c", data->main->output.to.stream, f_string_eol_s[0], data->main->output.set->title, data->main->output.set->title, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_section_header_pipe_

#ifndef _di_utf8_print_signal_received_
  void utf8_print_signal_received(utf8_data_t * const data, const f_status_t signal) {

    if (data->main->warning.verbosity != f_console_verbosity_verbose) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(data->main->warning.to.stream);

    flockfile(data->main->warning.to.stream);

    fl_print_format("%]%c%c%[Received signal code %]", data->main->warning.to.stream, data->main->context.set.reset, f_string_eol_s[0], f_string_eol_s[0], data->main->context.set.warning, data->main->context.set.warning);
    fl_print_format("%[%i%]", data->main->warning.to.stream, data->main->context.set.notable, signal, data->main->context.set.notable);
    fl_print_format("%[.%]%c", data->main->warning.to.stream, data->main->context.set.warning, data->main->context.set.warning, f_string_eol_s[0]);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_utf8_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
