#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_error_print_
  f_return_status fll_file_error_print(FILE *file, const f_color_context_t context, const f_string_t function_name, const f_string_t file_name, const f_status_t status) {

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      fl_color_print_line(file, context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
    }
    else if (status == F_file_closed) {
      fl_color_print(file, context.set.error, "INTERNAL ERROR: The file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "' is no longer open.");
    }
    else if (status == F_file_seek) {
      fl_color_print(file, context.set.error, "ERROR: A seek error occurred while accessing the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_file_read) {
      fl_color_print(file, context.set.error, "ERROR: A read error occurred while accessing the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_file_found_not) {
      fl_color_print(file, context.set.error, "ERROR: Unable to find the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_file_open) {
      fl_color_print(file, context.set.error, "ERROR: Unable to open the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_file_descriptor) {
      fl_color_print(file, context.set.error, "ERROR: File descriptor error while trying to open the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_parameter) {
      fl_color_print(file, context.set.error, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(file, context.set.notable, "%s()", function_name);
      fl_color_print_line(file, context.set.error, ".");
    }
    else if (status == F_number_overflow) {
      fl_color_print(file, context.set.error, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else if (status == F_number_underflow) {
      fl_color_print(file, context.set.error, "ERROR: Integer underflow while trying to buffer the file '");
      fl_color_print(file, context.set.notable, "%s", file_name);
      fl_color_print_line(file, context.set.error, "'.");
    }
    else {
      return F_false;
    }

    return F_true;
  }
#endif // _di_fll_file_error_print_

#ifndef _di_fll_file_mode_set_all_
  f_return_status fll_file_mode_set_all(const f_string_t path, const mode_t mode, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_file_mode_set_all(path, mode, depth_max, 0);
  }
#endif // _di_fll_file_mode_set_all_

#ifndef _di_fll_file_move_
  f_return_status fll_file_move(const f_string_t source, const f_string_t destination, const f_string_length_t source_length, const f_string_length_t destination_length, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_2_parameter_checking_
      if (!source) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = f_file_rename(source, destination);

    if (F_status_set_fine(status) != F_mount) {
      if (status == F_none && recurse.output && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }

      return status;
    }

    status = f_file_is(source, f_file_type_directory, F_false);

    if (status == F_file_found_not) {
      return F_status_set_error(status);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_true) {
      status = fl_directory_clone(source, destination, source_length, destination_length, F_true, recurse);

      if (F_status_is_error(status)) {
        return status;
      }

      status = f_directory_remove(source, recurse.depth_max, F_false);

      if (status == F_none && recurse.output && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }
    }
    else {
      status = f_file_clone(source, destination, F_true, recurse.size_block, recurse.exclusive);

      if (F_status_is_error(status)) {
        return status;
      }

      status = f_file_remove(source);

      if (status == F_none && recurse.output && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }
    }

    return status;
  }
#endif // _di_fll_file_move_

#ifndef _di_fll_file_role_change_all_
  f_return_status fll_file_role_change_all(const f_string_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
      if (uid == -1 && gid == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_file_role_change_all(path, uid, gid, dereference, depth_max, 0);
  }
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif
