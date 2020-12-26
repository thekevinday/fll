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
 *   fl_execute_parameter_option_exit: used to desginate to exit after calling child otherwise child process will return.
 *   fl_execute_parameter_option_path: used to designate that this is a path to a program (such as '/bin/bash').
 *
 * option:      accepts the bitwise options
 * environment: the environment variable name and value pairs, set to 0 to not use.
 * signals:     the set of signals the child process should or should block, set to 0 to not use.
 * data:        the data to pipe to the child process, set to 0 to not use.
 */
#ifndef _di_fl_execute_parameter_t_
  #define fl_execute_parameter_option_exit 0x1
  #define fl_execute_parameter_option_path 0x2

  typedef struct {
    uint8_t option;

    const f_string_maps_t *environment;
    const f_signal_how_t *signals;
    const f_string_static_t *data;
  } fl_execute_parameter_t;

  #define fl_execute_parameter_t_initialize { 0, 0, 0, 0 }

  #define fl_macro_execute_parameter_t_initialize(option, environment, signals, data) { option, environment, signals, data }

  #define fl_execute_parameter_t_clear(set) \
    set.option = 0; \
    set.environment = 0; \
    set.signals = 0; \
    set.data = 0;
#endif // _di_fl_execute_parameter_t_

/**
 * A structure representing a scheduler and its parameters for execution.
 *
 * policy:    the scheduler policy.
 * parameter: a pointer to the scheduler parameters;
 */
#ifndef _di_fl_execute_scheduler_t_
  typedef struct {
    int policy;
    const struct sched_param *parameter;
  } fl_execute_scheduler_t;

  #define fl_execute_scheduler_t_initialize { 0, 0 }

  #define fl_macro_execute_scheduler_t_initialize(policy, parameter) { policy, parameter }

  #define fl_execute_scheduler_t_clear(scheduler) \
    scheduler.policy = 0; \
    scheduler.parameter = 0;
#endif // _di_fl_execute_scheduler_t_

/**
 * A structure for containing identity and access related parameters for the execute functions that call the execv() family of functions.
 *
 * There are likely many more identity and access related things that can be done but this focuses on a small core set of those.
 *
 * Control Groups, or cgroups, exist here as a full file path in which the PID of a child process is to be written to.
 * This may change as more is learned about using cgroups, but it is not known if there are any functions available like set_cgroup(..).
 *
 * nice:       the niceness value to assign the child process to, set to 0 to not use.
 * id_user:    the id of the user to assign the child process to, set to 0 to not use.
 * id_group:   the id of the group to assign the child process to, set to 0 to not use.
 * capability: all of the capabilities to assign the child process to, set to 0 to not use (f_capability_t is a pointer).
 * id_groups:  the ids of each supplemental group to assign the child process to, set to 0 to not use.
 * scheduler:  the scheduler to assign the child process to, set to 0 to not use.
 * controls:   an array of cgroups (control groups) to assign the child PID to, set to 0 to not use.
 */
#ifndef _di_fl_execute_as_t_
  typedef struct {
    int *nice;
    uid_t *id_user;
    gid_t *id_group;
    f_capability_t capability;

    f_int32s_t *id_groups;
    fl_execute_scheduler_t *scheduler;
    f_string_dynamics_t *controls;
  } fl_execute_as_t;

  #define fl_execute_as_t_initialize { 0, 0, 0, 0, 0, 0, 0 }

  #define fl_macro_execute_as_t_initialize(nice, id_user, id_group, capability, id_groups, scheduler, controls) { nice, id_user, id_group, capability, id_groups, scheduler, controls }

  #define fl_execute_as_t_clear(as) \
    as.nice = 0; \
    as.id_user = 0; \
    as.id_group = 0; \
    as.capability = 0; \
    as.id_groups = 0; \
    as.scheduler = 0; \
    as.controls = 0;
#endif // _di_fl_execute_as_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_common_h
