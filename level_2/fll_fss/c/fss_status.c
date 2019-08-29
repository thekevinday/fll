#include <level_2/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_from_string_
  f_return_status fll_fss_status_from_string(const f_string string, f_status *error) {
    #ifndef _di_level_1_parameter_checking_
      if (error == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_string_length length = strlen(string);

    #ifndef _di_fll_fss_status_error_
      if (fl_compare_strings(string, fll_fss_status_string_invalid_format, length, fll_fss_status_string_invalid_format_length) == f_equal_to) {
        *error = fl_fss_invalid_format;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_invalid_format_eos, length, fll_fss_status_string_invalid_format_eos_length) == f_equal_to) {
        *error = fl_fss_invalid_format_eos;
        return f_none;
      }
    #endif // _di_fll_fss_status_error_

    #ifndef _di_fll_fss_status_warning_
      if (fl_compare_strings(string, fll_fss_status_string_no_header, length, fll_fss_status_string_no_header_length) == f_equal_to) {
        *error = fl_fss_no_header;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_accepted_but_invalid, length, fll_fss_status_string_accepted_but_invalid_length) == f_equal_to) {
        *error = fl_fss_accepted_but_invalid;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_no_header_eos, length, fll_fss_status_string_no_header_eos_length) == f_equal_to) {
        *error = fl_fss_no_header_eos;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_accepted_but_invalid_eos, length, fll_fss_status_string_accepted_but_invalid_eos_length) == f_equal_to) {
        *error = fl_fss_accepted_but_invalid_eos;
        return f_none;
      }
    #endif // _di_fll_fss_status_warning_

    #ifndef _di_fll_fss_status_success_
      if (fl_compare_strings(string, fll_fss_status_string_found_object, length, fll_fss_status_string_found_object_length) == f_equal_to) {
        *error = fl_fss_found_object;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_found_content, length, fll_fss_status_string_found_content_length) == f_equal_to) {
        *error = fl_fss_found_content;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_found_no_object, length, fll_fss_status_string_found_no_object_length) == f_equal_to) {
        *error = fl_fss_found_no_object;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_found_no_content, length, fll_fss_status_string_found_no_content_length) == f_equal_to) {
        *error = fl_fss_found_no_content;
        return f_none;
      }

      if (fl_compare_strings(string, fll_fss_status_string_found_object_no_content, length, fll_fss_status_string_found_object_no_content_length) == f_equal_to) {
        *error = fl_fss_found_object_no_content;
        return f_none;
      }
    #endif // _di_fll_fss_status_success_

    if (fl_compare_strings(string, fll_fss_status_string_last_error_code, length, fll_fss_status_string_last_error_code_length) == f_equal_to) {
      *error = f_last_status_code;
      return f_none;
    }

    return f_invalid_data;
  }
#endif // _di_fll_fss_status_from_string_

#ifndef _di_fll_fss_status_to_string_
  f_return_status fll_fss_status_to_string(const f_status error, f_string *string) {
    #ifndef _di_level_2_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status unmasked_error = f_status_set_fine(error);

    switch (unmasked_error) {
      #ifndef _di_fll_fss_status_error_
        case fl_fss_invalid_format:
          *string = fll_fss_status_string_invalid_format;
          break;
        case fl_fss_invalid_format_eos:
          *string = fll_fss_status_string_invalid_format_eos;
          break;
      #endif // _di_fll_fss_status_error_

      #ifndef _di_fll_fss_status_warning_
        case fl_fss_no_header:
          *string = fll_fss_status_string_no_header;
          break;
        case fl_fss_accepted_but_invalid:
          *string = fll_fss_status_string_accepted_but_invalid;
          break;
        case fl_fss_no_header_eos:
          *string = fll_fss_status_string_no_header_eos;
          break;
        case fl_fss_accepted_but_invalid_eos:
          *string = fll_fss_status_string_accepted_but_invalid_eos;
          break;
      #endif // _di_fll_fss_status_warning_

      #ifndef _di_fll_fss_status_success_
        case fl_fss_found_object:
          *string = fll_fss_status_string_found_object;
          break;
        case fl_fss_found_content:
          *string = fll_fss_status_string_found_content;
          break;
        case fl_fss_found_no_object:
          *string = fll_fss_status_string_found_no_object;
          break;
        case fl_fss_found_no_content:
          *string = fll_fss_status_string_found_no_content;
          break;
        case fl_fss_found_object_no_content:
          *string = fll_fss_status_string_found_object_no_content;
          break;
      #endif // _di_fll_fss_status_success_

      case fl_fss_last_error_code:
        *string = fll_fss_status_string_last_error_code;
        break;
    default:
        return fl_status_to_string(error, string);
    }

    return f_none;
  }
#endif // _di_fll_status_to_string_

#ifndef _di_fll_fss_status_is_error_
  f_return_status fll_fss_status_is_error(const f_status error) {
    if (fll_fss_status_is_fine(error) == f_true) {
      return f_false;
    }
    else if (fll_fss_status_is_warning(error) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fll_fss_status_is_error_

#ifndef _di_fll_fss_status_is_warning_
  f_return_status fll_fss_status_is_warning(const f_status error) {
    switch (error) {
      #ifndef _di_fll_fss_status_basic_
        case f_no_data:
          return f_true;
      #endif // _di_fll_fss_status_basic_

      #ifndef _di_f_status_buffers_
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
      #endif // _di_f_status_buffers_
    }

    return f_false;
  }
#endif // _di_fll_fss_status_is_warning_

#ifndef _di_fll_fss_status_is_fine_
  f_return_status fll_fss_status_is_fine(const f_status error) {
    switch (error) {
      #ifndef _di_fll_fss_status_booleans_
        case f_false:
          return f_true;
        case f_true:
          return f_true;
      #endif // _di_fll_fss_status_booleans_

      #ifndef _di_fll_fss_status_basic_
        case f_none:
          return f_true;
        case f_dummy:
          return f_true;
      #endif // _di_fll_fss_status_basic_

      #ifndef _di_fll_error_non_
        case f_less_than:
          return f_true;
        case f_equal_to:
          return f_true;
        case f_not_equal_to:
          return f_true;
        case f_greater_than:
          return f_true;
      #endif // _di_fll_fss_status_non_
    }

    return f_false;
  }
#endif // _di_fll_fss_status_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif
