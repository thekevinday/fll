#include "../account.h"
#include "accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_delete_
  f_status_t f_account_delete(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
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
    }

    return F_okay;
  }
#endif // _di_f_account_delete_

#ifndef _di_f_account_destroy_
  f_status_t f_account_destroy(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    account->id_user = 0;
    account->id_group = 0;

    {
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
    }

    return F_okay;
  }
#endif // _di_f_account_destroy_

#ifndef _di_f_accounts_delete_callback_
  f_status_t f_accounts_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_account_t * const array = (f_account_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamic_resize(0, &array[i].home);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array[i].label);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array[i].name);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array[i].password);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array[i].shell);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accounts_delete_callback_

#ifndef _di_f_accounts_destroy_callback_
  f_status_t f_accounts_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_account_t * const array = (f_account_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        array[i].id_user = 0;
        array[i].id_group = 0;

        status = f_string_dynamic_adjust(0, &array[i].home);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array[i].label);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array[i].name);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array[i].password);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array[i].shell);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accounts_destroy_callback_

#ifndef _di_f_accountss_delete_callback_
  f_status_t f_accountss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_dynamic_resize(0, &array[i].array[j].home);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_resize(0, &array[i].array[j].label);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_resize(0, &array[i].array[j].name);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_resize(0, &array[i].array[j].password);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_resize(0, &array[i].array[j].shell);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_account_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accountss_delete_callback_

#ifndef _di_f_accountss_destroy_callback_
  f_status_t f_accountss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_dynamic_adjust(0, &array[i].array[j].home);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_adjust(0, &array[i].array[j].label);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_adjust(0, &array[i].array[j].name);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_adjust(0, &array[i].array[j].password);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_adjust(0, &array[i].array[j].shell);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_account_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accountss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
