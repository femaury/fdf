/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 12:57:37 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	env->img.data = (unsigned int *)mlx_get_data_addr(env->img.ptr,
			&env->img.bpp, &env->img.ln_size, &env->img.endian);
}

int			main(int ac, char **av)
{
	t_mlx	env;

	init_env(&env);
	if (ac != 2 || parse_file(&env, av[1]))
	{
		ft_printf("Invalid file.\n");
		return (1);
	}
	draw_grid(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	mlx_string_put(env.mlx, env.win, 20, 20,
			0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
