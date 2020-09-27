//ft_puthex.c///////////////////////////////////////////////////////////////////
#include "libft.h"

void	ft_puthex(void *adr, size_t len, char pad)
{
	ft_puthex_fd(adr, len, 1, pad);
}

/*
#include <strings.h>
int		main(int argc, char **argv)
{
	char	c;

	if (argc != 2)
		return (1);
	c = atoi(argv[1]);
	ft_puthex(&c, 1);
	ft_putchar('\n');
	return (0);
}
*/
