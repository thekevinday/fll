#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t help__read_line_contents__single(FILE *file, f_string_dynamics_t * const contents) {

  size_t max = 255;
  char *line_string = 0;

  ssize_t result = getline(&line_string, &max, file);

  if (result == -1) {
    if (line_string) free(line_string);

    return F_true;
  }

  assert_int_not_equal(result, 0);
  assert_int_not_equal(line_string[0], 0);

  const f_number_unsigned_t count = (f_number_unsigned_t) atoi(line_string);

  if (!count) {
    assert_int_equal(line_string[0], '0');
  }

  contents->used = 0;

  {
    const f_status_t status = f_memory_array_increase_by(count, sizeof(f_string_dynamic_t), (void **) &contents->array, &contents->used, &contents->size);
    assert_true(F_status_is_error_not(status));
  }

  for (; contents->used < count; ++contents->used) {

    max = 255;
    contents->array[contents->used].used = 0;

    const f_status_t status = f_memory_array_increase_by(max, sizeof(f_string_t), (void **) &contents->array[contents->used].string, &contents->array[contents->used].used, &contents->array[contents->used].size);
    assert_true(F_status_is_error_not(status));

    result = getline(&contents->array[contents->used].string, &max, file);
    assert_int_not_equal(result, -1);
    assert_int_not_equal(result, 0);

    contents->array[contents->used].used = ((f_number_unsigned_t) result) - 1;
    contents->array[contents->used].string[contents->array[contents->used].used] = 0;
  } // for

  if (line_string) free(line_string);

  return F_false;
}

uint8_t help__read_line_expects__single(FILE *file, const f_string_static_t object, f_string_maps_t * const expects) {

  size_t max = 255;
  char *line_string = 0;
  f_status_t status = F_okay;

  ssize_t result = getline(&line_string, &max, file);

  if (result == -1) {
    if (line_string) free(line_string);

    return F_true;
  }

  assert_int_not_equal(result, 0);
  assert_int_not_equal(line_string[0], 0);

  const f_number_unsigned_t count = (f_number_unsigned_t) atoi(line_string);

  if (!count) {
    assert_int_equal(line_string[0], '0');
  }

  status = f_memory_array_increase_by(count, sizeof(f_string_map_t), (void **) &expects->array, &expects->used, &expects->size);
  assert_true(F_status_is_error_not(status));

  for (f_number_unsigned_t i = 0; i < count; ++i, ++expects->used) {

    max = 255;
    expects->array[expects->used].name.used = 0;
    expects->array[expects->used].value.used = 0;

    status = f_string_dynamic_append(object, &expects->array[expects->used].name);
    assert_true(F_status_is_error_not(status));

    status = f_string_dynamic_terminate_after(&expects->array[expects->used].name);
    assert_true(F_status_is_error_not(status));

    status = f_memory_array_increase_by(max, sizeof(f_string_t), (void **) &expects->array[expects->used].value.string, &expects->array[expects->used].value.used, &expects->array[expects->used].value.size);
    assert_true(F_status_is_error_not(status));

    result = getline(&expects->array[expects->used].value.string, &max, file);
    assert_int_not_equal(result, -1);
    assert_int_not_equal(result, 0);

    expects->array[expects->used].value.used = ((f_number_unsigned_t) result) - 1;
    expects->array[expects->used].value.string[expects->array[expects->used].value.used] = 0;
  } // for

  if (line_string) free(line_string);

  return F_false;
}

uint8_t help__read_line_object(FILE *file, f_string_dynamic_t * const object) {

  size_t max = 255;

  object->used = 0;

  const f_status_t status = f_memory_array_increase_by(max, sizeof(f_string_t), (void **) &object->string, &object->used, &object->size);
  assert_true(F_status_is_error_not(status));

  const ssize_t result = getline(&object->string, &max, file);
  if (result == -1) return F_true;

  assert_int_not_equal(result, 0);

  object->used = ((f_number_unsigned_t) result) - 1;
  object->string[object->used] = 0;

  return F_false;
}

#ifdef __cplusplus
} // extern "C"
#endif
