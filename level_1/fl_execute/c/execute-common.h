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
 * FL_execute_parameter_option_*:
 * - exit:       Used to desginate to exit after calling child otherwise child process will return.
 * - path:       Used to designate that the full path to the program is to be passed in argument[0] instead of the program name (such as '/bin/bash' instead of 'bash').
 * - return:     Used to designate that the parent process will immediately return instead of waiting for the child process to complete.
 * - session:    Start a new session, set the process of the child as the controlling terminal.
 * - terminal:   (Not Implemented) open() a terminal (tty) before executing. @todo determine if and how to setup the terminal properly (this needs research and planning and may require further structural changes).
 * - threadsafe: Used to designate that threadsafe functions are to be used (such as: f_thread_signal_mask instead of f_signal_mask).
 *
 * option:      Accepts the bitwise options
 * wait:        Represents options passed to waitpid(), such as WUNTRACED.
 * environment: The environment variable name and value pairs, set to 0 to not use.
 * signals:     The set of signals the child process should or should block, set to 0 to not use.
 * data:        The data to pipe to the child process, set to 0 to not use.
 */
#ifndef _di_fl_execute_parameter_t_
  #define FL_execute_parameter_option_exit_d        0x1
  #define FL_execute_parameter_option_path_d        0x2
  #define FL_execute_parameter_option_return_d      0x4
  #define FL_execute_parameter_option_session_d     0x8
  #define FL_execute_parameter_option_terminal_d    0x10
  #define FL_execute_parameter_option_threadsafe_d  0x20

  typedef struct {
    uint8_t option;
    int wait;

    const f_string_maps_t *environment;
    const f_signal_how_t *signals;
    const f_string_static_t *data;
  } fl_execute_parameter_t;

  #define fl_execute_parameter_t_initialize { 0, 0, 0, 0, 0 }

  #define macro_fl_execute_parameter_t_initialize(option, wait, environment, signals, data) { option, wait, environment, signals, data }

  #define macro_fl_execute_parameter_t_clear(set) \
    set.option = 0; \
    set.wait = 0; \
    set.environment = 0; \
    set.signals = 0; \
    set.data = 0;
#endif // _di_fl_execute_parameter_t_

/**
 * A structure for containing identity and access related parameters for the execute functions that call the execv() family of functions.
 *
 * There are likely many more identity and access related things that can be done but this focuses on a small core set of those.
 *
 * Control Groups, or cgroups, exist here as a full file path in which the PID of a child process is to be written to.
 * This may change as more is learned about using cgroups, but it is not known if there are any functions available like set_cgroup(..).
 *
 * nice:          the niceness value to assign the child process to, set to 0 to not use.
 * id_user:       the id of the user to assign the child process to, set to 0 to not use.
 * id_group:      the id of the group to assign the child process to, set to 0 to not use.
 * affinity:      the cpu affinity to assign the child process to, set to 0 to not use (this is an array of CPU ids, starting from 0).
 * capability:    all of the capabilities to assign the child process to, set to 0 to not use (f_capability_t is a pointer).
 * control_group: an array of cgroups (control groups) to assign the child PID to, set to 0 to not use.
 * limits:        the resource limits to assign the child process to, set to 0 to not use.
 * id_groups:     the ids of each supplemental group to assign the child process to, set to 0 to not use.
 * scheduler:     the scheduler to assign the child process to, set to 0 to not use.
 */
#ifndef _di_fl_execute_as_t_
  typedef struct {
    int *nice;
    uid_t *id_user;
    gid_t *id_group;

    f_int32s_t *affinity;
    f_capability_t capability;
    f_control_group_t *control_group;
    f_int32s_t *id_groups;
    f_limit_sets_t *limits;
    f_execute_scheduler_t *scheduler;
  } fl_execute_as_t;

  #define fl_execute_as_t_initialize { 0, 0, 0, 0, 0, 0, 0, 0, 0 }

  #define macro_fl_execute_as_t_initialize(nice, id_user, id_group, affinity, capability, control_group, id_groups, limits, scheduler) { nice, id_user, id_group, affinity, capability, control_group, id_groups, limits, scheduler }

  #define macro_fl_execute_as_t_clear(as) \
    as.nice = 0; \
    as.id_user = 0; \
    as.id_group = 0; \
    as.affinity = 0; \
    as.capability = 0; \
    as.control_group = 0; \
    as.id_groups = 0; \
    as.limits = 0; \
    as.scheduler = 0;
#endif // _di_fl_execute_as_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_common_h
