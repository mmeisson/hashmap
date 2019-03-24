
#include <string.h>
#include "_hashmap.h"

static inline void     swap_entries(s_entry *a, s_entry *b)
{
	s_entry		tmp;

	memcpy(&tmp, a, sizeof(tmp));
	memcpy(a, b, sizeof(tmp));
	memcpy(b, &tmp, sizeof(tmp));
}

void    hashmap_reverse(s_hashmap *map)
{
	size_t		hash;
	size_t		normalized_hash;

	if (map->entries != NULL)
	{
		for (size_t i = 0; i < map->nentries / 2; i++)
		{
			swap_entries(
				map->entries + i,
				map->entries + ((map->nentries - i) - 1)
			);
		}

		/*
		**	Remap the indices
		*/
		for (size_t i = 0; i < map->capacity; i++)
		{
			map->indices[i] = HASHMAP_DEFAULT_ENTRY;
		}
		for (size_t i = 0; i < map->nentries; i++)
		{
			if (map->entries[i].key != NULL)
			{
				hash = map->entries[i].hash;

				do
				{
					normalized_hash = hashmap_hash_norm(hash++, map->capacity);
				}
				while (map->indices[i] != HASHMAP_UNUSED_ENTRY);
				map->indices[normalized_hash] = i;
			}
		}
	}
}