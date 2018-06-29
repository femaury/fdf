/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_img_refresh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:42:43 by femaury           #+#    #+#             */
/*   Updated: 2018/06/29 15:57:14 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_env(t_mlx *env)
{
	env->rgb = 0;
	env->rgb_count = 1;
	env->zoom = 10;
	env->height = 0.2;
	env->pad_x = WIN_W / 3;
	env->pad_y = WIN_H / 4;
	env->color = 0xFFFFFF;
}

static void	modify_color(t_mlx *env)
{
	if (env->keydown == K1_KEY || env->keydown == NK1_KEY)
		env->color = 0xFF0000;
	else if (env->keydown == K2_KEY || env->keydown == NK2_KEY)
		env->color = 0xFF8000;
	else if (env->keydown == K3_KEY || env->keydown == NK3_KEY)
		env->color = 0xFFFF00;
	else if (env->keydown == K4_KEY || env->keydown == NK4_KEY)
		env->color = 0x00FF00;
	else if (env->keydown == K5_KEY || env->keydown == NK5_KEY)
		env->color = 0x00FFFF;
	else if (env->keydown == K6_KEY || env->keydown == NK6_KEY)
		env->color = 0x0000FF;
	else if (env->keydown == K7_KEY || env->keydown == NK7_KEY)
		env->color = 0x7F00FF;
	else if (env->keydown == K8_KEY || env->keydown == NK8_KEY)
		env->color = 0xFF00FF;
	else if (env->keydown == K9_KEY || env->keydown == NK9_KEY)
		env->color = 0xFF007F;
	else if (env->keydown == K0_KEY || env->keydown == NK0_KEY)
		env->color = 0xFFFFFF;
}

static void	modify_env(t_mlx *env)
{
	if (env->keydown == PUP_KEY)
		env->height += 0.1;
	else if (env->keydown == PDOWN_KEY)
		env->height -= 0.1;
	else if (env->keydown == PL_KEY || env->keydown == NKPL_KEY)
		env->zoom += 1;
	else if (env->keydown == MN_KEY || env->keydown == NKMN_KEY)
		env->zoom -= env->zoom > 2 ? 1 : 0;
	else if (env->keydown == UP_KEY)
		env->pad_y += env->inverted ? 20 : -20;
	else if (env->keydown == DOWN_KEY)
		env->pad_y -= env->inverted ? 20 : -20;
	else if (env->keydown == RIGHT_KEY)
		env->pad_x -= env->inverted ? 20 : -20;
	else if (env->keydown == LEFT_KEY)
		env->pad_x += env->inverted ? 20 : -20;
	modify_color(env);
}

static void	set_rgb(t_mlx *env)
{
	if (env->rgb_count == 10)
		env->rgb_count = 1;
	else if (env->rgb_count == 1)
		env->color = 0xFF0000;
	else if (env->rgb_count == 2)
		env->color = 0xFF8000;
	else if (env->rgb_count == 3)
		env->color = 0xFFFF00;
	else if (env->rgb_count == 4)
		env->color = 0x00FF00;
	else if (env->rgb_count == 5)
		env->color = 0x00FFFF;
	else if (env->rgb_count == 6)
		env->color = 0x0000FF;
	else if (env->rgb_count == 7)
		env->color = 0x7F00FF;
	else if (env->rgb_count == 8)
		env->color = 0xFF00FF;
	else if (env->rgb_count == 9)
		env->color = 0xFF007F;
	env->rgb_count++;
	usleep(15000);
}

int			img_refresh(t_mlx *env)
{
	if (env->keydown == ESC_KEY)
		exit(EXIT_SUCCESS);
	if (env->keydown == CLR_KEY)
		reset_env(env);
	if (env->rgb)
		set_rgb(env);
	if (env->keydown)
		modify_env(env);
	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img.ptr);
	env->img.ptr = mlx_new_image(env->mlx, IMG_W, IMG_H);
	env->img.data = (unsigned int *)mlx_get_data_addr(env->img.ptr,
			&env->img.bpp, &env->img.ln_size, &env->img.endian);
	draw_grid(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.ptr, 0, 0);
	put_header_to_window(env);
	return (0);
}
