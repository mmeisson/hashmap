
NAME			= libhashmap

CC				= gcc

CFLAGS			= -MD -Wall -Wextra -O2 -g

VPATH			= ./srcs/

SRCS			= hashmap_new.c
SRCS			+= hashmap_insert.c
SRCS			+= hashmap_get.c
SRCS			+= hashmap_hash.c
SRCS			+= hashmap_resize.c
SRCS			+= hashmap_remove.c
SRCS			+= hashmap_len.c
SRCS			+= hashmap_delete.c
SRCS			+= hashmap_iter.c
SRCS			+= hashmap_map.c
SRCS			+= hashmap_filter.c
SRCS			+= hashmap_reduce.c
SRCS			+= hashmap_reverse.c
SRCS			+= hashmap_remap_indices.c
SRCS			+= hashmap_sort_keys.c
SRCS			+= hashmap_sort_content.c
SRCS			+= hashmap_find.c
SRCS			+= hashmap_find_ctx.c
SRCS			+= hashmap_iter_ctx.c
SRCS			+= hashmap_map_ctx.c
SRCS			+= hashmap_reduce_ctx.c
SRCS			+= hashmap_filter_ctx.c
SRCS			+= hashmap_sort_keys_ctx.c
SRCS			+= hashmap_sort_content_ctx.c
SRCS			+= hashmap_concat.c

INCS_PATHS		= ./incs/ ./

INCS			= $(addprefix -I,$(INCS_PATHS))

OBJS_PATH		= ./.objs/
OBJS_NAME		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_PATH), $(OBJS_NAME))


DEPS			= $(OBJS:.o=.d)

LDFLAGS			=



all: $(NAME)

$(NAME): static

static: $(OBJS)
	ar rc $(NAME).a $(OBJS)

$(OBJS_PATH)%.o: $(SRCS_PATHS)%.c Makefile
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	rm -rf $(OBJS_PATH)

fclean:
	rm -rf $(OBJS_PATH)
	rm -f $(NAME).a

re:
	make fclean
	make -j32 all

-include $(DEPS)
