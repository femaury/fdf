/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:52:10 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 18:18:31 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	modify_color(int keycode, t_mlx *env)
{
	if (keycode == K1_KEY)
		env->color = 0x990000;
	else if (keycode == K2_KEY)
		env->color = 0x663300;
	else if (keycode == K3_KEY)
		env->color = 0x666600;
	else if (keycode == K4_KEY)
		env->color = 0x006600;
	else if (keycode == K5_KEY)
		env->color = 0x006666;
	else if (keycode == K6_KEY)
		env->color = 0x003366;
	else if (keycode == K7_KEY)
		env->color = 0x330066;
	else if (keycode == K8_KEY)
		env->color = 0x660066;
	else if (keycode == K9_KEY)
		env->color = 0x660033;
	else if (keycode == K0_KEY)
		env->color = 0xFFFFFF;
}

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
	modify_color(keycode, env);
	draw_grid(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	put_header_to_window(env);
	return (0);
}
