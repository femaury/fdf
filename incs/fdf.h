/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:49:58 by femaury           #+#    #+#             */
/*   Updated: 2018/06/25 14:43:50 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
**	----------------------------- SYSTEM LIBRARIES -----------------------------
*/

# include <math.h>

/*
**	------------------------------- MY LIBRARIES -------------------------------
*/

# include "../minilibx/mlx.h"
# include "../minilibx/mlx_keycodes.h"
# include "../libft/incs/libft.h"

/*
**	--------------------------------- DEFINES ----------------------------------
*/

# define WIN_W 1600
# define WIN_H 900
# define IMG_W WIN_W
# define IMG_H WIN_H

/*
**	-------------------------------- STRUCTURES --------------------------------
*/

typedef struct	s_img
{
	int				bpp;
	int				ln_size;
	int				endian;
	void			*ptr;
	unsigned int	*data;

}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		**file;
	t_img	img;
}				t_mlx;

/*
**	------------------------------- FDF FUNCTIONS ------------------------------
*/

int				parse_file(t_mlx *env, char *file);

#endif
