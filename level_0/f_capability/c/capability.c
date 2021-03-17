#include "capability.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _di_libcap_

  #ifndef _di_f_capability_clear_
    f_status_t f_capability_clear(f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_clear_

  #ifndef _di_f_capability_clear_flag_
    f_status_t f_capability_clear_flag(const f_capability_flag_t flag, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_clear_flag_

  #ifndef _di_f_capability_compare_
    f_status_t f_capability_compare(const f_capability_t capability1, const f_capability_t capability2, int *flags) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_compare_

  #ifndef _di_f_capability_copy_external_
    f_status_t f_capability_copy_external(const f_capability_t capability, const ssize_t max, void *external, ssize_t *size) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_copy_external_

  #ifndef _di_f_capability_copy_internal_
    f_status_t f_capability_copy_internal(const void *external, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_copy_internal_

  #ifndef _di_f_capability_delete_
    f_status_t f_capability_delete(f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_delete_

  #ifndef _di_f_capability_duplicate_
    f_status_t f_capability_duplicate(const f_capability_t source, f_capability_t *destination) {
      #ifndef _di_level_0_parameter_checking_
        if (!destination) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_duplicate_

  #ifndef _di_f_capability_flag_get_
    f_status_t f_capability_flag_get(const f_capability_t capability, const f_capability_value_t code, const f_capability_flag_t flag, f_capability_flag_value_t *enabled) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_flag_get_

  #ifndef _di_f_capability_flag_set_
    f_status_t f_capability_flag_set(const f_capability_flag_t flag, const f_capability_flag_value_t enabled, const f_int32s_t codes, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_flag_set_

  #ifndef _di_f_capability_from_name_
    f_status_t f_capability_from_name(const f_string_t name, f_capability_value_t *code) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_from_name_

  #ifndef _di_f_capability_from_text_
    f_status_t f_capability_from_text(const f_string_t text, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_from_text_

  #ifndef _di_f_capability_get_file_
    f_status_t f_capability_get_file(const f_string_t path, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_get_file_

  #ifndef _di_f_capability_get_file_descriptor_
    f_status_t f_capability_get_file_descriptor(const int descriptor, f_capability_t *capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_get_file_descriptor_

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

  #ifndef _di_f_capability_initialize_
    f_status_t f_capability_initialize(f_capability_t *capability) {
      #ifndef _di_level_0_parameter_checking_
        if (!capability) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_initialize_

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

  #ifndef _di_f_capability_set_file_
    f_status_t f_capability_set_file(const f_string_t path, const f_capability_t capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_set_file_

  #ifndef _di_f_capability_set_file_descriptor_
    f_status_t f_capability_set_file_descriptor(const int descriptor, const f_capability_t capability) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_set_file_descriptor_

  #ifndef _di_f_capability_size_
    f_status_t f_capability_size(const f_capability_t capability, ssize_t *size) {
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_size_

  #ifndef _di_f_capability_supported_
    bool f_capability_supported() {
      return F_false;
    }
  #endif // _di_f_capability_supported_

  #ifndef _di_f_capability_supported_ambient_
    bool f_capability_supported_ambient() {
      return F_false;
    }
  #endif // _di_f_capability_supported_ambient_

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
      return F_status_set_error(F_implemented_not);
    }
  #endif // _di_f_capability_to_text_

#else // _di_libcap_

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
      if (*flags) {
        *flags = 0;
      }

      const int result = cap_compare(capability1, capability2);

      if (result == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      if (result) {
        if (*flags) {
          *flags = result;
        }

        return F_equal_to_not;
      }

      return F_equal_to;
    }
  #endif // _di_f_capability_compare_

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

      if (cap_free(*capability) == -1) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        return F_status_set_error(F_failure);
      }

      *capability = 0;

      return F_none;
    }
  #endif // _di_f_capability_delete_

  #ifndef _di_f_capability_duplicate_
    f_status_t f_capability_duplicate(const f_capability_t source, f_capability_t *destination) {
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
  #endif // _di_f_capability_duplicate_

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

  #ifndef _di_f_capability_get_file_
    f_status_t f_capability_get_file(const f_string_t path, f_capability_t *capability) {
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
  #endif // _di_f_capability_get_file_

  #ifndef _di_f_capability_get_file_descriptor_
    f_status_t f_capability_get_file_descriptor(const int descriptor, f_capability_t *capability) {
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
  #endif // _di_f_capability_get_file_descriptor_

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

  #ifndef _di_f_capability_process_bound_drop_
    f_status_t f_capability_process_bound_drop(f_capability_value_t code, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *bound = cap_drop_bound(code);

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
    f_status_t f_capability_process_bound_get(f_capability_value_t code, int *bound) {
      #ifndef _di_level_0_parameter_checking_
        if (!bound) return F_status_set_error(F_parameter);
      #endif // _di_level_0_parameter_checking_

      *bound = cap_get_bound(code);

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

  #ifndef _di_f_capability_set_file_
    f_status_t f_capability_set_file(const f_string_t path, const f_capability_t capability) {

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
  #endif // _di_f_capability_set_file_

  #ifndef _di_f_capability_set_file_descriptor_
    f_status_t f_capability_set_file_descriptor(const int descriptor, const f_capability_t capability) {

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
  #endif // _di_f_capability_set_file_descriptor_

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
    bool f_capability_supported() {
      return F_true;
    }
  #endif // _di_f_capability_supported_

  #ifndef _di_f_capability_supported_ambient_
    bool f_capability_supported_ambient() {
      return CAP_AMBIENT_SUPPORTED();
    }
  #endif // _di_f_capability_supported_ambient_

  #ifndef _di_f_capability_supported_code_
    bool f_capability_supported_code(const f_capability_value_t code) {
      return CAP_IS_SUPPORTED(code);
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
          if (name->used + length + 1 > f_array_length_t_size) {
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

      f_array_length_t length = 0;

      char *result = cap_to_text(capability, &length);

      if (result) {
        if (text->used + length + 1 > text->size) {
          if (text->used + length + 1 > f_array_length_t_size) {
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

#ifdef __cplusplus
} // extern "C"
#endif
