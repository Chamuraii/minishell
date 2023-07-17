#include "../includes/minishell.h"

extern t_all	g_all;

char	*ft_change_str(char **str, const char *str2)
{
	free((*str));
	if (!str2)
		return (0);
	str2 = ft_strdup(str2);
	return ((char *) str2);
}

char	*ft_expand(char **str)
{
	int		i;
	char	*str2;
	char	aux;

	i = 0;
	while ((*str)[i] != '$')
		i++;
	i++;
	aux = (*str)[i - 1];
	(*str)[i - 1] = 0;
	str2 = ft_strjoin(ft_strdup((*str)), ft_get_var((*str) + i));
	(*str)[i - 1] = aux;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '\023' || (*str)[i] == '\024')
		i++;
	(*str) = ft_strjoin(str2, ft_strdup((*str) + i));
	free ((*str));
	return ((*str));
}

char	*ft_reassign(char **str)
{
	int	i;

	i = 0;
	if (!ft_strcmp((*str), ">|"))
		ft_change_str(str, ">");
	if (!ft_strcmp((*str), "<>"))
		ft_change_str(str, "<");
	ft_var_declare((*str));
	while (str[i])
	{
		if ((*str)[i] == 20)
			(*str)[i] = 32;
		if ((*str)[0] != SQ)
		{
			if ((*str)[i] == '$')
			{
				(*str) = ft_expand(str);
				i = 0;
			}
		}
		i++;
	}
	return ((*str));
}

char	**to_double_pointer(char **str)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_split((*str), ' ');
	while (array[i])
	{
		array[i] = ft_reassign(&(array[i]));
		i++;
	}
	return (array);
}
