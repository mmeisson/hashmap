
#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

const void	*hashmap_get(s_hashmap *map, const void *key, size_t key_size)
{
	size_t	hash = hashmap_hash(key, key_size);
	size_t	normalized_hash;
	ssize_t	entry_index;

	while (1)
	{
		normalized_hash = hashmap_hash_norm(hash, map->capacity);
		entry_index = map->indices[normalized_hash];
		if (entry_index >= 0)
		{
			s_entry		*entry = &map->entries[entry_index];
			if (
				entry->key_size == key_size
				&& memcmp(key, entry->key, key_size) == 0
			)
			{
				return entry->content;
			}
		}
		else if (entry_index == HASHMAP_UNUSED_ENTRY)
		{
			// We passed every dummy and used entry
			break ;
		}
		hash++;
	}
	return NULL;
}