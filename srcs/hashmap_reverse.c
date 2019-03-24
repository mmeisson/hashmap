
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
	if (map->entries != NULL)
	{
		for (size_t i = 0; i < map->nentries / 2; i++)
		{
			swap_entries(
				map->entries + i,
				map->entries + ((map->nentries - i) - 1)
			);
		}
		hashmap_remap_indices(map);
	}
}