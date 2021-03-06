#include "account.h"
#include "private-account.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)
  f_status_t private_f_account_from_passwd(const struct passwd password, const f_array_length_t password_length, f_account_t *account) {
    f_status_t status = F_none;


    // Account UID and GID.
    account->id_user = password.pw_uid;
    account->id_group = password.pw_gid;


    // account home directory.
    f_array_length_t string_length = strnlen(password.pw_dir, password_length);

    f_macro_string_dynamic_t_resize(status, account->home, string_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(account->home.string, password.pw_dir, string_length);

    account->home.string[string_length] = 0;
    account->home.used = string_length;


    // account label (gecos).
    string_length = strnlen(password.pw_gecos, password_length);

    f_macro_string_dynamic_t_resize(status, account->label, string_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(account->label.string, password.pw_gecos, string_length);

    account->label.string[string_length] = 0;
    account->label.used = string_length;


    // account name.
    string_length = strnlen(password.pw_name, password_length);

    f_macro_string_dynamic_t_resize(status, account->name, string_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(account->name.string, password.pw_name, string_length);

    account->name.string[string_length] = 0;
    account->name.used = string_length;


    // account password directory.
    string_length = strnlen(password.pw_passwd, password_length);

    f_macro_string_dynamic_t_resize(status, account->password, string_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(account->password.string, password.pw_passwd, string_length);

    account->password.string[string_length] = 0;
    account->password.used = string_length;


    // account shell directory.
    string_length = strnlen(password.pw_shell, password_length);

    f_macro_string_dynamic_t_resize(status, account->shell, string_length + 1);
    if (F_status_is_error(status)) return status;

    memcpy(account->shell.string, password.pw_shell, string_length);

    account->shell.string[string_length] = 0;
    account->shell.used = string_length;

    return F_none;
  }
#endif // !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)

#ifdef __cplusplus
} // extern "C"
#endif
