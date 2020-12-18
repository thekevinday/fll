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
 * A structure for use in processing asynchronous execute behavior.
 *
 * Future versions may suppot stdwarn and stddebug if there ever is such a thing.
 *
 * Descriptors always use -1 to designate not used because 0 represent a valid descriptor.
 * The process ID always uses -1 to designate no valid process ID is set.
 *
 * input:   the input file descriptor.
 * output:  the output file descriptor.
 * error:   the error file descriptor.
 * process: the process ID whereas 0 represents a parent and anything greater than 0 represents a child.
 */
#ifndef _di_f_execute_asynchronous_t_
  typedef struct {
    int input;
    int output;
    int error;
    int process;
  } f_execute_asynchronous_t;

  #define f_execute_asynchronous_t_initialize { -1, -1, -1, -1 }

  #define f_execute_asynchronous_t_clear(set) \
    set.input = -1; \
    set.output = -1; \
    set.error = -1; \
    set.process = -1;
#endif // _di_f_execute_asynchronous_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_common_h
