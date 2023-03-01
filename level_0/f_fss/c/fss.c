#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_apply_delimit_
  void f_fss_apply_delimit(const f_fss_delimits_t delimits, f_string_static_t * const buffer, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!buffer) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer->used) {
      state->status = F_data_not;

      return;
    }

    for (f_array_length_t i = 0; i < delimits.used; ++i) {

      if (delimits.array[i] < buffer->used) {
        buffer->string[delimits.array[i]] = f_fss_placeholder_s.string[0];
      }
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_apply_delimit_

#ifndef _di_f_fss_apply_delimit_range_
  void f_fss_apply_delimit_range(const f_fss_delimits_t delimits, const f_string_range_t range, f_string_static_t * const buffer, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!buffer) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer->used || range.start > range.stop || range.start >= buffer->used) {
      state->status = F_data_not;

      return;
    }

    for (f_array_length_t i = 0; i < delimits.used; ++i) {

      if (delimits.array[i] < buffer->used && delimits.array[i] >= range.start && delimits.array[i] <= range.stop) {
        buffer->string[delimits.array[i]] = f_fss_placeholder_s.string[0];
      }
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_apply_delimit_range_

#ifndef _di_f_fss_count_lines_
  void f_fss_count_lines(const f_string_static_t buffer, const f_array_length_t before, f_array_length_t * const line, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!line) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) {
      state->status = F_data_not;

      return;
    }

    for (f_array_length_t i = 0; i < before && i < buffer.used; i += macro_f_utf_byte_width(buffer.string[i])) {

      if (buffer.string[i] == f_fss_eol_s.string[0]) {
        ++(*line);
      }
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_count_lines_

#ifndef _di_f_fss_count_lines_range_
  void f_fss_count_lines_range(const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const line, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!line) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      state->status = F_data_not;

      return;
    }

    for (f_array_length_t i = range.start; i <= range.stop && i < buffer.used; i += macro_f_utf_byte_width(buffer.string[i])) {

      if (buffer.string[i] == f_fss_eol_s.string[0]) {
        ++(*line);
      }
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_count_lines_range_

#ifndef _di_f_fss_fail_utf_
  void f_fss_fail_utf(f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;
    #endif // _di_level_0_parameter_checking_

    if (F_status_is_error(state->status)) {
      if (F_status_set_fine(state->status) == F_utf_fragment || F_status_set_fine(state->status) == F_complete_not_utf || F_status_set_fine(state->status) == F_utf_not) {
        if (!(state->flag & f_fss_state_flag_utf_fail_on_valid_not_e)) {
          state->status = F_status_set_fine(state->status);
        }
      }
    }
  }
#endif // _di_f_fss_fail_utf_

#ifndef _di_f_fss_fail_utf_to_false_
  void f_fss_fail_utf_to_false(f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;
    #endif // _di_level_0_parameter_checking_

    if (F_status_is_error(state->status)) {
      if (F_status_set_fine(state->status) == F_utf_fragment || F_status_set_fine(state->status) == F_complete_not_utf || F_status_set_fine(state->status) == F_utf_not) {
        if (!(state->flag & f_fss_state_flag_utf_fail_on_valid_not_e)) {
          state->status = F_false;
        }
      }
    }
  }
#endif // _di_f_fss_fail_utf_to_false_

#ifndef _di_f_fss_is_combining_
  f_status_t f_fss_is_combining(const f_string_static_t buffer, const f_string_range_t range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      state->status = F_data_not;

      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    state->status = f_utf_is_combining(buffer.string + range.start, width_max);
    if (state->status == F_true) return F_true;

    f_fss_fail_utf_to_false(state);

    return F_false;
  }
#endif // _di_f_fss_is_combining_

#ifndef _di_f_fss_is_graph_
  f_status_t f_fss_is_graph(const f_string_static_t buffer, const f_string_range_t range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      state->status = F_data_not;

      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    state->status = f_utf_is_graph(buffer.string + range.start, width_max);
    if (state->status == F_true) return F_true;

    f_fss_fail_utf_to_false(state);

    return F_false;
  }
#endif // _di_f_fss_is_graph_

#ifndef _di_f_fss_is_space_
  f_status_t f_fss_is_space(const f_string_static_t buffer, const f_string_range_t range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      state->status = F_data_not;

      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    state->status = f_utf_is_zero_width(buffer.string + range.start, width_max);
    if (state->status != F_false) return F_false;

    f_fss_fail_utf_to_false(state);

    state->status = f_utf_is_whitespace(buffer.string + range.start, width_max, F_false);
    if (state->status == F_true) return F_true;

    f_fss_fail_utf_to_false(state);

    if (state->status == F_false) {
      state->status = f_utf_is_control(buffer.string + range.start, width_max);
      if (state->status == F_true) return F_true;

      f_fss_fail_utf_to_false(state);
    }

    return F_false;
  }
#endif // _di_f_fss_is_space_

#ifndef _di_f_fss_is_zero_width_
  f_status_t f_fss_is_zero_width(const f_string_static_t buffer, const f_string_range_t range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range.start > range.stop || range.start >= buffer.used) {
      state->status = F_data_not;

      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    state->status = f_utf_is_zero_width(buffer.string + range.start, width_max);
    if (state->status == F_true) return F_true;

    f_fss_fail_utf_to_false(state);

    return F_false;
  }
#endif // _di_f_fss_is_zero_width_

#ifndef _di_f_fss_seek_to_eol_
  void f_fss_seek_to_eol(const f_string_dynamic_t buffer, f_string_range_t * const range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!range) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      state->status = F_data_not;

      return;
    }

    for (;; ++range->start) {

      if (range->start >= buffer.used) {
        state->status = F_none_eos;

        return;
      }

      if (range->start > range->stop) {
        state->status = F_none_stop;

        return;
      }

      if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_seek_to_eol_

#ifndef _di_f_fss_skip_past_delimit_
  void f_fss_skip_past_delimit(const f_string_static_t buffer, f_string_range_t * const range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!range) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      state->status = F_data_not;

      return;
    }

    for (;; ++range->start) {

      if (range->start >= buffer.used) {
        state->status = F_none_eos;

        return;
      }

      if (range->start > range->stop) {
        state->status = F_none_stop;

        return;
      }

      if (buffer.string[range->start] != f_fss_placeholder_s.string[0]) break;
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_skip_past_delimit_

#ifndef _di_f_fss_skip_past_space_
  void f_fss_skip_past_space(const f_string_static_t buffer, f_string_range_t * const range, f_state_t * const state) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;

      if (!range) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      state->status = F_data_not;

      return;
    }

    uint8_t width = 0;
    f_array_length_t width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    // Check that the first character is not a combining character.
    state->status = f_utf_is_combining(buffer.string + range->start, width_max);

    f_fss_fail_utf_to_false(state);
    if (F_status_is_error(state->status)) return;

    if (state->status == F_true) {
      state->status = F_status_set_error(F_complete_not_utf_start);

      return;
    }

    for (;;) {

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }

      if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
        state->status = F_none_eol;

        return;
      }

      if (buffer.string[range->start] == f_fss_placeholder_s.string[0]) {
        ++range->start;

        continue;
      }

      state->status = f_utf_is_whitespace(buffer.string + range->start, width_max, F_false);

      f_fss_fail_utf_to_false(state);

      if (state->status == F_false) {
        state->status = f_utf_is_control(buffer.string + range->start, width_max);

        f_fss_fail_utf_to_false(state);

        if (state->status == F_false) {
          state->status = f_utf_is_combining(buffer.string + range->start, width_max);

          f_fss_fail_utf_to_false(state);

          if (state->status == F_false) {
            state->status = f_utf_is_zero_width(buffer.string + range->start, width_max);

            f_fss_fail_utf_to_false(state);
            if (state->status == F_false) break;
          }
        }
      }

      if (F_status_is_error(state->status)) return;

      width = macro_f_utf_byte_width(buffer.string[range->start]);

      if (width > 1) {
        if (range->start + width >= buffer.used) {
          state->status = F_status_set_error(F_complete_not_utf_eos);

          f_fss_fail_utf(state);

          return;
        }

        if (range->start + width > range->stop) {
          state->status = F_status_set_error(F_complete_not_utf_stop);

          f_fss_fail_utf(state);

          return;
        }
      }

      range->start += width;

      if (range->start >= buffer.used) {
        state->status = F_none_eos;

        return;
      }

      if (range->start > range->stop) {
        state->status = F_none_stop;

        return;
      }
    } // for

    state->status = F_none;
  }
#endif // _di_f_fss_skip_past_space_

#ifdef __cplusplus
} // extern "C"
#endif
