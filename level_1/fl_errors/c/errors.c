/* FLL - Level 1
 * Project:       Errors
 * Version:       0.3.x
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
      if (string == f_null) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    switch(error){
      #ifndef _di_fl_errors_booleans_
        case f_false:
          *string = "false";
          break;
        case f_true:
          *string = "true";
          break;
      #endif // _di_fl_errors_booleans_

      #ifndef _di_fl_errors_basic_
        case f_none:
          *string = "none";
          break;
        case f_dummy:
          *string = "dummy";
          break;
        case f_warn:
          *string = "warn";
          break;
        case f_critical:
          *string = "critical";
          break;
        case f_unknown:
          *string = "unknown";
          break;
        case f_unsupported:
          *string = "unsupported";
          break;
        case f_invalid_parameter:
          *string = "invalid parameter";
          break;
        case f_invalid_syntax:
          *string = "invalid syntax";
          break;
        case f_invalid_data:
          *string = "invalid data";
          break;
        case f_no_data:
          *string = "no data";
          break;
        case f_output_error:
          *string = "output error";
          break;
        case f_does_not_exist:
          *string = "does not exist";
          break;
        case f_failure:
          *string = "failure";
          break;
      #endif // _di_fl_errors_basic_

      #ifndef _di_fl_errors_digits_
        case f_underflow:
          *string = "underflow";
          break;
        case f_overflow:
          *string = "overflow";
          break;
        case f_divide_by_zero:
          *string = "divide_by_zero";
          break;
        case f_cannot_be_negative:
          *string = "cannot_be_negative";
          break;
        case f_cannot_be_positive:
          *string = "cannot_be_positive";
          break;
        case f_cannot_be_zero:
          *string = "cannot_be_zero";
          break;
      #endif // _di_fl_errors_digits_

      #ifndef _di_fl_errors_buffers_
        case f_no_data_on_eof:
          *string = "no data on eof";
          break;
        case f_no_data_on_eos:
          *string = "no data on eos";
          break;
        case f_no_data_on_stop:
          *string = "no data on stop";
          break;
        case f_none_on_eof:
          *string = "none on eof";
          break;
        case f_none_on_eos:
          *string = "none on eos";
          break;
        case f_none_on_stop:
          *string = "none on stop";
          break;
        case f_error_on_eof:
          *string = "error on eof";
          break;
        case f_error_on_eos:
          *string = "error on eos";
          break;
        case f_error_on_stop:
          *string = "error on stop";
          break;
        case f_buffer_too_small:
          *string = "buffer too small";
          break;
        case f_buffer_too_large:
          *string = "buffer too large";
          break;
        case f_string_too_small:
          *string = "string too small";
          break;
        case f_string_too_large:
          *string = "string too large";
          break;
        case f_unterminated_nest:
          *string = "unterminated nest";
          break;
        case f_unterminated_nest_on_eos:
          *string = "unterminated nest on eos";
          break;
        case f_unterminated_nest_on_eof:
          *string = "unterminated nest on eof";
          break;
        case f_unterminated_nest_on_stop:
          *string = "unterminated nest on stop";
          break;
        case f_unterminated_group:
          *string = "unterminated group";
          break;
        case f_unterminated_group_on_eos:
          *string = "unterminated group on eos";
          break;
        case f_unterminated_group_on_eof:
          *string = "unterminated group on eof";
          break;
        case f_unterminated_group_on_stop:
          *string = "unterminated group on_ top";
          break;
      #endif // _di_fl_errors_buffers_

      #ifndef _di_fl_errors_allocation_
        case f_allocation_error:
          *string = "allocation error";
          break;
        case f_reallocation_error:
          *string = "reallocation error";
          break;
      #endif // _di_fl_errors_allocation_

      #ifndef _di_fl_errors_fork_
        case f_fork_failed:
          *string = "fork failed";
          break;
      #endif // _di_fl_errors_fork_

      #ifndef _di_fl_errors_file_
        case f_file_seek_error:
          *string = "file seek error";
          break;
        case f_file_read_error:
          *string = "file read error";
          break;
        case f_file_write_error:
          *string = "file write error";
          break;
        case f_file_flush_error:
          *string = "file flush error";
          break;
        case f_file_purge_error:
          *string = "file purge error";
          break;
        case f_file_open_error:
          *string = "file open error";
          break;
        case f_file_close_error:
          *string = "file close error";
          break;
        case f_file_synchronize_error:
          *string = "file synchronize error";
          break;
        case f_file_descriptor_error:
          *string = "file descriptor error";
          break;
        case f_file_not_found:
          *string = "file not found";
          break;
        case f_file_is_empty:
          *string = "file is empty";
          break;
        case f_file_not_open:
          *string = "file not open";
          break;
        case f_file_allocation_error:
          *string = "file allocation error";
          break;
        case f_file_reallocation_error:
          *string = "file reallocation error";
          break;
        case f_file_stat_error:
          *string = "file stat error";
          break;
        case f_file_error:
          *string = "file error";
          break;
      #endif // _di_fl_errors_file_

      // most of these are a guess until I get around to researching & implementing linux directory I/O
      #ifndef _di_fl_errors_directory_
        case f_directory_read_error:
          *string = "directory read error";
          break;
        case f_directory_write_error:
          *string = "directory write error";
          break;
        case f_directory_flush_error:
          *string = "directory flush error";
          break;
        case f_directory_purge_error:
          *string = "directory purge error";
          break;
        case f_directory_open_error:
          *string = "directory open error";
          break;
        case f_directory_close_error:
          *string = "directory close error";
          break;
        case f_directory_synchronize_error:
          *string = "directory synchronize error";
          break;
        case f_directory_descriptor_error:
          *string = "directory descriptor error";
          break;
        case f_directory_not_found:
          *string = "directory not found";
          break;
        case f_directory_is_empty:
          *string = "directory is empty";
          break;
        case f_directory_not_open:
          *string = "directory not open";
          break;
        case f_directory_allocation_error:
          *string = "directory allocation error";
          break;
        case f_directory_reallocation_error:
          *string = "directory reallocation error";
          break;
        case f_directory_error:
          *string = "directory error";
          break;
      #endif // _di_fl_errors_directory_

      #ifndef _di_fll_error_non_
        case f_less_than:
          *string = "less than";
          break;
        case f_equal_to:
          *string = "equal to";
          break;
        case f_not_equal_to:
          *string = "not equal to";
          break;
        case f_greater_than:
          *string = "greater than";
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
    if (fl_errors_is_okay(error) == f_true) {
      return f_false;
    } else if (fl_errors_is_warning(error) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fl_errors_is_error_

#ifndef _di_fl_errors_is_warning_
  f_return_status fl_errors_is_warning(const f_status error) {
    switch(error){
      #ifndef _di_fl_errors_basic_
        case f_no_data:
          return f_true;
      #endif // _di_fl_errors_basic_

      #ifndef _di_f_errors_buffers_
        case f_no_data_on_eof:
          return f_true;
        case f_no_data_on_eos:
          return f_true;
        case f_no_data_on_stop:
          return f_true;
        case f_none_on_eof:
          return f_true;
        case f_none_on_eos:
          return f_true;
        case f_none_on_stop:
          return f_true;
      #endif // _di_f_errors_buffers_

      default:
        return f_false;
    }

    return f_unknown;
  }
#endif // _di_fl_errors_is_warning_

#ifndef _di_fl_errors_is_okay_
  // Returns true or false depending on whether the standard context of the error code represents an normal return status and not an error.
  // Keep in mind that many of the error codes are context-specific and may be reported as an "okay" here when it is in fact not okay.
  f_return_status fl_errors_is_okay(const f_status error) {
    switch(error){
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

      default:
        return f_false;
    }

    return f_unknown;
  }
#endif // _di_fl_errors_is_okay_

#ifdef __cplusplus
} // extern "C"
#endif
