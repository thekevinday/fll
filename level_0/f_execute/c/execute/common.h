/**
 * FLL - Level 0
 *
 * Project: Execute
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project execute.
 *
 * This is auto-included by execute.h and should not need to be explicitly included.
 */
#ifndef _F_execute_common_h
#define _F_execute_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * All special case execute codes.
 *
 * Only the lower 8-bits are available for return codes and so this is a special small set of status codes to be returned by a child process for a parent process to get.
 * A waitpid() call can be used within the parent to get these codes if the child returns with these codes.
 *
 * All codes, except 0, represent an error.
 *
 * Code 1 is used as a general error code across many programs.
 * Code 2 is used as invalid parameters.
 * Special code F_execute_code_middle is used as the middle point and must be less than 126.
 * Special codes 126 to 255 are intended to match GNU Bash like exit codes.
 * All other codes are in alphabetic order (inclusively between codes 3 to 125).
 *
 * Anything between F_execute_code_middle and 126 is a hole (not used for any status code).
 * The codes in this hole are available for custom use.
 *
 * F_execute_code_last, this is intended to designate the last code provided by level_0 execute project.
 * All code sets started by another project must start at this number + 1 with a code start map.
 *
 * Warning: F_execute and F_execute_not are F_status_t status codes and are not F_execute_codes.
 * The F_execute_off is the execute code equivalent of F_execute_not.
 */
#ifndef _di_f_execute_e_
  enum {
    F_execute_none = 0,
    F_execute_failure,
    F_execute_parameter,
    F_execute_access,
    F_execute_bad,
    F_execute_buffer,
    F_execute_busy,
    F_execute_capability,
    F_execute_control_group,
    F_execute_child,
    F_execute_directory_not,
    F_execute_file_found_not,
    F_execute_file_type_directory,
    F_execute_fork_not,
    F_execute_format_not,
    F_execute_group,
    F_execute_input_output,
    F_execute_limit,
    F_execute_loop,
    F_execute_memory_not,
    F_execute_name_not,
    F_execute_nice,
    F_execute_pipe,
    F_execute_processor,
    F_execute_prohibited,
    F_execute_resource_not,
    F_execute_schedule,
    F_execute_terminal,
    F_execute_terminal_known_not,
    F_execute_terminal_not,
    F_execute_terminal_prohibited,
    F_execute_terminal_valid_not,
    F_execute_too_large,
    F_execute_user,
    F_execute_valid_not,
    F_execute_code_middle,

    // Special codes for compatibility with GNU Bash like return codes.
    F_execute_invoke_not = 126,
    F_execute_found_not,
    F_execute_exit_parameter,
    F_execute_signal_hangup,
    F_execute_signal_interrupt,
    F_execute_signal_quit,
    F_execute_signal_illegal,
    F_execute_signal_trap,
    F_execute_signal_abort,
    F_execute_signal_bus_error,
    F_execute_signal_floating_point_error,
    F_execute_signal_kill,
    F_execute_signal_user_1,
    F_execute_signal_segmentation_fault,
    F_execute_signal_user_2,
    F_execute_signal_broken_pipe,
    F_execute_signal_alarm_clock,
    F_execute_signal_termination,
    F_execute_signal_stack_fault,
    F_execute_signal_child,
    F_execute_signal_continue,
    F_execute_signal_stop,
    F_execute_signal_keyboard_stop,
    F_execute_signal_tty_in,
    F_execute_signal_tty_out,
    F_execute_signal_urgent,
    F_execute_signal_cpu_limit,
    F_execute_signal_file_size_limit,
    F_execute_signal_virtual_alarm_clock,
    F_execute_signal_profile_alarm_clock,
    F_execute_signal_window_size_change,
    F_execute_signal_pollable_event,
    F_execute_signal_power_failure,
    F_execute_signal_bad_system_call,
    F_execute_signal_reserved_32,
    F_execute_signal_reserved_33,
    F_execute_signal_reserved_34,
    F_execute_signal_reserved_35,
    F_execute_signal_reserved_36,
    F_execute_signal_reserved_37,
    F_execute_signal_reserved_38,
    F_execute_signal_reserved_39,
    F_execute_signal_reserved_40,
    F_execute_signal_reserved_41,
    F_execute_signal_reserved_42,
    F_execute_signal_reserved_43,
    F_execute_signal_reserved_44,
    F_execute_signal_reserved_45,
    F_execute_signal_reserved_46,
    F_execute_signal_reserved_47,
    F_execute_signal_reserved_48,
    F_execute_signal_reserved_49,
    F_execute_signal_reserved_50,
    F_execute_signal_reserved_51,
    F_execute_signal_reserved_52,
    F_execute_signal_reserved_53,
    F_execute_signal_reserved_54,
    F_execute_signal_reserved_55,
    F_execute_signal_reserved_56,
    F_execute_signal_reserved_57,
    F_execute_signal_reserved_58,
    F_execute_signal_reserved_59,
    F_execute_signal_reserved_60,
    F_execute_signal_reserved_61,
    F_execute_signal_reserved_62,
    F_execute_signal_reserved_63,
    F_execute_signal_reserved_64,

    // Required.
    F_execute_code_last = 255,
  }; // enum
#endif // _di_f_execute_e_

/**
 * A structure representing a scheduler and its parameters for execution.
 *
 * policy:   The scheduler policy.
 * priority: The scheduler priority;
 */
#ifndef _di_f_execute_scheduler_t_
  typedef struct {
    int policy;
    int priority;
  } f_execute_scheduler_t;

  #define f_execute_scheduler_t_initialize { 0, 0 }

  #define macro_f_execute_scheduler_t_initialize_1(policy, priority) { policy, priority }

  #define f_execute_scheduler_t_clear(scheduler) \
    scheduler.policy = 0; \
    scheduler.priority = 0;
#endif // _di_f_execute_scheduler_t_

/**
 * A structure representing either a pid_t or an f_status_t.
 *
 * This is intended to be used for the execute functions that may store a pid_t in a parent process but a f_status_t in a child process.
 * These would use the same variable, but it may be stored differently.
 *
 * status: The status code, generally used by the child process.
 * pid:    The process id (PID) of the child process, generally used by the parent process;
 */
#ifndef _di_f_execute_result_t_
  typedef union {
    int status;
    pid_t pid;
  } f_execute_result_t;

  #define f_execute_result_t_initialize { 0 }

  #define macro_f_execute_result_t_initialize_1(status, pid) { status, pid }

  #define f_execute_result_t_clear(execute_result) \
    execute_result.status = 0; \
    execute_result.pid = 0;
#endif // _di_f_execute_result_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_common_h
