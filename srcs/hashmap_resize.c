
#include "_hashmap.h"

void	hashmap_resize(s_hashmap **map, size_t new_capacity)
{
	s_hashmap	*current = *map;
	s_hashmap	*new = hashmap_new_cap(new_capacity);
	size_t		normed_hash;
	size_t		hash;

	if (new != NULL)
	{
		memcpy(new, current, sizeof(*new));
		new->capacity = new_capacity;
		for (size_t i = 0; i < new->nentries; i++)
		{
			hash = new->entries[i].hash;
			do
			{
				normed_hash = HASH_NORM(hash++, new_capacity);
			}
			while (new->indices[i] != UNUSED_ENTRY);

			new->indices[normed_hash] = i;
		}
	}
}