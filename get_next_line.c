/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aurbuche <aurbuche@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 16:22:31 by aurbuche     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 16:34:52 by aurbuche    ###    #+. /#+    ###.fr     */
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
	int		ret;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
	}
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
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (ft_nb_line(*str) >= 1)
	{
		if ((*str)[i])
		{
			if (i == 0)
			{
				*line = ft_strdup("");
				(*str) = (*str) + 1;
			}
			else
			{
				*line = ft_substr(*str, 0, i);
				(*str) = (*str) + i + 1;
			}
			return (1);
		}
		else
			*line = ft_strdup("");
	}
	else
		*line = ft_substr(*str, 0, i);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char		*str = NULL;
	int				i;

	if (ft_check_error(fd, &str, line) == -1)
		return (-1);
	str = ft_read(str, fd);
	return (ft_complete(&str, line));
}
