/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 01:41:37 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/07 06:26:53 by ltanenba         ###   ########.fr       */
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
	int				i;
	static int		lol = 0;

	i = -1;
	if (img->rave)
		lol = lol - clock() / CLOCKS_PER_SEC;
	while (++i < y_start)
		draw_pixel(img, x, i, SKY_COLOR + lol);
	while (++i < y_end)
		draw_pixel(img, x, i, img->color + lol);
	while (++i < WIN_Y)
		draw_pixel(img, x, i, view_fade(FLOOR_COLOR, abs(i - WIN_Y) * 0.030) + lol);
}
