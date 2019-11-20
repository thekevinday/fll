#include <level_2/file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_error_print_
  f_return_status fll_file_error_print(FILE *file, const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status) {

    if (status == f_error_allocation || status == f_error_reallocation) {
      fl_color_print_line(file, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory.");
    }
    else if (status == f_file_not_open) {
      fl_color_print(file, context.error, context.reset, "INTERNAL ERROR: The file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "' is no longer open.");
    }
    else if (status == f_file_error_seek) {
      fl_color_print(file, context.error, context.reset, "ERROR: A seek error occurred while accessing the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_read) {
      fl_color_print(file, context.error, context.reset, "ERROR: A read error occurred while accessing the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_file_not_found) {
      fl_color_print(file, context.error, context.reset, "ERROR: Unable to find the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_open) {
      fl_color_print(file, context.error, context.reset, "ERROR: Unable to open the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_descriptor) {
      fl_color_print(file, context.error, context.reset, "ERROR: File descriptor error while trying to open the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_invalid_parameter) {
      fl_color_print(file, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(file, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(file, context.error, context.reset, ".");
    }
    else if (status == f_number_overflow) {
      fl_color_print(file, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else if (status == f_number_underflow) {
      fl_color_print(file, context.error, context.reset, "ERROR: Integer underflow while trying to buffer the file '");
      fl_color_print(file, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(file, context.error, context.reset, "'.");
    }
    else {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fll_file_error_print_

#ifdef __cplusplus
} // extern "C"
#endif
