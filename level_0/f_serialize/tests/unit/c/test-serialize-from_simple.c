#include "test-serialize.h"
#include "test-serialize-from_simple.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_serialize_from_simple__parameter_checking(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_serialize_from_simple(source, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_serialize_from_simple__returns_data_not(void **state) {

  const f_string_static_t source = f_string_static_t_initialize;

  f_string_dynamics_t destination = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_serialize_from_simple(source, &destination);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamics_resize(0, &destination);
}

void test__f_serialize_from_simple__works(void **state) {

  f_string_static_t sources[] = {
    macro_f_string_static_t_initialize("", 0, 1),
    macro_f_string_static_t_initialize("first", 0, 5),
    macro_f_string_static_t_initialize(".:", 0, 2),
    macro_f_string_static_t_initialize(":cc", 0, 3),
    macro_f_string_static_t_initialize("first:2::蠇", 0, 12),
    macro_f_string_static_t_initialize("им:蠇", 0, 8),
    macro_f_string_static_t_initialize("им:?", 0, 6),
  };

  f_string_static_t individuals[] = {
    f_string_empty_s,
    macro_f_string_static_t_initialize("", 0, 1),
    macro_f_string_static_t_initialize("first", 0, 5),
    macro_f_string_static_t_initialize(".", 0, 1),
    macro_f_string_static_t_initialize("?", 0, 1),
    macro_f_string_static_t_initialize("cc", 0, 2),
    macro_f_string_static_t_initialize("2", 0, 1),
    macro_f_string_static_t_initialize("蠇", 0, 3),
    macro_f_string_static_t_initialize("им", 0, 4),
  };

  f_string_static_t expected_array_0[] = { individuals[1] };
  f_string_static_t expected_array_1[] = { individuals[2] };
  f_string_static_t expected_array_2[] = { individuals[3], individuals[0] };
  f_string_static_t expected_array_3[] = { individuals[0], individuals[5] };
  f_string_static_t expected_array_4[] = { individuals[2], individuals[6], individuals[0], individuals[7] };
  f_string_static_t expected_array_5[] = { individuals[8], individuals[7] };
  f_string_static_t expected_array_6[] = { individuals[8], individuals[4] };

  f_string_statics_t expecteds[] = {
    macro_f_string_statics_t_initialize(expected_array_0, 0, 1),
    macro_f_string_statics_t_initialize(expected_array_1, 0, 1),
    macro_f_string_statics_t_initialize(expected_array_2, 0, 2),
    macro_f_string_statics_t_initialize(expected_array_3, 0, 2),
    macro_f_string_statics_t_initialize(expected_array_4, 0, 4),
    macro_f_string_statics_t_initialize(expected_array_5, 0, 2),
    macro_f_string_statics_t_initialize(expected_array_6, 0, 2),
  };

  f_string_dynamics_t destination = f_string_dynamics_t_initialize;

  for (uint8_t i = 0; i < 7; ++i) {

    const f_status_t status = f_serialize_from_simple(sources[i], &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expecteds[i].used);

    for (uint8_t j = 0; j < destination.used; ++j) {

      assert_int_equal(destination.array[j].used, expecteds[i].array[j].used);

      if (destination.array[j].used) {
        assert_string_equal(destination.array[j].string, expecteds[i].array[j].string);
      }
    } // for

    destination.used = 0;
  } // for

  {
    const f_string_static_t incompletes[] = {
      macro_f_string_static_t_initialize("蠇", 0, 2),
      macro_f_string_static_t_initialize("蠇", 0, 1),
    };

    for (uint8_t i = 0; i < 2; ++i) {

      destination.used = 0;

      const f_status_t status = f_serialize_from_simple(incompletes[i], &destination);

      assert_int_equal(status, F_complete_not_utf_eos);
      assert_int_equal(destination.used, 1);
      assert_int_equal(destination.array[destination.used - 1].used, 0);
    } // for
  }

  f_string_dynamics_resize(0, &destination);
}

#ifdef __cplusplus
} // extern "C"
#endif
