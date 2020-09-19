#include "account.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_id_group_by_name_
  f_return_status f_account_id_group_by_name(const f_string_t name, gid_t *id) {
    f_status_t status = F_none;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // note: pointer seems pointless except that it is used to determine if the name was found.
    struct group grp;
    struct group *pointer;

    size_t length = length_max;

    {
      if (length == -1) {
        length = f_account_pwd_length_fallback_first;
      }

      // must be set to 0 to avoid problems due to the design of getgrnam()/getgrnam_r().
      errno = 0;

      char buffer[length];
      int result = getgrnam_r(name, &grp, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_out);

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

        *id = grp.gr_gid;

        return F_none;
      }
    }

    length = f_account_pwd_length_fallback_second;

    char buffer[f_account_pwd_length_fallback_second];

    const int result = getgrnam_r(name, &grp, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    *id = grp.gr_gid;

    return F_none;
  }
#endif // _di_f_account_id_group_by_name_

#ifndef _di_f_account_id_user_by_name_
  f_return_status f_account_id_user_by_name(const f_string_t name, uid_t *id) {
    f_status_t status = F_none;

    const size_t length_max = sysconf(_SC_GETPW_R_SIZE_MAX);

    // note: pointer seems pointless except that it is used to determine if the name was found.
    struct passwd password;
    struct passwd *pointer;

    size_t length = length_max;

    {
      if (length == -1) {
        length = f_account_pwd_length_fallback_first;
      }

      // must be set to 0 to avoid problems due to the design of getpwnam()/getpwnam_r().
      errno = 0;

      char buffer[length];
      const int result = getpwnam_r(name, &password, buffer, length, &pointer);

      if (result) {
        if (errno == EINTR) return F_status_set_error(F_interrupted);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENFILE) return F_status_set_error(F_file_open_max);
        if (errno == ENOMEM) return F_status_set_error(F_memory_out);

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

    length = f_account_pwd_length_fallback_second;

    char buffer[f_account_pwd_length_fallback_second];

    const int result = getpwnam_r(name, &password, buffer, length, &pointer);

    if (result) {
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (!pointer) {
      return F_exist_not;
    }

    *id = password.pw_uid;

    return F_none;
  }
#endif // _di_f_account_id_user_by_name_

#ifdef __cplusplus
} // extern "C"
#endif
