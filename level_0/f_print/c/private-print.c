#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  f_return_status private_f_print(FILE *output, const f_string_t string, const f_string_length_t length) {

    if (!length) return F_data_not;

    for (register f_string_length_t i = 0; i < length; ++i) {
      if (string[i]) {
        if (!fputc(string[i], output)) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

#if !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)
  f_return_status private_f_print_except(FILE *output, const f_string_t string, const f_string_length_t length, const f_string_lengths_t except) {

    if (!length) return F_data_not;

    f_string_length_t j = 0;

    for (register f_string_length_t i = 0; i < length; ++i) {
      for (; j < except.used; j++) {
        if (except.array[j] >= i) break;
      } // for

      if (j < except.used && except.array[j] == i) continue;

      if (string[i]) {
        if (!fputc(string[i], output)) {
          return F_status_set_error(F_output);
        }
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_except_) || !defined(_di_f_print_except_dynamic_) || !defined(_di_f_print_except_dynamic_partial_)

#if !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)
  f_return_status private_f_print_to(const int id, const f_string_t string, const f_string_length_t length) {

    if (!length) return F_data_not;

    register f_string_length_t i = 0;
    f_string_length_t start = 0;
    f_string_length_t total = 0;

    for (; i < length; ++i) {

      if (string[i]) {
        total++;
        continue;
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupted);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      start = i + 1;
      total = 0;
    } // for

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)

#if !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)
  f_return_status private_f_print_to_except(const int id, const f_string_t string, const f_string_length_t length, const f_string_lengths_t except) {

    if (!length) return F_data_not;

    register f_string_length_t i = 0;
    f_string_length_t j = 0;
    f_string_length_t start = 0;
    f_string_length_t total = 0;

    for (; i < length; ++i) {

      for (; j < except.used; j++) {
        if (except.array[j] >= i) break;
      } // for

      if (j >= except.used || except.array[j] != i) {
        if (string[i]) {
          total++;
          continue;
        }
      }

      if (total) {
        if (write(id, string + start, total) == -1) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
          if (errno == EBADF) return F_status_set_error(F_file_descriptor);
          if (errno == EFAULT) return F_status_set_error(F_buffer);
          if (errno == EINTR) return F_status_set_error(F_interrupted);
          if (errno == EINVAL) return F_status_set_error(F_parameter);
          if (errno == EIO) return F_status_set_error(F_input_output);
          if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

          return F_status_set_error(F_output);
        }
      }

      start = i + 1;
      total = 0;
    } // for

    if (total) {
      if (write(id, string + start, total) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    }

    return F_none;
  }
#endif // !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)

#ifdef __cplusplus
} // extern "C"
#endif
