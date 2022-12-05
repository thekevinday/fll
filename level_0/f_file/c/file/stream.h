/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project file.
 *
 * This is auto-included by file.h and should not need to be explicitly included.
 */
#ifndef _F_file_stream_h
#define _F_file_stream_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Close an open file stream.
 *
 * @param file
 *   The file information.
 *   The file.stream is set to NULL, on both success or on failure.
 *
 * @return
 *   F_none on success.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_block (with error bit) if the action would block and non-blocking is set on the stream.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_overflow (with error bit) if the write exceeds some implementation defined maximum file size.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_lock (with error bit) if failed to lock, such as lock table is full or too many open segments.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe_not (with error bit) if the stream is a pipe or a socket but the pipe or socket is already closed.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_socket_not (with error bit) if the datagram socket in which a peer has not been set (for socket related streams).
 *
 *   F_file_close (with error bit) on any other error.
 *
 * @see fclose()
 */
#ifndef _di_f_file_stream_close_
  extern f_status_t f_file_stream_close(f_file_t * const file);
#endif // _di_f_file_stream_close_

/**
 * Flush a file stream.
 *
 * @param file
 *   The file information.
 *   The file.id is updated with the file descriptor, if necessary and able.
 *
 * @return
 *   F_none is returned on success.
 *   F_stream_not if file.stream is NULL.
 *   F_file_descriptor_not if file.id is -1.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *
 *   F_file_synchronize (with error bit) on any other error.
 *
 * @see fflush()
 */
#ifndef _di_f_file_stream_flush_
  extern f_status_t f_file_stream_flush(const f_file_t file);
#endif // _di_f_file_stream_flush_

/**
 * Lock a file stream.
 *
 * As per flockfile(), this waits (blocks) until the file stream is available to lock again.
 *
 * @param file
 *   The file to lock.
 *
 * @return
 *   F_none on success.
 *   F_stream_not if file.stream is NULL.
 *
 * @see flockfile()
 */
#ifndef _di_f_file_stream_lock_
  extern f_status_t f_file_stream_lock(const f_file_t file);
#endif // _di_f_file_stream_lock_

/**
 * Try to lock a file stream.
 *
 * As per flockfile(), this does not wait (does not block) when the file stream is already locked.
 *
 * @param file
 *   The file to lock.
 *
 * @return
 *   F_none on success.
 *   F_busy on success, but the file.stream is already locked.
 *   F_stream_not if file.stream is NULL.
 *
 * @see ftrylockfile()
 */
#ifndef _di_f_file_stream_lock_try_
  extern f_status_t f_file_stream_lock_try(const f_file_t file);
#endif // _di_f_file_stream_lock_try_

/**
 * Open a file stream.
 *
 * The file descriptor is retrieved on success, if necessary and able.
 *
 * If the file stream is open, it is closed before re-opening.
 *
 * This is often used for changing the file pointed to by standard streams such as stdout.
 *
 * @param path
 *   The file path.
 * @param mode
 *   The file modes do use when opening, as an fopen() file mode string.
 *   Set mode.used to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are specified in write only mode, then the failsafe is to append.
 *
 *   File Modes (fopen() file modes vs open file modes):
 *     - "r":  O_RDONLY.
 *     - "w":  O_WRONLY | O_CREAT | O_TRUNC.
 *     - "a":  O_WRONLY | O_CREAT | O_APPEND.
 *     - "r+": O_RDWR.
 *     - "w+": O_RDWR | O_CREAT | O_TRUNC.
 *     - "a+": O_RDWR | O_CREAT | O_APPEND.
 * @param file
 *   The file information.
 *   The file.stream is updated if necessary.
 *   The file.id is updated with the file descriptor, if necessary and able.
 *
 * @return
 *   F_none is returned on success.
 *   F_data_not if both path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name is too long.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_support_not (with error bit) fo unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see fopen()
 */
#ifndef _di_f_file_stream_open_
  extern f_status_t f_file_stream_open(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_open_

/**
 * Open a file stream from a file descriptor.
 *
 * @param mode
 *   The file modes do use when opening.
 *   Set mode.used to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are not specified in write only mode, then the failsafe is to append.
 *   This should match the modes used to open the file descriptor as it relates to the stream modes.
 * @param file
 *   The file with a valid file descriptor (file.id).
 *
 * @return
 *   F_none is returned on success.
 *   F_file_descriptor_not if file.id is -1.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_block (with error bit) if the action would block and non-blocking is set on the stream.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_overflow (with error bit) if the write exceeds some implementation defined maximum file size.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_lock (with error bit) if failed to lock, such as lock table is full or too many open segments.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe_not (with error bit) if the stream is a pipe or a socket but the pipe or socket is already closed.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_socket_not (with error bit) if socket is not connected.
 *   F_space_not (with error bit) if the file system is out of space (or file system quota is reached).
 *
 * @see fdopen()
 */
#ifndef _di_f_file_stream_open_descriptor_
  extern f_status_t f_file_stream_open_descriptor(const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_open_descriptor_

/**
 * Read until EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file.size_read represents the amount to process at a given time.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_error (with error bit) if the file is already in the error state at the start of this function.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see flockfile()
 * @see feof_unlocked()
 * @see ferror_unlocked()
 * @see fread_unlocked()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_read_
  extern f_status_t f_file_stream_read(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_

/**
 * Read until a single block is filled or EOF is reached.
 *
 * To determine how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file.size_read represents the amount to process at a given time.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   F_none on success.
 *   F_none_eof on success and EOF was reached.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_error (with error bit) if the file is already in the error state at the start of this function.
 *   F_file_closed (with error bit) if the file is closed.
 *   F_file_read (with error bit) on file read error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see feof_unlocked()
 * @see ferror_unlocked()
 * @see flockfile()
 * @see fread()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_read_block_
  extern f_status_t f_file_stream_read_block(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_block_

/**
 * Read until a given number or EOF is reached, storing it in the buffer.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * This is different from simply using the file.size_read.
 * The file.size_read represents the amount to process at a given time.
 * The total represents the maximum number of file.size_read to process.
 * For example, if file.size_read is 16 and total is 128, then this function would need to be called 8 times until total is reached.
 *
 * @param file
 *   The file to read.
 *   The file.size_read represents the amount to process at a given time.
 * @param total
 *   The total bytes to read, unless EOF is reached first.
 * @param buffer
 *   The buffer the file is being read into.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *   F_none_stop on success and total was reached.
 *   F_data_not if total is 0.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_error (with error bit) if the file is already in the error state at the start of this function.
 *   F_file_closed (with error bit) if the file is closed.
 *   F_file_read (with error bit) on file read error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see feof_unlocked()
 * @see ferror_unlocked()
 * @see flockfile()
 * @see fread_unlocked()
 * @see funlockfile()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_file_stream_read_until_
  extern f_status_t f_file_stream_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_until_

/**
 * Re-open a file stream.
 *
 * This allows for re-using an existing file stream and possibly file-descriptor.
 *
 * The file descriptor is retrieved on success, if necessary and able.
 *
 * @param path
 *   The file path.
 *   Set path.used to 0 with a non-empty mode (mode.used > 0) to only change the mode of the existing stream.
 * @param mode
 *   The file modes do use when opening.
 *   Set to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are not specified in write only mode, then the failsafe is to append.
 * @param file
 *   The file information.
 *   The file.stream is updated, if necessary.
 *
 * @return
 *   F_none is returned on success.
 *   F_data_not if both path.used and mode.used are 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name is too long.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_support_not (with error bit) fo unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see fileno()
 * @see freopen()
 */
#ifndef _di_f_file_stream_reopen_
  extern f_status_t f_file_stream_reopen(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_reopen_

/**
 * Unlock a locked file stream.
 *
 * @param file
 *   The file to unlock.
 *
 * @return
 *   F_none on success.
 *   F_stream_not if file.stream is NULL.
 *
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_unlock_
  extern f_status_t f_file_stream_unlock(const f_file_t file) ;
#endif // _di_f_file_stream_unlock_

/**
 * Write until entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   (optional) The total bytes written.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_eof when the file stream is at the end of the file.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_data_not on success but buffer.used is 0.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_file_write (with error bit) on error during file write.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_file_write (with error bit) on any other error.
 *
 * @see ferror_unlocked()
 * @see flockfile()
 * @see fwrite_unlocked()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_write_
  extern f_status_t f_file_stream_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_stream_write_

/**
 * Write until a single block is filled or entire buffer is written.
 *
 * To check how much was write into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   (optional) The total bytes written.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_eof when the file stream is at the end of the file.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_data_not on success but buffer.used is 0.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_file_write (with error bit) on error during file write.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_file_write (with error bit) on any other error.
 *
 * @see flockfile()
 * @see fwrite_unlocked()
 * @see ferror_unlocked()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_write_block_
  extern f_status_t f_file_stream_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_stream_write_block_

/**
 * Write until a given number or entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param total
 *   The total bytes to write, unless end of buffer is reached first.
 * @param written
 *   (optional) The total bytes written.
 *   Set to NULL to not use..
 *
 * @return
 *   F_none on success.
 *   F_none_eof when the file stream is at the end of the file.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_data_not on success but either buffer.used or total is 0.
 *   F_stream_not if file.stream is NULL.
 *
 *   F_file_write (with error bit) on error during file write.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_file_write (with error bit) on any other error.
 *
 * @see flockfile()
 * @see fwrite_unlocked()
 * @see ferror_unlocked()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_write_until_
  extern f_status_t f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written);
#endif // _di_f_file_stream_write_until_

/**
 * Write a given range within the buffer.
 *
 * @param file
 *   The file to write to.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param range
 *   An inclusive start an stop range within the buffer to read.
 * @param written
 *   (optional) The total bytes written.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_stream_not if file.stream is NULL.
 *
 *   F_file_write (with error bit) on error during file write.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_file_stream_write_range_
  extern f_status_t f_file_stream_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written);
#endif // _di_f_file_stream_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_stream_h
