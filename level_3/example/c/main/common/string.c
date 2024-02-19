#include "../example.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_example_program_version_s_
  const f_string_static_t example_program_version_s = macro_f_string_static_t_initialize_1(EXAMPLE_program_version_s, 0, EXAMPLE_program_version_s_length);
#endif // _di_example_program_version_s_

#ifndef _di_example_program_name_s_
  const f_string_static_t example_program_name_s = macro_f_string_static_t_initialize_1(EXAMPLE_program_name_s, 0, EXAMPLE_program_name_s_length);
  const f_string_static_t example_program_name_long_s = macro_f_string_static_t_initialize_1(EXAMPLE_program_name_long_s, 0, EXAMPLE_program_name_long_s_length);
#endif // _di_example_program_name_s_

#ifndef _di_example_parameter_s_
  const f_string_static_t example_short_example_s = macro_f_string_static_t_initialize_1(EXAMPLE_short_example_s, 0, EXAMPLE_short_example_s_length);

  const f_string_static_t example_long_example_s = macro_f_string_static_t_initialize_1(EXAMPLE_long_example_s, 0, EXAMPLE_long_example_s_length);
#endif // _di_example_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif
