
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "_hashmap.h"

static inline int	hashmap_shrink_entries(s_hashmap *map)
{
	s_entry		*new_entries = malloc(
		sizeof(*new_entries) * (map->used + 1)
	);
	size_t		new_entries_index = 0;

	if (new_entries != NULL)
	{
		map->nentries = map->used + 1;
		for (size_t i = 0; i < map->nentries; i++)
		{
			if (map->entries[i].key != NULL)
			{
				memcpy(
					new_entries + new_entries_index,
					map->entries + HASHMAP_OVERSIZE_ENTRIES,
					sizeof(map->entries[i])
				);
				new_entries_index++;
			}
		}
		memset(new_entries + new_entries_index, 0, sizeof(new_entries[0]));
		free(map->entries);
		map->entries = new_entries;
		return 0;
	}
	return -1;
}

int		hashmap_resize(s_hashmap *map, size_t new_capacity)
{
	size_t		normed_hash;
	size_t		hash;
	ssize_t		*indices;

	// Sanity check, should never happen
	assert(map->nentries <= new_capacity);

	if (new_capacity < map->capacity)
	{
		/*
		** Since this action has a cost ( reallocating entries manually )
		** We perform it only when we resize down the entier hashmap
		*/
		if (hashmap_shrink_entries(map) < 0)
		{
			return -1;
		}
	}

	indices = malloc(sizeof(*indices) * new_capacity);
	if (indices != NULL)
	{
		map->capacity = new_capacity;
		for (size_t i = 0; i < new_capacity; i++) {
			indices[i] = HASHMAP_DEFAULT_ENTRY;
		}
		for (size_t i = 0; i < map->nentries; i++)
		{
			hash = map->entries[i].hash;
			do
			{
				normed_hash = hashmap_hash_norm(hash++, new_capacity);
			}
			while (indices[normed_hash] != HASHMAP_UNUSED_ENTRY);

			indices[normed_hash] = i;
		}
		free(map->indices);
		map->indices = indices;
		return 0;
	}
	return -1;
}
