/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/26 16:30:58 by femaury          ###   ########.fr       */
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
	if (x0 != x1)
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

int			*get_coords(t_mlx *env, int i, int j)
{
	int		*coords;
	int		x;
	int		y;

	if (!(coords = (int *)malloc(sizeof(int) * 2)))
		return (NULL);
	y = i * ((WIN_H - 200) / env->file_sz);
	x = j * ((WIN_W - 200) / env->file_ln);
	coords[0] = (int)((float)x + 1 * (float)(env->file[i][j]));
	coords[1] = (int)((float)y + 1 * (float)(env->file[i][j]));
	return (coords);
}

void		map_grid(t_mlx *env)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	while (i < env->file_sz)
	{
		j = 0;
		while (j < env->file_ln)
		{
			x = get_coords(env, i, j)[0];
			y = get_coords(env, i, j)[1];
			put_line_to_image(env, 100 + x, 100 + y, 100 + get_coords(env, i, j + (j == env->file_ln - 1 ? 0: 1))[0], 100 + y);
			put_line_to_image(env, 100 + x, 100 + y, 100 + x, 100 + get_coords(env, i + (i == env->file_sz - 1 ? 0 : 1), j)[1]);
			j++;
		}
		i++;
	}
}

void		print_tab(t_mlx *env)
{
	int		i;
	int		j;
	
	i = 0;
	while (i < env->file_sz)
	{
		j = 0;
		ft_printf("Row %d:", i);
		while (j < env->file_ln)
		{
			ft_printf(" %02d", env->file[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int			main(int ac, char **av)
{
	t_mlx	env;
	
	env.file_ln = 0;
	if (ac == 2)
		parse_file(&env, av[1]);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, "FDF femaury");
	env.img.ptr = mlx_new_image(env.mlx, IMG_W, IMG_H);
	env.img.data = (unsigned int *)mlx_get_data_addr(env.img.ptr, &env.img.bpp, &env.img.ln_size, &env.img.endian);
//	print_tab(&env);
	map_grid(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	mlx_string_put(env.mlx, env.win, 20, 20, 0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
