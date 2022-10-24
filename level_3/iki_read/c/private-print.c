#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_substitutions_print_
  void iki_read_substitutions_print(iki_read_data_t * const data, const f_iki_data_t iki_data, const f_string_ranges_t ranges, const iki_read_substitution_t replacement, const iki_read_substitution_t wraps, const iki_read_substitutions_t substitutions, const iki_read_substitutions_t reassignments, const f_array_length_t index, const bool content_only) {

    uint8_t matched = 0x0; // 0x0 = no match, 0x1 = match re-assignment, 0x2 = match substitution.
    f_array_length_t at = 0;
    f_array_length_t i = 0;

    // Grab the last (right-most) match.
    for (; i < reassignments.used; ++i) {

      if (fl_string_dynamic_partial_compare_string(reassignments.array[i].replace.string, data->buffer, reassignments.array[i].replace.used, iki_data.content.array[index]) == F_equal_to) {
        matched = 0x1;
        at = i;
      }
    } // for

    // Grab the last (right-most) match.
    if (!matched) {
      for (i = 0; i < substitutions.used; ++i) {

        if (fl_string_dynamic_partial_compare_string(substitutions.array[i].replace.string, data->buffer, substitutions.array[i].replace.used, iki_data.content.array[index]) == F_equal_to) {
          matched = 0x2;
          at = i;
        }
      } // for
    }

    if (matched) {
      if (content_only) {
        if (matched == 0x1) {
          f_print_dynamic(reassignments.array[at].with, data->main->output.to.stream);
        }
        else {
          // The wraps.replace represents the "before", which is a string to prepend.
          if (wraps.replace.used) {
            f_print_dynamic(wraps.replace, data->main->output.to.stream);
          }

          f_print_dynamic(substitutions.array[at].with, data->main->output.to.stream);

          // The wraps.replace represents the "after", which is a string to append.
          if (wraps.with.used) {
            f_print_dynamic(wraps.with, data->main->output.to.stream);
          }
        }
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(iki_data.variable.array[index].start, iki_data.content.array[index].start - 1);

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);

        if (matched == 0x1) {
          f_print_dynamic(reassignments.array[at].with, data->main->output.to.stream);
        }
        else {

          // The wraps.replace represents the "before", which is a string to prepend.
          if (wraps.replace.used) {
            f_print_dynamic(wraps.replace, data->main->output.to.stream);
          }

          f_print_dynamic(substitutions.array[at].with, data->main->output.to.stream);

          // The wraps.replace represents the "after", which is a string to append.
          if (wraps.with.used) {
            f_print_dynamic(wraps.with, data->main->output.to.stream);
          }
        }

        range.start = iki_data.content.array[index].stop + 1;
        range.stop = iki_data.variable.array[index].stop;

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);
      }
    }
    else if (replacement.replace.used) {
      if (content_only) {

        // The wraps.replace represents the "before", which is a string to prepend.
        if (wraps.replace.used) {
          f_print_dynamic(wraps.replace, data->main->output.to.stream);
        }

        f_print_dynamic(replacement.with, data->main->output.to.stream);

        // The wraps.replace represents the "after", which is a string to append.
        if (wraps.with.used) {
          f_print_dynamic(wraps.with, data->main->output.to.stream);
        }
      }
      else {
        f_string_range_t range = macro_f_string_range_t_initialize(iki_data.variable.array[index].start, iki_data.content.array[index].start - 1);

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);

        // The wraps.replace represents the "before", which is a string to prepend.
        if (wraps.replace.used) {
          f_print_dynamic(wraps.replace, data->main->output.to.stream);
        }

        f_print_dynamic(replacement.with, data->main->output.to.stream);

        // The wraps.replace represents the "after", which is a string to append.
        if (wraps.with.used) {
          f_print_dynamic(wraps.with, data->main->output.to.stream);
        }

        range.start = iki_data.content.array[index].stop + 1;
        range.stop = iki_data.variable.array[index].stop;

        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);
      }
    }
    else if (content_only) {

      // The wraps.replace represents the "before", which is a string to prepend.
      if (wraps.replace.used) {
        f_print_dynamic(wraps.replace, data->main->output.to.stream);
      }

      f_print_dynamic_partial(data->buffer, ranges.array[index], data->main->output.to.stream);

      // The wraps.replace represents the "after", which is a string to append.
      if (wraps.with.used) {
        f_print_dynamic(wraps.with, data->main->output.to.stream);
      }
    }
    else {
      f_string_range_t range = macro_f_string_range_t_initialize(iki_data.variable.array[index].start, iki_data.content.array[index].start - 1);

      f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);

      // The wraps.replace represents the "before", which is a string to prepend.
      if (wraps.replace.used) {
        f_print_dynamic(wraps.replace, data->main->output.to.stream);
      }

      f_print_dynamic_partial(data->buffer, iki_data.content.array[index], data->main->output.to.stream);

      // The wraps.replace represents the "after", which is a string to append.
      if (wraps.with.used) {
        f_print_dynamic(wraps.with, data->main->output.to.stream);
      }

      range.start = iki_data.content.array[index].stop + 1;
      range.stop = iki_data.variable.array[index].stop;

      f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);
    }
  }
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif
