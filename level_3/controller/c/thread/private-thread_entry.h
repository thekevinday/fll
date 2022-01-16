/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_thread_entry_h
#define _PRIVATE_thread_entry_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread for handling entry processing.
 *
 * This acts as the main rule thread during entry processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_entry_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_entry_
  extern void * controller_thread_entry(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_entry_

/**
 * Thread for handling exit file processing.
 *
 * This acts as the main rule thread during exit processing.
 * This runs all synchronous rules or spawns asynchronous rules.
 *
 * Do not confuse this with exiting a thread, this is the what process the exit files (similar to that of an entry file).
 * Exit files process the "stop" action, whereas the Entry files process the "start" Action
 *
 * @param arguments
 *   The thread arguments.
 *   Must be of type controller_main_entry_t.
 *
 * @return
 *   0, always.
 */
#ifndef _di_controller_thread_exit_
  extern void * controller_thread_exit(void * const arguments) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_thread_entry_h
