#include "fss_status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_string_
  #ifndef _di_fll_fss_status_error_
    const f_string_t fll_fss_status_format_s = FLL_fss_status_format_s;
    const f_string_t fll_fss_status_format_eos_s = FLL_fss_status_format_eos_s;
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    const f_string_t fll_fss_status_accepted_invalid_s = FLL_fss_status_accepted_invalid_s;
    const f_string_t fll_fss_status_accepted_invalid_eos_s = FLL_fss_status_accepted_invalid_eos_s;
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    const f_string_t fll_fss_status_found_object_s = FLL_fss_status_found_object_s;
    const f_string_t fll_fss_status_found_content_s = FLL_fss_status_found_content_s;
    const f_string_t fll_fss_status_found_object_not_s = FLL_fss_status_found_object_not_s;
    const f_string_t fll_fss_status_found_content_not_s = FLL_fss_status_found_content_not_s;
    const f_string_t fll_fss_status_found_object_content_not_s = FLL_fss_status_found_object_content_not_s;
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    const f_string_t fll_fss_status_found_comment_s = FLL_fss_status_found_comment_s;
  #endif // _di_fll_fss_status_codes_

  const f_string_t fll_fss_status_status_code_first_s = FLL_fss_status_status_code_first_s;
  const f_string_t fll_fss_status_status_code_last_s = FLL_fss_status_status_code_last_s;
#endif // _di_FLL_fss_status_string_

#ifndef _di_fll_fss_status_string_from_
  f_status_t fll_fss_status_string_from(const f_string_t string, f_status_t *code) {
    #ifndef _di_level_2_parameter_checking_
      if (!code) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t length = strlen(string);

    if (!length) {
      return F_data_not;
    }

    // Numbers are not valid status code strings.
    status = f_conversion_character_is_decimal(string[0]);

    if (status == F_true) {
      return F_status_set_error(F_data);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    #ifndef _di_fll_fss_status_error_
      if (fl_string_compare(string, FLL_fss_status_format_s, length, FLL_fss_status_format_s_length) == F_equal_to) {
        *code = F_fss_format;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_format_eos_s, length, FLL_fss_status_format_eos_s_length) == F_equal_to) {
        *code = F_fss_format_eos;

        return F_none;
      }
    #endif // _di_fll_fss_status_error_

    #ifndef _di_fll_fss_status_warning_
      if (fl_string_compare(string, FLL_fss_status_accepted_invalid_s, length, FLL_fss_status_accepted_invalid_s_length) == F_equal_to) {
        *code = F_fss_accepted_invalid;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_accepted_invalid_eos_s, length, FLL_fss_status_accepted_invalid_eos_s_length) == F_equal_to) {
        *code = F_fss_accepted_invalid_eos;

        return F_none;
      }
    #endif // _di_fll_fss_status_warning_

    #ifndef _di_fll_fss_status_success_
      if (fl_string_compare(string, FLL_fss_status_found_object_s, length, FLL_fss_status_found_object_s_length) == F_equal_to) {
        *code = F_fss_found_object;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_found_content_s, length, FLL_fss_status_found_content_s_length) == F_equal_to) {
        *code = F_fss_found_content;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_found_object_not_s, length, FLL_fss_status_found_object_not_s_length) == F_equal_to) {
        *code = F_fss_found_object_not;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_found_content_not_s, length, FLL_fss_status_found_content_not_s_length) == F_equal_to) {
        *code = F_fss_found_content_not;

        return F_none;
      }

      if (fl_string_compare(string, FLL_fss_status_found_object_content_not_s, length, FLL_fss_status_found_object_content_not_s_length) == F_equal_to) {
        *code = F_fss_found_object_content_not;

        return F_none;
      }
    #endif // _di_fll_fss_status_success_

    #ifndef _di_fll_fss_status_codes_
      if (fl_string_compare(string, FLL_fss_status_found_comment_s, length, FLL_fss_status_found_comment_length_s) == F_equal_to) {
        *code = F_fss_found_object;

        return F_none;
      }
    #endif // _di_fll_fss_status_codes_

    if (fl_string_compare(string, FLL_fss_status_status_code_first_s, length, FLL_fss_status_status_code_first_s_length) == F_equal_to) {
      *code = F_fss_status_code_first;

      return F_none;
    }

    if (fl_string_compare(string, FLL_fss_status_status_code_last_s, length, FLL_fss_status_status_code_last_s_length) == F_equal_to) {
      *code = F_fss_status_code_last;

      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fll_fss_status_string_from_

#ifndef _di_fll_fss_status_string_to_
  f_status_t fll_fss_status_string_to(const f_status_t code, f_string_t *string) {
    #ifndef _di_level_2_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_fll_fss_status_error_
        case F_fss_format:
          *string = FLL_fss_status_format_s;
          break;
        case F_fss_format_eos:
          *string = FLL_fss_status_format_eos_s;
          break;
      #endif // _di_fll_fss_status_error_

      #ifndef _di_fll_fss_status_warning_
        case F_fss_accepted_invalid:
          *string = FLL_fss_status_accepted_invalid_s;
          break;
        case F_fss_accepted_invalid_eos:
          *string = FLL_fss_status_accepted_invalid_eos_s;
          break;
      #endif // _di_fll_fss_status_warning_

      #ifndef _di_fll_fss_status_success_
        case F_fss_found_object:
          *string = FLL_fss_status_found_object_s;
          break;
        case F_fss_found_content:
          *string = FLL_fss_status_found_content_s;
          break;
        case F_fss_found_object_not:
          *string = FLL_fss_status_found_object_not_s;
          break;
        case F_fss_found_content_not:
          *string = FLL_fss_status_found_content_not_s;
          break;
        case F_fss_found_object_content_not:
          *string = FLL_fss_status_found_object_content_not_s;
          break;
      #endif // _di_fll_fss_status_success_

      #ifndef _di_fll_fss_status_codes_
        case F_fss_found_comment:
          *string = FLL_fss_status_found_comment_s;
          break;
      #endif // _di_fll_fss_status_codes_

      case F_fss_status_code_first:
        *string = FLL_fss_status_status_code_first_s;
        break;

      case F_fss_status_code_last:
        *string = FLL_fss_status_status_code_last_s;
        break;

      default:
        return f_status_string_to(code, string);
    }

    return F_none;
  }
#endif // _di_fll_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif
