#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>
# include <string.h>


/*
**	hashmap's Data
**	The hashmap is a data structure used to store any kind of data in a way
**	you can retrieve it in contant time with a key of any type.
**	This library gives a macro HASHMAP_DATA that will be used to define at
**	compile time what kind of data can be used, and some usefull hopefully
**	generic usefull data structures to use.
**
**	If you intend to use the hashmap only as an int store, you can
**	define HASHMAP_DATA (int)
**
**	Avoid to set HASHMAP_DATA to a complex type since it it passed to
**	hashmap's function by itself and not by pointers
*/

/*
**	u_genmap_container is used to store data of basic types
**	Gives the possibility to store both pointers and primitive types
**	without casts everywhere
*/
typedef union		u_genmap_container
{
	void	*as_ptr;
	char	*as_str;
	size_t	as_uint;
	ssize_t	as_sint;
	double	as_float;
	char	as_char;
}					u_genmap_container;

typedef enum		e_genmap_type_container
{
	TYPE_PTR,
	TYPE_STR,
	TYPE_UINT,
	TYPE_SINT,
	TYPE_FLOAT,
	TYPE_CHAR,
}					e_genmap_type_container;


/*
**	The following structure stores a type hinter if you need to use one at runtime
**	for the u_genmap_container
*/

typedef struct		t_genmap_hint_container
{
	u_genmap_container			container;
	e_genmap_type_container		type;
}					t_genmap_hint_container;

# define HASHMAP_DATA		u_genmap_container

typedef void	(*c_hashmap_iterator)(const void *key, size_t key_size, const void *content);
typedef void	(*c_hashmap_iterator_ctx)(
	const void *key, size_t key_size, const void *content, void *ctx
);
typedef void	(*c_hashmap_creator)(
	const void *key,
	size_t key_size,
	const void *content,
	void **new_key,
	size_t *new_key_size,
	void **new_content
);
typedef void	(*c_hashmap_creator_ctx)(
	const void *key,
	size_t key_size,
	const void *content,
	void **new_key,
	size_t *new_key_size,
	void **new_content,
	void *context
);
typedef int	(*c_hashmap_validator)(const void *key, size_t key_size, const void *content);
typedef int	(*c_hashmap_validator_ctx)(const void *key, size_t key_size, const void *content, void *context);
typedef void	(*c_hashmap_reducor)(const void *key, size_t key_size, const void *content, void **data);
typedef void	(*c_hashmap_reducor_ctx)(const void *key, size_t key_size, const void *content, void **data, void *context);
typedef int		(*c_hashmap_comparator)(const void *left, const void *right);
# if defined(__APPLE__) || defined(BSD)
typedef int		(*c_hashmap_comparator_ctx)(void *context, const void *left, const void *right);
# else
typedef int		(*c_hashmap_comparator_ctx)(const void *left, const void *right, void *context);
# endif

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
int				hashmap_insert(s_hashmap *map, const void *key, size_t key_size, const void *content);

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

void			hashmap_reverse(s_hashmap *map);

void			hashmap_iter(s_hashmap *map, c_hashmap_iterator callback);
const void		*hashmap_find(s_hashmap *map, c_hashmap_validator callback);

s_hashmap		*hashmap_map(s_hashmap *map, c_hashmap_creator callback);
s_hashmap		*hashmap_filter(s_hashmap *map, c_hashmap_validator callback);
void			hashmap_reduce(s_hashmap *map, c_hashmap_reducor callback);

void			hashmap_iter_ctx(s_hashmap *map, c_hashmap_iterator_ctx callback, void *context);
const void		*hashmap_find_ctx(s_hashmap *map, c_hashmap_validator_ctx callback, void *context);

s_hashmap		*hashmap_map_ctx(s_hashmap *map, c_hashmap_creator_ctx callback, void *context);
s_hashmap		*hashmap_filter_ctx(s_hashmap *map, c_hashmap_validator_ctx callback, void *context);
void			hashmap_reduce_ctx(s_hashmap *map, c_hashmap_reducor_ctx callback, void *context);

void			hashmap_sort_keys(s_hashmap *map, c_hashmap_comparator);
void			hashmap_sort_content(s_hashmap *map, c_hashmap_comparator);

void			hashmap_sort_keys_ctx(s_hashmap *map, c_hashmap_comparator_ctx, void *content);
void			hashmap_sort_content_ctx(s_hashmap *map, c_hashmap_comparator_ctx, void *content);


/*
**	Some utilities when keys are strings
*/
static inline int	hashmap_ks_insert(s_hashmap *map, const char *key, const void *content)
{
	return hashmap_insert(map, key, strlen(key), content);
}

static inline const void	*hashmap_ks_get(s_hashmap *map, const void * key)
{
	return hashmap_get(map, key, strlen(key));
}

static inline void	    	hashmap_ks_remove(s_hashmap *map, const void * key, void (*remove)(void *, void *))
{
	hashmap_remove(map, key, strlen(key), remove);
}

/*
**	A default sort ?
*/
# define hashmap_sort(map, comparator) hashmap_sort_content(map, comparator)

#endif
