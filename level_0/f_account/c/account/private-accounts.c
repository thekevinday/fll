#include "../account.h"
#include "accounts.h"
#include "private-accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)
  extern f_status_t private_f_accounts_append_all(const f_accounts_t source, f_accounts_t * const destination) {

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_account_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

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

#ifdef __cplusplus
} // extern "C"
#endif
