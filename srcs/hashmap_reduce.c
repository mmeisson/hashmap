
#include "_hashmap.h"

void        hashmap_reduce(s_hashmap *map, c_hashmap_reducor callback, void **data)
{
	if (map->entries != NULL)
	{
		for (size_t i = 0; i < map->nentries; i++)
		{
			s_entry		*entry = map->entries + i;

			if (entry->key != NULL)
			{
				callback(entry->key, entry->key_size, entry->content, data);
			}
		}
	}
}
