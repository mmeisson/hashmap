
#include "_hashmap.h"

s_hashmap       *hashmap_filter(s_hashmap *map, c_hashmap_validator callback)
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
				entry->content
			) != 0)
            {
				hashmap_insert(new, entry->key, entry->key_size, entry->content);
			}
		}
	}
	return new;
}
