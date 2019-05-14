
#include <stdlib.h>
#include "_hashmap.h"

static int	key_comparator(void *first, const void *second, const void *context)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	const struct	s_hashmap_sortcontext		*ctx = context;

	return ctx->callback((void *)f->key, s->key, ctx->context);
}

void    hashmap_sort_keys_ctx(s_hashmap *map, c_hashmap_comparator_ctx callback, void *context)
{
	struct		s_hashmap_sortcontext		*ctx = malloc(sizeof(*ctx));

	if (ctx == NULL)
	{
		return;
	}
	ctx->context = context;
	ctx->callback = callback;
	if (map->entries != NULL)
	{
		QSORT_R_COMPATIBLE(
			map->entries,
			map->nentries,
			sizeof(map->entries[0]),
			key_comparator,
			ctx
		);

		hashmap_remap_indices(map);
	}
	free(ctx);
}