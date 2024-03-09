#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__fl_fss_payload_header_map__parameter_checking(void **void_state) {

  const f_abstruse_maps_t headers = f_abstruse_maps_t_initialize;
  f_state_t state = f_state_t_initialize;
  fl_fss_payload_header_state_t data = fl_fss_payload_header_state_t_initialize;
  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_string_maps_t destinations = f_string_maps_t_initialize;

  {
    state.status = F_none;
    state.data = &data;
    data.cache = &cache;

    fl_fss_payload_header_map(headers, 0, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;
    state.data = 0;
    data.cache = 0;

    fl_fss_payload_header_map(headers, &destinations, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;
    state.data = &data;
    data.cache = 0;

    fl_fss_payload_header_map(headers, &destinations, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }

  {
    state.status = F_none;
    state.data = 0;
    data.cache = &cache;

    fl_fss_payload_header_map(headers, &destinations, &state);

    assert_int_equal(state.status, F_status_set_error(F_parameter));
  }
}

void test__fl_fss_payload_header_map__returns_data_not(void **void_state) {

  const f_abstruse_maps_t headers = f_abstruse_maps_t_initialize;
  f_state_t state = f_state_t_initialize;
  fl_fss_payload_header_state_t data = fl_fss_payload_header_state_t_initialize;
  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_string_maps_t destinations = f_string_maps_t_initialize;

  {
    state.status = F_none;
    state.data = &data;
    data.cache = &cache;

    fl_fss_payload_header_map(headers, &destinations, &state);

    assert_int_equal(state.status, F_data_not);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
