#include "../includes/minishell.h"

extern t_all g_all;

char	*ft_change_str(char *str, const char *str2)
{
	if (str)
		free(str);
	if (!str2)
		return (0);
	str2 = strdup(str2);
	return ((char *) str2);
}

char *ft_remove_19(char *str)
{
	int	i;
	int j;
	char	*str2;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != 19)
		{
			i++;
			j++;
		}
		if (str[i])
			i++;
	}
	str2 = (char *)malloc(j + 1);
	if (!str2)
		return (0);
	i = 0;
	str2[j] = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 19)
			str2[j++] = str[i];
		i++;
	}
	free (str);
	return (str2);
}

char *ft_expand(char *str)
{
	int		i;
	char	*str2;
	char 	aux;

	i = 0;
	while (str[i] != '\20')
		i++;
	i++;
	aux = str[i - 1];
	str[i - 1] = 0;
	str2 = ft_strjoin(ft_strdup(str), ft_get_var(str + i));
	str[i - 1] = aux;
	while (ft_isalnum(str[i]) || str[i] == '\023' || str[i] == '\024')
		i++;
	str2 = ft_strjoin(str2, ft_strdup(str + i));
	free (str);
	return (str2);
}

char	*ft_reassign(char *str)
{
	int	i;

	i = 0;
	if (!strcmp(str, ">|"))
		ft_change_str(str, ">");
	if (!strcmp(str, "<>"))
		ft_change_str(str, "<");
	if (!strcmp(str, "\21"))
		ft_change_str(str, "");
	ft_var_declare(str);
	while (str[i])
	{
		if (str[i] == 20)
			str[i] = 32;
		if (str[i] == 19)
		{
			str = ft_remove_19(str);
			i = 0;
		}
		if (str[i] == '\20')
		{
			str = ft_expand(str);
			i = 0;
		}
		i++;
	}
	return (str);
}

char	**to_double_pointer(char *str)
{
	int	i;
	char **array;

	i = 0;
	array = ft_split(str, ' ');
	while (array[i])
	{
		array[i] = ft_reassign(array[i]);
		i++;
	}
	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return (array);
}
