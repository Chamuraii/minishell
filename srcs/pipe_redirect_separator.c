#include "../includes/minishell.h"

extern t_all g_all;

void	ft_rseparator_1(char *str, int i)
{
	char *str2;
	char *str3;

	str[i] = 0;
	str2 = ft_strdup(str);
	str3 = ft_strdup(str + i + 1);
	if (i != 0)
		if (str[i - 1] != 32 && str[i - 1] != '>')
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("|"));
	if (str[i + 1] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free(str);
	str = ft_strjoin(str2, str3);
}

void	ft_rseparator_2(char *str, int i)
{
	char *str2;
	char *str3;

	str[i] = 0;
	str2 = ft_strdup(str);
	str3 = ft_strdup(str + i + 2);
	if (i != 0)
		if (str[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("<<"));
	if (str[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free(str);
	str = ft_strjoin(str2, str3);
}
void	ft_rseparator_3(char *str, int i)
{
	char *str2;
	char *str3;

	str[i] = 0;
	str2 = ft_strdup(str);
	str3 = ft_strdup(str + i + 2);
	if (i != 0)
		if (str[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup(">>"));
	if (str[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free(str);
	str = ft_strjoin(str2, str3);
}
void	ft_rseparator_4(char *str, int i)
{
	char *str2;
	char *str3;

	str[i] = 0;
	str2 = ft_strdup(str);
	str3 = ft_strdup(str + i + 2);
	if (i != 0)
		if (str[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("<>"));
	if (str[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free(str);
	str = ft_strjoin(str2, str3);
}

void	ft_rseparator(int state, char *str, int i)
{
	if (state == NQ)
	{
		if (!ft_strncmp(str + i, "|", 1))
			ft_rseparator_1(str, i);
		else if (!ft_strncmp(str + i, "<<", 2))
			ft_rseparator_2(str, i);
		else if (!ft_strncmp(str + i, ">>", 2))
			ft_rseparator_3(str, i);
		else if (!ft_strncmp(str + i, "<>", 2))
			ft_rseparator_4(str, i);
		else if (!ft_strncmp(str + i, "<", 1))
			ft_rseparator_5(str, i);
		else if (!ft_strncmp(str + i, ">", 1))
			ft_rseparator_6(str, i);
	}
}