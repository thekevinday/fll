#include "test-file.h"
#include "test-file-mode_determine.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_mode_determine__parameter_checking(void **state) {

  const mode_t mode_file = 0;
  const f_file_mode_t mode_change = f_file_mode_t_initialize;

  {
    const f_status_t status = f_file_mode_determine(mode_file, mode_change, 0, F_false, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_mode_determine__works_basic(void **state) {

  const mode_t existing = 0;

  {
    f_file_mode_t changes[] = {
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_group_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_owner_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_sticky_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
    };

    mode_t changeds[] = {
      F_file_mode_all_x_d,
      0,
      F_file_mode_all_r_d,
      F_file_mode_special_set_group_d,
      F_file_mode_special_set_user_d,
      F_file_mode_special_sticky_d,
      F_file_mode_all_w_d,
      F_file_mode_owner_x_d,
      0,
      F_file_mode_owner_r_d,
      F_file_mode_owner_w_d,
      F_file_mode_group_x_d,
      0,
      F_file_mode_group_r_d,
      F_file_mode_group_w_d,
      F_file_mode_world_x_d,
      0,
      F_file_mode_world_r_d,
      F_file_mode_world_w_d,
    };

    for (uint8_t i = 0; i < 19; ++i) {

      mode_t changed = 0;

      const f_status_t status = f_file_mode_determine(existing, changes[i], 0, F_false, &changed);

      assert_int_equal(status, F_okay);
      assert_int_equal(changed, changeds[i]);
    } // for
  }

  {
    f_file_mode_t changes[] = {
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_group_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_owner_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_sticky_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
    };

    mode_t changeds[] = {
      F_file_mode_all_x_d,
      F_file_mode_all_x_d,
      F_file_mode_all_r_d,
      F_file_mode_special_set_group_d,
      F_file_mode_special_set_user_d,
      F_file_mode_special_sticky_d,
      F_file_mode_all_w_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_r_d,
      F_file_mode_owner_w_d,
      F_file_mode_group_x_d,
      F_file_mode_group_x_d,
      F_file_mode_group_r_d,
      F_file_mode_group_w_d,
      F_file_mode_world_x_d,
      F_file_mode_world_x_d,
      F_file_mode_world_r_d,
      F_file_mode_world_w_d,
    };

    for (uint8_t i = 0; i < 19; ++i) {

      mode_t changed = 0;

      const f_status_t status = f_file_mode_determine(existing, changes[i], 0, F_true, &changed);

      assert_int_equal(status, F_okay);
      assert_int_equal(changed, changeds[i]);
    } // for
  }
}

void test__f_file_mode_determine__works_basic_replace(void **state) {

  const mode_t existing = F_file_mode_all_rwx_d;

  {
    f_file_mode_t changes[] = {
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_group_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_owner_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_sticky_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
    };

    mode_t changeds[] = {
      F_file_mode_all_x_d,
      F_file_mode_all_x_d,
      F_file_mode_all_r_d,
      F_file_mode_special_set_group_d,
      F_file_mode_special_set_user_d,
      F_file_mode_special_sticky_d,
      F_file_mode_all_w_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_r_d,
      F_file_mode_owner_w_d,
      F_file_mode_group_x_d,
      F_file_mode_group_x_d,
      F_file_mode_group_r_d,
      F_file_mode_group_w_d,
      F_file_mode_world_x_d,
      F_file_mode_world_x_d,
      F_file_mode_world_r_d,
      F_file_mode_world_w_d,
    };

    for (uint8_t i = 0; i < 19; ++i) {

      mode_t changed = 0;

      const f_status_t status = f_file_mode_determine(existing, changes[i], F_file_mode_t_replace_all_d, F_false, &changed);

      assert_int_equal(status, F_okay);
      assert_int_equal(changed, changeds[i]);
    } // for
  }

  {
    f_file_mode_t changes[] = {
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_group_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_set_owner_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_sticky_d,
      F_file_mode_t_block_all_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_owner_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_group_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_execute_only_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_read_d,
      F_file_mode_t_block_world_d & F_file_mode_t_mask_how_add_d & F_file_mode_t_mask_bit_write_d,
    };

    mode_t changeds[] = {
      F_file_mode_all_x_d,
      F_file_mode_all_x_d,
      F_file_mode_all_r_d,
      F_file_mode_special_set_group_d,
      F_file_mode_special_set_user_d,
      F_file_mode_special_sticky_d,
      F_file_mode_all_w_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_x_d,
      F_file_mode_owner_r_d,
      F_file_mode_owner_w_d,
      F_file_mode_group_x_d,
      F_file_mode_group_x_d,
      F_file_mode_group_r_d,
      F_file_mode_group_w_d,
      F_file_mode_world_x_d,
      F_file_mode_world_x_d,
      F_file_mode_world_r_d,
      F_file_mode_world_w_d,
    };

    for (uint8_t i = 0; i < 19; ++i) {

      mode_t changed = 0;

      const f_status_t status = f_file_mode_determine(existing, changes[i], F_file_mode_t_replace_all_d, F_true, &changed);

      assert_int_equal(status, F_okay);
      assert_int_equal(changed, changeds[i]);
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
