char	*ft_strstr(char *s1, char *s2)
{
	size_t	s2_len;
	int i;

	if (!(*s2) || s1 == s2)
		return ((char *)s1);
	s2_len = ft_strlen(s2);
	i = 0;
	while (s1[i])
	{
		if (!(ft_strncmp((char *)s1, (char *)s2, s2_len)))
			return ((char *)(s1 + i));
		i++;
	}
	return (0);
}