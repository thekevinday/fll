/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make operate block functionality.
 *
 * This is auto-included and should not need to be explicitly included.
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
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This does not alter data_make.setting.state.status.
 * @param last
 *   If TRUE, then this is the last line.
 *   If FALSE, then this is not the last line.
 * @param state_process
 *   The operation and if-condition states.
 */
#ifndef _di_fake_make_operate_block_postprocess_
  extern void fake_make_operate_block_postprocess(fake_make_data_t * const data_make, const bool last, fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_block_postprocess_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_block_h
