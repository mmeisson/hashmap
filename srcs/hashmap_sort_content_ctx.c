
#include <stdlib.h>
#include "_hashmap.h"

#if defined(__APPLE__) || defined(BSD)

static int	content_comparator(void *context, const void *first, const void *second)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	const struct	s_hashmap_sortcontext		*ctx = context;

	return ctx->callback(f->content, s->content, ctx->context);
}

#else

static int	content_comparator(const void *first, const void *second, void *context)
{
	const s_entry	*f = first;
	const s_entry	*s = second;
	const struct	s_hashmap_sortcontext		*ctx = context;

	return ctx->callback(f->content, s->content, ctx->context);
}

#endif

void    hashmap_sort_content_ctx(s_hashmap *map, c_hashmap_comparator_ctx callback, void *context)
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
			content_comparator,
			ctx
		);

		hashmap_remap_indices(map);
	}
	free(ctx);
}
