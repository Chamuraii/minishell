#include "../includes/minishell.h"

extern t_all g_all;

char	*ft_get_var(char *key)
{
	t_varlist	*head;
	int 		key_len;

	key_len = 0;
	while (ft_isalnum(key[key_len]))
		key_len++;
	head = g_all.varlist[0];
	if (!head)
		return (strdup(""));
	while (head)
	{
		if (!strncmp(key, head->key, key_len))
			if (!head->key[key_len])
				return (ft_strdup(head->value));
		head = head->next;
	}
	return (strdup(""));
}