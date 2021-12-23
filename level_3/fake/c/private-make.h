/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_h
#define _PRIVATE_make_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Assure that a path is within the project root path.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The data_make.path_cache will be updated to reflect the full path to this file.
 * @param path
 *   file path to get the real path of.
 *
 * @return
 *   F_true if inside the project.
 *   F_false (with error bit) if path exists outside of the root project path.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_assure_inside_project_
  extern f_status_t fake_make_assure_inside_project(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_static_t path) F_attribute_visibility_internal_d;
#endif // _di_fake_make_assure_inside_project_

/**
 * Get the group id from either a string representing the number or a string representing the name.
 *
 * @param main
 *   The main program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected group id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no group by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_group_
  f_status_t fake_make_get_id_group(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, gid_t *id) F_attribute_visibility_internal_d;
#endif // _di_fake_make_get_id_group_

/**
 * Get the mode id from either a string representing the number or a string representing the mode.
 *
 * @param main
 *   The main program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param mode
 *   The determined mode.
 *   This uses bitwise data.
 * @param replace
 *   The determined modes that are to be replaced, such as: F_file_mode_t_replace_owner_d.
 *   This uses bitwise data.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no mode by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_mode_
  f_status_t fake_make_get_id_mode(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace) F_attribute_visibility_internal_d;
#endif // _di_fake_make_get_id_mode_

/**
 * Get the user id from either a string representing the number or a string representing the name.
 *
 * @param main
 *   The main program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected user id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no user by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_owner_
  f_status_t fake_make_get_id_owner(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, uid_t *id) F_attribute_visibility_internal_d;
#endif // _di_fake_make_get_id_owner_

/**
 * Get a path, relative to the project root.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The relative path is stored in data_make.path_cache.
 * @param path
 *   The NULL terminated path to get the relative path of.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_path_relative_
  extern f_status_t fake_make_path_relative(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_static_t path) F_attribute_visibility_internal_d;
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_h
