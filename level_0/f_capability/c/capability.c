#include "capability.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_ambient_get_
    f_status_t f_capability_ambient_get(const f_capability_value_t value, int *ambient) {
      #ifndef _di_level_0_parameter_checking_
        if (!ambient) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_ambient_get_

  #ifndef _di_f_capability_ambient_reset_
    f_status_t f_capability_ambient_reset(void) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_ambient_reset_

  #ifndef _di_f_capability_ambient_set_
    f_status_t f_capability_ambient_set(const f_capability_value_t value, const f_capability_flag_value_t value_flag) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_ambient_set_

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#ifdef _di_libcap_

  #ifndef _di_f_capability_clear_
    f_status_t f_capability_clear(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_clear_

  #ifndef _di_f_capability_clear_flag_
    f_status_t f_capability_clear_flag(const f_capability_flag_t flag, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_clear_flag_

  #ifndef _di_f_capability_compare_
    f_status_t f_capability_compare(const f_capability_t capability1, const f_capability_t capability2, int *flags) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_compare_

  #ifndef _di_f_capability_copy_
    f_status_t f_capability_copy(const f_capability_t source, f_capability_t *destination) {
      #ifndef _di_level_0_parameter_checking_
        if (!destination) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_copy_

  #ifndef _di_f_capability_copy_external_
    f_status_t f_capability_copy_external(const f_capability_t capability, const ssize_t max, void *external, ssize_t *size) {
      #ifndef _di_level_0_parameter_checking_
        if (!external) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_copy_external_

  #ifndef _di_f_capability_copy_internal_
    f_status_t f_capability_copy_internal(const void *external, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!external) return F_status_set_error(F_parameter);
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_copy_internal_

  #ifndef _di_f_capability_delete_
    f_status_t f_capability_delete(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_delete_

  #ifndef _di_f_capability_file_descriptor_get_
    f_status_t f_capability_file_descriptor_get(const int descriptor, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_file_descriptor_get_

  #ifndef _di_f_capability_file_descriptor_set_
    f_status_t f_capability_file_descriptor_set(const int descriptor, const f_capability_t capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_file_descriptor_set_

  #ifndef _di_f_capability_file_get_
    f_status_t f_capability_file_get(const f_string_t path, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_file_get_

  #ifndef _di_f_capability_file_set_
    f_status_t f_capability_file_set(const f_string_t path, const f_capability_t capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_file_set_

  #ifndef _di_f_capability_flag_get_
    f_status_t f_capability_flag_get(const f_capability_t capability, const f_capability_value_t code, const f_capability_flag_t flag, f_capability_flag_value_t *enabled) {
      #ifndef _di_level_0_parameter_checking_
        if (!enabled) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_flag_get_

  #ifndef _di_f_capability_flag_set_
    f_status_t f_capability_flag_set(const f_capability_flag_t flag, const f_capability_flag_value_t enabled, const f_int32s_t codes, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_flag_set_

  #ifndef _di_f_capability_from_name_
    f_status_t f_capability_from_name(const f_string_t name, f_capability_value_t *code) {
      #ifndef _di_level_0_parameter_checking_
        if (!code) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_from_name_

  #ifndef _di_f_capability_from_text_
    f_status_t f_capability_from_text(const f_string_t text, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_from_text_

#endif // _di_libcap_

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_groups_set_
    f_status_t f_capability_groups_set(const gid_t id_group, const size_t total, const gid_t id_groups[]) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_groups_set_

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#ifdef _di_libcap_

  #ifndef _di_f_capability_initialize_
    f_status_t f_capability_initialize(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_initialize_

#endif // _di_libcap_

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_mode_get_
    f_status_t f_capability_mode_get(f_capability_mode_t *mode) {
      #ifndef _di_level_0_parameter_checking_
        if (!mode) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_mode_get_

  #ifndef _di_f_capability_mode_get_name_
    f_status_t f_capability_mode_get_name(const f_capability_mode_t mode, f_string_constant_t *name) {
      #ifndef _di_level_0_parameter_checking_
        if (!name) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_mode_get_name_

  #ifndef _di_f_capability_mode_set_
    f_status_t f_capability_mode_set(const f_capability_mode_t mode) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_mode_set_

  #ifndef _di_f_capability_owner_get_
    f_status_t f_capability_owner_get(const f_capability_t capability, uid_t *id_user) {
      #ifndef _di_level_0_parameter_checking_
        if (!id_user) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_owner_get_

  #ifndef _di_f_capability_owner_set_
    f_status_t f_capability_owner_set(const f_capability_t capability, const uid_t id_user) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_owner_set_

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#ifdef _di_libcap_

  #ifndef _di_f_capability_process_bound_drop_
    f_status_t f_capability_process_bound_drop(f_capability_value_t code, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_process_bound_drop_

  #ifndef _di_f_capability_process_bound_get_
    f_status_t f_capability_process_bound_get(f_capability_value_t code, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_process_bound_get_

  #ifndef _di_f_capability_process_get_
    f_status_t f_capability_process_get(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_process_get_

  #ifndef _di_f_capability_process_get_by_id_
    f_status_t f_capability_process_get_by_id(const pid_t id, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_process_get_by_id_

  #ifndef _di_f_capability_process_set_
    f_status_t f_capability_process_set(const f_capability_t capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_process_set_

#endif // _di_libcap_

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_security_bits_get_
    f_status_t f_capability_security_bits_get(f_capability_bits_t *bits) {
      #ifndef _di_level_0_parameter_checking_
        if (!bits) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_security_bits_get_

  #ifndef _di_f_capability_security_bits_set_
    f_status_t f_capability_security_bits_set(const f_capability_bits_t bits) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_security_bits_set_

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#ifdef _di_libcap_

  #ifndef _di_f_capability_size_
    f_status_t f_capability_size(const f_capability_t capability, ssize_t *size) {
      #ifndef _di_level_0_parameter_checking_
        if (!size) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_size_

  #ifndef _di_f_capability_supported_
    bool f_capability_supported(void) {
      return F_false;
    }
  #endif // _di_f_capability_supported_

#endif // _di_libcap_

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_supported_ambient_
    bool f_capability_supported_ambient(void) {
      return F_false;
    }
  #endif // _di_f_capability_supported_ambient_

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#ifdef _di_libcap_

  #ifndef _di_f_capability_supported_code_
    bool f_capability_supported_code(const f_capability_value_t code) {
      return F_false;
    }
  #endif // _di_f_capability_supported_code_

  #ifndef _di_f_capability_to_name_
    f_status_t f_capability_to_name(const int code, f_string_dynamic_t *name) {
      #ifndef _di_level_0_parameter_checking_
        if (!name) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_to_name_

  #ifndef _di_f_capability_to_text_
    f_status_t f_capability_to_text(const f_capability_t capability, f_string_dynamic_t *text) {
      #ifndef _di_level_0_parameter_checking_
        if (!text) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_to_text_

#endif // _di_libcap_

#if defined(_di_libcap_) || defined(_libcap_legacy_only_)

  #ifndef f_capability_user_set
    f_status_t f_capability_user_set(const uid_t id_user) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // f_capability_user_set

#endif // defined(_di_libcap_) || defined(_libcap_legacy_only_)

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_ambient_get_
    f_status_t f_capability_ambient_get(const f_capability_value_t value, int *ambient) {
      #ifndef _di_level_0_parameter_checking_
        if (!ambient) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *ambient = cap_get_ambient(value);

      if (*ambient == -1) {
        return F_status_set_error(F_supported_not);
      }

      return F_none;
    }
  #endif // _di_f_capability_ambient_get_

  #ifndef _di_f_capability_ambient_reset_
    f_status_t f_capability_ambient_reset(void) {

      if (cap_reset_ambient() == -1) {

        // The documentation doesn't explicitly describe this for "reset" but it can be implicitly inferred because they say "..all of the setting functions..".
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_ambient_reset_

  #ifndef _di_f_capability_ambient_set_
    f_status_t f_capability_ambient_set(const f_capability_value_t value, const f_capability_flag_value_t value_flag) {

      if (cap_set_ambient(value, value_flag) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_ambient_set_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifndef _di_libcap_

  #ifndef _di_f_capability_clear_
    f_status_t f_capability_clear(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_clear(*capability) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ERANGE) return F_status_set_error(F_range_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_clear_

  #ifndef _di_f_capability_clear_flag_
    f_status_t f_capability_clear_flag(const f_capability_flag_t flag, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_clear_flag(*capability, flag) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_clear_flag_

  #ifndef _di_f_capability_compare_
    f_status_t f_capability_compare(const f_capability_t capability1, const f_capability_t capability2, int *flags) {

      if (flags) {
        *flags = 0;
      }

      const int result = cap_compare(capability1, capability2);

      if (result == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      if (result) {
        if (flags) {
          *flags = result;
        }

        return F_equal_to_not;
      }

      return F_equal_to;
    }
  #endif // _di_f_capability_compare_

  #ifndef _di_f_capability_copy_
    f_status_t f_capability_copy(const f_capability_t source, f_capability_t *destination) {
      #ifndef _di_level_0_parameter_checking_
        if (!destination) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *destination = cap_dup(source);

      if (*destination) {
        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_copy_

  #ifndef _di_f_capability_copy_external_
    f_status_t f_capability_copy_external(const f_capability_t capability, const ssize_t max, void *external, ssize_t *size) {
      #ifndef _di_level_0_parameter_checking_
        if (!external) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      const ssize_t result = cap_copy_ext(external, capability, max);

      if (result == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ERANGE) return F_status_set_error(F_range_not);

        return F_status_set_error(F_failure);
      }

      if (size) *size = result;

      return F_none;
    }
  #endif // _di_f_capability_copy_external_

  #ifndef _di_f_capability_copy_internal_
    f_status_t f_capability_copy_internal(const void *external, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!external) return F_status_set_error(F_parameter);
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_copy_int(external);

      if (*capability) {
        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_range_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_copy_internal_

  #ifndef _di_f_capability_delete_
    f_status_t f_capability_delete(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_free((void *) *capability) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        return F_status_set_error(F_failure);
      }

      *capability = 0;

      return F_none;
    }
  #endif // _di_f_capability_delete_

  #ifndef _di_f_capability_file_descriptor_get_
    f_status_t f_capability_file_descriptor_get(const int descriptor, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_get_fd(descriptor);

      if (*capability) {
        return F_none;
      }

      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADFD) return F_status_set_error(F_descriptor_not);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_file_descriptor_get_

  #ifndef _di_f_capability_file_descriptor_set_
    f_status_t f_capability_file_descriptor_set(const int descriptor, const f_capability_t capability) {

      const int result = cap_set_fd(descriptor, capability);

      if (result == -1) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EBADFD) return F_status_set_error(F_descriptor_not);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
        if (errno == ENOENT) return F_status_set_error(F_file_found_not);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);
        if (errno == EROFS) return F_status_set_error(F_supported_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_file_descriptor_set_

  #ifndef _di_f_capability_file_get_
    f_status_t f_capability_file_get(const f_string_t path, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_get_file(path);

      if (*capability) {
        return F_none;
      }

      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADFD) return F_status_set_error(F_descriptor_not);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_file_get_

  #ifndef _di_f_capability_file_set_
    f_status_t f_capability_file_set(const f_string_t path, const f_capability_t capability) {

      const int result = cap_set_file(path, capability);

      if (result == -1) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EBADFD) return F_status_set_error(F_descriptor_not);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
        if (errno == ENOENT) return F_status_set_error(F_file_found_not);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);
        if (errno == EROFS) return F_status_set_error(F_supported_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_file_set_

  #ifndef _di_f_capability_flag_get_
    f_status_t f_capability_flag_get(const f_capability_t capability, const f_capability_value_t code, const f_capability_flag_t flag, f_capability_flag_value_t *enabled) {
      #ifndef _di_level_0_parameter_checking_
        if (!enabled) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_get_flag(capability, code, flag, enabled) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_flag_get_

  #ifndef _di_f_capability_flag_set_
    f_status_t f_capability_flag_set(const f_capability_flag_t flag, const f_capability_flag_value_t enabled, const f_int32s_t codes, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_set_flag(*capability, flag, codes.used, codes.array, enabled) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_flag_set_

  #ifndef _di_f_capability_from_name_
    f_status_t f_capability_from_name(const f_string_t name, f_capability_value_t *code) {
      #ifndef _di_level_0_parameter_checking_
        if (!code) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      if (cap_from_name(name, code) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_from_name_

  #ifndef _di_f_capability_from_text_
    f_status_t f_capability_from_text(const f_string_t text, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_from_text(text);

      if (*capability) {
        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_from_text_

#endif // _di_libcap_

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_groups_set_
    f_status_t f_capability_groups_set(const gid_t id_group, const size_t total, const gid_t id_groups[]) {

      if (cap_setgroups(id_group, total, id_groups) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ERANGE) return F_status_set_error(F_range_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_groups_set_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifndef _di_libcap_

  #ifndef _di_f_capability_initialize_
    f_status_t f_capability_initialize(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_init();

      if (*capability) {
        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_initialize_

#endif // _di_libcap_

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_mode_get_
    f_status_t f_capability_mode_get(f_capability_mode_t *mode) {
      #ifndef _di_level_0_parameter_checking_
        if (!mode) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *mode = cap_get_mode();

      return F_none;
    }
  #endif // _di_f_capability_mode_get_

  #ifndef _di_f_capability_mode_get_name_
    f_status_t f_capability_mode_get_name(const f_capability_mode_t mode, f_string_constant_t *name) {
      #ifndef _di_level_0_parameter_checking_
        if (!mode) return F_status_set_error(F_parameter);
        if (!name) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *name = cap_mode_name(mode);

      return F_none;
    }
  #endif // _di_f_capability_mode_get_name_

  #ifndef _di_f_capability_mode_set_
    f_status_t f_capability_mode_set(const f_capability_mode_t mode) {

      if (cap_set_mode(mode) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_mode_set_

  #ifndef _di_f_capability_owner_get_
    f_status_t f_capability_owner_get(const f_capability_t capability, uid_t *id_user) {
      #ifndef _di_level_0_parameter_checking_
        if (!id_user) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *id_user = cap_get_nsowner(capability);

      return F_none;
    }
  #endif // _di_f_capability_owner_get_

  #ifndef _di_f_capability_owner_set_
    f_status_t f_capability_owner_set(const f_capability_t capability, const uid_t id_user) {

      if (cap_set_nsowner(capability, id_user) == -1) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EBADFD) return F_status_set_error(F_descriptor_not);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_name_not);
        if (errno == ENOENT) return F_status_set_error(F_file_found_not);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);
        if (errno == EROFS) return F_status_set_error(F_supported_not);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_owner_set_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifndef _di_libcap_

  #ifndef _di_f_capability_process_bound_drop_
    f_status_t f_capability_process_bound_drop(f_capability_value_t value, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *bound = cap_drop_bound(value);

      if (*bound == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_process_bound_drop_

  #ifndef _di_f_capability_process_bound_get_
    f_status_t f_capability_process_bound_get(f_capability_value_t value, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *bound = cap_get_bound(value);

      if (*bound == -1) {
        return F_status_set_error(F_known_not);
      }

      return F_none;
    }
  #endif // _di_f_capability_process_bound_get_

  #ifndef _di_f_capability_process_get_
    f_status_t f_capability_process_get(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_get_proc();

      if (*capability) {
        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_process_get_

  #ifndef _di_f_capability_process_get_by_id_
    f_status_t f_capability_process_get_by_id(const pid_t id, f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *capability = cap_get_pid(id);

      if (*capability) {
        return F_none;
      }

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_process_get_by_id_

  #ifndef _di_f_capability_process_set_
    f_status_t f_capability_process_set(const f_capability_t capability) {

      if (cap_set_proc(capability) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_process_set_

#endif // _di_libcap_

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_security_bits_get_
    f_status_t f_capability_security_bits_get(f_capability_bits_t *bits) {
      #ifndef _di_level_0_parameter_checking_
        if (!bits) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *bits = cap_get_secbits();

      return F_none;
    }
  #endif // _di_f_capability_security_bits_get_

  #ifndef _di_f_capability_security_bits_set_
    f_status_t f_capability_security_bits_set(const f_capability_bits_t bits) {

      if (cap_set_secbits(bits) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_security_bits_set_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifndef _di_libcap_

  #ifndef _di_f_capability_size_
    f_status_t f_capability_size(const f_capability_t capability, ssize_t *size) {
      #ifndef _di_level_0_parameter_checking_
        if (!size) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *size = cap_size(capability);

      if (*size == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_size_

  #ifndef _di_f_capability_supported_
    bool f_capability_supported(void) {
      return F_true;
    }
  #endif // _di_f_capability_supported_

#endif // _di_libcap_

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_supported_ambient_
    bool f_capability_supported_ambient(void) {

      if (CAP_AMBIENT_SUPPORTED()) {
        return F_true;
      }

      return F_false;
    }
  #endif // _di_f_capability_supported_ambient_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifndef _di_libcap_

  #ifndef _di_f_capability_supported_code_
    bool f_capability_supported_code(const f_capability_value_t code) {

      if (CAP_IS_SUPPORTED(code)) {
        return F_true;
      }

      return F_false;
    }
  #endif // _di_f_capability_supported_code_

  #ifndef _di_f_capability_to_name_
    f_status_t f_capability_to_name(const int code, f_string_dynamic_t *name) {
      #ifndef _di_level_0_parameter_checking_
        if (!name) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      char *result = cap_to_name(code);

      if (result) {
        const f_array_length_t length = strlen(result);

        if (name->used + length + 1 > name->size) {
          if (name->used + length + 1 > F_string_t_size_d) {
            return F_status_set_error(F_string_too_large);
          }

          const f_status_t status = f_string_dynamic_resize(name->used + length + 1, name);

          if (F_status_is_error(status)) {
            cap_free(result);

            return status;
          }
        }

        memcpy(name->string + name->used, result, length);
        name->used += length;
        name->string[name->used] = 0;

        cap_free(result);

        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_to_name_

  #ifndef _di_f_capability_to_text_
    f_status_t f_capability_to_text(const f_capability_t capability, f_string_dynamic_t *text) {
      #ifndef _di_level_0_parameter_checking_
        if (!text) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      ssize_t length = 0;

      char *result = cap_to_text(capability, &length);

      if (result) {
        if (text->used + length + 1 > text->size) {
          if (text->used + length + 1 > F_string_t_size_d) {
            return F_status_set_error(F_string_too_large);
          }

          const f_status_t status = f_string_dynamic_resize(text->used + length + 1, text);

          if (F_status_is_error(status)) {
            cap_free(result);

            return status;
          }
        }

        memcpy(text->string + text->used, result, length);
        text->used += length;
        text->string[text->used] = 0;

        cap_free(result);

        return F_none;
      }

      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }
  #endif // _di_f_capability_to_text_

#endif // _di_libcap_

#if !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

  #ifndef _di_f_capability_user_set_
    f_status_t f_capability_user_set(const uid_t id_user) {

      if (cap_setuid(id_user) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }

      return F_none;
    }
  #endif // _di_f_capability_user_set_

#endif // !defined(_di_libcap_) && !defined(_libcap_legacy_only_)

#ifdef __cplusplus
} // extern "C"
#endif
