/* FLL - Level 2
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_2/fss_errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_fss_errors_to_string_
  // Convert error codes to their string equivalents.
  f_return_status fll_fss_errors_to_string(const f_status error, f_string *string) {
    #ifndef _di_level_2_parameter_checking_
      if (string == f_null) return f_invalid_parameter;
    #endif // _di_level_2_parameter_checking_

    switch(error){
      #ifndef _di_fll_fss_errors_error_
        case fl_fss_invalid_format:
          *string = "fss invalid format";
          break;
        case fl_fss_invalid_format_eos:
          *string = "fss invalid format eos";
          break;
      #endif // _di_fll_fss_errors_error_

      #ifndef _di_fll_fss_errors_warning_
        case fl_fss_no_header:
          *string = "fss no header";
          break;
        case fl_fss_accepted_but_invalid:
          *string = "fss accepted but invalid";
          break;
        case fl_fss_no_header_eos:
          *string = "fss no header eos";
          break;
        case fl_fss_accepted_but_invalid_eos:
          *string = "fss accepted but invalid eos";
          break;
      #endif // _di_fll_fss_errors_warning_

      #ifndef _di_fll_fss_errors_success_
        case fl_fss_found_object:
          *string = "fss found object";
          break;
        case fl_fss_found_content:
          *string = "fss found content";
          break;
        case fl_fss_found_no_object:
          *string = "fss found no object";
          break;
        case fl_fss_found_no_content:
          *string = "fss found no content";
          break;
        case fl_fss_found_object_no_content:
          *string = "fss found object no content";
          break;
      #endif // _di_fll_fss_errors_success_
    default:
        return fl_errors_to_string(error, string);
    }

    return f_none;
  }
#endif // _di_fll_errors_to_string_

#ifdef __cplusplus
} // extern "C"
#endif
