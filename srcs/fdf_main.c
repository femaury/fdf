/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:56:14 by femaury           #+#    #+#             */
/*   Updated: 2018/06/21 15:24:58 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int keycode, void *param)
{
	t_mlx_ptr	*ptr;

	ptr = (t_mlx_ptr *)param;
	if (ptr)
	{
		if (keycode == ESC_KEY)
			exit(1);
	}
	return (0);
}

int		main()
{
	t_mlx_ptr	ptr;

	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 1920, 1080, "FDF femaury");
	mlx_key_hook(ptr.win, key_hook, &ptr);
	mlx_loop(ptr.mlx);
	return (0);
}
