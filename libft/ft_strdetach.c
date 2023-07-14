#include "libft.h"

char *ft_strdetach(char *str, char *str2)
{
	char	*str3;
	int 	i;
	int 	max;

	max = 0;
	while (ft_strcmp(str + max, str2))
		max++;
	str3 = (char *)ft_calloc(max, sizeof(char));
	i = 0;
	while (i < max)
	{
		str3[i] = str[i];
		i++;
	}
	free (str);
	if (str2)
		free (str2);
	return (str3);
}