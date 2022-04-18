#include "test-file.h"
#include "test-file-mode_to_mode.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_file_mode_to_mode__parameter_checking(void **state) {

    const f_file_mode_t mode = f_file_mode_t_initialize;

    {
      const f_status_t status = f_file_mode_to_mode(mode, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_mode_to_mode__works(void **state) {

  f_file_mode_t file_modes[] = {
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_read_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_write_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_execute_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_owner_d & (F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_read_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_write_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_execute_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_group_d & (F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_read_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_write_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_execute_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_world_d & (F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & F_file_mode_t_mask_bit_read_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & F_file_mode_t_mask_bit_write_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & F_file_mode_t_mask_bit_execute_d,
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_write_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & (F_file_mode_t_mask_bit_read_d | F_file_mode_t_mask_bit_execute_d),
    F_file_mode_t_mask_how_add_d & F_file_mode_t_block_all_d & (F_file_mode_t_mask_bit_write_d | F_file_mode_t_mask_bit_execute_d),
  };

  f_file_mode_t modes[] = {
    F_file_mode_owner_rwx_d,
    F_file_mode_owner_r_d,
    F_file_mode_owner_w_d,
    F_file_mode_owner_x_d,
    F_file_mode_owner_rw_d,
    F_file_mode_owner_rx_d,
    F_file_mode_owner_wx_d,
    F_file_mode_group_rwx_d,
    F_file_mode_group_r_d,
    F_file_mode_group_w_d,
    F_file_mode_group_x_d,
    F_file_mode_group_rw_d,
    F_file_mode_group_rx_d,
    F_file_mode_group_wx_d,
    F_file_mode_world_rwx_d,
    F_file_mode_world_r_d,
    F_file_mode_world_w_d,
    F_file_mode_world_x_d,
    F_file_mode_world_rw_d,
    F_file_mode_world_rx_d,
    F_file_mode_world_wx_d,
    F_file_mode_all_rwx_d,
    F_file_mode_all_r_d,
    F_file_mode_all_w_d,
    F_file_mode_all_x_d,
    F_file_mode_all_rw_d,
    F_file_mode_all_rx_d,
    F_file_mode_all_wx_d,
  };

  for (f_array_length_t i = 0; i < 28; ++i) {

    mode_t mode = 0;

    const f_status_t status = f_file_mode_to_mode(file_modes[i], &mode);

    assert_int_equal(status, F_none);
    assert_int_equal(mode, modes[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
