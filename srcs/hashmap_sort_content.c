
#include <stdlib.h>
#include "_hashmap.h"

#if defined(__APPLE__) || defined(BSD)

static int	content_comparator(void *callback, const void *first, const void *second)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	c_hashmap_comparator	c = callback;

	return c(f->content, s->content);
}

#else

static int	content_comparator(const void *first, const void *second, void *callback)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	c_hashmap_comparator	c = callback;

	return c(f->content, s->content);
}

#endif

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
