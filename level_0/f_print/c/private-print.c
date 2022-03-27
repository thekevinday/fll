#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  f_status_t private_f_print(const f_string_t string, const f_array_length_t length, FILE * const output) {

    f_array_length_t total = 0;
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    for (register f_array_length_t i = 0; i < length; ) {

      total = strnlen((string + i), length - i);

      if (total) {
        if (total > F_print_write_max_d) {
          total = F_print_write_max_d;
        }

        count = 0;

        do {
          count += fwrite_unlocked(string + i + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        i += total;
        total = 0;
      }

      if (i < length && !string[i]) {
        do {
          ++i;
        } while (i < length && !string[i]);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  const f_string_static_t private_f_print_character_safely_get(const f_char_t character) {

    if (character == 0x7f) {
      return f_print_sequence_delete_s;
    }

    if (macro_f_utf_character_t_width_is(character) == 1) {
      return f_print_sequence_unknown_s;
    }

    if (macro_f_utf_character_t_width_is(character) > 1 || character > 0x1f) {
      return f_string_empty_s;
    }

    return f_print_sequence_set_control_s[character];
  }
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

#if !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)
  f_status_t private_f_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const output) {

    register f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (string[i]) {
        ++total;
      }

      if (!string[i] || i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)

#if !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_in_dynamic_) || !defined(_di_f_print_except_in_dynamic_partial_)
  f_status_t private_f_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            count = 0;

            do {
              count += fwrite_unlocked(string + start + count, 1, total - count, output);

              if (ferror_unlocked(output)) {
                return F_status_set_error(F_output);
              }

            } while (count < total);

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        ++total;
      }

      if (!string[i] || i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_) || !defined(_di_f_print_except_in_dynamic_) || !defined(_di_f_print_except_in_dynamic_partial_)

#if !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_in_dynamic_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)
  f_status_t private_f_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            count = 0;

            do {
              count += fwrite_unlocked(string + start + count, 1, total - count, output);

              if (ferror_unlocked(output)) {
                return F_status_set_error(F_output);
              }

            } while (count < total);

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      ++total;

      if (i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_raw_) || !defined(_di_f_print_except_in_dynamic_raw_) || !defined(_di_f_print_except_in_dynamic_partial_raw_)

#if !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_in_dynamic_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_)
  f_status_t private_f_print_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
            count = 0;

            do {
              count += fwrite_unlocked(string + start + count, 1, total - count, output);

              if (ferror_unlocked(output)) {
                return F_status_set_error(F_output);
              }

            } while (count < total);

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < safe.used);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      count = 0;

      do {
        count += fwrite_unlocked(string + start + count, 1, total - count, output);

        if (ferror_unlocked(output)) {
          return F_status_set_error(F_output);
        }

      } while (count < total);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_raw_safely_) || !defined(_di_f_print_except_in_dynamic_raw_safely_) || !defined(_di_f_print_except_in_dynamic_partial_raw_safely_)

#if !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)
  f_status_t private_f_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t at = 0;
    f_array_length_t in = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (at < except_at.used && except_at.array[at] < i) {
        ++at;
      } // while

      if (at < except_at.used && except_at.array[at] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (in < except_in.used) {
        while (in < except_in.used && except_in.array[in].start < i && except_in.array[in].stop < i) {
          ++in;
        } // while

        if (in < except_in.used && except_in.array[in].start <= i && except_in.array[in].stop >= i) {
          if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

            total = 0;
          }

          i = except_in.array[in].stop + 1;
          start = i;

          continue;
        }
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < safe.used);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      count = 0;

      do {
        count += fwrite_unlocked(string + start + count, 1, total - count, output);

        if (ferror_unlocked(output)) {
          return F_status_set_error(F_output);
        }

      } while (count < total);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_)

#if !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)
  f_status_t private_f_print_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const output) {

    register f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      ++total;

      if (i + 1 == stop || total == F_print_write_max_d) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;
      }
      else {
        ++i;
      }
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_raw_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)

#if !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)
  f_status_t private_f_print_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < safe.used);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_raw_safely_) || !defined(_di_f_print_except_dynamic_raw_) || !defined(_di_f_print_except_dynamic_partial_raw_)

#if !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)
  f_status_t private_f_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, FILE * const output) {

    f_array_length_t i = offset;
    f_array_length_t j = 0;
    f_array_length_t start = i;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_status_t status = F_none;
    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < stop) {

      while (j < except.used && except.array[j] < i) {
        ++j;
      } // while

      if (j < except.used && except.array[j] == i) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < safe.used);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    return F_none;
  }
#endif // !defined(_di_f_print_except_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_)

#if !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)
  f_status_t private_f_print_raw(const f_string_t string, const f_array_length_t length, FILE * const output) {

    f_array_length_t count = 0;

    clearerr_unlocked(output);

    if (length < F_print_write_max_d) {
      count = 0;

      do {
        count += fwrite_unlocked(string + count, 1, length - count, output);

        if (ferror_unlocked(output)) {
          return F_status_set_error(F_output);
        }

      } while (count < length);
    }
    else {
      for (f_array_length_t total = 0; ; total += F_print_write_max_d) {

        if (length - total > F_print_write_max_d) {
          count = 0;

          do {
            count += fwrite_unlocked(string + count, 1, F_print_write_max_d - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < F_print_write_max_d);
        }
        else {
          count = 0;

          do {
            count += fwrite_unlocked(string + count, 1, length - total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < length - total);

          break;
        }
      } // for
    }

    return F_none;
  }
#endif // !defined(_di_f_print_raw_) || !defined(_di_f_print_raw_dynamic_) || !defined(_di_f_print_raw_dynamic_partial_)

#if !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_)
  f_status_t private_f_print_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    f_status_t status = F_none;

    register f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < length) {

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        width = 1;
        safe.used = 0;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < safe.used);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      count = 0;

      do {
        count += fwrite_unlocked(string + start + count, 1, total - count, output);

        if (ferror_unlocked(output)) {
          return F_status_set_error(F_output);
        }

      } while (count < total);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_raw_safely_) || !defined(_di_f_print_raw_safely_dynamic_) || !defined(_di_f_print_raw_safely_dynamic_partial_)

#if !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)
  f_status_t private_f_print_safely(const f_string_t string, const f_array_length_t length, FILE * const output) {

    f_status_t status = F_none;

    register f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t total = 0;
    f_array_length_t count = 0;

    f_string_static_t safe = f_string_static_t_initialize;

    uint8_t width = 0;

    clearerr_unlocked(output);

    while (i < length) {

      if (string[i]) {
        width = macro_f_utf_character_t_width(string[i]);

        safe = private_f_print_safely_get(string + i, width);
      }
      else {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        start = ++i;

        continue;
      }

      if (safe.used) {
        if (total) {
          count = 0;

          do {
            count += fwrite_unlocked(string + start + count, 1, total - count, output);

            if (ferror_unlocked(output)) {
              return F_status_set_error(F_output);
            }

          } while (count < total);

          total = 0;
        }

        count = 0;

        do {
          count += fwrite_unlocked(safe.string + count, 1, safe.used - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        i += width;
        start = i;

        continue;
      }

      if (total + width >= F_print_write_max_d) {
        count = 0;

        do {
          count += fwrite_unlocked(string + start + count, 1, total - count, output);

          if (ferror_unlocked(output)) {
            return F_status_set_error(F_output);
          }

        } while (count < total);

        total = 0;
        start = i;
      }

      total += width;
      i += width;
    } // while

    if (total) {
      count = 0;

      do {
        count += fwrite_unlocked(string + start + count, 1, total - count, output);

        if (ferror_unlocked(output)) {
          return F_status_set_error(F_output);
        }

      } while (count < total);
    }

    return F_none;
  }
#endif // !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_dynamic_) || !defined(_di_f_print_safely_dynamic_partial_)

#if !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)
  const f_string_static_t private_f_print_safely_get(const f_string_t character, const f_array_length_t width_max) {

    if (character[0] == 0x7f) {
      return f_print_sequence_delete_s;
    }

    if (macro_f_utf_character_t_width_is(character[0])) {
      if (f_utf_is_valid(character, width_max) != F_true || f_utf_is_control(character, width_max)) {
        return f_print_sequence_unknown_s;
      }

      return f_string_empty_s;
    }

    if (character[0] > 0x1f) {
      return f_string_empty_s;
    }

    return f_print_sequence_set_control_s[character[0]];
  }
#endif // !defined(_di_f_print_character_safely_get_) || !defined(_di_f_print_dynamic_partial_safely_) || !defined(_di_f_print_dynamic_safely_) || !defined(_di_f_print_except_dynamic_partial_safely_) || !defined(_di_f_print_except_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_safely_) || !defined(_di_f_print_except_in_dynamic_partial_safely_) || !defined(_di_f_print_except_in_safely_) || !defined(_di_f_print_except_safely_) || !defined(_di_f_print_safely_) || !defined(_di_f_print_safely_terminated_) || !defined(_di_f_print_to_dynamic_partial_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_safely_)

#if !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)
  f_status_t private_f_print_terminated(const f_string_t string, FILE * const output) {

    const size_t length = strlen(string);
    f_array_length_t count = 0;

    clearerr_unlocked(output);

    do {
      count += fwrite_unlocked(string + count, 1, length - count, output);

      if (ferror_unlocked(output)) {
        return F_status_set_error(F_output);
      }

    } while (count < length);

    return F_none;
  }
#endif // !defined(_di_f_print_terminated_) || !defined(_di_f_print_raw_terminated_)

#ifdef __cplusplus
} // extern "C"
#endif
