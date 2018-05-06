/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 00:38:53 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/05 00:40:00 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			colombia(t_wolf *w)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (++i < WIN_X)
	{
		while (++k < WIN_Y / 2)
		{
			mlx_pixel_put(w->mlx, w->win, i, k, YELLOW);
		}
		while (++k < WIN_Y - (WIN_Y / 4))
		{
			mlx_pixel_put(w->mlx, w->win, i, k, BLUE);
		}
		while (++k < WIN_Y)
		{
			mlx_pixel_put(w->mlx, w->win, i, k, RED);
		}
		k = -1;
	}
}
