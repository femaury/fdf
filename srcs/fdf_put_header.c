/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:16:51 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 16:55:14 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_header_to_window(t_mlx *env)
{
	mlx_destroy_image(env->mlx, env->header);
	env->header = mlx_new_image(env->mlx, IMG_W, 100);
	mlx_put_image_to_window(env->mlx, env->win, env->header, 0, 0);
	mlx_string_put(env->mlx, env->win, 20, 20,
			0xFFA500, "CONTROLS");
	mlx_string_put(env->mlx, env->win, 50, 50,
			0xFFA500, "Move: Arrows     Zoom: + / -"
			"     Height: PageUp/PageDown"
			"     Colors: 1 - 9     Color Reset: 0"
			"     Quit: ESC");
}
