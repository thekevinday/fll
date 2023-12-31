#include "fss_status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_string_
  #ifndef _di_fll_fss_status_error_
    const f_string_static_t fll_fss_status_format_s = macro_f_string_static_t_initialize_1(FLL_fss_status_format_s, 0, FLL_fss_status_format_s_length);
    const f_string_static_t fll_fss_status_format_eos_s = macro_f_string_static_t_initialize_1(FLL_fss_status_format_eos_s, 0, FLL_fss_status_format_eos_s_length);
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    const f_string_static_t fll_fss_status_accepted_invalid_s = macro_f_string_static_t_initialize_1(FLL_fss_status_accepted_invalid_s, 0, FLL_fss_status_accepted_invalid_s_length);
    const f_string_static_t fll_fss_status_accepted_invalid_eos_s = macro_f_string_static_t_initialize_1(FLL_fss_status_accepted_invalid_eos_s, 0, FLL_fss_status_accepted_invalid_eos_s_length);
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    const f_string_static_t fll_fss_status_found_content_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_content_s, 0, FLL_fss_status_found_content_s_length);
    const f_string_static_t fll_fss_status_found_content_not_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_content_not_s, 0, FLL_fss_status_found_content_not_s_length);
    const f_string_static_t fll_fss_status_found_object_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_object_s, 0, FLL_fss_status_found_object_s_length);
    const f_string_static_t fll_fss_status_found_object_content_not_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_object_content_not_s, 0, FLL_fss_status_found_object_content_not_s_length);
    const f_string_static_t fll_fss_status_found_object_not_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_object_not_s, 0, FLL_fss_status_found_object_not_s_length);
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    const f_string_static_t fll_fss_status_found_comment_s = macro_f_string_static_t_initialize_1(FLL_fss_status_found_comment_s, 0, FLL_fss_status_found_comment_s_length);
  #endif // _di_fll_fss_status_codes_

  const f_string_static_t fll_fss_status_status_code_first_s = macro_f_string_static_t_initialize_1(FLL_fss_status_status_code_first_s, 0, FLL_fss_status_status_code_first_s_length);
  const f_string_static_t fll_fss_status_status_code_last_s = macro_f_string_static_t_initialize_1(FLL_fss_status_status_code_last_s, 0, FLL_fss_status_status_code_last_s_length);
#endif // _di_FLL_fss_status_string_

#ifndef _di_fll_fss_status_string_from_
  f_status_t fll_fss_status_string_from(const f_string_static_t name, f_status_t * const code) {
    #ifndef _di_level_2_parameter_checking_
      if (!code) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_okay;

    if (!name.used) return F_data_not;

    // Numbers are not valid status code strings.
    status = f_conversion_character_is_decimal(name.string[0]);

    if (status == F_true) return F_status_set_error(F_data);
    if (F_status_is_error(status)) return status;

    #ifndef _di_fll_fss_status_error_
      if (f_compare_dynamic(name, fll_fss_status_format_s) == F_equal_to) {
        *code = F_fss_format;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_format_eos_s) == F_equal_to) {
        *code = F_fss_format_eos;

        return F_okay;
      }
    #endif // _di_fll_fss_status_error_

    #ifndef _di_fll_fss_status_warning_
      if (f_compare_dynamic(name, fll_fss_status_accepted_invalid_s) == F_equal_to) {
        *code = F_fss_accepted_invalid;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_accepted_invalid_eos_s) == F_equal_to) {
        *code = F_fss_accepted_invalid_eos;

        return F_okay;
      }
    #endif // _di_fll_fss_status_warning_

    #ifndef _di_fll_fss_status_success_
      if (f_compare_dynamic(name, fll_fss_status_found_object_s) == F_equal_to) {
        *code = F_fss_found_object;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_found_content_s) == F_equal_to) {
        *code = F_fss_found_content;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_found_object_not_s) == F_equal_to) {
        *code = F_fss_found_object_not;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_found_content_not_s) == F_equal_to) {
        *code = F_fss_found_content_not;

        return F_okay;
      }

      if (f_compare_dynamic(name, fll_fss_status_found_object_content_not_s) == F_equal_to) {
        *code = F_fss_found_object_content_not;

        return F_okay;
      }
    #endif // _di_fll_fss_status_success_

    #ifndef _di_fll_fss_status_codes_
      if (f_compare_dynamic(name, fll_fss_status_found_comment_s) == F_equal_to) {
        *code = F_fss_found_object;

        return F_okay;
      }
    #endif // _di_fll_fss_status_codes_

    if (f_compare_dynamic(name, fll_fss_status_status_code_first_s) == F_equal_to) {
      *code = F_fss_status_code_first;

      return F_okay;
    }

    if (f_compare_dynamic(name, fll_fss_status_status_code_last_s) == F_equal_to) {
      *code = F_fss_status_code_last;

      return F_okay;
    }

    return fl_status_string_from(name, code);
  }
#endif // _di_fll_fss_status_string_from_

#ifndef _di_fll_fss_status_string_to_
  f_status_t fll_fss_status_string_to(const f_status_t code, f_string_static_t * const name) {
    #ifndef _di_level_2_parameter_checking_
      if (!name) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_fll_fss_status_error_
        case F_fss_format:
          *name = fll_fss_status_format_s;
          break;

        case F_fss_format_eos:
          *name = fll_fss_status_format_eos_s;
          break;
      #endif // _di_fll_fss_status_error_

      #ifndef _di_fll_fss_status_warning_
        case F_fss_accepted_invalid:
          *name = fll_fss_status_accepted_invalid_s;
          break;

        case F_fss_accepted_invalid_eos:
          *name = fll_fss_status_accepted_invalid_eos_s;
          break;
      #endif // _di_fll_fss_status_warning_

      #ifndef _di_fll_fss_status_success_
        case F_fss_found_object:
          *name = fll_fss_status_found_object_s;
          break;

        case F_fss_found_content:
          *name = fll_fss_status_found_content_s;
          break;

        case F_fss_found_object_not:
          *name = fll_fss_status_found_object_not_s;
          break;

        case F_fss_found_content_not:
          *name = fll_fss_status_found_content_not_s;
          break;

        case F_fss_found_object_content_not:
          *name = fll_fss_status_found_object_content_not_s;
          break;
      #endif // _di_fll_fss_status_success_

      #ifndef _di_fll_fss_status_codes_
        case F_fss_found_comment:
          *name = fll_fss_status_found_comment_s;
          break;
      #endif // _di_fll_fss_status_codes_

      case F_fss_status_code_first:
        *name = fll_fss_status_status_code_first_s;
        break;

      case F_fss_status_code_last:
        *name = fll_fss_status_status_code_last_s;
        break;

      default:
        return f_status_string_to(code, name);
    }

    return F_okay;
  }
#endif // _di_fll_fss_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif
