#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_rvalidator_1(char **str, int i)
{
	int	ward;

	ward = i;
	if (i)
		i--;
	while (ft_isspace((*str)[i]) && i > 0)
		i--;
	if (ft_isspace((*str)[i]) || (*str)[i] == '|')
		return (0);
	i = ward;
	i += ft_strlen("|");
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] == '|' || !(*str)[i])
		return (0);
	if ((*str)[i])
		return (1);
	return (1);
}

int	ft_rvalidator_2(char **str, int i)
{
	i += ft_strlen(">>");
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] == '|' || (*str)[i] == '<' || (*str)[i] == '>')
		return (0);
	return (1);
}

int	ft_rvalidator_3(char **str, int i)
{
	i += ft_strlen("<<");
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] == '|' || (*str)[i] == '<' || (*str)[i] == '>')
		return (0);
	return (1);
}

int	ft_rvalidator_4(char **str, int i)
{
	i += ft_strlen("<");
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] == '|' || (*str)[i] == '<' || !(*str)[i])
		return (0);
	if ((*str)[i] == '>')
	{
		if (ft_isspace((*str)[i - 1]))
			return (0);
		i++;
		while (ft_isspace((*str)[i]))
			i++;
		if ((*str)[i] == '|')
			return (0);
	}
	return (1);
}

int	ft_rvalidator_5(char **str, int i)
{
	i += ft_strlen(">");
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] == '|')
	{
		if (ft_isspace((*str)[i - 1]))
			return (0);
		i++;
		while (ft_isspace((*str)[i]))
			i++;
	}
	if ((*str)[i] == '<' || (*str)[i] == '>' || !(*str)[i])
		return (0);
	return (1);
}
