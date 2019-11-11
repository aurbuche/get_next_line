/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aurbuche <aurbuche@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 11:10:12 by aurbuche     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 16:23:39 by aurbuche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int        main(int ac, char **av)
{
	int        fd;
	int        ret;
	char    *line;
	int        i;

	ac = 1;
	i = 1;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		dprintf(1, "%d\t", ret);
		dprintf(1, "|%s|\n", line);
		i++;
		free(line);
	}
	dprintf(1, "%d\t", ret);
	dprintf(1, "|%s|\n", line);
	free(line);
	close(fd);
}
