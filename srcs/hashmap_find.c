
#include "_hashmap.h"

const void		*hashmap_find(s_hashmap *map, c_hashmap_validator callback)
{
	if (map->entries != NULL)
	{
		for (size_t i = 0; i < map->nentries; i++)
		{
			s_entry		*entry = map->entries + i;

			if (callback(entry->key, entry->key_size, entry->content) != 0)
			{
				return (entry->content);
			}
		}
	}
	return NULL;
}
