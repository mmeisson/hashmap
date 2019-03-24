
#include <stdlib.h>
#include "_hashmap.h"

static int	content_comparator(const void *first, const void *second, void *callback)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	c_hashmap_comparator	c = callback;

	return c(f->content, s->content);
}

void    hashmap_sort_keys(s_hashmap *map, c_hashmap_comparator callback)
{
	if (map->entries != NULL)
	{
		qsort_r(
			map->entries,
			map->nentries,
			sizeof(map->entries[0]),
			content_comparator,
			callback
		);

		hashmap_remap_indices(map);
	}
}
