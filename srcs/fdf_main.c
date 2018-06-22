/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/22 18:14:31 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int keycode, t_mlx *env)
{
	(void)env;
	if (keycode == ESC_KEY)
		exit(1);
	return (0);
}

void		pixel_grid_to_image(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < WIN_H - 99)
	{
		j = 0;
		while (i > 99 && j < WIN_W - 99)
		{
			if (j > 99)
				if (!(i % 20) || !(j % 20))
					env->img.data[i * WIN_W + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void		low_diagonal(t_mlx *env, int x0, int y0, int x1, int y1)
{
	int		dx;
	int		dy;
	int		delta;

	dx = x1 - x0;
	dy = y1 - y0;
	dy = dy < 0 ? -dy : dy;
	delta = 2 * dy - dx;
	while (x0 < WIN_W)
	{
		if (y0 < y1 && x0 < x1)
			env->img.data[y0 * WIN_W + x0] = 0xFFFFFF;
		if (delta > 0)
		{
			y0 += dy < 0 ? -1 : 1;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		x0++;
	}
}

void		high_diagonal(t_mlx *env, int x0, int y0, int x1, int y1)
{
	int		dx;
	int		dy;
	int		delta;

	dx = x1 - x0;
	dy = y1 - y0;
	dx = dx < 0 ? -dx : dx;
	delta = 2 * dx - dy;
	while (y0 < WIN_H)
	{
		if (x0 < x1 && y0 < y1)
			env->img.data[y0 * WIN_W + x0] = 0xFFFFFF;
		if (delta > 0)
		{
			x0 += dx < 0 ? -1 : 1;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		y0++;
	}
}

void	put_diagonal_to_image(t_mlx *env, int x0, int y0, int x1, int y1)
{
	if (ft_abs(y1 - y0) < ft_abs(x1 - x0))
	{
		if (x0 > x1)
			low_diagonal(env, x1, y1, x0, y0);
		else
			low_diagonal(env, x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			high_diagonal(env, x1, y1, x0, y0);
		else
			high_diagonal(env, x0, y0, x1, y1);
	}
}

int			main()
{
	t_mlx	env;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, "FDF femaury");
	env.img.ptr = mlx_new_image(env.mlx, IMG_W, IMG_H);
	env.img.data = (unsigned int *)mlx_get_data_addr(env.img.ptr, &env.img.bpp, &env.img.ln_size, &env.img.endian);
	put_diagonal_to_image(&env, 100, 800, 1400, 100);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	mlx_string_put(env.mlx, env.win, 20, 20, 0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
