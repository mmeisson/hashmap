
#include "_hashmap.h"

void        hashmap_remap_indices(s_hashmap *map)
{
	size_t		hash;
	size_t		normalized_hash;

    for (size_t i = 0; i < map->capacity; i++)
    {
        map->indices[i] = HASHMAP_DEFAULT_ENTRY;
    }
    for (size_t i = 0; i < map->nentries; i++)
    {
        if (map->entries[i].key != NULL)
        {
            hash = map->entries[i].hash;

            do
            {
                normalized_hash = hashmap_hash_norm(hash++, map->capacity);
            }
            while (map->indices[i] != HASHMAP_UNUSED_ENTRY);
            map->indices[normalized_hash] = i;
        }
    }
}
