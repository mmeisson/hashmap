
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

s_hashmap	*hashmap_new_cap(s_hashmap *new, size_t initial_capacity)
{
	assert(is_power_of_two(initial_capacity));

	if (new == NULL)
	{
		new = malloc(sizeof(*new));
	}
	if (new != NULL)
	{
		memset(new, 0, sizeof(*new));
		new->indices = malloc(sizeof(*new->indices) * initial_capacity);
		for (size_t i = 0; i < initial_capacity; i++)
		{
			new->indices[i] = HASHMAP_DEFAULT_ENTRY;
		}
		new->capacity = initial_capacity;
	}
	return new;
}

s_hashmap	*hashmap_new(s_hashmap *new)
{
	return hashmap_new_cap(new, HASHMAP_BASE_SIZE);
}
