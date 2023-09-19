/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines state type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_state_h
#define _F_type_state_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A representation of a state to be shared between different levels for some function.
 *
 * This is used to provide advanced controls on different levels of the project to something outside.
 *
 * The allocate provides an allocation step so that the caller can determine a better performing allocation step for their purpose.
 * For example, if the caller knows that they need to allocate a hundred megabytes of data of which is separated into blocks of 8k, then allocate could be set to 8192.
 *
 * There are two standard callbacks that are expected to be commonly available: interrupt() and handle().
 * Additional callbacks are stored in the structure "callbacks" as defined by the class requiring the use of this structure (f_state_t).
 *
 * All state values may be NULL, in which case they are to be ignored.
 *
 * The general interpretation of the state.status results of interrupt() or any of the functions should have an error bit to designate an error and not an error bit to designate not an error.
 * In the case of interrupt(), the F_interrupt and F_interrupt_not must be returned as appropriate and if not an error (the F_interrupt and F_interrupt_not may have an error bit).
 * To keep the logic simple, it is recommended that F_interrupt always be returned with the error bit set.
 *
 * The general interpretation of handle() is to either print an error message or to perform additional tasks when an error occurs (such as saving state data for use at a higher level).
 * This allows for the error to be processed with all relevant data before the function returns.
 *
 * These two callbacks (handle() and interrupt()) accept the following parameters:
 *   - state:    The state data. Must be of type f_state_t. Must not be NULL.
 *   - internal: Additional data passed by the function being called, often containing internal data to the called function. May be NULL.
 *
 * The "custom" property on f_state_t is intended to be used so that the callback, such as the interrupt(), can make changes to something within the scope of the parent.
 *
 * For example:
 *   There exists some project "bob" with some functions "bob_does()" and "bob_interrupts()".
 *   The function "bob_does()" maintains a state (f_state_t) called "bob_state".
 *   The function "bob_does()" will call "f_talk()" that accepts a state (f_state_t) and defines the data structure type "f_interject_t" to be called interject.
 *   While "f_talk()" executes, "bob_interrupts()" is periodically with the state (f_state_t) "bob_state" as the first parameter and the data structure (f_interject_t) "interject" as the second parameter.
 *   If Bob interjects the talk, then bob_interrupts() would set state.status to F_interrupt.
 *   If Bob does not interject the talk, then bob_interrupts() would set state.status to F_interrupt_not.
 *   This response is handled within f_talk().
 *   The f_talk() function will then set the state.status when done and might immediately set state.status to F_interrupt (with error bit) if bob_interrupts() returns F_interrupt (with/without error bit).
 *
 * Properties:
 *   - step_large: The allocation step to use for large buffers.
 *   - step_small: The allocation step to use for small buffers.
 *   - flag:       A 64-bit digit intended for provided flags that are defined by the function.
 *   - code:       A 64-bit digit intended for provided flags that are defined by the caller.
 *   - status:     The status used while processing (This should hold the error passed to the handle callback and should be updated as necessary).
 *   - handle:     A function to call on a specific error (allowing for the error to be handled before function returns). May be NULL.
 *   - interrupt:  A function to call for checking to see if an interrupt is to be called. May be NULL.
 *   - callbacks:  A structure (defined by function/project using this) of additional functions to call. May be NULL.
 *   - custom:     A structure (defined by caller/parent) for holding custom data to be passed along to the interrupt() or one of the functions. May be NULL.
 *   - data:       A structure (defined by function) for holding data relevant to the function. May be NULL. May be required.
 */
#ifndef _di_f_state_t_
  typedef struct {
    uint16_t step_large;
    uint16_t step_small;
    f_status_t status;
    uint64_t flag;
    uint64_t code;

    void (*handle)(void * const state, void * const internal);
    void (*interrupt)(void * const state, void * const internal);

    void *callbacks;
    void *custom;
    void *data;
  } f_state_t;

  #define f_state_t_initialize { \
    F_memory_default_allocation_large_d, \
    F_memory_default_allocation_small_d, \
    F_okay, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }

  #define macro_f_state_t_initialize_1(step_large, step_small, status, flag, code, handle, interrupt, callbacks, custom, data) { \
    step_large, \
    step_small, \
    status, \
    flag, \
    code, \
    handle, \
    interrupt, \
    callbacks, \
    custom, \
    data, \
  }

  #define macro_f_state_t_clear(state) \
    state.step_large = 0; \
    state.step_small = 0; \
    state.status = F_okay; \
    state.flag = 0; \
    state.code = 0; \
    state.handle = 0; \
    state.interrupt = 0; \
    state.callbacks = 0; \
    state.custom = 0; \
    state.data = 0;
#endif // _di_f_state_t_

/**
 * This holds an array of f_state_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_state_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_states_t_
  typedef struct {
    f_state_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_states_t;

  #define f_states_t_initialize { 0, 0, 0 }

  #define macro_f_states_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_states_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_states_t_

/**
 * This holds an array of f_states_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_state_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_statess_t_
  typedef struct {
    f_states_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_statess_t;

  #define f_statess_t_initialize { 0, 0, 0 }

  #define macro_f_statess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_statess_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_statess_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_state_h
