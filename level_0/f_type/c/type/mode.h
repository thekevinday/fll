/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines mode type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_mode_h
#define _F_type_mode_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure representing a set of modes intended to be used by file or directory operations.
 *
 * Properties:
 *   - block:     The mode for a block.
 *   - character: The mode for a character.
 *   - directory: The mode for a directory.
 *   - fifo:      The mode for a FIFO.
 *   - regular:   The mode for a regular file.
 *   - link:      The mode for a link.
 *   - socket:    The mode for a socket.
 *   - unknown:   The mode for unknown types.
 */
#ifndef _di_f_mode_t_
  typedef struct {
    mode_t block;     // S_IFBLK
    mode_t character; // S_IFCHR
    mode_t directory; // S_IFDIR
    mode_t fifo;      // S_IFIFO
    mode_t regular;   // S_IFREG
    mode_t link;      // S_IFLNK
    mode_t socket;    // S_IFSOCK
    mode_t unknown;
  } f_mode_t;

  #define f_mode_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }

  #define macro_f_mode_t_set_default(mode) \
    mode.block = F_file_mode_all_rw_d; \
    mode.character = F_file_mode_all_rw_d; \
    mode.directory = F_file_mode_all_rwx_d; \
    mode.fifo = F_file_mode_all_rw_d; \
    mode.regular = F_file_mode_all_rw_d; \
    mode.link = F_file_mode_all_rw_d; \
    mode.socket = F_file_mode_all_rw_d; \
    mode.unknown = F_file_mode_all_rw_d;

  #define macro_f_mode_t_set_default_umask(mode, mask) \
    mode.block = F_file_mode_all_rw_d & ~mask; \
    mode.character = F_file_mode_all_rw_d & ~mask; \
    mode.directory = F_file_mode_all_rwx_d & ~mask; \
    mode.fifo = F_file_mode_all_rw_d & ~mask; \
    mode.regular = F_file_mode_all_rw_d & ~mask; \
    mode.link = F_file_mode_all_rw_d & ~mask; \
    mode.socket = F_file_mode_all_rw_d & ~mask; \
    mode.unknown = F_file_mode_all_rw_d & ~mask;

  #define macro_f_mode_t_set_all(mode, value) \
    mode.block = value; \
    mode.character = value; \
    mode.directory = value; \
    mode.fifo = value; \
    mode.regular = value; \
    mode.link = value; \
    mode.socket = value; \
    mode.unknown = value;

  #define macro_f_mode_t_set_common(mode, value_directory, value_file, value_link) \
    mode.directory = value_directory; \
    mode.regular = value_file; \
    mode.link = value_link;

  #define macro_f_mode_t_set_uncommon(mode, value_block, value_character, value_fifo, value_socket, value_unknown) \
    mode.block = value_block; \
    mode.character = value_character; \
    mode.fifo = value_fifo; \
    mode.socket = value_socket; \
    mode.unknown = value_unknown;
#endif // _di_f_mode_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_mode_h
