/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_thread_rule_h
#define _PRIVATE_thread_rule_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling rule processing.
 *
 * This acts as the main rule thread after entry processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * @todo the control thread should send commands to this thread, somehow.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_global_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_rule_
  extern void * controller_thread_rule(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_rule_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_rule_h
