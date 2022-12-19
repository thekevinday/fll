#include "test-iki.h"
#include "test-iki-read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_read__parameter_checking(void **state) {

  const f_state_t the_state = f_state_t_initialize;
  f_string_static_t empty = macro_f_string_static_t_initialize(f_string_empty_s.string, f_string_empty_s.size, f_string_empty_s.used);

  {
    f_string_range_t range = f_string_range_t_initialize;
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, 0, &range, &iki);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, &empty, 0, &iki);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_iki_read(the_state, &empty, &range, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_iki_read__returns_data_not(void **state) {

  const f_state_t the_state = f_state_t_initialize;
  f_string_static_t empty = macro_f_string_static_t_initialize(f_string_empty_s.string, f_string_empty_s.size, f_string_empty_s.used);

  {
    f_string_range_t range = f_string_range_t_initialize;
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, &empty, &range, &iki);

    assert_int_equal(F_status_set_fine(status), F_data_not);
  }
}

void test__f_iki_read__returns_data_not_eos(void **state) {

  const f_state_t the_state = f_state_t_initialize;
  f_string_static_t ascii_a = macro_f_string_static_t_initialize(f_string_ascii_a_s.string, f_string_ascii_a_s.size, f_string_ascii_a_s.used);

  {
    f_string_range_t range = macro_f_string_range_t_initialize(f_string_ascii_a_s.used, f_string_ascii_a_s.used);
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, &ascii_a, &range, &iki);

    assert_int_equal(F_status_set_fine(status), F_data_not_eos);
  }
}

void test__f_iki_read__returns_data_not_stop(void **state) {

  const f_state_t the_state = f_state_t_initialize;
  f_string_static_t ascii_a = macro_f_string_static_t_initialize(f_string_ascii_a_s.string, f_string_ascii_a_s.size, f_string_ascii_a_s.used);

  {
    f_string_range_t range = f_string_range_t_initialize;
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, &ascii_a, &range, &iki);

    assert_int_equal(F_status_set_fine(status), F_data_not_stop);
  }
}

void test__f_iki_read__works(void **state) {

  const f_state_t the_state = f_state_t_initialize;
  f_string_static_t empty = macro_f_string_static_t_initialize(f_string_empty_s.string, f_string_empty_s.size, f_string_empty_s.used);
  f_string_static_t ascii_a = macro_f_string_static_t_initialize(f_string_ascii_a_s.string, f_string_ascii_a_s.size, f_string_ascii_a_s.used);

  f_string_static_t buffers[] = {
    empty,
    ascii_a,
    macro_f_string_static_t_initialize("iki:'one'", 0, 9),
    macro_f_string_static_t_initialize("Has iki:'one' two:'iki and spaces'.", 0, 35),
    macro_f_string_static_t_initialize("iki:\"one\"", 0, 9),
    macro_f_string_static_t_initialize("Has iki:\"one\" two:\"iki and spaces\".", 0, 35),
    macro_f_string_static_t_initialize("export PATH=\"/bin:/sbin:some:'A_PATH'\"", 0, 38),
    macro_f_string_static_t_initialize("export PATH=\"/bin:/sbin:some:\"A_PATH\"\"", 0, 38),
    macro_f_string_static_t_initialize("This wor_ks:'hopefully'!", 0, 24),
    macro_f_string_static_t_initialize("This work-s:'hopefully'!", 0, 24),
    macro_f_string_static_t_initialize("This wor++ks:'hopefully'!", 0, 25),
    macro_f_string_static_t_initialize("This w_-+s:'hopefully'!", 0, 23),
    macro_f_string_static_t_initialize("This wor_ks:\"hopefully\"!", 0, 24),
    macro_f_string_static_t_initialize("This work-s:\"hopefully\"!", 0, 24),
    macro_f_string_static_t_initialize("This wor++ks:\"hopefully\"!", 0, 25),
    macro_f_string_static_t_initialize("This w_-+s:\"hopefully\"!", 0, 23),
    macro_f_string_static_t_initialize("IKI Content:'May have spaces\\' and quotes.'", 0, 43),
    macro_f_string_static_t_initialize("IKI Content:\"May have spaces\\\" and quotes.\"", 0, 43),
    macro_f_string_static_t_initialize("IKI Content:'May have spaces\\' and\" quotes.'", 0, 44),
    macro_f_string_static_t_initialize("IKI Content:\"May have spaces\\\" and' quotes.\"", 0, 44),
    macro_f_string_static_t_initialize("url:'https://localhost/fake-0.6.3.tar.gz?query=xx&parameter=yyy%20' end.", 0, 72),
    macro_f_string_static_t_initialize("url:\"https://localhost/fake-0.6.3.tar.gz?query=xx&parameter=yyy%20\" end.", 0, 72),
  };

  const f_array_length_t matches[] = {
    0,
    0,
    1,
    2,
    1,
    2,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
  };

  const f_status_t statuss[] = {
    F_data_not,
    F_data_not_stop,
    F_none_stop,
    F_none,
    F_none_stop,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none,
    F_none_stop,
    F_none_stop,
    F_none_stop,
    F_none_stop,
    F_none,
    F_none,
  };

  const f_string_range_t variables[][22] = {
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 8), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 12), macro_f_string_range_t_initialize(14, 33) },
    { macro_f_string_range_t_initialize(0, 8), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 12), macro_f_string_range_t_initialize(14, 33) },
    { macro_f_string_range_t_initialize(24, 36), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(24, 36), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 23), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 23), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 42), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 42), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 43), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 43), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 66), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 66), f_string_range_t_initialize },
  };

  const f_string_range_t vocabularys[][22] = {
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 2), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 6), macro_f_string_range_t_initialize(14, 16) },
    { macro_f_string_range_t_initialize(0, 2), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 6), macro_f_string_range_t_initialize(14, 16) },
    { macro_f_string_range_t_initialize(24, 27), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(24, 27), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 11), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 9), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 11), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 9), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(4, 10), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 2), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(0, 2), f_string_range_t_initialize },
  };

  const f_string_range_t contents[][22] = {
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { f_string_range_t_initialize, f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 7), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(9, 11), macro_f_string_range_t_initialize(19, 32) },
    { macro_f_string_range_t_initialize(5, 7), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(9, 11), macro_f_string_range_t_initialize(19, 32) },
    { macro_f_string_range_t_initialize(30, 35), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(30, 35), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(14, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(12, 20), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 21), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(14, 22), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(12, 20), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 41), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 41), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 42), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(13, 42), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 65), f_string_range_t_initialize },
    { macro_f_string_range_t_initialize(5, 65), f_string_range_t_initialize },
  };

  for (uint8_t i = 0; i < 22; ++i) {

    f_string_range_t range = macro_f_string_range_t_initialize2(buffers[i].used);
    f_iki_data_t iki = f_iki_data_t_initialize;

    const f_status_t status = f_iki_read(the_state, &buffers[i], &range, &iki);

    assert_int_equal(status, statuss[i]);

    if (matches[i] == 2) {
      const f_status_t status = f_iki_read(the_state, &buffers[i], &range, &iki);

      assert_int_equal(F_status_is_error_not(status) ? 0 : 1, 0);
    }

    assert_int_equal(iki.variable.used, matches[i]);

    if (iki.variable.used) {
      assert_int_equal(iki.variable.array[0].start, variables[i][0].start);
      assert_int_equal(iki.variable.array[0].stop, variables[i][0].stop);

      assert_int_equal(iki.vocabulary.array[0].start, vocabularys[i][0].start);
      assert_int_equal(iki.vocabulary.array[0].stop, vocabularys[i][0].stop);

      assert_int_equal(iki.content.array[0].start, contents[i][0].start);
      assert_int_equal(iki.content.array[0].stop, contents[i][0].stop);

      if (iki.variable.used == 2) {
        assert_int_equal(iki.variable.array[1].start, variables[i][1].start);
        assert_int_equal(iki.variable.array[1].stop, variables[i][1].stop);

        assert_int_equal(iki.vocabulary.array[1].start, vocabularys[i][1].start);
        assert_int_equal(iki.vocabulary.array[1].stop, vocabularys[i][1].stop);

        assert_int_equal(iki.content.array[1].start, contents[i][1].start);
        assert_int_equal(iki.content.array[1].stop, contents[i][1].stop);
      }
    }

    f_iki_data_delete(&iki);

    iki.variable.used = 0;
    iki.vocabulary.used = 0;
    iki.content.used = 0;
    iki.delimits.used = 0;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
