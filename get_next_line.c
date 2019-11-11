/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aurbuche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 16:22:31 by aurbuche     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 16:22:38 by aurbuche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

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

int				ft_check_error(int fd, char *str)
{
	if (str == NULL || fd < 0 || BUFFER_SIZE < 1)
	{
		if (str)
			free(str);
		return (-1);
	}
	return (0);
}

int			ft_complete(char **str, char **line, int i)
{
	i = 0;
	*str = ft_strchr(*str, '\n');
	if (i == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
	{
		*line = ft_substr(*str, 0, i);
		*str = *str + i + 1;
		return (1);
	}
}

int				get_next_line(int fd, char **line)
{
	static char	*str = NULL;
	int			i;

	if (str == NULL)
	{
		if (!(str = ft_strdup("")))
		{
			free(str);
			return (-1);
		}
	}
	if (ft_check_error(fd, str) == -1)
		return (-1);
	str = ft_read(str, fd);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (str[i])
	{
		return (ft_complete(&str, &(*line), i));
	}
	else
		*line = ft_substr(str, 0, i);
	return (0);
}
