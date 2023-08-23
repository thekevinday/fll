#include "test-control_group.h"
#include "test-control_group-copy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_control_group_copy__parameter_checking(void **state) {

  const f_control_group_t source = f_control_group_t_initialize;

  {
    const f_status_t status = f_control_group_copy(source, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_control_group_copy__works(void **state) {

  f_control_group_t source = f_control_group_t_initialize;

  {
    source.as_new = F_true;

    f_control_group_t destination = f_control_group_t_initialize;

    const f_status_t status = f_control_group_copy(source, &destination);

    assert_int_equal(status, F_okay);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination.path.string, &destination.path.used, &destination.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination.groups.array, &destination.groups.used, &destination.groups.size, &f_string_dynamics_delete_callback);

    assert_int_equal(destination.as_new, source.as_new);

    assert_null(destination.path.string);
    assert_int_equal(destination.path.used, 0);

    assert_null(destination.groups.array);
    assert_int_equal(destination.groups.used, 0);
  }

  {
    f_control_group_t destination = f_control_group_t_initialize;

    source.as_new = F_true;
    source.path.string = "source.path";
    source.path.used = 11;
    source.path.size = 0;

    const f_status_t status = f_control_group_copy(source, &destination);

    assert_int_equal(status, F_okay);

    assert_int_equal(destination.as_new, source.as_new);

    assert_string_equal(destination.path.string, source.path.string);
    assert_int_equal(destination.path.used, source.path.used);

    assert_null(destination.groups.array);
    assert_int_equal(destination.groups.used, 0);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination.path.string, &destination.path.used, &destination.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination.groups.array, &destination.groups.used, &destination.groups.size, &f_string_dynamics_delete_callback);
  }

  {
    f_control_group_t destination = f_control_group_t_initialize;

    source.as_new = F_true;
    source.path.string = 0;
    source.path.used = 0;
    source.path.size = 0;

    f_string_static_t groups[] = {
      f_string_static_t_initialize,
      f_string_static_t_initialize,
    };

    groups[0].string = "group_1";
    groups[0].used = 7;
    groups[0].size = 0;

    groups[1].string = "group_2";
    groups[1].used = 7;
    groups[1].size = 0;

    source.groups.array = groups;
    source.groups.used = 2;
    source.groups.size = 0;

    const f_status_t status = f_control_group_copy(source, &destination);

    assert_int_equal(status, F_okay);

    assert_int_equal(destination.as_new, source.as_new);

    assert_null(destination.path.string);
    assert_int_equal(destination.path.used, source.path.used);

    assert_non_null(destination.groups.array);
    assert_int_equal(destination.groups.used, source.groups.used);

    assert_string_equal(destination.groups.array[0].string, source.groups.array[0].string);
    assert_string_equal(destination.groups.array[1].string, source.groups.array[1].string);

    assert_int_equal(destination.groups.array[0].used, source.groups.array[0].used);
    assert_int_equal(destination.groups.array[1].used, source.groups.array[1].used);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination.path.string, &destination.path.used, &destination.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination.groups.array, &destination.groups.used, &destination.groups.size, &f_string_dynamics_delete_callback);
  }

  {
    f_control_group_t destination = f_control_group_t_initialize;

    source.as_new = F_false;
    source.path.string = "source.path";
    source.path.used = 11;
    source.path.size = 0;

    f_string_static_t groups[] = {
      f_string_static_t_initialize,
      f_string_static_t_initialize,
      f_string_static_t_initialize,
    };

    groups[0].string = "group_1";
    groups[0].used = 7;
    groups[0].size = 0;

    groups[1].string = "group_2";
    groups[1].used = 7;
    groups[1].size = 0;

    groups[2].string = "group_3";
    groups[2].used = 7;
    groups[2].size = 0;

    source.groups.array = groups;
    source.groups.used = 3;
    source.groups.size = 0;

    const f_status_t status = f_control_group_copy(source, &destination);

    assert_int_equal(status, F_okay);

    assert_int_equal(destination.as_new, source.as_new);

    assert_string_equal(destination.path.string, source.path.string);
    assert_int_equal(destination.path.used, source.path.used);

    assert_non_null(destination.groups.array);
    assert_int_equal(destination.groups.used, source.groups.used);

    assert_string_equal(destination.groups.array[0].string, source.groups.array[0].string);
    assert_string_equal(destination.groups.array[1].string, source.groups.array[1].string);
    assert_string_equal(destination.groups.array[2].string, source.groups.array[2].string);

    assert_int_equal(destination.groups.array[0].used, source.groups.array[0].used);
    assert_int_equal(destination.groups.array[1].used, source.groups.array[1].used);
    assert_int_equal(destination.groups.array[2].used, source.groups.array[2].used);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination.path.string, &destination.path.used, &destination.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination.groups.array, &destination.groups.used, &destination.groups.size, &f_string_dynamics_delete_callback);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
