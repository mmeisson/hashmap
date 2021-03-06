#ifndef _HASHMAP_H
# define _HASHMAP_H

# include <stdlib.h>
# include <unistd.h>

# include "hashmap.h"

/*
**	REPLACE		If a key is already inserted, replace his value
**	KEEP		If a key is already inserted, let his value unchanged
**	INSERT		Re insert the key, no matter if already exists or not
*/
# define DUPP_REPLACE		0
# define DUPP_KEEP			1
# define DUPP_INSERT		2

# define DUPPLICATE_POLICY	DUPP_REPLACE

# define HASHMAP_UNUSED_ENTRY	-1
# define HASHMAP_DUMMY_ENTRY	-2

# define HASHMAP_DEFAULT_ENTRY	HASHMAP_UNUSED_ENTRY

# define HASHMAP_BASE_SIZE			8
# define HASHMAP_MAX_LOAD	((float)0.66)
# define HASHMAP_MIN_LOAD	((float)0.22)

# if defined(BSD) || defined(__APPLE__)
#  define QSORT_R_COMPATIBLE(base, nmemb, size, cmp, arg) qsort_r(base, nmemb, size, arg, cmp)
# else
#  define QSORT_R_COMPATIBLE(base, nmemb, size, cmp, arg) qsort_r(base, nmemb, size, cmp, arg)
# endif

/*
**	When reallocing entries
*/
# define HASHMAP_OVERSIZE_ENTRIES	3

/*
**	Utilities
*/
static inline size_t	hashmap_hash_norm(size_t hash, size_t norm)
{
	// Returns normalized hash, aka hash % norm, where norm
	// is the current capacity of a hashmap
	return hash & (norm - 1);
}

static inline int		is_power_of_two(size_t capacity)
{
	return (capacity & (capacity - 1)) == 0;
}

static inline int		hashmap_is_overloaded(size_t capacity, size_t used)
{
	// Returns true if hashmap's load is over 66%
	return used / (float)capacity >= HASHMAP_MAX_LOAD;
}

static inline int		hashmap_is_underloaded(size_t capacity, size_t used)
{
	// Returns true if hashmap's load is over 66%
	return capacity > HASHMAP_BASE_SIZE
		&& used / (float)capacity < HASHMAP_MIN_LOAD;
}


/*
**	An entry is a container for user data
**	
**	hash : the hash for the key. Stored in order not to have to
**		to recompute it on every resize
**	key_size : The size of the key. Since the key can be any data
**		type, we have to store it's size
**
**	key : Any data type used as index. This data is stored as is
**		and thus, should be freed with hashmap_remove or hashmap_delete
**		if mallocated.
**		/!\ The key should have at least the same life time as the hashmap
**
**	content : Any data type used as index. This data is stored as is
**		and thus, should be freed with hashmap_remove or hashmap_delete
**		if mallocated.
**		/!\ The key should have at least the same life time as the hashmap
**
**	The choice was made not to reallocate given input not only for performance,
**	but also to be able to store things like function's pointers
*/
typedef struct	s_entry
{
	size_t			hash;
	size_t			key_size;
	const void		*key;
	HASHMAP_DATA	content;
}				s_entry;


struct			s_hashmap
{
	size_t			capacity;
	size_t			used;
	size_t			nentries;
	s_entry			*entries;
	ssize_t			*indices;
};

struct			s_hashmap_key_sortcontext
{
	void							*context;
	c_hashmap_key_comparator_ctx	callback;
};

struct			s_hashmap_sortcontext
{
	void						*context;
	c_hashmap_comparator_ctx	callback;
};


size_t		hashmap_hash(const void *content, size_t size);
void		hashmap_remap_indices(s_hashmap *map);
int			hashmap_resize(s_hashmap *hashmap, size_t new_capacity);

#endif
