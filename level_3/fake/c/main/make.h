/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_h
#define _fake_make_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Assure that a path is within the project root path.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The data_make.cache_path will be updated to reflect the full path to this file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_true if inside the project.
 *     F_false (with error bit) if path exists outside of the root project path.
 *
 *     Errors (with error bit) from: fl_string_dynamic_partial_compare()
 *     Errors (with error bit) from: fl_path_canonical()
 * @param path
 *   file path to get the real path of.
 *
 * @see fl_string_dynamic_partial_compare()
 * @see fl_path_canonical()
 */
#ifndef _di_fake_make_assure_inside_project_
  extern void fake_make_assure_inside_project(fake_make_data_t * const data_make, const f_string_static_t path);
#endif // _di_fake_make_assure_inside_project_

/**
 * Get the group id from either a string representing the number or a string representing the name.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The data_make.cache_path will be updated to reflect the full path to this file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *     F_exist_not (with error bit) if there is no owner or group by the given name.
 *     F_parameter (with error bit) on invalid parameter.
 *
 *     Errors (with error bit) from: f_account_group_id_by_name()
 *     Errors (with error bit) from: f_account_id_by_name()
 *     Errors (with error bit) from: fl_conversion_dynamic_to_unsigned_detect()
 * @param is_owner
 *   If TRUE, then buffer represents a UID.
 *   If FALSE, then buffer represents a GID.
 * @param buffer
 *   The string containing the name or number.
 *
 * @return
 *   The detected owner id or group id.
 *   When is_owner is TRUE, then this should be cast to type (uid_t *).
 *   When is_owner is TRUE, then this should be cast to type (gid_t *).
 *   This is set to 0 on any error, check data_make.main->setting.state.status for error.
 *
 * @see f_account_group_id_by_name()
 * @see f_account_id_by_name()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#ifndef _di_fake_make_get_id_
  extern f_number_unsigned_t fake_make_get_id(fake_make_data_t * const data_make, const bool is_owner, const f_string_static_t buffer);
#endif // _di_fake_make_get_id_

/**
 * Get the mode id from either a string representing the number or a string representing the mode.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The data_make.cache_path will be updated to reflect the full path to this file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *     F_parameter (with error bit) on invalid parameter.
 *
 *     Errors (with error bit) from: f_file_mode_from_string()
 * @param buffer
 *   The string containing the name or number.
 * @param mode
 *   The determined mode.
 *   This uses bitwise data.
 * @param replace
 *   The determined modes that are to be replaced, such as: F_file_mode_t_replace_owner_d.
 *   This uses bitwise data.
 *
 * @see f_file_mode_from_string()
 */
#ifndef _di_fake_make_get_id_mode_
  extern void fake_make_get_id_mode(fake_make_data_t * const data_make, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace);
#endif // _di_fake_make_get_id_mode_

/**
 * Get a path, relative to the project root.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   The relative path is stored in data_make.cache_path.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *     F_parameter (with error bit) on invalid parameter.
 *
 *     Errors (with error bit) from: f_file_mode_from_string()
 * @param path
 *   The NULL terminated path to get the relative path of.
 *
 * @see f_string_dynamic_partial_append()
 * @see f_string_dynamic_terminate()
 */
#ifndef _di_fake_make_path_relative_
  extern void fake_make_path_relative(fake_make_data_t * const data_make, const f_string_static_t path);
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_h
