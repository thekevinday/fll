/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the payload functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_payload_h
#define _control_payload_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify the payload code the given name represents.
 *
 * @param payload
 *   The string representing a payload.
 *
 * @return
 *   The payload type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_control_payload_type_identify_
  extern const uint8_t control_payload_type_identify(const f_string_static_t payload);
#endif // _di_control_payload_type_identify_

/**
 * Get a string representing the payload type.
 *
 * @param type
 *   The payload type id.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_control_payload_type_name_
  extern const f_string_static_t control_payload_type_name(const uint8_t type);
#endif // _di_control_payload_type_name_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_payload_h
