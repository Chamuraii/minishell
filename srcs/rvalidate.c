#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_rvalidator(char **str, int i)
{
	while (ft_isspace((*str)[i]))
		i++;
	if (!ft_strncmp(((*str) + i), "|", ft_strlen("|")))
		return (ft_rvalidator_pipe(str, i));
	if (!ft_strncmp(((*str) + i), ">>", ft_strlen(">>")))
		return (ft_rvalidator_append(str, i));
	if (!ft_strncmp(((*str) + i), "<<", ft_strlen("<<")))
		return (ft_rvalidator_heredoc(str, i));
	if (!ft_strncmp(((*str) + i), "<", ft_strlen("<")))
		return (ft_rvalidator_infile(str, i));
	if (!ft_strncmp(((*str) + i), ">", ft_strlen(">")))
		return (ft_rvalidator_outfile(str, i));
	return (1);
}
