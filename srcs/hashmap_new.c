
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

s_hashmap	hashmap_new_cap(size_t initial_capacity)
{
	assert(is_power_of_two(initial_capacity));
	s_hashmap		new;

	memset(&new, 0, sizeof(new));
	new.indices = malloc(sizeof(*new.indices) * initial_capacity);
	for (size_t i = 0; i < initial_capacity; i++)
	{
		new.indices[i] = HASHMAP_DEFAULT_ENTRY;
	}
	new.capacity = initial_capacity;
	return new;
}

s_hashmap	hashmap_new(void)
{
	return hashmap_new_cap(HASHMAP_BASE_SIZE);
}
