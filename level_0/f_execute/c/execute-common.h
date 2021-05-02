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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_common_h
