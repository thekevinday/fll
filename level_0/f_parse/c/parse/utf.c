#include "../parse.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_parse_utf_dynamic_seek_line_to_char_
  f_status_t f_parse_utf_dynamic_seek_line_to_char(const f_utf_string_static_t buffer, f_range_t * const range, const f_char_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_utf_char_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (buffer.string[range->start] != seek_to_character) {

      if (buffer.string[range->start++] == f_utf_char_eol_s) {
        return F_okay_eol;
      }

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start >= buffer.used) {
        return F_okay_eos;
      }

      if (range->start > range->stop) {
        return F_okay_stop;
      }
    } // while

    return F_okay;
  }
#endif // _di_f_parse_utf_dynamic_seek_line_to_char_

#ifndef _di_f_parse_utf_dynamic_seek_line_until_graph_
  f_status_t f_parse_utf_dynamic_seek_line_until_graph(const f_utf_string_static_t buffer, f_range_t * const range, const f_utf_char_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_okay;

    if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_graph(buffer.string[range->start])) == F_false) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (buffer.string[range->start++] == f_utf_char_eol_s) {
        return F_okay_eol;
      }

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start >= buffer.used) {
        return F_okay_eos;
      }

      if (range->start > range->stop) {
        return F_okay_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_okay;
  }
#endif // _di_f_parse_utf_dynamic_seek_line_until_graph_

#ifndef _di_f_parse_utf_dynamic_seek_line_until_graph_non_
  f_status_t f_parse_utf_dynamic_seek_line_until_graph_non(const f_utf_string_static_t buffer, f_range_t * const range, const f_utf_char_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_okay;

    if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (buffer.string[range->start] == placeholder || (status = f_utf_character_is_whitespace(buffer.string[range->start], F_false)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_utf_char_eol_s) return F_okay_eol;

      ++range->start;

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start >= buffer.used) return F_okay_eos;
      if (range->start > range->stop) return F_okay_stop;
    } // while

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_parse_utf_dynamic_seek_line_until_graph_non_

#ifndef _di_f_parse_utf_dynamic_seek_to_char_
  f_status_t f_parse_utf_dynamic_seek_to_char(const f_utf_string_static_t buffer, f_range_t * const range, const f_char_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (buffer.used <= range->start) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;

    f_utf_char_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (buffer.string[range->start] != seek_to_character) {

      ++range->start;

      if (macro_f_utf_char_t_width_is(buffer.string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start >= buffer.used) {
        return F_okay_eos;
      }

      if (range->start > range->stop) {
        return F_okay_stop;
      }
    } // while

    return F_okay;
  }
#endif // _di_f_parse_utf_dynamic_seek_to_char_

#ifndef _di_f_parse_utf_seek_line_to_char_
  f_status_t f_parse_utf_seek_line_to_char(const f_utf_string_t string, f_range_t * const range, const f_char_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_utf_char_t seek_to_character = seek_to_this << 24;

    for (; range->start <= range->stop; ++range->start) {

      if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (string[range->start] == f_utf_char_eol_s) {
        return F_okay_eol;
      }

      if (string[range->start] == seek_to_character) {
        return F_okay;
      }
    } // for

    return F_okay_stop;
  }
#endif // _di_f_parse_utf_seek_line_to_char_

#ifndef _di_f_parse_utf_seek_line_until_graph_
  f_status_t f_parse_utf_seek_line_until_graph(const f_utf_string_t string, f_range_t * const range, const f_utf_char_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_status_t status = F_okay;

    if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_false) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start++] == f_utf_char_eol_s) {
        return F_okay_eol;
      }

      if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start > range->stop) {
        return F_okay_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_okay;
  }
#endif // _di_f_parse_utf_seek_line_until_graph_

#ifndef _di_f_parse_utf_seek_line_until_graph_non_
  f_status_t f_parse_utf_seek_line_until_graph_non(const f_utf_string_t string, f_range_t * const range, const f_utf_char_t placeholder) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    f_status_t status = F_okay;

    if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (string[range->start] == placeholder || (status = f_utf_character_is_graph(string[range->start])) == F_true) {

      if (F_status_is_error(status)) {
        return status;
      }

      if (string[range->start++] == f_utf_char_eol_s) {
        return F_okay_eol;
      }

      if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }

      if (range->start > range->stop) {
        return F_okay_stop;
      }
    } // while

    if (F_status_is_error(status)) {
      return status;
    }

    return F_okay;
  }
#endif // _di_f_parse_utf_seek_line_until_graph_non_

#ifndef _di_f_parse_utf_seek_to_char_
  f_status_t f_parse_utf_seek_to_char(const f_utf_string_t string, f_range_t * const range, const f_char_t seek_to_this) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    const f_utf_char_t seek_to_character = seek_to_this << 24;

    if (macro_f_utf_char_t_width_is(string[0]) == 1) {
      return F_status_set_error(F_utf_fragment);
    }

    while (range->start <= range->stop) {

      if (string[range->start++] == seek_to_character) {
        return F_okay;
      }

      if (macro_f_utf_char_t_width_is(string[range->start]) == 1) {
        return F_status_set_error(F_utf_fragment);
      }
    } // while

    return F_okay_stop;
  }
#endif // _di_fl_utf_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif
