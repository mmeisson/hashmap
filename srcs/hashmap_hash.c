#include <stdlib.h>

size_t		hashmap_hash(const void * key, size_t key_size)
{
	const unsigned char		*ckey = key;
	size_t					hash = 5381;

	for (size_t i = 0; i < key_size; i++)
	{
		hash = (hash << 5) + hash + ckey[i];
	}
	return hash;
}