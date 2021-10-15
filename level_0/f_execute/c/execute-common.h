/**
 * FLL - Level 0
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * F_execute_code_last, this is intended to designate the last code provided by level_0 execute project.
 * All code sets started by another project must start at this number + 1 with a code start map.
 *
 * Warning: F_execute and F_execute_not are F_status_t status codes and are not F_execute_codes.
 * The F_execute_off is the execute code equivalent of F_execute_not.
 */
#ifndef _di_F_execute_codes_
  enum {
    F_execute_none = 0,
    F_execute_access,
    F_execute_bad,
    F_execute_buffer,
    F_execute_busy,
    F_execute_capability,
    F_execute_control_group,
    F_execute_child,
    F_execute_directory_not,
    F_execute_failure,
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
    F_execute_parameter,
    F_execute_pipe,
    F_execute_processor,
    F_execute_prohibited,
    F_execute_resource_not,
    F_execute_schedule,
    F_execute_too_large,
    F_execute_user,
    F_execute_valid_not,

    // Required.
    F_execute_code_last,
  }; // enum
#endif // _di_F_execute_codes_

/**
 * A structure representing a scheduler and its parameters for execution.
 *
 * @todo move this into a f_scheduler project.
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

  #define macro_f_execute_scheduler_t_initialize(policy, priority) { policy, priority }

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

  #define f_execute_result_t_clear(execute_result) \
    execute_result.status = 0; \
    execute_result.pid = 0;
#endif // _di_f_execute_result_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_common_h
