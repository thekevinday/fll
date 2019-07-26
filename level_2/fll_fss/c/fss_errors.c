/* FLL - Level 2
 * Project:       FSS
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_2/fss_errors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_errors_to_string_
  f_return_status fll_fss_errors_to_string(const f_status error, f_string *string) {
    #ifndef _di_level_2_parameter_checking_
      if (string == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status unmasked_error = f_error_set_fine(error);

    switch (unmasked_error) {
      #ifndef _di_fll_fss_errors_error_
        case fl_fss_invalid_format:
          *string = "fl_fss_invalid_format";
          break;
        case fl_fss_invalid_format_eos:
          *string = "fl_fss_invalid_format_eos";
          break;
      #endif // _di_fll_fss_errors_error_

      #ifndef _di_fll_fss_errors_warning_
        case fl_fss_no_header:
          *string = "fl_fss_no_header";
          break;
        case fl_fss_accepted_but_invalid:
          *string = "fl_fss_accepted_but_invalid";
          break;
        case fl_fss_no_header_eos:
          *string = "fl_fss_no_header_eos";
          break;
        case fl_fss_accepted_but_invalid_eos:
          *string = "fl_fss_accepted_but_invalid_eos";
          break;
      #endif // _di_fll_fss_errors_warning_

      #ifndef _di_fll_fss_errors_success_
        case fl_fss_found_object:
          *string = "fl_fss_found_object";
          break;
        case fl_fss_found_content:
          *string = "fl_fss_found_content";
          break;
        case fl_fss_found_no_object:
          *string = "fl_fss_found_no_object";
          break;
        case fl_fss_found_no_content:
          *string = "fl_fss_found_no_content";
          break;
        case fl_fss_found_object_no_content:
          *string = "fl_fss_found_object_no_content";
          break;
      #endif // _di_fll_fss_errors_success_
    default:
        return fl_errors_to_string(error, string);
    }

    return f_none;
  }
#endif // _di_fll_errors_to_string_

#ifndef _di_fll_fss_errors_is_error_
  f_return_status fll_fss_errors_is_error(const f_status error) {
    if (fll_fss_errors_is_fine(error) == f_true) {
      return f_false;
    } else if (fll_fss_errors_is_warning(error) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fll_fss_errors_is_error_

#ifndef _di_fll_fss_errors_is_warning_
  f_return_status fll_fss_errors_is_warning(const f_status error) {
    switch (error) {
      #ifndef _di_fll_fss_errors_basic_
        case f_no_data:
          return f_true;
      #endif // _di_fll_fss_errors_basic_

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
    }

    return f_false;
  }
#endif // _di_fll_fss_errors_is_warning_

#ifndef _di_fll_fss_errors_is_fine_
  f_return_status fll_fss_errors_is_fine(const f_status error) {
    switch (error) {
      #ifndef _di_fll_fss_errors_booleans_
        case f_false:
          return f_true;
        case f_true:
          return f_true;
      #endif // _di_fll_fss_errors_booleans_

      #ifndef _di_fll_fss_errors_basic_
        case f_none:
          return f_true;
        case f_dummy:
          return f_true;
      #endif // _di_fll_fss_errors_basic_

      #ifndef _di_fll_error_non_
        case f_less_than:
          return f_true;
        case f_equal_to:
          return f_true;
        case f_not_equal_to:
          return f_true;
        case f_greater_than:
          return f_true;
      #endif // _di_fll_fss_errors_non_
    }

    return f_false;
  }
#endif // _di_fll_fss_errors_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif
