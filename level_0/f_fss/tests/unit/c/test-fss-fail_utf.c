#include "test-fss.h"
#include "test-fss-fail_utf.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_fail_utf__works_for_error(void **state) {

  f_state_t state_data = f_state_t_initialize;

  {
    f_status_t statuss[] = {
      F_utf_fragment,
      F_complete_not_utf,
      F_utf_not,
    };

    uint8_t j = 0;

    for (f_status_t i = 0; i < F_status_code_last; ++i) {

      state_data.status = F_status_set_error(i);

      f_fss_fail_utf(&state_data);

      for (j = 0; j < 3; ++j) {
        if (i == statuss[j]) break;
      } // for

      if (j == 3) {
        assert_int_equal(state_data.status, F_status_set_error(i));
      }
      else {
        assert_int_equal(state_data.status, statuss[j]);
      }
    } // for
  }

  state_data.flag |= f_fss_state_flag_utf_fail_on_valid_not_e;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    state_data.status = F_status_set_error(i);

    f_fss_fail_utf(&state_data);

    assert_int_equal(state_data.status, F_status_set_error(i));
  } // for
}

void test__f_fss_fail_utf__works_for_no_error(void **state) {

  f_state_t state_data = f_state_t_initialize;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    state_data.status = i;

    f_fss_fail_utf(&state_data);

    assert_int_equal(state_data.status, i);
  } // for

  state_data.flag |= f_fss_state_flag_utf_fail_on_valid_not_e;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    state_data.status = i;

    f_fss_fail_utf(&state_data);

    assert_int_equal(state_data.status, i);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
