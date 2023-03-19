#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_context_important_simple_
  void fake_print_context_important_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    const fl_print_t custom = macro_fl_print_t_initialize(print.to, print.verbosity, 0, f_string_empty_s, f_string_empty_s, print.set->important, print.set->notable, print.set, 0);

    fake_print_context_simple(setting, custom, message);
  }
#endif // _di_fake_print_context_important_simple_

#ifndef _di_fake_print_context_simple_
  void fake_print_context_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    if (!setting) return;

    fll_print_format("%[%Q%S.%]%r", print.to, print.context, print.prefix, message, print.context, f_string_eol_s);
  }
#endif // _di_fake_print_context_simple_

#ifndef _di_fake_print_context_simple_variable_
  void fake_print_context_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_simple_variable_

#ifndef _di_fake_print_context_wrapped_number_
  void fake_print_context_wrapped_number(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_number_unsigned_t number, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%un%]", print.to, print.notable, number, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_number_

#ifndef _di_fake_print_context_wrapped_parameter_
  void fake_print_context_wrapped_parameter(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol, name, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_parameter_

#ifndef _di_fake_print_context_wrapped_parameter_value_
  void fake_print_context_wrapped_parameter_value(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t between, const f_string_static_t value, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol, name, print.notable);
    fl_print_format("%['%S'%]%r", print.to, print.context, between, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, value, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_parameter_value_

#ifndef _di_fake_print_context_wrapped_parameters_
  void fake_print_context_wrapped_parameters(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_t between_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_t between_2, const f_string_static_t symbol_3, const f_string_static_t name_3, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_1, name_1, print.notable);
    fl_print_format("%['%S'%]%r", print.to, print.context, between_1, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_2, name_2, print.notable);
    fl_print_format("%['%S'%]%r", print.to, print.context, between_2, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_3, name_3, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_parameters_

#ifndef _di_fake_print_context_wrapped_variable_
  void fake_print_context_wrapped_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_variable_

#ifndef _di_fake_print_context_wrapped_variables_
  void fake_print_context_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, first, print.notable);
    fl_print_format("%['%S'%]", print.to, print.context, between, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, second, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif
