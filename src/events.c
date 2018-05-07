/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:06:57 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/07 08:06:12 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				movement(t_wolf *w, float move_speed)
{
	if (g_temp_map[(int)(w->pov.pos.x + w->pov.dir.x * move_speed)]
			[(int)(w->pov.pos.y)] == 0)
		w->pov.pos.x += w->pov.dir.x * move_speed;
	if (g_temp_map[(int)(w->pov.pos.x)]
			[(int)(w->pov.pos.y + w->pov.dir.y * move_speed)] == 0)
		w->pov.pos.y += w->pov.dir.y * move_speed;
}

int					key_up(int key_id, t_wolf *w)
{
	if (key_id == LEFT_KEY)
		w->pov.left = 0;
	if (key_id == RIGHT_KEY)
		w->pov.right = 0;
	if (key_id == DOWN_KEY)
		w->pov.down = 0;
	if (key_id == UP_KEY)
		w->pov.up = 0;
	return (0);
}

int					key_down(int key_id, t_wolf *w)
{
	if (key_id == ESC_KEY)
		sheep(0);
	if (key_id == LEFT_KEY)
		w->pov.left = 1;
	if (key_id == RIGHT_KEY)
		w->pov.right = 1;
	if (key_id == DOWN_KEY)
		w->pov.down = 1;
	if (key_id == UP_KEY)
		w->pov.up = 1;
	if (key_id == A_KEY)
		w->img->rave = !w->img->rave;
	return (0);
}

static void			st_rotate_vector(t_vector *v, float angle)
{
	float x;
	float c;
	float s;

	x = v->x;
	c = cos(angle);
	s = sin(angle);
	v->x = v->x * c - v->y * s;
	v->y = x * s + v->y * c;
}

void				rotate_pov(t_pov *p, float angle)
{
	st_rotate_vector(&p->dir, angle);
	st_rotate_vector(&p->pln, angle);
}
