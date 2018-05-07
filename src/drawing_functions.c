/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 01:41:37 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/07 08:12:56 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				draw_pixel(t_img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x <= WIN_X && y <= WIN_Y)
		img->data[(x + y * WIN_X)] = color;
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
		draw_pixel(img, x, i,
				view_fade(FLOOR_COLOR, abs(i - WIN_Y) * 0.030) + lol);
}

int					view_fade(int color, float wall_dist)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = color;
	g = color >> 8;
	b = color >> 16;
	wall_dist = 7 / (100 / wall_dist);
	if (wall_dist > 0.9)
		wall_dist = 0.9;
	if (r > 0)
		r = r - (r * wall_dist);
	if (g > 0)
		g = g - (g * wall_dist);
	if (b > 0)
		b = b - (b * wall_dist);
	return ((r << 16) + (g << 8) + b);
}

int					color_picker(t_ray *ray, t_vars *v)
{
	int				tmp;

	tmp = 0;
	if (v->side == 1)
		if (ray->dir.y < 0)
			tmp = RED;
		else
			tmp = GREEN;
	else
	{
		if (ray->dir.x < 0)
			tmp = BLUE;
		else
			tmp = ORANGE;
	}
	tmp = view_fade(tmp, v->wall_dist);
	return (tmp);
}
