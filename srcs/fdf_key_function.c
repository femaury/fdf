/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:52:10 by femaury           #+#    #+#             */
/*   Updated: 2018/06/29 15:08:00 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			hook_keydown(int keycode, t_mlx *env)
{
	env->keydown = keycode;
	return (0);
}

int			hook_keyup(int keycode, t_mlx *env)
{
	if (keycode == RTN_KEY || keycode == NKNTR_KEY)
		env->inverted = env->inverted ? 0 : 1;
	else if (keycode == HOME_KEY)
		env->rgb = 1;
	else if (keycode == END_KEY)
		env->rgb = 0;
	env->keydown = 0;
	return (0);
}
