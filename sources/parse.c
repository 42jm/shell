//parse.c///////////////////////////////////////////////////////////////////////

#include "minishell.h"

int	parse_userinput(char *line, char ***aargs)
{
	char	*ptr;

	if (!line)
		return (1);
	if (*line == '\0')
	{
		*aargs = (char **)malloc(sizeof(**aargs) * 2);
		(*aargs)[0] = ft_strdup("exit");
		(*aargs)[1] = NULL;
		return (0);
	}
	if (*line == '\n')
	{
		*aargs = NULL;
		return (0);
	}
	if ((ptr = ft_strchr(line, '\n')))
		*ptr = '\0';
	else
		pr_putstr_fd("\n", 1);
	*aargs = ft_strcsplit(line, ' ');
	return (0);
}
