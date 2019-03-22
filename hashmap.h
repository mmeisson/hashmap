#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>

struct s_hashmap;
typedef struct s_hashmap s_hashmap;

s_hashmap		*hashmap_new();

/*	Base capacity has to be a power of 2, else undefined behavior
*/
s_hashmap		*hashmap_new_cap(size_t base_capacity);


void			hashmap_insert(s_hashmap *map, const void *key, size_t key_size, const void * content);

#endif