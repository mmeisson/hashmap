
#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

s_hashmap	*hashmap_new_cap(size_t initial_capacity)
{
	s_hashmap		*new = malloc(
		sizeof(*new)
		+ sizeof(new->indices[0]) * initial_capacity
	);

	if (new != NULL)
	{
		bzero(
			new,
			sizeof(*new) + sizeof(new->indices[0]) * initial_capacity
		);
		for (size_t i = 0; i < initial_capacity; i++)
		{
			new->indices[i] = UNUSED_ENTRY;
		}
		new->capacity = initial_capacity;
	}
	return new;
}

s_hashmap	*hashmap_new(void)
{
	return hashmap_new_cap(BASE_SIZE);
}
