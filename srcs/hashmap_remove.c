
#include <string.h>
#include <stdlib.h>
#include "_hashmap.h"

void    hashmap_remove(
	s_hashmap *map,
	const void *key,
	size_t key_size,
	void (*remove)(void *, void *)
)
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
				if (remove != NULL)
				{
					remove((void *)entry->key, (void *)entry->content);
				}
				map->used--;
				map->indices[normalized_hash] = HASHMAP_DUMMY_ENTRY;
				memset(entry, 0, sizeof(*entry));
				if (hashmap_is_underloaded(map->capacity, map->used))
				{
					hashmap_resize(map, map->capacity >> 1);
				}
#if DUPPLICATE_POLICY != DUPP_INSERT
				break ;
#endif
			}
		}
		else if (entry_index == HASHMAP_UNUSED_ENTRY)
		{
			// We passed every dummy and used entry
			break ;
		}
		hash++;
	}
}