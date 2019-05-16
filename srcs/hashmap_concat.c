
#include <math.h>
#include "_hashmap.h"

void			_hashmap_concat(const void *key, size_t key_size, HASHMAP_DATA content, void **data)
{
	struct s_hashmap	*new = *data;

	hashmap_insert(new, key, key_size, content);
}

s_hashmap		*hashmap_concat(s_hashmap *first, s_hashmap *second)
{
	s_hashmap	*new = NULL;
	size_t		new_capacity;

	new_capacity = first->used > second->used ? first->used : second->used;
	if (hashmap_is_overloaded(new_capacity, first->used + second->used)) {
		new_capacity <<= 1;
	}

	new = hashmap_new_cap(NULL, new_capacity);
	if (new != NULL)
	{
		hashmap_reduce(first, _hashmap_concat, (void **)&new);
	}
	return new;
}
