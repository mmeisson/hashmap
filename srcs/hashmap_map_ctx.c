
#include <stdlib.h>
#include "_hashmap.h"

s_hashmap   *hashmap_map_ctx(s_hashmap *map, c_hashmap_creator_ctx callback, void *context)
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

			size_t		key_size = 0;
			void		*key = NULL;
			void		*content = NULL;

			callback(
				entry->key,
				entry->key_size,
				entry->content,
				&key,
				&key_size,
				&content,
				context
			);
			if (key != NULL)
			{
				hashmap_insert(new, key, key_size, content);
			}
		}
	}
	return new;
}
