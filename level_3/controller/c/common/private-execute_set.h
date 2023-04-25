/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_execute_set_h
#define _PRIVATE_common_execute_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for passing execution arguments to the execute functions.
 *
 * parameter: All parameters sent to the program on execution.
 * as:        All special properties to apply, such as cpu affinity.
 */
#ifndef _di_controller_execute_set_t_
  typedef struct {
    fl_execute_parameter_t parameter;
    fl_execute_as_t as;
  } controller_execute_set_t;

  #define controller_execute_set_t_initialize_1 { \
    fl_execute_parameter_t_initialize, \
    fl_execute_as_t_initialize \
  }

  #define macro_controller_execute_set_t_initialize_1(option, wait, environment, signals, main, as) { \
    macro_fl_execute_parameter_t_initialize_1(option, wait, environment, signals, main), \
    as, \
  }
#endif // _di_controller_execute_set_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_execute_set_h
