/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/23 17:13:59 by femaury          ###   ########.fr       */
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

void		put_line_to_image(t_mlx *env, int x0, int y0, int x1, int y1)
{
	float	dx;
	float	dy;
	float	deltaerr;
	float	error;

	dx = x1 - x0;
	dy = y1 - y0;
	deltaerr = dy / dx < 0 ? -(dy / dx) : dy / dx;
	error = 0.0;
	while (x0 != x1)
	{
		env->img.data[y0 * WIN_W + x0] = 0xFFFFFF;
		error += deltaerr;
		while (error > 0.5)
		{
			y0 += dy < 0.0 ? -1 : 1;
			error -= 1.0;
		}
		x0 += dx < 0.0 ? -1 : 1;
	}
}

int			main()
{
	t_mlx	env;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, "FDF femaury");
	env.img.ptr = mlx_new_image(env.mlx, IMG_W, IMG_H);
	env.img.data = (unsigned int *)mlx_get_data_addr(env.img.ptr, &env.img.bpp, &env.img.ln_size, &env.img.endian);
	put_line_to_image(&env, 100, 80, WIN_W - 80, WIN_H - 100);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	mlx_string_put(env.mlx, env.win, 20, 20, 0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
