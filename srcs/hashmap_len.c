
#include <stdlib.h>
#include "_hashmap.h"

size_t      hashmap_len(s_hashmap *map)
{
    return map->used;
}