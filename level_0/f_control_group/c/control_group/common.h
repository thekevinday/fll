/**
 * FLL - Level 0
 *
 * Project: Control Group
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by control group (cgroup) related functionality.
 *
 * This is auto-included by control.h and should not need to be explicitly included.
 */
#ifndef _F_control_group_common_h
#define _F_control_group_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The defines for control groups.
 */
#ifndef _di_f_control_group_defines_
  #define F_control_group_path_system_default_s "sys/fs/cgroup/"
  #define F_control_group_path_system_prefix_s  "/"
  #define F_control_group_path_system_suffix_s  "/cgroup.procs"

  #define F_control_group_path_system_default_s_length 14
  #define F_control_group_path_system_prefix_s_length  1
  #define F_control_group_path_system_suffix_s_length  13

  #define F_control_group_pid_length_max_d 64

  extern const f_string_static_t f_control_group_path_system_default_s;
  extern const f_string_static_t f_control_group_path_system_prefix_s;
  extern const f_string_static_t f_control_group_path_system_suffix_s;
#endif // _di_f_control_group_defines_

/**
 * Provide a structure for associating some process with one or more control groups (cgroups).
 *
 * as_new: If TRUE then the control group is to be unshared, and FALSE the control group is not to be unshared.
 * path:   The sysfs path, must have the trailing slash (such as "/sys/fs/cgroup/").
 * groups: An array of control groups, relative to the sysfs path (such as "memory/example").
 */
#ifndef _di_f_control_group_t_
  typedef struct {
    bool as_new;

    f_string_dynamic_t path;
    f_string_dynamics_t groups;
  } f_control_group_t;

  #define f_control_group_t_initialize { F_false, f_string_dynamic_t_initialize, f_string_dynamics_t_initialize }

  #define macro_f_control_group_t_initialize(as_new, path, groups) { as_new, path, groups }

  #define macro_f_control_group_t_clear(control) \
    control.as_new = F_false; \
    macro_f_string_dynamic_t_clear(control.path); \
    macro_f_string_dynamics_t_clear(control.groups);

  #define macro_f_control_group_t_delete_simple(control) \
    macro_f_string_dynamic_t_delete_simple(control.path); \
    macro_f_string_dynamics_t_delete_simple(control.groups);

  #define macro_f_control_group_t_destroy_simple(control) \
    macro_f_string_dynamic_t_destroy_simple(control.path); \
    macro_f_string_dynamics_t_destroy_simple(control.groups);
#endif // _di_f_control_group_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_control_group_common_h
