
#include <stdlib.h>
#include "_hashmap.h"

static int	content_comparator(void *first, const void *second, const void *callback)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	c_hashmap_comparator	c = callback;

	return c((void *)f->content, s->content);
}

void    hashmap_sort_content(s_hashmap *map, c_hashmap_comparator callback)
{
	if (map->entries != NULL)
	{
		QSORT_R_COMPATIBLE(
			map->entries,
			map->nentries,
			sizeof(map->entries[0]),
			content_comparator,
			callback
		);

		hashmap_remap_indices(map);
	}
}
