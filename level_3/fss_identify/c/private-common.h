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
 * total:   The total ids across all files.
 * name:    The name to select.
 */
#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_array_length_t current;
    f_array_length_t line;
    f_array_length_t total;

    f_string_dynamic_t name;
  } fss_identify_data_t;

  #define fss_identify_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_fss_identify_data_t_

/**
 * Fully deallocate all memory.
 *
 * @param data
 *   The data to deallocate.
 */
#ifndef _di_fss_identify_data_delete_
  extern void fss_identify_data_delete(fss_identify_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
