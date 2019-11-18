#include "get_next_line.h"

char		*ft_create_str(int fd, int j)
{
    int		ret;
    int		i;
    int		size;
    char	buff[BUFFER_SIZE + 1];
    char	*str;

    i = 0;
    size = 0;
    while ((ret = read(fd, buff, BUFFER_SIZE)))
    {
        size = size + BUFFER_SIZE;
        if (!(str = malloc(sizeof(char) * (size + 1))))
            return (NULL);
        while (buff[j])
        {
            str[i] = buff[j];
            ret++;
            i++;
			j++;
        }
        str[i] = '\0';
    }
    printf("%s\n", str);
    return (str);
}

int				get_next_line(int fd, char **line)
{
	static int		line_nbr;
    char			*text;

    line_nbr = 0;
    if (fd == -1)
        return (-1);
    text = ft_create_str(fd, 0);
    printf("%s\n", text);
    line_nbr++;
    return (0);
}

int            main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*line;
	int		count = 0;
    
	line = NULL;
    fd = open(av[1], O_RDONLY);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
		dprintf(1, "%d\n", 5);
    	puts(line);
    	free(line);
    	count++;
    	printf("\nVALEUR DE RETOUR : %d\n", ret);
    }
	printf("VALEUR DE RETOUR : %d\n", ret);
	printf("LIGNE LUE(S) : %d\n", count);
	close(fd);
    // char    *line[0];
    // int        fd = open("text.txt", O_RDONLY);
    // get_next_line(fd, line);
    // printf("%s", line[0]);
    // free(line);
}










/************************************************************************************************************/

#include "get_next_line.h"

static size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void		ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int				get_next_line(int fd, char **line)
{
	int		test;
	int		BUFFER_SIZE;
	char	*str;

	BUFFER_SIZE = 32;
	if (!(str = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (0);
	test = read(fd, str, BUFFER_SIZE);
	str[test] = '\0';
	ft_putstr(str);
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	ac = 1;
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &line);
}