/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_print_h
#define _fake_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for being used in print functions.
 *
 * These serve two primary purposes:
 * 1) Reduce repition of strings, saving space.
 * 2) Provide a central location for changing strings to another langauge.
 *
 * The macro macro_fake_p() is used to reference the array index by the enum name.
 *
 * macro_fake_p():
 *   - name: A name or alias representing the string.
 */
#ifndef _di_fake_p_a_
  extern const f_string_t fake_p_a[];

  #define macro_fake_p(name) fake_p_a[fake_p_##name##_e]
#endif // _di_fake_f_p_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_fake_p_e_
  enum {
    fake_p__e,
  }; // enum
#endif // _di_fake_p_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_print_string_h
