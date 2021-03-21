/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:12:25 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/11/01 17:53:27 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <inttypes.h>
# include <stdarg.h>

# define PAGEBUF 32

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			ft_strlast(char *s);
size_t			ft_strlen(const char *s);
size_t			ft_strlen_arr(const char **a);
char			*ft_strdup(char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s, const char *t, size_t n);
size_t			ft_strlcat(char *d, const char *s, size_t sz);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_atoi_strict(char *str);
uint64_t		ft_atollu(char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

void			*ft_memalloc(size_t sz);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t sz);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcjoin(char c, char const *s1, char const *s2);
char			*ft_strjoin_arr(char **arr, size_t n, char sep);
char			*ft_strtrim(char const *s);
char			**ft_strcsplit(char const *s, char c);
char			**ft_strnsplit(char const *s, size_t n);
char			**ft_strstrsplit(char *s, char *delim);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, int base);
void			ft_putchar(char c);
void			ft_putchar_binary(char byte);
void			ft_putstr(char const *s);
void			ft_putstr_lower(char const *s);
void			ft_putstr_upper(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar_binary_fd(char byte, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putusage(char *exename, char *usage);

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstadd(t_list **alst, t_list *newlmnt);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *lmnt));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *lmnt));
t_list			*ft_strarr_to_lst(char **strarr);
char			**ft_lst_to_strarr(t_list *lst);
void			ft_lstappend(t_list **alst, t_list *lmnt);
size_t			ft_lstget_id(t_list **alst, void *content, size_t content_size);
t_list			*ft_lstpop(t_list **alst, size_t id);
size_t			ft_lstlen(t_list **alst);
size_t			ft_lstlen_upto(t_list *head, t_list *tail);
void			ft_lstprint(t_list **alst, void (*ft_putlmnt)(t_list *));
t_list			*ft_lstfind_head(t_list **alist, void *content, size_t len);
void			ft_lstfree(t_list *lst);
t_list			*ft_lstdup(t_list *lst);

void			*ft_memrchr(const void *s, int c, size_t n);
char			*ft_strndup(char *s, size_t len);
void			ft_putnstr(const char *s, size_t n);
char			*ft_strcdup(char *str, char c);
size_t			ft_strclen(char *str, char c);
void			ft_putstr_arr(char **arr);
char			*ft_strcnew(size_t sz, char c);
char			*ft_strlower(char *str);
char			*ft_strupper(char *str);
int				ft_strcmp_ci(const char *s1, const char *s2);
char			*ft_strcrop(char *str, size_t start, size_t end);
char			*ft_strdrop(char *str, size_t i, size_t j);
int				ft_strdrop_inplace(char **as, size_t i, size_t j);
char			*ft_strninsert(char *str, char *needle, size_t n);
char			*ft_strreplace(char *str, char *needle, size_t i, size_t j);
char			*ft_ltoa(long long int n);

char			*ft_strhex(unsigned char *ptr, size_t n);
void			endian_toggle(void *ptr, size_t n);
long long		ft_pow(int n, int exp);
char			*ft_read(int fd, char delim);
void			ft_puthex_fd(void *adr, size_t len, int fd, char pad);
void			ft_puthex(void *adr, size_t len, char pad);
uint64_t		*ft_intarr(uint64_t len, ...);
void			ft_putjoin(size_t len, ...);
char			*ft_lutoa(uint64_t n);
size_t			ft_arrint(int *arr, int i);
char			*ft_arrstr(char **arr, char *s);
char			*ft_arrnstr(char **arr, char *s, size_t n);
int				ft_arrstr_id(char **arr, char *s);
char			**ft_strdup_arr(char **src);

void			free_strarr(char **arr, size_t len);
void			free_strarr_all(char **arr);

int				pr_putendl_fd(char const *s, int fd);
int				pr_putstr_fd(char const *s, int fd);
int				pr_strlen(const char *s, size_t *c);

char			*ft_optset(int *aargc, char ***aargv, char *opt_all);
#endif
