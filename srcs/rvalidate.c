#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_rvalidator(char **str, int i)
{
	while (ft_isspace((*str)[i]))
		i++;
	if (!ft_strncmp(((*str) + i), "|", ft_strlen("|")))
		return (ft_rvalidator_1(str, i));
	if (!ft_strncmp(((*str) + i), ">>", ft_strlen(">>")))
		return (ft_rvalidator_2(str, i));
	if (!ft_strncmp(((*str) + i), "<<", ft_strlen("<<")))
		return (ft_rvalidator_3(str, i));
	if (!ft_strncmp(((*str) + i), "<", ft_strlen("<")))
		return (ft_rvalidator_4(str, i));
	if (!ft_strncmp(((*str) + i), ">", ft_strlen(">")))
		return (ft_rvalidator_5(str, i));
	return (1);
}
