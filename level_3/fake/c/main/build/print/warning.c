#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_warning_parameters_contradict_
  f_status_t fake_build_print_warning_parameters_contradict(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_static_t symbol_3, const f_string_static_t name_3) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_wrapped_parameters(setting, print, "The parameters ", symbol_1, name_1, " and ", symbol_2, name_2, " contradict, defaulting to ", symbol_3, name_3, 0);

    return F_none;
  }
#endif // _di_fake_build_print_warning_parameters_contradict_

#ifndef _di_fake_build_print_warning_setting_boolean_may_only_be_
  f_status_t fake_build_print_warning_setting_boolean_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%r%[%QThe setting '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' in the file '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
    fl_print_format("%[' may be either '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_common_setting_bool_yes_s, print.notable);
    fl_print_format("%[' or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_common_setting_bool_no_s, print.notable);
    fl_print_format("%[', defaulting to '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, default_to, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_build_print_warning_setting_boolean_may_only_be_

#ifndef _di_fake_build_print_warning_setting_both_cannot_using_language_
  f_status_t fake_build_print_warning_setting_both_cannot_when_language(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name_1, const f_string_static_t name_2, const f_string_static_t language) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_wrapped_parameters(setting, print, "The build settings ", f_string_empty_s, name_1, " and ", f_string_empty_s, name_2, " cannot both be false when using the language ", f_string_empty_s, language, 0);

    return F_none;
  }
#endif // _di_fake_build_print_warning_setting_both_cannot_using_language_

#ifndef _di_fake_build_print_warning_setting_language_may_only_be_
  f_status_t fake_build_print_warning_setting_language_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe setting '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' in the file '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
    fl_print_format("%[' may only be one of '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_language_bash_s, print.notable);
    fl_print_format("%[', '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_language_c_s, print.notable);
    fl_print_format("%[', or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_language_cpp_s, print.notable);
    fl_print_format("%[', defaulting to '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, default_to, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_build_print_warning_setting_language_may_only_be_

#ifndef _di_fake_build_print_warning_setting_required_default_to_
  f_status_t fake_build_print_warning_setting_required_default_to(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe setting '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' in the file '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
    fl_print_format("%[' is required, defaulting to '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, default_to, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_build_print_warning_setting_required_default_to_

#ifndef _di_fake_build_print_warning_setting_version_may_only_be_
  f_status_t fake_build_print_warning_setting_version_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe setting '%]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' in the file '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
    fl_print_format("%[' may only be one of '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_version_major_s, print.notable);
    fl_print_format("%[', '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_version_minor_s, print.notable);
    fl_print_format("%[', '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_version_micro_s, print.notable);
    fl_print_format("%[', or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_build_version_nano_s, print.notable);
    fl_print_format("%[', defaulting to '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, default_to, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_build_print_warning_setting_version_may_only_be_

#ifdef __cplusplus
} // extern "C"
#endif
