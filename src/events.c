/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:06:57 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/06 20:25:40 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			st_movement(t_wolf *w, float move_speed)
{
	if (g_temp_map[(int)(w->pov.pos.x + w->pov.dir.x * move_speed)]
			[(int)(w->pov.pos.y)] == 0)
		w->pov.pos.x += w->pov.dir.x * move_speed;
	if (g_temp_map[(int)(w->pov.pos.x)]
			[(int)(w->pov.pos.y + w->pov.dir.y * move_speed)] == 0)
		w->pov.pos.y += w->pov.dir.y * move_speed;
}

int					key_handler(int key_id, t_wolf *w)
{
	if (key_id == ESC_KEY)
		sheep(0);
	if (key_id == LEFT_KEY)
		rotate_pov(&w->pov, -TURN_SPEED);
	if (key_id == RIGHT_KEY)
		rotate_pov(&w->pov, TURN_SPEED);
	if (key_id == DOWN_KEY)
		st_movement(w, -MOVE_SPEED);
	if (key_id == UP_KEY)
		st_movement(w, MOVE_SPEED);
	draw_pass(w);
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
