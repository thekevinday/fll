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
 * A set containing the three standard descriptors for use in pipes.
 *
 * Future versions may suppot stdwarn and stddebug if there ever is such a thing.
 *
 * Descriptors always use -1 to designate not used because 0 represent a valid descriptor.
 *
 * input:  the input file descriptor.
 * output: the output file descriptor.
 * error:  the error file descriptor.
 */
#ifndef _di_f_execute_pipe_t_
  typedef struct {
    int input;
    int output;
    int error;
  } f_execute_pipe_t;

  #define f_execute_pipe_t_initialize { -1, -1, -1 }

  #define f_execute_pipe_t_clear(set) \
    set.input = -1; \
    set.output = -1; \
    set.error = -1;
#endif // _di_f_execute_pipe_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_common_h
