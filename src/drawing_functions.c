/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 01:41:37 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/06 04:25:59 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				draw_pixel(t_img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x <= WIN_X && y <= WIN_Y)
		img->data[(x + y * WIN_X)] = color;
	else
		printf("Cafe colombiano\n");
}

void				draw_vert(t_img *img, int x, int y_start, int y_end)
{
	while (++y_start < y_end)
		draw_pixel(img, x, y_start, img->color);
}
/*
void				draw_pass(t_wolf *w)
{
	int			i;
	static int	lol = 0;

	lol += 1;
	i = -1;
	clear_img(w->img);
	while (++i < WIN_X)
	{
		draw_vert(w->img, i, lol, 600);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img->img, 0, 0);
}*/
