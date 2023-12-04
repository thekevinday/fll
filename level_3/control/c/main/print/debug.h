/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_print_debug_h
#define _control_print_debug_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message displaying the object and content for some packet header.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param object
 *   The object string.
 * @param content
 *   The content string.
 * @param content_range
 *   The range representing the content where the content is found within the content string.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_debug_packet_header_object_and_content_
  extern f_status_t control_print_debug_packet_header_object_and_content(fl_print_t * const print, const f_string_static_t object, const f_string_static_t content, const f_range_t content_range);
#endif // _di_control_print_debug_packet_header_object_and_content_

/**
 * Print a debug message regarding some packet.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param message
 *   The message to print.
 *
 *   A single "%[" followed by a single "%]" is supported in the message and is replaced with "notable" context.
 * @param buffer
 *   (optional) An additonal message to print (this is syntax highlighted).
 *   Set to NULL to not use.
 * @param range
 *   (optional) The range within the buffer to print rather than printing the entire buffer.
 *   Set to NULL to not use.
 *   This is ignored when buffer is NULL.
 * @param status
 *   (optional) A status code that triggered the failure (this is syntax highlighted).
 *   Set to NULL to not use.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_debug_packet_message_
  extern f_status_t control_print_debug_packet_message(fl_print_t * const print, const f_string_t message, const f_string_static_t *buffer, const f_range_t *range);
#endif // _di_control_print_debug_packet_message_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_debug_h
