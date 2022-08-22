/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common/generic definitions.
 *
 * iki_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 *
 * iki_read_block_*:
 *   - max:        The max block read size before checking for interrupt.
 *   - read_small: The block read size for small files.
 *   - read_large: The block read size for large files.
 */
#ifndef _di_iki_read_common_
  #define iki_read_common_allocation_large_d 256
  #define iki_read_common_allocation_small_d 16

  #define iki_read_block_max        16777216
  #define iki_read_block_read_small 8192
  #define iki_read_block_read_large 65536
#endif // _di_iki_read_common_

/**
 * The program data.
 *
 * argv:   The argument structure in the progam data parameters for simplifying syntax.
 * at:     The processed at parameter value.
 * buffer: The buffer containing the file.
 * line:   The processed line parameter value.
 * main:   The main program data.
 * mode:   The read mode to operate in.
 */
#ifndef _di_iki_read_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    uint8_t mode;

    f_number_unsigned_t at;
    f_number_unsigned_t line;

    f_string_dynamic_t buffer;
  } iki_read_data_t;

  #define iki_read_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_iki_read_data_t_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_read_data_delete_
  extern f_status_t iki_read_data_delete(fll_program_data_t * const main, status_code_setting_t * const setting, iki_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
