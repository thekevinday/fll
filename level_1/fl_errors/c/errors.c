/* FLL - Level 1
 * Project:       Errors
 * Version:       0.4.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides error functions, such as those that translate error codes into strings.
 */
#include <level_1/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_errors_to_string_
  f_return_status fl_errors_to_string(const f_status error, f_string *string) {
    #ifndef _di_level_1_parameter_checking_
      if (string == f_null) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status umasked_error = f_error_unmask(error);

    switch (umasked_error) {
      #ifndef _di_fl_errors_booleans_
        case f_false:
          *string = "f_false";
          break;
        case f_true:
          *string = "f_true";
          break;
      #endif // _di_fl_errors_booleans_

      #ifndef _di_fl_errors_basic_
        case f_none:
          *string = "f_none";
          break;
        case f_dummy:
          *string = "f_dummy";
          break;
        case f_warn:
          *string = "f_warn";
          break;
        case f_critical:
          *string = "f_critical";
          break;
        case f_unknown:
          *string = "f_unknown";
          break;
        case f_unsupported:
          *string = "f_unsupported";
          break;
        case f_invalid_parameter:
          *string = "f_invalid_parameter";
          break;
        case f_invalid_syntax:
          *string = "f_invalid_syntax";
          break;
        case f_invalid_data:
          *string = "f_invalid_data";
          break;
        case f_no_data:
          *string = "f_no_data";
          break;
        case f_output_error:
          *string = "f_output_error";
          break;
        case f_does_not_exist:
          *string = "f_does_not_exist";
          break;
        case f_failure:
          *string = "f_failure";
          break;
      #endif // _di_fl_errors_basic_

      #ifndef _di_fl_errors_digits_
        case f_underflow:
          *string = "f_underflow";
          break;
        case f_overflow:
          *string = "f_overflow";
          break;
        case f_divide_by_zero:
          *string = "f_divide_by_zero";
          break;
        case f_cannot_be_negative:
          *string = "f_cannot_be_negative";
          break;
        case f_cannot_be_positive:
          *string = "f_cannot_be_positive";
          break;
        case f_cannot_be_zero:
          *string = "f_cannot_be_zero";
          break;
      #endif // _di_fl_errors_digits_

      #ifndef _di_fl_errors_buffers_
        case f_no_data_on_eof:
          *string = "f_no_data_on_eof";
          break;
        case f_no_data_on_eol:
          *string = "f_no_data_on_eol";
          break;
        case f_no_data_on_eos:
          *string = "f_no_data_on_eos";
          break;
        case f_no_data_on_stop:
          *string = "f_no_data_on_stop";
          break;
        case f_none_on_eof:
          *string = "f_none_on_eof";
          break;
        case f_none_on_eol:
          *string = "f_none_on_eol";
          break;
        case f_none_on_eos:
          *string = "f_none_on_eos";
          break;
        case f_none_on_stop:
          *string = "f_none_on_stop";
          break;
        case f_error_on_eof:
          *string = "f_error_on_eof";
          break;
        case f_error_on_eol:
          *string = "f_error_on_eol";
          break;
        case f_error_on_eos:
          *string = "f_error_on_eos";
          break;
        case f_error_on_stop:
          *string = "f_error_on_stop";
          break;
        case f_buffer_too_small:
          *string = "f_buffer_too_small";
          break;
        case f_buffer_too_large:
          *string = "f_buffer_too_large";
          break;
        case f_string_too_small:
          *string = "f_string_too_small";
          break;
        case f_string_too_large:
          *string = "f_string_too_large";
          break;
        case f_unterminated_nest:
          *string = "f_unterminated_nest";
          break;
        case f_unterminated_nest_on_eof:
          *string = "f_unterminated_nest_on_eof";
          break;
        case f_unterminated_nest_on_eol:
          *string = "f_unterminated_nest_on_eol";
          break;
        case f_unterminated_nest_on_eos:
          *string = "f_unterminated_nest_on_eos";
          break;
        case f_unterminated_nest_on_stop:
          *string = "f_unterminated_nest_on_stop";
          break;
        case f_unterminated_group:
          *string = "f_unterminated_group";
          break;
        case f_unterminated_group_on_eof:
          *string = "f_unterminated_group_on_eof";
          break;
        case f_unterminated_group_on_eol:
          *string = "f_unterminated_group_on_eol";
          break;
        case f_unterminated_group_on_eos:
          *string = "f_unterminated_group_on_eos";
          break;
        case f_unterminated_group_on_stop:
          *string = "f_unterminated_group_on_stop";
          break;
      #endif // _di_fl_errors_buffers_

      #ifndef _di_fl_errors_allocation_
        case f_allocation_error:
          *string = "f_allocation_error";
          break;
        case f_reallocation_error:
          *string = "f_reallocation_error";
          break;
      #endif // _di_fl_errors_allocation_

      #ifndef _di_fl_errors_fork_
        case f_fork_failed:
          *string = "f_fork_failed";
          break;
      #endif // _di_fl_errors_fork_

      #ifndef _di_fl_errors_file_
        case f_file_seek_error:
          *string = "f_file_seek_error";
          break;
        case f_file_read_error:
          *string = "f_file_read_error";
          break;
        case f_file_write_error:
          *string = "f_file_write_error";
          break;
        case f_file_flush_error:
          *string = "f_file_flush_error";
          break;
        case f_file_purge_error:
          *string = "f_file_purge_error";
          break;
        case f_file_open_error:
          *string = "f_file_open_error";
          break;
        case f_file_close_error:
          *string = "f_file_close_error";
          break;
        case f_file_synchronize_error:
          *string = "f_file_synchronize_error";
          break;
        case f_file_descriptor_error:
          *string = "f_file_descriptor_error";
          break;
        case f_file_not_found:
          *string = "f_file_not_found";
          break;
        case f_file_is_empty:
          *string = "f_file_is_empty";
          break;
        case f_file_not_open:
          *string = "f_file_not_open";
          break;
        case f_file_allocation_error:
          *string = "f_file_allocation_error";
          break;
        case f_file_reallocation_error:
          *string = "f_file_reallocation_error";
          break;
        case f_file_stat_error:
          *string = "f_file_stat_error";
          break;
        case f_file_error:
          *string = "f_file_error";
          break;
      #endif // _di_fl_errors_file_

      // most of these are a guess until I get around to researching & implementing linux directory I/O
      #ifndef _di_fl_errors_directory_
        case f_directory_read_error:
          *string = "f_directory_read_error";
          break;
        case f_directory_write_error:
          *string = "f_directory_write_error";
          break;
        case f_directory_flush_error:
          *string = "f_directory_flush_error";
          break;
        case f_directory_purge_error:
          *string = "f_directory_purge_error";
          break;
        case f_directory_open_error:
          *string = "f_directory_open_error";
          break;
        case f_directory_close_error:
          *string = "f_directory_close_error";
          break;
        case f_directory_synchronize_error:
          *string = "f_directory_synchronize_error";
          break;
        case f_directory_descriptor_error:
          *string = "f_directory_descriptor_error";
          break;
        case f_directory_not_found:
          *string = "f_directory_not_found";
          break;
        case f_directory_is_empty:
          *string = "f_directory_is_empty";
          break;
        case f_directory_not_open:
          *string = "f_directory_not_open";
          break;
        case f_directory_allocation_error:
          *string = "f_directory_allocation_error";
          break;
        case f_directory_reallocation_error:
          *string = "f_directory_reallocation_error";
          break;
        case f_directory_error:
          *string = "f_directory_error";
          break;
      #endif // _di_fl_errors_directory_

      #ifndef _di_fll_error_non_
        case f_less_than:
          *string = "f_less_than";
          break;
        case f_equal_to:
          *string = "f_equal_to";
          break;
        case f_not_equal_to:
          *string = "f_not_equal_to";
          break;
        case f_greater_than:
          *string = "f_greater_than";
          break;
      #endif // _di_fl_errors_non_

      default:
        *string = f_null;
        return f_invalid_data;
    }

    return f_none;
  }
#endif // _di_fl_errors_to_string_

#ifndef _di_fl_errors_is_error_
  f_return_status fl_errors_is_error(const f_status error) {
    if (fl_errors_is_fine(error) == f_true) {
      return f_false;
    } else if (fl_errors_is_warning(error) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fl_errors_is_error_

#ifndef _di_fl_errors_is_warning_
  f_return_status fl_errors_is_warning(const f_status error) {
    switch (error) {
      #ifndef _di_fl_errors_basic_
        case f_no_data:
          return f_true;
      #endif // _di_fl_errors_basic_

      #ifndef _di_f_errors_buffers_
        case f_no_data_on_eof:
          return f_true;
        case f_no_data_on_eol:
          return f_true;
        case f_no_data_on_eos:
          return f_true;
        case f_no_data_on_stop:
          return f_true;
        case f_none_on_eof:
          return f_true;
        case f_none_on_eol:
          return f_true;
        case f_none_on_eos:
          return f_true;
        case f_none_on_stop:
          return f_true;
      #endif // _di_f_errors_buffers_
    }

    return f_false;
  }
#endif // _di_fl_errors_is_warning_

#ifndef _di_fl_errors_is_fine_
  f_return_status fl_errors_is_fine(const f_status error) {
    switch (error) {
      #ifndef _di_fl_errors_booleans_
        case f_false:
          return f_true;
        case f_true:
          return f_true;
      #endif // _di_fl_errors_booleans_

      #ifndef _di_fl_errors_basic_
        case f_none:
          return f_true;
        case f_dummy:
          return f_true;
      #endif // _di_fl_errors_basic_

      #ifndef _di_fll_error_non_
        case f_less_than:
          return f_true;
        case f_equal_to:
          return f_true;
        case f_not_equal_to:
          return f_true;
        case f_greater_than:
          return f_true;
      #endif // _di_fl_errors_non_
    }

    return f_false;
  }
#endif // _di_fl_errors_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif
