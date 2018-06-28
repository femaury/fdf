/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:02:31 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 16:45:59 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_line_vertical(t_mlx *env, t_point p1, t_point p2)
{
	float	dx;
	float	dy;
	float	deltaerr;
	float	error;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	deltaerr = dx / dy < 0 ? -(dx / dy) : dx / dy;
	error = 0.0;
	while (p1.y != p2.y)
	{
		if (p1.x >= 0 && p1.x < WIN_W && p1.y >= 0 && p1.y < WIN_H)
			env->img.data[p1.y * WIN_W + p1.x] = env->color;
		error += deltaerr;
		while (error > 0.5)
		{
			p1.x += dx < 0.0 ? -1 : 1;
			error -= 1.0;
		}
		p1.y += dy < 0.0 ? -1 : 1;
	}
}

void		put_line_to_image(t_mlx *env, t_point p1, t_point p2)
{
	float	dx;
	float	dy;
	float	deltaerr;
	float	error;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	deltaerr = dy / dx < 0 ? -(dy / dx) : dy / dx;
	error = 0.0;
	if (ft_abs((int)dy) < ft_abs((int)dx))
		while (p1.x != p2.x)
		{
			if (p1.x >= 0 && p1.x < WIN_W && p1.y >= 0 && p1.y < WIN_H)
				env->img.data[p1.y * WIN_W + p1.x] = env->color;
			error += deltaerr;
			while (error > 0.5)
			{
				p1.y += dy < 0.0 ? -1 : 1;
				error -= 1.0;
			}
			p1.x += dx < 0.0 ? -1 : 1;
		}
	else
		put_line_vertical(env, p1, p2);
}
