
#include <unistd.h>
#include "_hashmap.h"

void    hashmap_delete(
	s_hashmap *map,
	c_hashmap_eraser remove
)
{
    if (map->indices != NULL)
    {
        free(map->indices);
        map->indices = NULL;
    }
    if (map->entries != NULL)
    {
        if (remove != NULL)
        {
            for (size_t i = 0; i < map->nentries; i++)
            {
                s_entry     *entry = map->entries + i;

                if (entry->key != NULL)
                {
                    remove((void *)entry->key, entry->content);
                }
            }
        }
        free(map->entries);
        map->entries = NULL;
    }
}
