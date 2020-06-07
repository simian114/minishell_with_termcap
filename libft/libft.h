/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:52:28 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/07 22:27:36 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <string.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>

# define IS_VALID(x) (((x) >= ' ' && (x) <= '~'))

# define X				1
# define Y				0
# define RET			10
# define DEL			127
# define ESC			27
# define UP				65
# define DOWN			66
# define RIGHT			67
# define LEFT			68
# define HOME			72
# define END			70
# define TAB			9
# define LINE_BUFF_SIZE	4096

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct		s_term
{
	struct termios	term;
	struct winsize	window_size;
	char			*name;
	size_t			width;
	size_t			height;
}					t_term;

typedef struct		s_line
{
	char			buf[6];
	char			*line;
	size_t			line_size;
	char			*prompt;
	size_t			prompt_size;
	size_t			cursor_pos;
	size_t			cursor[2];
	t_term			*config;
	int				sigint_count;
}					t_line;

t_line				g_data;

/*
** util.c
*/
int					ft_putchar(int c);
void				ft_tputs(char *cmd);
void				sigint_getline(int signo);

/*
** 1.get_line.c
*/
char				*get_line_term(char *prompt, t_dlist **his);
int					my_out(int c);
void				my_tputs(char *cmd);

/*
** 2.init_term.c
*/
int					init_terminal(t_term *config, t_line *data, char *prompt);
void				get_window_size(t_term *config);
void				init_line(t_line *data, char *prompt);
void				restore_term(void);

/*
** 3.init_cursor.c
*/
void				init_cursor(t_term *config, t_line *data);
void				get_cursor_pos(t_term *config, t_line *data);

/*
** 4.move_cursor.c
*/
void				move_cursor(t_line *data);
void				left_arrow(t_line *data);
void				right_arrow(t_line *data);
void				move_home(t_line *data);
void				move_end(t_line *data);

/*
** 5.insert.c
*/
void				insert(t_line *data);

/*
** 6.delete.c
*/
void				delete(t_line *data);

/*
** 7.history.c
*/
t_dlist				*search_history(t_line *data,
					t_dlist *history, char arrow);

/*
** 8.ctrl_arrow.c
*/
void				ctrl_arrow(t_line *data, char arrow);
void				up_line(t_line *data);
void				down_line(t_line *data);


char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoin_s1free(char *s1, char *s2);
char				*ft_strjoin_s2free(char *s1, char *s2);
void				ft_free_splited(char **freed);
int					ft_split_count(char **split);

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
								size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_calloc(size_t num, size_t size);
char				*ft_strdup(const char *s);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));

t_dlist				*ft_dlstnew(void *content);
int					ft_dlstsize(t_dlist *lst);
void				ft_dlstadd_front(t_dlist **lst, t_dlist *new);

int					get_next_line(int fd, char **line);

#endif
