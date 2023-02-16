#include "../fake.h"
#include "print-error.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_error_argument_invalid_section_
  f_status_t fake_make_print_error_argument_invalid_section(fake_setting_t * const setting, const fl_print_t print, const f_console_parameters_t parameters, const f_array_length_t index) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe argument '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, parameters.arguments.array[index], print.notable);
    fl_print_format("%[' is not a valid section name.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_argument_invalid_section_

#ifndef _di_fake_make_print_error_define_invalid_character_
  f_status_t fake_make_print_error_define_invalid_character(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QInvalid characters in the define setting name '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) are allowed.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_define_invalid_character_

#ifndef _di_fake_make_print_error_fakefile_item_missing_
  f_status_t fake_make_print_error_fakefile_item_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t item) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe fakefile '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, fakefile, print.notable);
    fl_print_format("%[' is missing the required '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, item, print.notable);
    fl_print_format("%[' item.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_error_fakefile_item_missing_

#ifdef __cplusplus
} // extern "C"
#endif
