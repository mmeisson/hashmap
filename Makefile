
NAME			= hashmap

CC				= gcc

CFLAGS			= -MD -Wall -Werror -Wextra -g

VPATH			= ./srcs/

SRCS			= hashmap_new.c
SRCS			+= hashmap_insert.c
SRCS			+= hashmap_get.c
SRCS			+= hashmap_hash.c
SRCS			+= hashmap_resize.c
SRCS			+= hashmap_remove.c

INCS_PATHS		= ./incs/

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
	rm -f $(NAME)

re:
	make fclean
	make -j32 all

-include $(DEPS)
