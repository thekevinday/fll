/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_make_operate_block_h
#define _fake_make_operate_block_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prepare the block for the next operation.
 *
 * This is to be called before validation but after expanding the operation.
 * Whether or not a block ends can only be done after the next line is processed.
 *
 * @param state_process
 *   The operation and if-condition states.
 */
#ifndef _di_fake_make_operate_block_prepare_
  extern void fake_make_operate_block_prepare(fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_block_prepare_

/**
 * Perform block post-processing.
 *
 * This is to be called once an operation is performed or skipped.
 *
 * @param last
 *   If TRUE, then this is the last line.
 *   If FALSE, then this is not the last line.
 * @param state_process
 *   The operation and if-condition states.
 * @param status
 *   The status code.
 */
#ifndef _di_fake_make_operate_block_postprocess_
  extern void fake_make_operate_block_postprocess(const bool last, fake_state_process_t * const state_process, f_status_t * const status);
#endif // _di_fake_make_operate_block_postprocess_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_block_h
