/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:56:17 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 12:57:20 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		find_size(char *file)
{
	int		fd;
	int		size;
	char	*line;

	size = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	while (ft_gnl(fd, &line) > 0 && ++size)
		ft_strdel(&line);
	close(fd);
	return (size);
}

static int		create_tab(t_mlx *env, int fd, int size, char *line)
{
	int		i;
	int		j;
	char	**coords;

	i = 0;
	while (ft_gnl(fd, &line) > 0)
	{
		coords = ft_strsplit(line, ' ');
		size = ft_strtabsize(coords);
		if (!size || !(env->file[i] = (int *)malloc(sizeof(int) * size)))
			return (1);
		j = 0;
		env->file_ln = env->file_ln ? env->file_ln : size;
		while (j < size)
		{
			env->file[i][j] = ft_atoi(coords[j]);
			j++;
		}
		ft_tabdel((void **)coords, size);
		ft_strdel(&line);
		i++;
	}
	return (0);
}

int				parse_file(t_mlx *env, char *file)
{
	int		fd;
	int		size;
	char	*line;

	size = 0;
	line = NULL;
	if (!(env->file_sz = find_size(file)))
		return (1);
	if (!(env->file = (int **)malloc(sizeof(int *) * env->file_sz)))
		return (1);
	fd = open(file, O_RDONLY);
	if (create_tab(env, fd, size, line))
		return (1);
	close(fd);
	return (0);
}
