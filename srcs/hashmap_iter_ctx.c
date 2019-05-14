
#include "_hashmap.h"

void			hashmap_iter_ctx(s_hashmap *map, c_hashmap_iterator_ctx iter, void *context)
{
	if (map->entries != NULL)
	{
		for (size_t i = 0; i < map->nentries; i++)
		{
			s_entry		*entry = map->entries + i;

			if (entry->key != NULL)
			{
				iter(entry->key, entry->key_size, entry->content, context);
			}
		}
	}
}
