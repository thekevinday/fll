#include "utf8.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_binary_
  void utf8_print_binary(utf8_data_t * const data, const f_string_static_t character) {

    fl_print_format("%s%r%s", data->file.stream, data->prepend, character, data->append);
  }
#endif // _di_utf8_print_binary_

#ifndef _di_utf8_print_character_invalid_
  void utf8_print_character_invalid(utf8_data_t * const data, const f_string_static_t character) {

    if (data->main->parameters.array[utf8_parameter_strip_invalid_e].result == f_console_result_found_e) return;
    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) return;

    if (!character.used) return;

    if ((data->mode & utf8_mode_to_combining_d) || (data->mode & utf8_mode_to_width_d)) {
      utf8_print_combining_or_width(data, character);
    }
    else if (data->mode & utf8_mode_to_binary_d) {
      fl_print_format("%s%[%r%]%s", data->file.stream, data->prepend, data->valid_not, character, data->valid_not, data->append);
    }
    else if (data->mode & utf8_mode_from_codepoint_d) {
      fl_print_format("%s%[%Q%]%s", data->file.stream, data->prepend, data->valid_not, character, data->valid_not, data->append);
    }
    else {
      fl_print_format("%s%[0x", data->file.stream, data->prepend, data->valid_not);

      for (uint8_t i = 0; i < character.used; ++i) {
        fl_print_format("%02_uii", data->file.stream, (uint8_t) character.string[i]);
      } // for

      fl_print_format("%]%s", data->file.stream, data->valid_not, data->append);
    }
  }
#endif // _di_utf8_print_character_invalid_

#ifndef _di_utf8_print_codepoint_
  void utf8_print_codepoint(utf8_data_t * const data, const uint32_t codepoint) {

    if (codepoint < 0xffff) {
      fl_print_format("%sU+%04_U%s", data->file.stream, data->prepend, codepoint, data->append);
    }
    else if (codepoint < 0x100000) {
      fl_print_format("%sU+%05_U%s", data->file.stream, data->prepend, codepoint, data->append);
    }
    else {
      fl_print_format("%sU+%06_U%s", data->file.stream, data->prepend, codepoint, data->append);
    }
  }
#endif // _di_utf8_print_codepoint_

#ifndef _di_utf8_print_combining_or_width_
  void utf8_print_combining_or_width(utf8_data_t * const data, const f_string_static_t character) {

    f_status_t status = F_none;

    if (data->mode & utf8_mode_to_combining_d) {
      status = f_utf_is_combining(character.string, character.used);

      if (status == F_true) {
        fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_combining_is_s, data->append);
      }
      else if (status == F_false) {
        status = f_utf_is_private(character.string, character.used);

        if (status == F_true) {
          fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_unknown_s, data->append);
        }
        else if (data->mode & utf8_mode_to_width_d) {
          utf8_print_width(data, character);
        }
        else {
          fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_combining_not_s, data->append);
        }
      }
      else if (data->main->parameters.array[utf8_parameter_strip_invalid_e].result == f_console_result_none_e && data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
        fl_print_format("%s%[%s%]%s", data->file.stream, data->prepend, data->valid_not, utf8_string_unknown_s, data->valid_not, data->append);
      }
    }
    else if (data->mode & utf8_mode_to_width_d) {
      utf8_print_width(data, character);
    }
  }
#endif // _di_utf8_print_combining_or_width_

#ifndef _di_utf8_print_error_decode_
  void utf8_print_error_decode(utf8_data_t * const data, const f_status_t status, const f_string_static_t character) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;
    if (data->main->parameters.array[utf8_parameter_strip_invalid_e].result == f_console_result_found_e) return;
    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) return;

    fl_print_format("%r%[%QFailed to decode character code '%]", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);

    if (character.used) {
      fl_print_format("%[0x", data->main->error.to.stream, data->main->context.set.notable);

      for (uint8_t i = 0; i < character.used; ++i) {
        fl_print_format("%02_uii", data->main->error.to.stream, (uint8_t) character.string[i]);
      } // for

      fl_print_format("%]", data->main->error.to.stream, data->main->context.set.notable);
    }

    if (F_status_set_fine(status) == F_utf) {
      fl_print_format("%[', not a valid UTF-8 character sequence.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
    }
    else if (F_status_set_fine(status) == F_utf_fragment) {
      fl_print_format("%[', invalid UTF-8 fragment.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
      fl_print_format("%[%ui%]", data->main->error.to.stream, data->main->context.set.notable, F_status_set_fine(status), data->main->context.set.notable);
      fl_print_format("%[.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
    }
  }
#endif // _di_utf8_print_error_decode_

#ifndef _di_utf8_print_error_encode_
  void utf8_print_error_encode(utf8_data_t * const data, const f_status_t status, const uint32_t codepoint) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QFailed to encode Unicode codepoint '%]", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
    fl_print_format("%[U+%_U%]", data->main->error.to.stream, data->main->context.set.notable, codepoint, data->main->context.set.notable);

    if (F_status_set_fine(status) == F_utf) {
      fl_print_format("%[', not a valid Unicode codepoint.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
      fl_print_format("%[%ui%]", data->main->error.to.stream, data->main->context.set.notable, F_status_set_fine(status), data->main->context.set.notable);
      fl_print_format("%[.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);
    }
  }
#endif // _di_utf8_print_error_encode_

#ifndef _di_utf8_print_error_no_from_
  void utf8_print_error_no_from(utf8_data_t * const data) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QNo from sources are specified, please pipe data, designate a file, or add parameters.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context, f_string_eol_s);
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_no_value_
  void utf8_print_error_no_value(utf8_data_t * const data, const f_string_t parameter) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
    fl_print_format("%[%r%r%]", data->main->error.to.stream, data->main->context.set.notable, f_console_symbol_long_enable_s, parameter, data->main->context.set.notable);
    fl_print_format("%[' is specified, but no value was given.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_no_value_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  void utf8_print_error_parameter_file_name_empty(utf8_data_t * const data, const f_array_length_t index) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QNo file specified at parameter index %]", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
    fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->context.set.notable, index, data->main->context.set.notable);
    fl_print_format("%[.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  void utf8_print_error_parameter_file_not_found(utf8_data_t * const data, const bool from, const f_string_t name) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(data->main->error.to.stream);

    fl_print_format("%r%[%QFailed to find the %s file '%]", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, from ? utf8_string_from_s : utf8_string_to_s, data->main->context.set.error);
    fl_print_format("%[%S%]", data->main->error.to.stream, data->main->context.set.notable, name, data->main->context.set.notable);
    fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s);

    funlockfile(data->main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  void utf8_print_error_parameter_file_to_too_many(utf8_data_t * const data) {

    if (data->main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QToo many %r files specified, there may only be one to file.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->context.set.error, data->main->error.prefix, utf8_string_to_s, data->main->context.set.error, f_string_eol_s);
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifndef _di_utf8_print_section_header_file_
  void utf8_print_section_header_file(utf8_data_t * const data, const f_string_t name) {

    if (data->main->parameters.array[utf8_parameter_headers_e].result == f_console_result_none_e) return;
    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) return;

    flockfile(data->main->output.to.stream);

    fl_print_format("%r%[File%] ", data->main->output.to.stream, f_string_eol_s, data->main->output.set->title, data->main->output.set->title);

    if (data->file.stream == data->main->output.to.stream) {
      fl_print_format("%[%S%]:%r", data->main->output.to.stream, data->main->output.set->notable, name, data->main->output.set->notable, f_string_eol_s);
    }
    else {
      fl_print_format("%[%S%]: %S.%r", data->main->output.to.stream, data->main->output.set->notable, name, data->main->output.set->notable, data->file_name, f_string_eol_s);
    }

    funlockfile(data->main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_file_

#ifndef _di_utf8_print_section_header_parameter_
  void utf8_print_section_header_parameter(utf8_data_t * const data, const f_array_length_t index) {

    if (data->main->parameters.array[utf8_parameter_headers_e].result == f_console_result_none_e) return;
    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) return;

    flockfile(data->main->output.to.stream);

    fl_print_format("%r%[Parameter%] ", data->main->output.to.stream, f_string_eol_s, data->main->output.set->title, data->main->output.set->title);
    fl_print_format("%[%ul%]:%r", data->main->output.to.stream, data->main->output.set->notable, index, data->main->output.set->notable, f_string_eol_s);

    funlockfile(data->main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_parameter_

#ifndef _di_utf8_print_section_header_pipe_
  void utf8_print_section_header_pipe(utf8_data_t * const data) {

    if (data->main->parameters.array[utf8_parameter_headers_e].result == f_console_result_none_e) return;
    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_found_e) return;

    fll_print_format("%r%[Pipe%]:%r", data->main->output.to.stream, f_string_eol_s, data->main->output.set->title, data->main->output.set->title, f_string_eol_s);
  }
#endif // _di_utf8_print_section_header_pipe_

#ifndef _di_utf8_print_signal_received_
  void utf8_print_signal_received(utf8_data_t * const data, const f_status_t signal) {

    if (data->main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(data->main->warning.to.stream);

    flockfile(data->main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", data->main->warning.to.stream, data->main->context.set.reset, f_string_eol_s, f_string_eol_s, data->main->context.set.warning, data->main->context.set.warning);
    fl_print_format("%[%i%]", data->main->warning.to.stream, data->main->context.set.notable, signal, data->main->context.set.notable);
    fl_print_format("%[.%]%r", data->main->warning.to.stream, data->main->context.set.warning, data->main->context.set.warning, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_utf8_print_signal_received_

#ifndef _di_utf8_print_width_
  void utf8_print_width(utf8_data_t * const data, const f_string_static_t character) {

    f_status_t status = f_utf_is_wide(character.string, character.used);

    if (status == F_true) {
      fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_width_2_s, data->append);

      return;
    }

    if (status == F_false) {
      status = f_utf_is_graph(character.string, character.used);

      if (status == F_true) {
        fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_width_1_s, data->append);

        return;
      }

      if (status == F_false) {
        fl_print_format("%s%s%s", data->file.stream, data->prepend, utf8_string_width_0_s, data->append);

        return;
      }
    }

    if (data->main->parameters.array[utf8_parameter_strip_invalid_e].result == f_console_result_none_e && data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
      fl_print_format("%s%[%s%]%s", data->file.stream, data->prepend, data->valid_not, utf8_string_unknown_s, data->valid_not, data->append);
    }
  }
#endif // _di_utf8_print_width_

#ifdef __cplusplus
} // extern "C"
#endif
