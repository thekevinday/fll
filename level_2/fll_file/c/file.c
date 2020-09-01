#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_error_print_
  f_return_status fll_file_error_print(FILE *file, const fl_color_context_t context, const f_string_t function_name, const f_string_t file_name, const f_status_t status) {

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      fl_color_print_line(file, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory.");
    }
    else if (status == F_file_closed) {
      fl_color_print(file, context.error, context.reset, "INTERNAL ERROR: The file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "' is no longer open.");
    }
    else if (status == F_file_seek) {
      fl_color_print(file, context.error, context.reset, "ERROR: A seek error occurred while accessing the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_file_read) {
      fl_color_print(file, context.error, context.reset, "ERROR: A read error occurred while accessing the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_file_found_not) {
      fl_color_print(file, context.error, context.reset, "ERROR: Unable to find the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_file_open) {
      fl_color_print(file, context.error, context.reset, "ERROR: Unable to open the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_file_descriptor) {
      fl_color_print(file, context.error, context.reset, "ERROR: File descriptor error while trying to open the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_parameter) {
      fl_color_print(file, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(file, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(file, context.error, context.reset, ".");
    }
    else if (status == F_number_overflow) {
      fl_color_print(file, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == F_number_underflow) {
      fl_color_print(file, context.error, context.reset, "ERROR: Integer underflow while trying to buffer the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else {
      return F_false;
    }

    return F_true;
  }
#endif // _di_fll_file_error_print_

#ifdef __cplusplus
} // extern "C"
#endif
