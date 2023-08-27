#include "test-serialize.h"
#include "test-serialize-from_simple_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_serialize_from_simple_range__parameter_checking(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_serialize_from_simple_range(source, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_serialize_from_simple_range__returns_data_not(void **state) {

  const f_string_static_t source = f_string_static_t_initialize;

  f_string_ranges_t ranges = f_string_ranges_t_initialize;

  {
    const f_status_t status = f_serialize_from_simple_range(source, &ranges);

    assert_int_equal(status, F_data_not);
  }

  free((void *) ranges.array);
}

void test__f_serialize_from_simple_range__works(void **state) {

  f_string_static_t sources[] = {
    macro_f_string_static_t_initialize_1("", 0, 1),
    macro_f_string_static_t_initialize_1("first", 0, 5),
    macro_f_string_static_t_initialize_1(".:", 0, 2),
    macro_f_string_static_t_initialize_1(":cc", 0, 3),
    macro_f_string_static_t_initialize_1("first:2::蠇", 0, 12),
    macro_f_string_static_t_initialize_1("им:蠇", 0, 8),
    macro_f_string_static_t_initialize_1("им:?", 0, 6),
  };

  f_string_range_t expected_array_0[] = { { 0, 0 } };
  f_string_range_t expected_array_1[] = { { 0, 4 } };
  f_string_range_t expected_array_2[] = { { 0, 0 }, { 1, 0 } };
  f_string_range_t expected_array_3[] = { { 1, 0 }, { 1, 2 } };
  f_string_range_t expected_array_4[] = { { 0, 4 }, { 6, 6 }, { 1, 0 }, { 9, 11 } };
  f_string_range_t expected_array_5[] = { { 0, 3 }, { 5, 7 } };
  f_string_range_t expected_array_6[] = { { 0, 3 }, { 5, 5 } };

  f_string_ranges_t expecteds[] = {
    macro_f_string_statics_t_initialize_1(expected_array_0, 0, 1),
    macro_f_string_statics_t_initialize_1(expected_array_1, 0, 1),
    macro_f_string_statics_t_initialize_1(expected_array_2, 0, 2),
    macro_f_string_statics_t_initialize_1(expected_array_3, 0, 2),
    macro_f_string_statics_t_initialize_1(expected_array_4, 0, 4),
    macro_f_string_statics_t_initialize_1(expected_array_5, 0, 2),
    macro_f_string_statics_t_initialize_1(expected_array_6, 0, 2),
  };

  f_string_ranges_t ranges = f_string_ranges_t_initialize;

  for (uint8_t i = 0; i < 7; ++i) {

    const f_status_t status = f_serialize_from_simple_range(sources[i], &ranges);

    assert_int_equal(status, F_okay);
    assert_int_equal(ranges.used, expecteds[i].used);

    for (uint8_t j = 0; j < ranges.used; ++j) {

      assert_int_equal(ranges.array[j].start, expecteds[i].array[j].start);
      assert_int_equal(ranges.array[j].stop, expecteds[i].array[j].stop);
    } // for

    ranges.used = 0;
  } // for

  {
    const f_string_static_t incompletes[] = {
      macro_f_string_static_t_initialize_1("蠇", 0, 2),
      macro_f_string_static_t_initialize_1("蠇", 0, 1),
    };

    for (uint8_t i = 0; i < 2; ++i) {

      ranges.used = 0;

      const f_status_t status = f_serialize_from_simple_range(incompletes[i], &ranges);

      assert_int_equal(status, F_complete_not_utf_eos);
      assert_int_equal(ranges.used, 1);
      assert_int_equal(ranges.array[ranges.used - 1].start, 1);
      assert_int_equal(ranges.array[ranges.used - 1].stop, 0);
    } // for
  }

  free((void *) ranges.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
