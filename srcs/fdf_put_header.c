/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:16:51 by femaury           #+#    #+#             */
/*   Updated: 2018/06/29 15:09:07 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_header_to_window(t_mlx *env)
{
	mlx_destroy_image(env->mlx, env->header);
	env->header = mlx_new_image(env->mlx, IMG_W, 130);
	mlx_put_image_to_window(env->mlx, env->win, env->header, 0, 0);
	mlx_string_put(env->mlx, env->win, 20, 15,
			0xFFFFFF, "CONTROLS");
	mlx_string_put(env->mlx, env->win, 70, 50, 0xFFA500, "MOVE"
			"               ZOOM"
			"               HEIGHT               COLOR               RGB"
			"               INVERT CAM               RESET               QUIT");
	mlx_string_put(env->mlx, env->win, 60, 80, 0xFFFFFF, "arrows");
	mlx_string_put(env->mlx, env->win, 255, 80, 0xFFFFFF, "+ / -");
	mlx_string_put(env->mlx, env->win, 390, 80, 0xFFFFFF, "page up / page down");
	mlx_string_put(env->mlx, env->win, 660, 80, 0xFFFFFF, "0 - 9");
	mlx_string_put(env->mlx, env->win, 820, 80, 0xFFFFFF, "home / end");
	mlx_string_put(env->mlx, env->win, 1060, 80, 0xFFFFFF, "return");
	mlx_string_put(env->mlx, env->win, 1290, 80, 0xFFFFFF, "clear");
	mlx_string_put(env->mlx, env->win, 1495, 80, 0xFFFFFF, "esc");
}
