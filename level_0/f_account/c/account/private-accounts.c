#include "../account.h"
#include "accounts.h"
#include "private-accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_account_delete_) || !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  f_status_t private_f_account_delete(f_account_t *account) {

    f_status_t status = f_string_dynamic_resize(0, &account->home);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_resize(0, &account->label);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_resize(0, &account->name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_resize(0, &account->password);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_resize(0, &account->shell);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_account_delete_) || !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

#if !defined(_di_f_account_destroy_) || !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  f_status_t private_f_account_destroy(f_account_t *account) {

    f_status_t status = f_string_dynamic_adjust(0, &account->home);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_adjust(0, &account->label);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_adjust(0, &account->name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_adjust(0, &account->password);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_adjust(0, &account->shell);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_account_destroy_) || !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

#if !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  f_status_t private_f_accounts_adjust(const f_array_length_t length, f_accounts_t *accounts) {

    f_status_t status = F_none;

    if (length < accounts->size) {
      for (f_array_length_t i = length; i < accounts->size; ++i) {

        status = private_f_account_destroy(&accounts->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust(accounts->size, length, sizeof(f_account_t), (void **) & accounts->array);
    if (F_status_is_error(status)) return status;

    accounts->size = length;

    if (accounts->used > accounts->size) {
      accounts->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

#if !defined(_di_f_accounts_append_) || !defined(_di_f_accountss_append_)
  extern f_status_t private_f_accounts_append(const f_account_t source, f_accounts_t *destination) {

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_accounts_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].home.used = 0;
    destination->array[destination->used].label.used = 0;
    destination->array[destination->used].name.used = 0;
    destination->array[destination->used].password.used = 0;
    destination->array[destination->used].shell.used = 0;

    status = f_string_dynamic_append(source.home, &destination->array[destination->used].home);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.label, &destination->array[destination->used].label);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.name, &destination->array[destination->used].name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.password, &destination->array[destination->used].password);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.shell, &destination->array[destination->used].shell);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // !defined(_di_f_accounts_append_) || !defined(_di_f_accountss_append_)

#if !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)
  extern f_status_t private_f_accounts_append_all(const f_accounts_t source, f_accounts_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_accounts_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].home.used = 0;
      destination->array[destination->used].label.used = 0;
      destination->array[destination->used].name.used = 0;
      destination->array[destination->used].password.used = 0;
      destination->array[destination->used].shell.used = 0;

      status = f_string_dynamic_append(source.array[i].home, &destination->array[destination->used].home);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(source.array[i].label, &destination->array[destination->used].label);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(source.array[i].name, &destination->array[destination->used].name);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(source.array[i].password, &destination->array[destination->used].password);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_append(source.array[i].shell, &destination->array[destination->used].shell);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)

#if !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  f_status_t private_f_accounts_resize(const f_array_length_t length, f_accounts_t *accounts) {

    f_status_t status = F_none;

    if (length < accounts->size) {
      for (f_array_length_t i = length; i < accounts->size; ++i) {

        status = f_string_dynamic_resize(0, &accounts->array[i].home);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &accounts->array[i].label);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &accounts->array[i].name);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &accounts->array[i].password);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &accounts->array[i].shell);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize(accounts->size, length, sizeof(f_account_t), (void **) & accounts->array);
    if (F_status_is_error(status)) return status;

    accounts->size = length;

    if (accounts->used > accounts->size) {
      accounts->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

#if !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  f_status_t private_f_accountss_adjust(const f_array_length_t length, f_accountss_t *accountss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < accountss->size; ++i) {

      status = private_f_accounts_adjust(0, &accountss->array[i]);
      if (F_status_is_error(status)) return status;

      accountss->array[i].size = 0;
      accountss->array[i].used = 0;
    } // for

    status = f_memory_adjust(accountss->size, length, sizeof(f_accounts_t), (void **) & accountss->array);
    if (F_status_is_error(status)) return status;

    accountss->size = length;

    if (accountss->used > accountss->size) {
      accountss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

#if !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  f_status_t private_f_accountss_resize(const f_array_length_t length, f_accountss_t *accountss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < accountss->size; ++i) {

      status = private_f_accounts_resize(0, &accountss->array[i]);
      if (F_status_is_error(status)) return status;

      accountss->array[i].size = 0;
      accountss->array[i].used = 0;
    } // for

    status = f_memory_resize(accountss->size, length, sizeof(f_accounts_t), (void **) & accountss->array);
    if (F_status_is_error(status)) return status;

    accountss->size = length;

    if (accountss->used > accountss->size) {
      accountss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
