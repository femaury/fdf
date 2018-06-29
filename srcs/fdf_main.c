/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/29 15:05:56 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_env(t_mlx *env)
{
	env->inverted = 0;
	env->keydown = 0;
	env->rgb = 0;
	env->rgb_count = 1;
	env->zoom = 10;
	env->height = 0.2;
	env->pad_x = WIN_W / 3;
	env->pad_y = WIN_H / 4;
	env->file_ln = 0;
	env->file_sz = 0;
	env->file = NULL;
	env->color = 0xFFFFFF;
}

static int	click_close(t_mlx *env)
{
	(void)env;
	exit(1);
}

int			main(int ac, char **av)
{
	t_mlx	env;

	init_env(&env);
	if (ac != 2 || parse_file(&env, av[1]))
	{
		ft_printf("{RED}Invalid file.{EOC}\nUsage: ./fdf map_file.fdf\n");
		return (1);
	}
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_W, WIN_H, env.win_name);
	env.img.ptr = mlx_new_image(env.mlx, IMG_W, IMG_H);
	env.img.data = (unsigned int *)mlx_get_data_addr(env.img.ptr,
			&env.img.bpp, &env.img.ln_size, &env.img.endian);
	draw_grid(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.ptr, 0, 0);
	env.header = mlx_new_image(env.mlx, 100, 100);
	put_header_to_window(&env);
//	mlx_key_hook(env.win, key_hook, &env);
	mlx_hook(env.win, 2, 0, hook_keydown, &env);
	mlx_hook(env.win, 3, 0, hook_keyup, &env);
	mlx_hook(env.win, 17, 0, click_close, &env);
	mlx_loop_hook(env.mlx, img_refresh, &env);
	mlx_loop(env.mlx);
	return (0);
}
