#include "../controller.h"
#include "../private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_cache_action_delete_simple_
  void controller_cache_action_delete_simple(controller_cache_action_t * const cache) {

    f_string_dynamic_resize(0, &cache->name_action);
    f_string_dynamic_resize(0, &cache->name_file);
    f_string_dynamic_resize(0, &cache->name_item);
    f_string_dynamic_resize(0, &cache->generic);
  }
#endif // _di_controller_cache_action_delete_simple_

#ifndef _di_controller_cache_delete_simple_
  void controller_cache_delete_simple(controller_cache_t * const cache) {

    macro_f_array_lengths_t_delete_simple(cache->ats)
    macro_f_array_lengths_t_delete_simple(cache->stack)
    macro_f_fss_delimits_t_delete_simple(cache->delimits)

    f_string_dynamic_resize(0, &cache->buffer_file);
    f_string_dynamic_resize(0, &cache->buffer_item);
    f_string_dynamic_resize(0, &cache->buffer_path);

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
