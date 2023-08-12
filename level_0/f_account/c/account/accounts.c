#include "../account.h"
#include "accounts.h"
#include "private-accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_delete_
  f_status_t f_account_delete(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

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
#endif // _di_f_account_delete_

#ifndef _di_f_account_destroy_
  f_status_t f_account_destroy(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

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
#endif // _di_f_account_destroy_

#ifndef _di_f_accounts_adjust_callback_
  f_status_t f_accounts_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamic_adjust(0, &array->array[i].home);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array->array[i].label);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array->array[i].name);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array->array[i].password);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array->array[i].shell);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_accounts_adjust_callback_

#ifndef _di_f_accounts_append_
  f_status_t f_accounts_append(const f_account_t source, f_accounts_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_account_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

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
#endif // _di_f_accounts_append_

#ifndef _di_f_accounts_append_all_
  f_status_t f_accounts_append_all(const f_accounts_t source, f_accounts_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_accounts_append_all(source, destination);
  }
#endif // _di_f_accounts_append_all_

#ifndef _di_f_accounts_resize_callback_
  f_status_t f_accounts_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamic_resize(0, &array->array[i].home);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array->array[i].label);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array->array[i].name);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array->array[i].password);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array->array[i].shell);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_accounts_resize_callback_

#ifndef _di_f_accountss_append_
  f_status_t f_accountss_append(const f_accounts_t source, f_accountss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_accounts_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_accounts_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_accountss_append_

#ifndef _di_f_accountss_append_all_
  f_status_t f_accountss_append_all(const f_accountss_t source, f_accountss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_accounts_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

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

#ifdef __cplusplus
} // extern "C"
#endif
