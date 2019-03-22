#ifndef _HASH_MAP_H
# define _HASH_MAP_H

# include <stdlib.h>
# include <unistd.h>

/*
**	REPLACE		If a key is already inserted, replace his value
**	KEEP		If a key is already inserted, let his value unchanged
**	INSERT		Re insert the key, no matter if already exists or not
*/
# define DUPP_REPLACE		0
# define DUPP_KEEP			1
# define DUPP_INSERT		2

# define DUPPLICATE_POLICY	DUPP_REPLACE

# define UNUSED_ENTRY	-1
# define DUMMY_ENTRY	-2

# define BASE_SIZE		8

# define HASH_NORM(hash, norm) (hash & (norm - 1))
# define IS_POWER_OF_TWO(val) ((val) & (val - 1) == 0)

typedef struct	s_entry
{
	size_t			hash;
	size_t			key_size;
	const void		*key;
	const void		*content;
}				s_entry;


typedef struct s_hashmap
{
	size_t			capacity;
	size_t			used;
	size_t			nentries;
	s_entry			*entries;
	unsigned char	indices[];
}				s_hashmap;

size_t			hashmap_hash(const void *content, size_t size);

#endif