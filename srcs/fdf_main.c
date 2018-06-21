/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/21 20:21:50 by femaury          ###   ########.fr       */
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

int		main()
{
	t_mlx	env;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, 1920, 1080, "FDF femaury");
	mlx_string_put(env.mlx, env.win, 20, 20, 0xFFFFFF, "Press <ESC> to quit FDF");
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
