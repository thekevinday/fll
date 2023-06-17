#include "account.h"
#include "account/accounts.h"
#include "private-account.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)
  f_status_t private_f_account_from_passwd(const struct passwd password, const f_number_unsigned_t password_length, f_account_t * const account) {

    f_status_t status = F_none;

    // Account UID and GID.
    account->id_user = password.pw_uid;
    account->id_group = password.pw_gid;

    // Account home directory.
    f_number_unsigned_t string_length = strnlen(password.pw_dir, password_length);

    account->home.used = 0;

    status = f_string_dynamic_increase_by(string_length + 1, &account->home);
    if (F_status_is_error(status)) return status;

    memcpy(account->home.string, password.pw_dir, sizeof(f_char_t) * string_length);

    account->home.string[string_length] = 0;
    account->home.used = string_length;

    // Account label (gecos).
    string_length = strnlen(password.pw_gecos, password_length);

    account->label.used = 0;

    status = f_string_dynamic_increase_by(string_length + 1, &account->label);
    if (F_status_is_error(status)) return status;

    memcpy(account->label.string, password.pw_gecos, sizeof(f_char_t) * string_length);

    account->label.string[string_length] = 0;
    account->label.used = string_length;

    // Account name.
    string_length = strnlen(password.pw_name, password_length);

    account->name.used = 0;

    status = f_string_dynamic_increase_by(string_length + 1, &account->name);
    if (F_status_is_error(status)) return status;

    memcpy(account->name.string, password.pw_name, sizeof(f_char_t) * string_length);

    account->name.string[string_length] = 0;
    account->name.used = string_length;

    // Account password directory.
    string_length = strnlen(password.pw_passwd, password_length);

    account->password.used = 0;

    status = f_string_dynamic_increase_by(string_length + 1, &account->password);
    if (F_status_is_error(status)) return status;

    memcpy(account->password.string, password.pw_passwd, sizeof(f_char_t) * string_length);

    account->password.string[string_length] = 0;
    account->password.used = string_length;

    // Account shell directory.
    string_length = strnlen(password.pw_shell, password_length);

    account->shell.used = 0;

    status = f_string_dynamic_increase_by(string_length + 1, &account->shell);
    if (F_status_is_error(status)) return status;

    memcpy(account->shell.string, password.pw_shell, sizeof(f_char_t) * string_length);

    account->shell.string[string_length] = 0;
    account->shell.used = string_length;

    return F_none;
  }
#endif // !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)

#ifdef __cplusplus
} // extern "C"
#endif
