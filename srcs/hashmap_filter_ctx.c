
#include "_hashmap.h"

s_hashmap       *hashmap_filter_ctx(s_hashmap *map, c_hashmap_validator_ctx callback, void *context)
{
	s_hashmap	*new = hashmap_new_cap(NULL, map->capacity);

	if (new == NULL)
	{
		return NULL;
	}

	if (map->entries)
	{
		for (size_t i = 0; i < map->nentries; i++)
		{
			s_entry		*entry = map->entries + i;

			if (callback(
				entry->key,
				entry->key_size,
				entry->content,
				context
			) != 0)
            {
				hashmap_insert(new, entry->key, entry->key_size, entry->content);
			}
		}
	}
	return new;
}
