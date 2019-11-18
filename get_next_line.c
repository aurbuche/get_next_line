/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aurbuche <aurbuche@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 16:22:31 by aurbuche     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 17:12:39 by aurbuche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_check_error(int fd, char **str, char **line)
{
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		if (*str)
			free(*str);
		return (-1);
	}
	if (*str == NULL)
	{
		if (!(*str = ft_strdup("")))
		{
			free(*str);
			return (-1);
		}
	}
	return (0);
}

static char		*ft_read(char *str, int fd)
{
	char	*buff;
	char	*tmp;
	int		ret;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(str, buff);
		str = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

int				ft_nb_line(char *str)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			n++;
		i++;
	}
	return (n);
}

int				ft_complete(char **str, char **line)
{
	size_t i;
	char *tmp;

	i = 0;
	while (*str && *str[i])
	{
		while ((*str)[i] && (*str)[i] != '\n')
			i++;
		if ((*str)[i] == '\n')
		{
			*line = ft_substr(*str, 0, i);
			tmp = ft_strdup((*str) + i + 1);
			free(*str);
			*str = tmp;
			return (1);
		}
		else
		{
			*line = ft_substr(*str, 0, i);
			return (0);
		}
	}
	*line = ft_strdup("");
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char		*str = NULL;
	int				i;

	*line = NULL;
	if (ft_check_error(fd, &str, line) == -1)
		return (-1);
	str = ft_read(str, fd);
	if (ft_complete(&str, line) == 0)
	{
		free(str);
		return (0);
	}
	return (1);
}
