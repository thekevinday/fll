#include "print.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)
  f_return_status private_f_print(FILE *output, const f_string_t string, const f_string_length_t length) {

    if (!length) return F_data_not;

    for (register f_string_length_t i = 0; i < length; ++i) {
      if (!string[i]) continue;

      if (!fputc(string[i], output)) {
        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_) || !defined(_di_f_print_dynamic_) || !defined(_di_f_print_dynamic_partial_)

#if !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)
  f_return_status private_f_print_to(const int id, const f_string_t string, const f_string_length_t length) {

    if (!length) return F_data_not;

    for (register f_string_length_t i = 0; i < length; ++i) {
      if (!string[i]) continue;

      if (write(id, string + i, 1) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_output);
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_dynamic_to_) || !defined(_di_f_print_dynamic_partial_to_)

#ifdef __cplusplus
} // extern "C"
#endif
