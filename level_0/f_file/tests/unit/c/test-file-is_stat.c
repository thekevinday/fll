#include "test-file.h"
#include "test-file-is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_is_stat__returns_false(void **state) {

  f_status_t types[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_directory_d,
    F_file_type_fifo_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  for (int j = 0; j < 8; ++j) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | types[j];

    for (int i = 0; i < 8; ++i) {

      // Skip what would return true.
      if (j == i) continue;

      const f_status_t status = f_file_is_stat(statistics, types[i]);

      assert_int_equal(status, F_false);
    } // for
  } // for
}

void test__f_file_is_stat__returns_true(void **state) {

  f_status_t types[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_directory_d,
    F_file_type_fifo_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  for (int j = 0; j < 8; ++j) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | types[j];

    for (int i = 0; i < 8; ++i) {

      // Skip what would return false.
      if (j != i) continue;

      const f_status_t status = f_file_is_stat(statistics, types[i]);

      assert_int_equal(status, F_true);
    } // for
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
