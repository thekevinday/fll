#include <level_1/console.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _fl_console_parameter_to_number_signed_
  f_return_status fl_console_parameter_to_number_signed(const f_string argument, f_number_signed *number) {
    #ifndef _di_level_0_parameter_checking_
      if (argument == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (argument[0] == '\0') {
      return f_status_set_error(f_no_data);
    }

    f_string_location location = f_string_location_initialize;
    location.start = 0;
    location.stop = strlen(argument) - 1;

    return f_conversion_string_to_number_signed(argument, number, location);
  }
#endif // _fl_console_parameter_to_number_signed_

#ifndef _fl_console_parameter_to_number_unsigned_
  f_return_status fl_console_parameter_to_number_unsigned(const f_string argument, f_number_unsigned *number) {
    #ifndef _di_level_0_parameter_checking_
      if (argument == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (argument[0] == '\0') {
      return f_status_set_error(f_no_data);
    }

    f_string_location location = f_string_location_initialize;
    location.start = 0;
    location.stop = strlen(argument) - 1;

    return f_conversion_string_to_number_unsigned(argument, number, location);
  }
#endif // _fl_console_parameter_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif
