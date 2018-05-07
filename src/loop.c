/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 05:28:39 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/07 05:52:47 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			loop_handler(t_wolf *w)
{
	if (w->pov.left)
		rotate_pov(&w->pov, -TURN_SPEED);
	if (w->pov.right)
		rotate_pov(&w->pov, TURN_SPEED);
	if (w->pov.down)
		movement(w, -MOVE_SPEED);
	if (w->pov.up)
		movement(w, MOVE_SPEED);

	draw_pass(w);
	return (0);
}
