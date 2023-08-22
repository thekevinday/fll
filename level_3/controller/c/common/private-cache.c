#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_cache_action_delete_simple_
  void controller_cache_action_delete_simple(controller_cache_action_t * const cache) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->name_action.string, &cache->name_action.used, &cache->name_action.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->name_file.string, &cache->name_file.used, &cache->name_file.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->name_item.string, &cache->name_item.used, &cache->name_item.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->generic.string, &cache->generic.used, &cache->generic.size);
  }
#endif // _di_controller_cache_action_delete_simple_

#ifndef _di_controller_cache_delete_simple_
  void controller_cache_delete_simple(controller_cache_t * const cache) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer_file.string, &cache->buffer_file.used, &cache->buffer_file.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer_item.string, &cache->buffer_item.used, &cache->buffer_item.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer_path.string, &cache->buffer_path.used, &cache->buffer_path.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &cache->expanded.array, &cache->expanded.used, &cache->expanded.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &cache->ats.array, &cache->ats.used, &cache->ats.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &cache->stack.array, &cache->stack.used, &cache->stack.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &cache->delimits.array, &cache->delimits.used, &cache->delimits.size);

    f_string_ranges_resize(0, &cache->comments);
    f_string_ranges_resize(0, &cache->content_action);
    f_string_ranges_resize(0, &cache->object_actions);
    f_string_ranges_resize(0, &cache->object_items);

    f_string_rangess_resize(0, &cache->content_actions);
    f_string_rangess_resize(0, &cache->content_items);

    controller_cache_action_delete_simple(&cache->action);
  }
#endif // _di_controller_cache_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
