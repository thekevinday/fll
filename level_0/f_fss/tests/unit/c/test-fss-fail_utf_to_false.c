#include "test-fss.h"
#include "test-fss-fail_utf_to_false.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_fail_utf_to_false__works_for_error(void **state) {

  f_state_t state_data = f_state_t_initialize;

  {
    f_status_t statuss[] = {
      F_utf_fragment,
      F_complete_not_utf,
      F_utf_not,
    };

    uint8_t j = 0;

    for (f_status_t i = 0; i < F_status_code_last; ++i) {

      const f_status_t status = f_fss_fail_utf_to_false(state_data, F_status_set_error(i));

      for (j = 0; j < 3; ++j) {
        if (i == statuss[j]) break;
      } // for

      if (j == 3) {
        assert_int_equal(status, F_status_set_error(i));
      }
      else {
        assert_int_equal(status, F_false);
      }
    } // for
  }

  state_data.flag |= f_fss_state_flag_utf_fail_on_valid_not_e;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    const f_status_t status = f_fss_fail_utf_to_false(state_data, F_status_set_error(i));

    assert_int_equal(status, F_status_set_error(i));
  } // for
}

void test__f_fss_fail_utf_to_false__works_for_no_error(void **state) {

  f_state_t state_data = f_state_t_initialize;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    const f_status_t status = f_fss_fail_utf_to_false(state_data, i);

    assert_int_equal(status, i);
  } // for

  state_data.flag |= f_fss_state_flag_utf_fail_on_valid_not_e;

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    const f_status_t status = f_fss_fail_utf_to_false(state_data, i);

    assert_int_equal(status, i);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
