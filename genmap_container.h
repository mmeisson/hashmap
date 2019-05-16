#ifndef GENMAP_CONTAINER_H
# define GENMAP_CONTAINER_H

/*
**	u_genmap_container is used to store data of basic types
**	Gives the possibility to store both pointers and primitive types
**	without casts everywhere
*/
typedef union		u_genmap_container
{
	const void	*as_ptr;
	const char	*as_str;
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



static inline u_genmap_container
	container_from_ptr(const void * ptr)
{
	const u_genmap_container	tmp = { .as_ptr = ptr };

	return tmp;
}

static inline u_genmap_container
	container_from_str(const char * str)
{
	const u_genmap_container	tmp = { .as_str = str };

	return tmp;
}

static inline u_genmap_container
	container_from_uint(size_t value)
{
	const u_genmap_container	tmp = { .as_uint = value };

	return tmp;
}

static inline u_genmap_container
	container_from_sint(ssize_t value)
{
	const u_genmap_container	tmp = { .as_sint = value };

	return tmp;
}

static inline u_genmap_container
	container_from_float(double value)
{
	const u_genmap_container	tmp = { .as_float = value };

	return tmp;
}

static inline u_genmap_container
	container_from_char(char value)
{
	const u_genmap_container	tmp = { .as_char = value };

	return tmp;
}

#endif
