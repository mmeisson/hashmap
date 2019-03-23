#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>

typedef void	(*c_hashmap_iterator)(const void *key, size_t key_size, const void *content);
typedef void	(*c_hashmap_creator)(
	const void *key,
	size_t key_size,
	const void *content,
	void **new_key,
	size_t *new_key_size,
	void **new_content
);

struct s_hashmap;
typedef struct s_hashmap s_hashmap;


/*
**	A hashmap is a data structure indexing data with an other data.
**	In a classic array, data is retrieved via integers, like array[6]
**	Here, you can retrieve data via any type
**
**	s_hashmap	map;
**
**	hashmap_new(&map);
**	hashmap_inset(&map, "A string key", strlen("A string key"), "Some random data");
**	hashmap_get(&map, "A string key", strlen("A strinf key")); // Returns a pointer to "Some random data"
**
**	The data stored in this hashmap has an interesting property :
**	It remains in insertion order when iterating over it ( Unless
**		you sort it after insertion(s))
*/


/*
**	Initiate a new hashmap with a default capacity ( Actually == 8 )
**	If the parameter is NULL, then a hashmap is allocated using malloc
**	and will have to be free manually, after the use of hashmap_delete
*/
s_hashmap		*hashmap_new(s_hashmap *hashmap);

/*	Base capacity has to be a power of 2, else the behavior is undefined
*/
s_hashmap		*hashmap_new_cap(s_hashmap *hasmap, size_t base_capacity);

/*
**	Insert a pair key - value in the hashmap
**	Key and values won't be reallocated, you are responsible of the availability
**	of these pointers until the hashmap is deleted
**	This also means you can store some abstract type like function's pointers
*/
int				hashmap_insert(s_hashmap *map, const void *key, size_t key_size, const void * content);

/*
**	Retrieve a data from a key. If the key does not exists, then return NULL.
**	You should NEVER free the object returned from hashmap_get. Use hashmap_remove instead
*/
const void		*hashmap_get(s_hashmap *hashmap, const void * key, size_t key_size);

/*
**	Remove a single item from hashmap. The callback will receive the key as first arg,
**	and the value as second arg.
**	If you don't want to do anything with either the key or the value, you can pass a
**	NULL pointer
*/
void	    	hashmap_remove(s_hashmap *hashmap, const void * key, size_t key_size, void (*remove)(void *, void *));

/*
**	Retrieve the "length", the number of item stored in this hash_map
**	This action has actually no cost
*/
size_t			hashmap_len(s_hashmap *map);

void			hashmap_iter(s_hashmap *map, c_hashmap_iterator callback);
s_hashmap		*hashmap_map(s_hashmap *map, c_hashmap_creator callback);

#endif