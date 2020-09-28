//env.c/////////////////////////////////////////////////////////////////////////

#include "minishell.h"

char	*env_getvalue(t_list *envlst, char *varname)
{
	char	*str;
	t_list	*env_entry;

	str = ft_strjoin(varname, "=");
	env_entry = ft_lstfind_head(&envlst, (void *)str, ft_strlen(str));
	free(str);
	if (!env_entry)
		return (NULL);
	str = ft_strchr((char *)(env_entry->content), '=') + 1;
	return (str);
}
