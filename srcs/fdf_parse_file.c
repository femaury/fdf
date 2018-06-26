/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:56:17 by femaury           #+#    #+#             */
/*   Updated: 2018/06/26 13:50:44 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	find_size(char *file)
{
	int		fd;
	char	*line;
	size_t	size;

	size = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	while (ft_gnl(fd, &line) > 0 && ++size)
		ft_strdel(&line);
	close(fd);
	return (size);
}

int				parse_file(t_mlx *env, char *file)
{
	int		i[2];
	int		fd;
	int		size;
	char	*line;
	char	**coords;

	i[0] = 0;
	line = NULL;
	if (!(env->file_sz = find_size(file)))
		return (1);
	if (!(env->file = (int **)malloc(sizeof(int *) * env->file_sz)))
		return (1);
	fd = open(file, O_RDONLY);
	while (ft_gnl(fd, &line) > 0)
	{
		coords = ft_strsplit(line, ' ');
		size = ft_strtabsize(coords);
		if (!size || !(env->file[i[0]] = (int *)malloc(sizeof(int) * size)))
			return (1);
		i[1] = 0;
		env->file_ln = env->file_ln ? env->file_ln : size;
		while (i[1] < size)
		{
			env->file[i[0]][i[1]] = ft_atoi(coords[i[1]]);
			i[1]++;
		}
		ft_tabdel((void **)coords, size);
		ft_strdel(&line);
		i[0]++;
	}
	close(fd);
	return (0);
}
