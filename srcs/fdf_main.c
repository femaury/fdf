/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/27 18:15:59 by femaury          ###   ########.fr       */
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
	if (ft_abs((int)dy) < ft_abs((int)dx))
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
	else
	{
		deltaerr = dx / dy < 0 ? -(dx / dy) : dx / dy;
		while (y0 != y1)
		{
			env->img.data[y0 * WIN_W + x0] = 0xFFFFFF;
			error += deltaerr;
			while (error > 0.5)
			{
				x0 += dx < 0.0 ? -1 : 1;
				error -= 1.0;
			}
			y0 += dy < 0.0 ? -1 : 1;
		}
	}
}

t_point		get_coords(t_mlx *env, int i, int j)
{
	t_point	p;

	p.x = (j - i) * env->zoom;
	p.y = ((i + j) - env->file[i][j] * env->height) * (env->zoom / 2);
	return (p);
}

void		map_grid(t_mlx *env)
{
	int		i;
	int		j;
	t_point		p1;
	t_point		p2;

	i = 0;
	while (i < env->file_sz)
	{
		j = 0;
		while (j < env->file_ln)
		{
			p1 = get_coords(env, i, j);
			p2 = get_coords(env, i, j + (j == env->file_ln - 1 ? 0 : 1));
			put_line_to_image(env, env->pad_x + p1.x, env->pad_y + p1.y, env->pad_x + p2.x, env->pad_y + p2.y);
			p2 = get_coords(env, i + (i == env->file_sz - 1 ? 0 : 1), j);
			put_line_to_image(env, env->pad_x + p1.x, env->pad_y + p1.y, env->pad_x + p2.x, env->pad_y + p2.y);
			j++;
		}
		i++;
	}
}

void		init_env(t_mlx *env)
{
	env->zoom = 30;
	env->height = 0.2;
	env->pad_x = 400;
	env->pad_y = 200;
	env->file_ln = 0;
	env->file_sz = 0;
	env->file = NULL;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_W, WIN_H, "FDF femaury");
	env->img.ptr = mlx_new_image(env->mlx, IMG_W, IMG_H);
	env->img.data = (unsigned int *)mlx_get_data_addr(env->img.ptr, &env->img.bpp,
			&env->img.ln_size, &env->img.endian);
}

int			main(int ac, char **av)
{
	t_mlx	env;

	init_env(&env);	
	if (ac == 2)
		if (parse_file(&env, av[1]))
			ft_printf("Error parsing!\n");
	ft_printf("file_ln: %d and file_sz: %d\nzoom: %d\npad_x: %d and pad_y: %d\n", env.file_ln, env.file_sz, env.zoom, env.pad_x, env.pad_y);
	map_grid(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	mlx_string_put(env.mlx, env.win, 20, 20, 0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
