/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides file-related datatype definitions needed by multiple level_0 projects.
 * This should be kept to a bare minimum.
 * Most of the file related code should instead be in f_file project.
 *
 * This is not auto-included by type.h.
 * This is done to prevent depending on the stdio.h, unless required.
 */
#ifndef _F_type_file_h
#define _F_type_file_h

// Libc includes.
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide file defaults needed by f_file_t.
 *
 * These are intended to be in level 0 project f_file but are defined here due to a requirement by f_file_t.
 *
 * F_file_default_*:
 *   - read_size:  Default read size in bytes.
 *   - write_size: Default write size in bytes.
 */
#ifndef _di_f_type_file_defaults_
  #define F_file_default_read_size_d  8192
  #define F_file_default_write_size_d 8192
#endif // _di_f_type_file_defaults_

/**
 * Commonly used file related properties.
 *
 * stream:     File stream.
 * id:         File descriptor, with a value of -1 represents a closed file.
 * flag:       Flags used for opening the file.
 * size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 * size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
 */
#ifndef _di_f_file_t_
  typedef struct {
    FILE   *stream;
    int    id;
    int    flag;
    size_t size_read;
    size_t size_write;
  } f_file_t;

  #define f_file_t_initialize { 0, -1, O_RDONLY, F_file_default_read_size_d, F_file_default_write_size_d }

  #define macro_f_file_t_initialize(stream, id, flag, read_size, write_size) { stream, id, flag, read_size, write_size }
  #define macro_f_file_t_initialize2(stream, id, flag) { stream, id, flag, F_file_default_read_size_d, F_file_default_write_size_d }
  #define macro_f_file_t_initialize_id(id) { 0, id, O_RDONLY, F_file_default_read_size_d, F_file_default_write_size_d }
  #define macro_f_file_t_initialize_stream(stream) { stream, -1, O_RDONLY, F_file_default_read_size_d, F_file_default_write_size_d }

  #define macro_f_file_t_clear(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = 0; \
    file.size_read = 0; \
    file.size_write = 0;

  #define macro_f_file_t_reset(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = O_RDONLY; \
    file.size_read = F_file_default_read_size_d; \
    file.size_write = F_file_default_write_size_d;
#endif // _di_f_file_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_file_h
