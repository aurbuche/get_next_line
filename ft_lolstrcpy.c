
char		*ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (dest[i] != '\0')
		i++;
	while (src[++j] != '\0')
		dest[++i] = src[j];
	dest[++i] = '\0';
	return (dest);
}

int		main(void)
{
	char s2[10];
	printf("s = |%s|\n", ft_strcat(s2, "Bonjour"));
	return (0);
}
