NAME = libft.a

SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strdup.c \
		ft_memcpy.c ft_memset.c ft_memmove.c ft_memccpy.c ft_memcmp.c \
		ft_calloc.c ft_bzero.c ft_memchr.c ft_atoi.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c \
		get_next_line.c get_next_line_utils.c \
		ft_strjoin_free.c ft_strjoin_s1free.c ft_strjoin_s2free.c \
		ft_dlstnew.c ft_dlstadd_front.c ft_dlstsize.c \
		ft_split_count.c ft_free_splited.c \
		util.c get_line.c init_term.c init_cursor.c \
		move_cursor.c insert.c delete.c \
		history.c ctrl_arrow.c ctrl_arrow_2.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
OBJS = $(SRCS:.c=.o)
INCS = .

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
