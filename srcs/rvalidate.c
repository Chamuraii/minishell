#include "../includes/minishell.h"

int ft_rvalidator(char *str, int i)
{
	int ward;

	while (ft_isspace(str[i]))
		i++;
	if (!ft_strncmp((str + i), "|", ft_strlen("|")))
	{
		ward = i;
		if (i)
			i--;
		while (ft_isspace(str[i]) && i > 0)
			i--;
		if (ft_isspace(str[i]) || str[i] == '|')
			return (0);
		i = ward;
		i += ft_strlen("|");
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|' || !str[i])
			return (0);
		if (str[i])
		return (1);
	}
	if (!ft_strncmp((str + i), ">>",ft_strlen(">>")))
	{
		i += ft_strlen(">>");
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (0);
		return (1);
	}
	if (!ft_strncmp((str + i), "<<",ft_strlen("<<")))
	{
		i += ft_strlen("<<");
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (0);
		return (1);
	}
	if (!ft_strncmp((str + i), "<",ft_strlen("<")))
	{
		ward = i;
		if (!i)
			i--;
		while (ft_isspace(str[i]) && i > 0)
			i--;
		if (!i)
			return (0);
		i = ward;
		i += ft_strlen("<");
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|' || str[i] == '<' || !str[i])
			return (0);
		if (str[i] == '>')
		{
			if (ft_isspace(str[i - 1]))
				return (0);
			i++;
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
				return (0);
		}
		return (1);
	}
	if (!ft_strncmp((str + i), ">",ft_strlen(">")))
	{
		i += ft_strlen(">");
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
		{
			if (ft_isspace(str[i - 1]))
				return (0);
			i++;
			while (ft_isspace(str[i]))
				i++;
		}
		if (str[i] == '<' || str[i] == '>' || !str[i])
			return (0);
		return (1);
	}
	return (1);
}

int	ft_rvalidate(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_rvalidator(str, i))
			return (0);
		i++;
	}
	return (1);
}