#include <level_2/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_from_string_
  f_return_status fll_fss_status_from_string(const f_string string, f_status *code) {
    #ifndef _di_level_1_parameter_checking_
      if (code == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    f_string_length length = strlen(string);

    if (length == 0) {
      return F_data_not;
    }

    // Numbers are not valid status code strings.
    if ((status = f_conversion_character_is_decimal(string[0])) == F_true) {
      return F_status_set_error(F_data);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    #ifndef _di_fll_fss_status_error_
      if (fl_string_compare(string, fll_fss_status_string_format, length, fll_fss_status_string_format_length) == F_equal_to) {
        *code = FL_fss_format;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_format_eos, length, fll_fss_status_string_format_eos_length) == F_equal_to) {
        *code = FL_fss_format_eos;
        return F_none;
      }
    #endif // _di_fll_fss_status_error_

    #ifndef _di_fll_fss_status_warning_
      if (fl_string_compare(string, fll_fss_status_string_header_not, length, fll_fss_status_string_header_not_length) == F_equal_to) {
        *code = FL_fss_header_not;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_accepted_invalid, length, fll_fss_status_string_accepted_invalid_length) == F_equal_to) {
        *code = FL_fss_accepted_invalid;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_header_not_eos, length, fll_fss_status_string_header_not_eos_length) == F_equal_to) {
        *code = FL_fss_header_not_eos;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_accepted_invalid_eos, length, fll_fss_status_string_accepted_invalid_eos_length) == F_equal_to) {
        *code = FL_fss_accepted_invalid_eos;
        return F_none;
      }
    #endif // _di_fll_fss_status_warning_

    #ifndef _di_fll_fss_status_success_
      if (fl_string_compare(string, fll_fss_status_string_found_object, length, fll_fss_status_string_found_object_length) == F_equal_to) {
        *code = FL_fss_found_object;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_found_content, length, fll_fss_status_string_found_content_length) == F_equal_to) {
        *code = FL_fss_found_content;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_found_object_not, length, fll_fss_status_string_found_object_not_length) == F_equal_to) {
        *code = FL_fss_found_object_not;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_found_content_not, length, fll_fss_status_string_found_content_not_length) == F_equal_to) {
        *code = FL_fss_found_content_not;
        return F_none;
      }

      if (fl_string_compare(string, fll_fss_status_string_found_object_content_not, length, fll_fss_status_string_found_object_content_not_length) == F_equal_to) {
        *code = FL_fss_found_object_content_not;
        return F_none;
      }
    #endif // _di_fll_fss_status_success_

    #ifndef _di_fll_fss_status_codes_
      if (fl_string_compare(string, fll_fss_status_string_found_comment, length, fll_fss_status_string_found_comment_length) == F_equal_to) {
        *code = FL_fss_found_object;
        return F_none;
      }
    #endif // _di_fll_fss_status_codes_

    if (fl_string_compare(string, fll_fss_status_string_status_code_first, length, fll_fss_status_string_status_code_first_length) == F_equal_to) {
      *code = FL_fss_status_code_first;
      return F_none;
    }

    if (fl_string_compare(string, fll_fss_status_string_status_code_last, length, fll_fss_status_string_status_code_last_length) == F_equal_to) {
      *code = FL_fss_status_code_last;
      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fll_fss_status_from_string_

#ifndef _di_fll_fss_status_to_string_
  f_return_status fll_fss_status_to_string(const f_status code, f_string *string) {
    #ifndef _di_level_2_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_fll_fss_status_error_
        case FL_fss_format:
          *string = fll_fss_status_string_format;
          break;
        case FL_fss_format_eos:
          *string = fll_fss_status_string_format_eos;
          break;
      #endif // _di_fll_fss_status_error_

      #ifndef _di_fll_fss_status_warning_
        case FL_fss_header_not:
          *string = fll_fss_status_string_header_not;
          break;
        case FL_fss_accepted_invalid:
          *string = fll_fss_status_string_accepted_invalid;
          break;
        case FL_fss_header_not_eos:
          *string = fll_fss_status_string_header_not_eos;
          break;
        case FL_fss_accepted_invalid_eos:
          *string = fll_fss_status_string_accepted_invalid_eos;
          break;
      #endif // _di_fll_fss_status_warning_

      #ifndef _di_fll_fss_status_success_
        case FL_fss_found_object:
          *string = fll_fss_status_string_found_object;
          break;
        case FL_fss_found_content:
          *string = fll_fss_status_string_found_content;
          break;
        case FL_fss_found_object_not:
          *string = fll_fss_status_string_found_object_not;
          break;
        case FL_fss_found_content_not:
          *string = fll_fss_status_string_found_content_not;
          break;
        case FL_fss_found_object_content_not:
          *string = fll_fss_status_string_found_object_content_not;
          break;
      #endif // _di_fll_fss_status_success_

      #ifndef _di_fll_fss_status_codes_
        case FL_fss_found_comment:
          *string = fll_fss_status_string_found_comment;
          break;
      #endif // _di_fll_fss_status_codes_

      case FL_fss_status_code_first:
        *string = fll_fss_status_string_status_code_first;
        break;

      case FL_fss_status_code_last:
        *string = fll_fss_status_string_status_code_last;
        break;

      default:
        return fl_status_to_string(code, string);
    }

    return F_none;
  }
#endif // _di_fll_status_to_string_

#ifndef _di_fll_fss_status_is_error_
  f_return_status fll_fss_status_is_error(const f_status code) {
    if (fll_fss_status_is_fine(code) == F_true) {
      return F_false;
    }
    else if (fll_fss_status_is_warning(code) == F_true) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_fll_fss_status_is_error_

#ifndef _di_fll_fss_status_is_warning_
  f_return_status fll_fss_status_is_warning(const f_status code) {
    switch (code) {
      #ifndef _di_fll_fss_status_basic_
        case F_data_not:
          return F_true;
      #endif // _di_fll_fss_status_basic_

      #ifndef _di_f_status_buffers_
        case F_data_no_eof:
          return F_true;
        case F_data_no_eos:
          return F_true;
        case F_data_no_stop:
          return F_true;
        case F_none_eof:
          return F_true;
        case F_none_eos:
          return F_true;
        case F_none_stop:
          return F_true;
      #endif // _di_f_status_buffers_
    }

    return F_false;
  }
#endif // _di_fll_fss_status_is_warning_

#ifndef _di_fll_fss_status_is_fine_
  f_return_status fll_fss_status_is_fine(const f_status code) {
    switch (code) {
      #ifndef _di_fll_fss_status_booleans_
        case F_false:
          return F_true;
        case F_true:
          return F_true;
      #endif // _di_fll_fss_status_booleans_

      #ifndef _di_fll_fss_status_basic_
        case F_none:
          return F_true;
        case F_dummy:
          return F_true;
      #endif // _di_fll_fss_status_basic_

      #ifndef _di_fll_error_non_
        case F_than_less:
          return F_true;
        case F_equal_to:
          return F_true;
        case F_equal_to_not:
          return F_true;
        case F_than_greater:
          return F_true;
      #endif // _di_fll_fss_status_non_
    }

    return F_false;
  }
#endif // _di_fll_fss_status_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif
