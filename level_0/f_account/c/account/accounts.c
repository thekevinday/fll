#include "../account.h"
#include "accounts.h"
#include "private-accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_delete_
  f_status_t f_account_delete(f_account_t *account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_account_delete(account);
  }
#endif // _di_f_account_delete_

#ifndef _di_f_account_destroy_
  f_status_t f_account_destroy(f_account_t *account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_account_destroy(account);
  }
#endif // _di_f_account_destroy_

#ifndef _di_f_accounts_adjust_
  f_status_t f_accounts_adjust(const f_number_unsigned_t length, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_accounts_adjust(length, accounts);
  }
#endif // _di_f_accounts_adjust_

#ifndef _di_f_accounts_append_
  f_status_t f_accounts_append(const f_account_t source, f_accounts_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_accounts_append(source, destination);
  }
#endif // _di_f_accounts_append_

#ifndef _di_f_accounts_append_all_
  f_status_t f_accounts_append_all(const f_accounts_t source, f_accounts_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_accounts_append_all(source, destination);
  }
#endif // _di_f_accounts_append_all_

#ifndef _di_f_accounts_decimate_by_
  f_status_t f_accounts_decimate_by(const f_number_unsigned_t amount, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accounts->size > amount) {
      return private_f_accounts_adjust(accounts->size - amount, accounts);
    }

    return private_f_accounts_adjust(0, accounts);
  }
#endif // _di_f_accounts_decimate_by_

#ifndef _di_f_accounts_decrease_by_
  f_status_t f_accounts_decrease_by(const f_number_unsigned_t amount, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accounts->size > amount) {
      return private_f_accounts_resize(accounts->size - amount, accounts);
    }

    return private_f_accounts_resize(0, accounts);
  }
#endif // _di_f_accounts_decrease_by_

#ifndef _di_f_accounts_increase_
  f_status_t f_accounts_increase(const f_number_unsigned_t step, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && accounts->used + 1 > accounts->size) {
      f_number_unsigned_t size = accounts->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (accounts->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_accounts_resize(size, accounts);
    }

    return F_data_not;
  }
#endif // _di_f_accounts_increase_

#ifndef _di_f_accounts_increase_by_
  f_status_t f_accounts_increase_by(const f_number_unsigned_t amount, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accounts->used + amount > accounts->size) {
      if (accounts->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_accounts_resize(accounts->used + amount, accounts);
    }

    return F_data_not;
  }
#endif // _di_f_accounts_increase_by_

#ifndef _di_f_accounts_resize_
  f_status_t f_accounts_resize(const f_number_unsigned_t length, f_accounts_t *accounts) {
    #ifndef _di_level_0_parameter_checking_
      if (!accounts) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_accounts_resize(length, accounts);
  }
#endif // _di_f_accounts_resize_

#ifndef _di_f_accountss_adjust_
  f_status_t f_accountss_adjust(const f_number_unsigned_t length, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_accountss_adjust(length, accountss);
  }
#endif // _di_f_accountss_adjust_

#ifndef _di_f_accountss_append_
  f_status_t f_accountss_append(const f_accounts_t source, f_accountss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_accountss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_accounts_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_accountss_append_

#ifndef _di_f_accountss_append_all_
  f_status_t f_accountss_append_all(const f_accountss_t source, f_accountss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_accountss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_accounts_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_accountss_append_all_

#ifndef _di_f_accountss_decimate_by_
  f_status_t f_accountss_decimate_by(const f_number_unsigned_t amount, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accountss->size > amount) {
      return private_f_accountss_adjust(accountss->size - amount, accountss);
    }

    return private_f_accountss_adjust(0, accountss);
  }
#endif // _di_f_accountss_decimate_by_

#ifndef _di_f_accountss_decrease_by_
  f_status_t f_accountss_decrease_by(const f_number_unsigned_t amount, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accountss->size > amount) {
      return private_f_accountss_resize(accountss->size - amount, accountss);
    }

    return private_f_accountss_resize(0, accountss);
  }
#endif // _di_f_accountss_decrease_by_

#ifndef _di_f_accountss_increase_
  f_status_t f_accountss_increase(const f_number_unsigned_t step, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && accountss->used + 1 > accountss->size) {
      f_number_unsigned_t size = accountss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (accountss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_accountss_resize(size, accountss);
    }

    return F_data_not;
  }
#endif // _di_f_accountss_increase_

#ifndef _di_f_accountss_increase_by_
  f_status_t f_accountss_increase_by(const f_number_unsigned_t amount, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (accountss->used + amount > accountss->size) {
      if (accountss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_accountss_resize(accountss->used + amount, accountss);
    }

    return F_data_not;
  }
#endif // _di_f_accountss_increase_by_

#ifndef _di_f_accountss_resize_
  f_status_t f_accountss_resize(const f_number_unsigned_t length, f_accountss_t *accountss) {
    #ifndef _di_level_0_parameter_checking_
      if (!accountss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_accountss_resize(length, accountss);
  }
#endif // _di_f_accountss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
