#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_block_prepare_
  void fake_make_operate_block_prepare(fake_state_process_t * const state_process) {

    if (!state_process) return;

    if (state_process->block) {
      if (state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_else_e || state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_or_e) {

        if (state_process->operation == fake_make_operation_type_if_e) {

          // When another if condition follows a non-if, non-and, non-or, and non-else, then this is the start of a new condition block.
          if (state_process->operation_previous != fake_make_operation_type_if_e && state_process->operation_previous != fake_make_operation_type_and_e && state_process->operation_previous != fake_make_operation_type_or_e && state_process->operation_previous != fake_make_operation_type_else_e) {
            state_process->block = fake_state_process_block_operate_e;
            state_process->block_result = 0;
          }
        }

        return;
      }

      if (state_process->operation_previous == fake_make_operation_type_and_e || state_process->operation_previous == fake_make_operation_type_else_e || state_process->operation_previous == fake_make_operation_type_if_e || state_process->operation_previous == fake_make_operation_type_or_e) {
        return;
      }

      // No further block operation detected, so wrap things up.
      state_process->block = 0;
      state_process->block_result = 0;

      if (state_process->block_result == fake_condition_result_error_e) {

        // When the block ends and the block success is false, pass the failure to the success variable so that "failure" conditions can catch this.
        if (state_process->success && !state_process->success_block) {
          state_process->success = F_false;
        }
      }
      else {
        state_process->success_block = F_true;
      }
    }
    else if (state_process->operation == fake_make_operation_type_if_e) {

      // This is the first if-condition, so setup the block.
      state_process->block = fake_state_process_block_operate_e;
      state_process->block_result = 0;
    }
  }
#endif // _di_fake_make_operate_block_prepare_

#ifndef _di_fake_make_operate_block_postprocess_
  void fake_make_operate_block_postprocess(fake_make_data_t * const data_make, const bool last, fake_state_process_t * const state_process) {

    if (!data_make || !data_make->main || !data_make->setting || !state_process) return;

    if (F_status_is_error(data_make->setting->state.status)) {
      state_process->block_result = fake_condition_result_error_e;
      state_process->success_block = F_false;

      return;
    }

    // When done processing an operation within an if/else condition, update the process state->
    if (state_process->block == fake_state_process_block_done_e) {
      // Nothing to do.
    }
    else if (state_process->block == fake_state_process_block_operate_e) {
      if (state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_or_e) {
        state_process->block_result = state_process->condition_result;

        if (state_process->block_result == fake_condition_result_false_e) {
          state_process->block = fake_state_process_block_skip_e;
        }
      }
      else if (state_process->operation == fake_make_operation_type_else_e) {
        state_process->block_result = 0;
      }
      else {
        state_process->block = fake_state_process_block_done_e;
        state_process->block_result = state_process->condition_result;
      }
    }
    else if (state_process->block == fake_state_process_block_skip_e) {
      if (state_process->operation != fake_make_operation_type_and_e && state_process->operation != fake_make_operation_type_if_e && state_process->operation != fake_make_operation_type_or_e) {

        // The operation has been skipped, so reset the block.
        state_process->block = fake_state_process_block_operate_e;
      }
    }
    else {
      state_process->block_result = state_process->condition_result;

      // If starting a new if-condition, setup the block.
      if (state_process->condition_result == fake_condition_result_true_e) {
        state_process->block = fake_state_process_block_operate_e;
      }
      else {
        state_process->block = fake_state_process_block_skip_e;
      }
    }

    if (last) {
      if (state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_else_e || state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_or_e) {
        return;
      }

      // No further block operation, so wrap things up.
      state_process->block = 0;
      state_process->block_result = 0;

      if (state_process->block_result == fake_condition_result_error_e) {

        // When the block ends and the block success is false, pass the failure to the success variable so that "failure" conditions can catch this.
        if (state_process->success && !state_process->success_block) {
          state_process->success = F_false;
        }
      }
      else {
        state_process->success_block = F_true;
      }
    }
  }
#endif // _di_fake_make_operate_block_postprocess_

#ifdef __cplusplus
} // extern "C"
#endif
