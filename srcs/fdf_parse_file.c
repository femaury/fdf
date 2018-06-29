/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 13:56:17 by femaury           #+#    #+#             */
/*   Updated: 2018/06/29 18:59:53 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		find_size(t_mlx *env, char *file)
{
	int		fd;
	int		size;
	char	*line;

	size = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	while (ft_gnl(fd, &line) > 0 && ++size && size < MAX_FILESIZE)
		ft_strdel(&line);
	close(fd);
	if (size == MAX_FILESIZE)
	{
		env->error = 1;
		return (0);
	}
	if (!size)
	{
		env->error = 2;
		return (0);
	}
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
		if (!size || (env->file_ln && size != env->file_ln)
				|| !(env->file[i] = (int *)malloc(sizeof(int) * size)))
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
	env->win_name = ft_strjoin("FDF ", ft_strchrrev(file, '/'));
	if (!(env->file_sz = find_size(env, file)))
		return (1);
	if (!(env->file = (int **)malloc(sizeof(int *) * env->file_sz)))
		return (env->error = 3);
	fd = open(file, O_RDONLY);
	if (create_tab(env, fd, size, line))
		return (env->error = 4);
	close(fd);
	return (0);
}
