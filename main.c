
#include <stdio.h>

#include "hashmap.h"
#include "./incs/_hashmap.h"

void	print_map(s_hashmap *map)
{
	printf("Hashmap.capacity == %zu, hashmap.used == %zu\n", map->capacity, map->used);
	printf("Indices:: [ ");
	for (size_t i = 0; i < map->capacity; i++) {
		printf("%ld, ", map->indices[i]);
	}
	printf("\b\b ]\n");
	printf("Entries :: [\n");
	for (size_t i = 0; i < map->nentries; i++) {
		if (map->entries[i].key != NULL)
		{
			printf("\tEntry {.key_size %zu, .key = %s, .content = %s}\n", map->entries[i].key_size, map->entries[i].key, (char *)map->entries[i].content);
		}
	}
	printf("]");
	printf("\n");

}

int		main(int ac, char **av)
{
	s_hashmap	*map = hashmap_new();

	print_map(map);
	hashmap_insert(map, "coucou", 7, "ca va ?");
	hashmap_insert(map, "wesh", 4, "ca va ?");
	hashmap_insert(map, "la caleche", 10, "ca va ?");
	hashmap_insert(map, "wesh", 4, "sa va ?");
	printf("Insertion done\n");
	print_map(map);
}
