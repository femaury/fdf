/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:52:10 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 12:49:38 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	modify_env(int keycode, t_mlx *env)
{
	if (keycode == PUP_KEY)
		env->height += 0.1;
	else if (keycode == PDOWN_KEY)
		env->height -= 0.1;
	else if (keycode == PL_KEY)
		env->zoom += 5;
	else if (keycode == MN_KEY)
		env->zoom -= env->zoom ? 5 : 0;
	else if (keycode == UP_KEY)
		env->pad_y += 20;
	else if (keycode == DOWN_KEY)
		env->pad_y -= 20;
	else if (keycode == RIGHT_KEY)
		env->pad_x -= 20;
	else if (keycode == LEFT_KEY)
		env->pad_x += 20;
}

int			key_hook(int keycode, t_mlx *env)
{
	if (keycode == ESC_KEY)
		exit(1);
	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img.ptr);
	env->img.ptr = mlx_new_image(env->mlx, IMG_W, IMG_H);
	env->img.data = (unsigned int *)mlx_get_data_addr(env->img.ptr,
			&env->img.bpp, &env->img.ln_size, &env->img.endian);
	modify_env(keycode, env);
	draw_grid(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	mlx_string_put(env->mlx, env->win, 20, 20,
			0xFFFFFF, "Press <ESC> to quit FDF");
	return (0);
}
