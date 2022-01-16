#include "account.h"
#include "private-account.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_by_id_
  f_status_t f_account_by_id(const uid_t id, f_account_t *account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    account->id_user = 0;
    account->id_group = 0;
    account->home.used = 0;
    account->label.used = 0;
    account->name.used = 0;
    account->password.used = 0;
    account->shell.used = 0;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct passwd password;
    struct passwd *pointer = 0;

    size_t length = length_max;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getpwuid()/getpwuid_r().
      errno = 0;

      char buffer[length];
      const int result = getpwuid_r(id, &password, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        return private_f_account_from_passwd(password, length, account);
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getpwuid_r(id, &password, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    return private_f_account_from_passwd(password, length, account);
  }
#endif // _di_f_account_by_id_

#ifndef _di_f_account_by_name_
  f_status_t f_account_by_name(const f_string_t name, f_account_t *account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    account->id_user = 0;
    account->id_group = 0;
    account->home.used = 0;
    account->label.used = 0;
    account->name.used = 0;
    account->password.used = 0;
    account->shell.used = 0;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct passwd password;
    struct passwd *pointer = 0;

    size_t length = length_max;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getpwnam()/getpwnam_r().
      errno = 0;

      char buffer[length];
      const int result = getpwnam_r(name, &password, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        return private_f_account_from_passwd(password, length, account);
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getpwnam_r(name, &password, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    return private_f_account_from_passwd(password, length, account);
  }
#endif // _di_f_account_by_name_

#ifndef _di_f_account_group_id_by_name_
  f_status_t f_account_group_id_by_name(const f_string_t name, gid_t *id) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct group group_data;
    struct group *pointer;

    size_t length = length_max;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getgrnam()/getgrnam_r().
      errno = 0;

      char buffer[length];
      int result = getgrnam_r(name, &group_data, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        *id = group_data.gr_gid;

        return F_none;
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getgrnam_r(name, &group_data, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    *id = group_data.gr_gid;

    return F_none;
  }
#endif // _di_f_account_group_id_by_name_

#ifndef _di_f_account_group_name_by_id_
  f_status_t f_account_group_name_by_id(const gid_t id, f_string_dynamic_t *name) {
    #ifndef _di_level_0_parameter_checking_
      if (!name) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    name->used = 0;

    f_status_t status = F_none;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct group group_data;
    struct group *pointer = 0;

    size_t length = length_max + 1;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getpwuid()/getpwuid_r().
      errno = 0;

      char buffer[length];
      const int result = getgrgid_r(id, &group_data, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        const f_array_length_t name_length = strnlen(group_data.gr_name, length);

        macro_f_string_dynamic_t_resize(status, (*name), name_length + 1);
        if (F_status_is_error(status)) return status;

        memcpy(name->string, group_data.gr_name, name_length);

        name->string[name_length] = 0;
        name->used = name_length;

        return F_none;
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getgrgid_r(id, &group_data, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    const f_array_length_t name_length = strnlen(group_data.gr_name, length);

    macro_f_string_dynamic_t_resize(status, (*name), name_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(name->string, group_data.gr_name, name_length);

    name->string[name_length] = 0;
    name->used = name_length;

    return F_none;
  }
#endif // _di_f_account_group_name_by_id_

#ifndef _di_f_account_id_by_name_
  f_status_t f_account_id_by_name(const f_string_t name, uid_t *id) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct passwd password;
    struct passwd *pointer = 0;

    size_t length = length_max;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getpwnam()/getpwnam_r().
      errno = 0;

      char buffer[length];
      const int result = getpwnam_r(name, &password, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        *id = password.pw_uid;

        return F_none;
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getpwnam_r(name, &password, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    *id = password.pw_uid;

    return F_none;
  }
#endif // _di_f_account_id_by_name_

#ifndef _di_f_account_name_by_id_
  f_status_t f_account_name_by_id(const uid_t id, f_string_dynamic_t *name) {
    #ifndef _di_level_0_parameter_checking_
      if (!name) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    name->used = 0;

    f_status_t status = F_none;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // Pointer seems pointless except that it is used to determine if the name was found.
    struct passwd password;
    struct passwd *pointer = 0;

    size_t length = length_max + 1;

    {
      if (length == -1) {
        length = F_account_pwd_length_fallback_first_d;
      }

      // Must be set to 0 to avoid problems due to the design of getpwuid()/getpwuid_r().
      errno = 0;

      char buffer[length];
      const int result = getpwuid_r(id, &password, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        if (errno == ERANGE) {
          if (length_max > 0) return F_status_set_error(F_buffer_too_small);
        }
        else {
          return F_status_set_error(F_failure);
        }
      }
      else {
        if (!pointer) {
          return F_exist_not;
        }

        const f_array_length_t name_length = strnlen(password.pw_name, length);

        macro_f_string_dynamic_t_resize(status, (*name), name_length + 1);
        if (F_status_is_error(status)) return status;

        memcpy(name->string, password.pw_name, name_length);

        name->string[name_length] = 0;
        name->used = name_length;

        return F_none;
      }
    }

    length = F_account_pwd_length_fallback_second_d;

    char buffer[F_account_pwd_length_fallback_second_d];

    const int result = getpwuid_r(id, &password, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    const f_array_length_t name_length = strnlen(password.pw_name, length);

    macro_f_string_dynamic_t_resize(status, (*name), name_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(name->string, password.pw_name, name_length);

    name->string[name_length] = 0;
    name->used = name_length;

    return F_none;
  }
#endif // _di_f_account_name_by_id_

#ifdef __cplusplus
} // extern "C"
#endif
