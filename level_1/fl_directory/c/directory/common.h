/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project directory.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _FL_directory_common_h
#define _FL_directory_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An association of a path and a status code.
 *
 * The allocation macros apply to the path.
 *
 * depth_max:
 *   The max recursion depth.
 * size_block:
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * flag:
 *   If f_file_stat_flag_exclusive_e, will fail when file already exists.
 *   If not f_file_stat_flag_exclusive_e, will not fail if file already exists (existing file will be replaced).
 *
 *   If f_file_stat_flag_reference_e, will operate directly on a link rather than what it references.
 *   If not f_file_stat_flag_reference_e, will dereference any links.
 *
 *   For clone operations:
 *     - If f_file_stat_flag_group_e or f_file_stat_flag_owner_e, will copy the owner and group ids.
 *     - If neither f_file_stat_flag_group_e nor f_file_stat_flag_owner_e, will not copy the owner and group ids.
 *     (In both cases for a clone operation, the file mode is copied.)
 * output:
 *   Set to -1 to not print on successful operation.
 *   Set to a valid file descriptor to print to on successful operation.
 *   This is passed to the verbose function if that function pointer is not -1.
 * verbose:
 *   Set to 0 to not print on successful operation.
 *   Set to address of a function to be called for printing such that:
 *     - The first parameter represents the output file type.
 *     - The second parameter represents the source string.
 *     - The third parameter represents the destination string.
 * failures:
 *   A list of paths and their respective status codes for clone failures.
 *   If 0, then this and statuses are ignored.
 */
#ifndef _di_fl_directory_recurse_t_
  #define FL_directory_recurse_depth_max_d 65535

  typedef struct {
    f_number_unsigned_t depth_max;
    f_number_unsigned_t size_block;

    uint8_t flag;
    f_file_t output;

    void (*verbose)(const f_file_t, const f_string_static_t, const f_string_static_t);

    f_directory_statuss_t *failures;
  } fl_directory_recurse_t;

  #define fl_directory_recurse_t_initialize { FL_directory_recurse_depth_max_d, F_file_default_read_size_d, 0, macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), 0, 0 }

  #define macro_fl_directory_recurse_t_initialize(depth_max, size_block, flag, output, verbose, failures) { \
    depth_max, \
    size_block, \
    flag, \
    output, \
    verbose, \
    failures \
  }
#endif // _di_fl_directory_recurse_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_common_h
