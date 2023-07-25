#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_builtin_cd(char *str, char **array, int i)
{
	str = array[i];
	if (!str || ft_is_p_or_r_between_quotes(str) || ft_is_p_or_r(str))
	{
		printf("%s", ft_get_var_exp(ft_strdup("PWD")));
		printf("\n");
		return (1);
	}
	if (ft_strcmp(ft_get_var(ft_strdup("PWD")), ft_get_var(ft_strdup("OLDPWD"))))
	{
		ft_add_var(ft_strdup("OLDPWD"), ft_strdup(ft_get_var(ft_strdup("PWD"))));
		ft_add_var_exp(ft_strdup("OLDPWD"), ft_strdup(ft_get_var(ft_strdup("PWD"))));
	}
	if (chdir(str) < 0)
	{
		printf("cd: %s: %s\n", strerror(errno), str);
		return (1);
	}
	ft_add_var(ft_strdup("PWD"), ft_strdup(getcwd(NULL, sizeof(char *))));
	ft_add_var_exp(ft_strdup("PWD"), ft_strdup(getcwd(NULL, sizeof(char *))));
	return (1);
}
