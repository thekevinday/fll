/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The data structure for FSS Identify.
 *
 * current: The current position within the ids, used to determine when the line is matched.
 * line:    The line number to select.
 */
#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_array_length_t current;
    f_array_length_t line;
  } fss_identify_data_t;

  #define fss_identify_data_t_initialize \
    { \
      0, \
      0, \
    }
#endif // _di_fss_identify_data_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
