#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

void	hashmap_insert(
	s_hashmap *map,
	const void *key,
	size_t key_size,
	const void *content
)
{
	size_t		entry_index;
	size_t		hash;
	size_t		normed_hash;
	ssize_t		indice;

	hash = hashmap_hash(key, key_size);
	normed_hash = HASH_NORM(hash, map->capacity);
	indice = -1;

	while ((indice = map->indices[normed_hash]) != UNUSED_ENTRY)
	{
#if (DUPPLICATE_POLICY == DUPP_REPLACE || DUPPLICATE_POLICY == DUPP_KEEP)
		if (indice != DUMMY_ENTRY)
		{
			if (
				key_size == map->entries[indice].key_size &&
				memcmp(map->entries[indice].key, key, key_size) == 0
			)
			{
# if DUPPLICATE_POLICY == DUPP_KEEP
				return ;
# else
				break ;
# endif
			}
		}
#endif
		normed_hash++;
		normed_hash = HASH_NORM(normed_hash, map->capacity);
	}

	if (DUPPLICATE_POLICY == DUPP_REPLACE && indice >= 0)
	{
		entry_index = indice;
	}
	else if (map->nentries > map->used)
	{
		/*
			* We have entries available
		*/
		for (entry_index = 0; entry_index < map->nentries; entry_index++)
		{
			if (map->entries[entry_index].key == NULL) {
				break ;
			}
		}
	}
	else
	{
		map->entries = realloc(map->entries, sizeof(map->entries[0]) * (map->nentries + 3));
		entry_index = map->nentries;
		map->nentries += 3;
	}
	map->indices[normed_hash] = entry_index;
	map->entries[entry_index].hash = hash;
	map->entries[entry_index].key_size = key_size;
	map->entries[entry_index].key = key;
	map->entries[entry_index].content = content;

	map->used += 1;
}