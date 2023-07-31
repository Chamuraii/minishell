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
	char 	*str3;

	i = 0;
	while ((*str)[i] != '$')
		i++;
	i++;
	(*str)[i - 1] = 0;
	str2 = ft_strjoin(ft_strdup(*str), ft_get_var((*str) + i));
	while (ft_isalnum((*str)[i]) || (*str)[i] == '?')
		i++;
	str3 = ft_strdup((*str) + i);
	free((*str));
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

int	ft_dont_expand(char *str, int i)
{
	while (str[i] != '=' && str[i] && !ft_isspace(str[i]))
		i++;
	if (str[i] == '=')
		return (1);
	else
		return (0);
}

char	*ft_reassign(char **str, char **array, int cnt)
{
	int		i;

	i = 0;
	if (!ft_strcmp((*str), ">|"))
		ft_change_str(str, ">");
	if (!ft_strcmp((*str), "<>"))
		ft_change_str(str, "<");
	while ((*str)[i])
	{
		if ((*str)[i] == 20)
			(*str)[i] = 32;
		if ((*str)[0] != SQ)
		{
			if ((*str)[i] == '$')
			{
				if (!ft_dont_expand(*str, i))
				{
					*str = ft_expand(str);
					i = -1;
				}
			}
		}
		i++;
	}
	if (!ft_is_p_or_r_between_quotes(*str) && !ft_quotes_jess(*str))
		(*str) = ft_remove_quotes_2(str);
	if (!array[i + 1] && cnt == 0)
		ft_var_declare((*str));
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
		array[i] = ft_reassign(&(array[i]), array, i);
		i++;
	}
	return (array);
}
