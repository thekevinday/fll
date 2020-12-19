/**
 * FLL - Level 1
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project execute.
 *
 * This is auto-included by execute.h and should not need to be explicitly included.
 */
#ifndef _FL_execute_common_h
#define _FL_execute_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for containing additional parameters for the execute functions that call the execv() family of functions.
 *
 * bitwise options:
 *   fl_execute_parameter_option_exit: use to desginate to exit after calling child otherwise child process will return.
 *   fl_execute_parameter_option_path: use to designate that this is a path to a program (such as '/bin/bash').
 *
 * option:  accepts the bitwise options
 * names:   the environment variable names, should have the same number of elements as values, set to 0 to not use.
 * values:  the environment variable values, should have the same number of elements as names, set to 0 to not use.
 * signals: the set of signals the child process should or should block, set to 0 to not use.
 * data:    the data to pipe to the child process, set to 0 to not use.
 */
#ifndef _di_fl_execute_parameter_t_
  #define fl_execute_parameter_option_exit 0x1
  #define fl_execute_parameter_option_path 0x2

  typedef struct {
    uint8_t option;

    const f_string_statics_t *names;
    const f_string_statics_t *values;
    const f_signal_how_t *signals;
    const f_string_static_t *data;
  } fl_execute_parameter_t;

  #define fl_execute_parameter_t_initialize { 0, 0, 0, 0, 0 }

  #define fl_macro_execute_parameter_t_initialize(option, names, values, signals, data) { option, names, values, signals, data }

  #define fl_execute_parameter_t_clear(set) \
    set.option = 0; \
    set.names = 0; \
    set.values = 0; \
    set.signals = 0; \
    set.data = 0;
#endif // _di_fl_execute_parameter_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_common_h
