/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:06:11 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 16:51:38 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	get_coords(t_mlx *env, int i, int j)
{
	t_point	p;

	p.x = ((j - i) * env->zoom) + env->pad_x;
	p.y = (((i + j) - env->file[i][j] * env->height) * (env->zoom / 2))
		+ env->pad_y;
	env->altitude = env->file[i][j];
	return (p);
}

void			draw_grid(t_mlx *env)
{
	int		i;
	int		j;
	t_point	p1;
	t_point	p2;

	i = 0;
	while (i < env->file_sz)
	{
		j = 0;
		while (j < env->file_ln)
		{
			p1 = get_coords(env, i, j);
			p2 = get_coords(env, i, j + (j == env->file_ln - 1 ? 0 : 1));
			put_line_to_image(env, p1, p2);
			p2 = get_coords(env, i + (i == env->file_sz - 1 ? 0 : 1), j);
			put_line_to_image(env, p1, p2);
			j++;
		}
		i++;
	}
}
