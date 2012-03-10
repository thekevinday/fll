/* FLL - Level 0
 * Project:       Errors
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides error definitions
 */
#ifndef _F_errors_h
#define _F_errors_h

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_macro_test_for_basic_errors_
  #define f_macro_test_for_basic_errors(potential_error) \
    ( potential_error == f_critical          || \
      potential_error == f_unknown           || \
      potential_error == f_unsupported       || \
      potential_error == f_invalid_parameter || \
      potential_error == f_invalid_syntax    || \
      potential_error == f_invalid_data      || \
      potential_error == f_output_error      || \
      potential_error == f_does_not_exist    || \
      potential_error == f_failure)
#endif // _di_f_macro_test_for_basic_errors_

#ifndef _di_f_macro_test_for_allocation_errors_
  // FIXME: invalid_parameter was temporarily added here so that parameter checking could be corrected for all allocations and deallocations
  #define f_macro_test_for_allocation_errors(potential_error) \
    ( potential_error == f_allocation_error           || \
      potential_error == f_reallocation_error         || \
      potential_error == f_file_allocation_error      || \
      potential_error == f_file_reallocation_error    || \
      potential_error == f_directory_allocation_error || \
      potential_error == f_invalid_parameter || \
      potential_error == f_directory_reallocation_error )
#endif // _di_f_macro_test_for_allocation_errors_

#ifndef _di_f_macro_test_for_non_errors_
  #define f_macro_test_for_non_errors(potential_error) \
    ( potential_error == f_true                     || \
      potential_error == f_false                    || \
      potential_error == f_warn                     || \
      potential_error == f_no_data                  || \
      potential_error == f_no_data_on_eos           || \
      potential_error == f_no_data_on_eof           || \
      potential_error == f_no_data_on_stop          || \
      potential_error == f_none_on_eof              || \
      potential_error == f_none_on_eos              || \
      potential_error == f_none_on_stop             || \
      potential_error == f_less_than                || \
      potential_error == f_equal_to                 || \
      potential_error == f_not_equal_to             || \
      potential_error == f_greater_than             || \
      potential_error == f_none )
#endif // _di_f_macro_test_for_non_errors_

#ifndef _di_macro_f_test_for_file_errors_
  #define f_macro_test_for_file_errors(potential_error) \
    ( potential_error == f_file_seek_error        || \
      potential_error == f_file_read_error        || \
      potential_error == f_file_write_error       || \
      potential_error == f_file_flush_error       || \
      potential_error == f_file_purge_error       || \
      potential_error == f_file_open_error        || \
      potential_error == f_file_close_error       || \
      potential_error == f_file_synchronize_error || \
      potential_error == f_file_descriptor_error  || \
      potential_error == f_file_not_found         || \
      potential_error == f_file_is_empty          || \
      potential_error == f_file_not_open )
#endif // _di_f_macro_test_for_file_errors_

#ifndef _di_f_macro_test_for_directory_errors_
  #define f_macro_test_for_directory_errors(parameter) \
    ( potential_error == f_directory_seek_error        || \
      potential_error == f_directory_read_error        || \
      potential_error == f_directory_write_error       || \
      potential_error == f_directory_flush_error       || \
      potential_error == f_directory_purge_error       || \
      potential_error == f_directory_open_error        || \
      potential_error == f_directory_close_error       || \
      potential_error == f_directory_synchronize_error || \
      potential_error == f_directory_descriptor_error  || \
      potential_error == f_directory_not_found         || \
      potential_error == f_directory_is_empty          || \
      potential_error == f_directory_not_open )
#endif // _di_f_macro_test_for_directory_errors_

// use of an enumerator makes more sense here than explicitly defining every error code
enum {
  #ifndef _di_f_error_booleans_
    f_false,
    f_true,
  #endif // _di_f_error_booleans_

  #ifndef _di_f_error_basic_
    f_none,
    f_dummy,             // to only be used as a placeholder
    f_warn,              // warning
    f_critical,
    f_unknown,           // For the "code should never get here" errors. (this is an EMERGENCY error)
    f_unsupported,
    f_invalid_parameter,
    f_invalid_syntax,
    f_invalid_data,
    f_no_data,           // warning
    f_output_error,
    f_does_not_exist,
    f_failure,
  #endif // _di_f_error_basic_

  #ifndef _di_f_error_digits_
    f_underflow,
    f_overflow,
    f_divide_by_zero,
    f_cannot_be_negative,
    f_cannot_be_positive,
    f_cannot_be_zero,
  #endif // _di_f_error_digits_

  #ifndef _di_f_error_buffers_
    f_no_data_on_eof,            // warning
    f_no_data_on_eos,            // warning
    f_no_data_on_stop,           // warning
    f_none_on_eof,               // warning
    f_none_on_eos,               // warning
    f_none_on_stop,              // "stop" location was reached
    f_error_on_eof,
    f_error_on_eos,
    f_error_on_stop,
    f_string_too_small,
    f_string_too_large,
    f_unterminated_nest,
    f_unterminated_nest_on_eos,
    f_unterminated_nest_on_eof,
    f_unterminated_nest_on_stop,
    f_unterminated_group,
    f_unterminated_group_on_eos,
    f_unterminated_group_on_eof,
    f_unterminated_group_on_stop,
  #endif // _di_f_error_buffers_

  #ifndef _di_f_error_allocation_
    f_allocation_error,
    f_reallocation_error,
  #endif // _di_f_error_allocation_

  #ifndef _di_f_error_fork_
    f_fork_failed,
  #endif // _di_f_error_fork_

  #ifndef _di_f_error_file_
    f_file_seek_error,
    f_file_read_error,
    f_file_write_error,
    f_file_flush_error,
    f_file_purge_error,
    f_file_open_error,
    f_file_close_error,
    f_file_synchronize_error,
    f_file_descriptor_error,
    f_file_not_found,
    f_file_is_empty,
    f_file_not_open,
    f_file_allocation_error,
    f_file_reallocation_error,
    f_file_stat_error,
    f_file_error,
  #endif // _di_f_error_file_

  // most of these are a guess until I get around to researching & implementing linux directory I/O
  #ifndef _di_f_error_directory_
    f_directory_read_error,
    f_directory_write_error,
    f_directory_flush_error,
    f_directory_purge_error,
    f_directory_open_error,
    f_directory_close_error,
    f_directory_synchronize_error,
    f_directory_descriptor_error,
    f_directory_not_found,
    f_directory_is_empty,
    f_directory_not_open,
    f_directory_allocation_error,
    f_directory_reallocation_error,
    f_directory_error,
  #endif // _di_f_error_directory_

  #ifndef _di_f_error_non_
    f_less_than,
    f_equal_to,
    f_not_equal_to,
    f_greater_than,
  #endif // _di_f_error_non_

  // required
  f_last_error_code
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_errors_h
