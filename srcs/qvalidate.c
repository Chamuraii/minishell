#include "../includes/minishell.h"

int	ft_squote_state(char c, int old_state)
{
	if ((!old_state || old_state == SQC || old_state == DQC) && c == SQ)
		return (SQO);
	else if ((old_state == SQO || old_state == SQI) && c != SQ)
		return (SQI);
	else if (old_state == SQI || old_state == SQO)
		return (SQC);
	return (NQ);
}

int	ft_dquote_state(char c, int old_state)
{
	if ((!old_state || old_state == SQC || old_state == DQC) && c == DQ)
		return (DQO);
	else if ((old_state == DQO || old_state == DQI) && c != DQ)
		return (DQI);
	else if (old_state == DQI || old_state == DQO)
		return (DQC);
	return (NQ);
}

int ft_quote_state(char c, int old_state)
{
	int state;

	state = ft_dquote_state(c, old_state);
	if (!state)
		state = ft_squote_state(c, old_state);
	return (state);
}

void	ft_expander_val(char *str, int i)
{
	char *str2;
	char *str3;

	str[i] = 0;
	str2 = ft_strdup(str);
	str3 = ft_strdup(str + i + 1);
	if (str[i + 1] == '$' || ft_isspace(str[i + 1]))
		str2 = ft_strjoin(str2, strdup("$"));
	else
		str2 = ft_strjoin(str2, strdup("\20"));
	free(str);
	str = ft_strjoin(str2, str3);
}

int ft_qvalidator(char *str)
{
	int i;
	int state;

	state = 0;
	i = 0;
	if (!str[0])
		return (1);
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\''))
		{
			str[i] = str[i + 1];
			str[i + 1] = 19;
			i++;
		}
		state = ft_quote_state(str[i], state);
		if ((state == DQI || state == SQI) && str[i] == 32)
			str[i] = 20;
		if (str[i] < 0)
		{
			str[i] = 0;
			if (str[i + 1] < 0)
				str[i + 1] = 32;
		}
		ft_rseparator(state, str, i);
		if (str[i] == '$' && (state == NQ || state == SQI))
			ft_expander_val(str, i);
		if (state == DQO || state == SQO || state == DQC || state == SQC)
			str[i] = 19;
		i++;
	}
	if (state == DQC || state == SQC || state == NQ)
		return (1);
	else
		return (0);
}