#include <stdlib.h>
#include <string.h>
#include "_hashmap.h"

int		hashmap_insert(
	s_hashmap	*map,
	const void	*key,
	size_t		key_size,
	const void	*content
)
{
	ssize_t		entry_index;
	size_t		hash;
	size_t		normed_hash;

	hash = hashmap_hash(key, key_size);
	normed_hash = hashmap_hash_norm(hash, map->capacity);
	entry_index = -1;

	if (hashmap_is_overloaded(map->capacity, map->used))
	{
		if (hashmap_resize(map, map->capacity << 1) < 0)
		return -1;
	}

	while ((entry_index = map->indices[normed_hash]) != HASHMAP_UNUSED_ENTRY)
	{
#if (DUPPLICATE_POLICY == DUPP_REPLACE || DUPPLICATE_POLICY == DUPP_KEEP)
		if (entry_index != HASHMAP_DUMMY_ENTRY)
		{
			if (
				key_size == map->entries[entry_index].key_size &&
				memcmp(map->entries[entry_index].key, key, key_size) == 0
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
		normed_hash = hashmap_hash_norm(normed_hash, map->capacity);
	}

	if (!(DUPPLICATE_POLICY == DUPP_REPLACE && entry_index >= 0))
	{
		if (map->nentries > map->used)
		{
			entry_index = map->nentries;
			while (entry_index-- > 0)
			{
				if (map->entries[entry_index].key != NULL) {
					entry_index++;
					break ;
				}
			}

			map->used += 1;
		}
		else
		{
			entry_index = map->nentries;
			map->nentries += (1 + HASHMAP_OVERSIZE_ENTRIES);

			s_entry	*tmp = realloc(
				map->entries,
				sizeof(map->entries[0]) * map->nentries
			);
			if (tmp == NULL)
			{
				return -1;
			}
			map->entries = tmp;
			memset(
				map->entries + entry_index,
				0,
				sizeof(map->entries[0]) * (1 + HASHMAP_OVERSIZE_ENTRIES)
			);

			map->used += 1;
		}
	}
	map->indices[normed_hash] = entry_index;
	map->entries[entry_index].hash = hash;
	map->entries[entry_index].key_size = key_size;
	map->entries[entry_index].key = key;
	map->entries[entry_index].content = content;
	return 0;
}
