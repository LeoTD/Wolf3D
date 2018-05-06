/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 19:26:07 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/05 22:57:58 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		clear_img(t_img *img)
{
	ft_memset(img->data, 0, img->width * img->height * img->bpp);
}

void		del_img(t_wolf *w, t_img **img)
{
	if (*img != NULL)
	{
		if ((*img)->img != NULL)
			mlx_destroy_image(w->mlx, (*img)->img);
		ft_memdel((void **)img);
	}
}

t_img		*new_img(t_wolf *w, int width, int height)
{
	t_img		*img;

	WOLF_ERROR((img = ft_memalloc(sizeof(t_img))), 2);
	WOLF_ERROR((img->img = mlx_new_image(w->mlx, WIN_X, WIN_Y)), 1);
	WOLF_ERROR((img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian)), 1);
	printf("bpp = %d\n", img->bpp);
	img->bpp /= 8;
	img->width = width;
	img->height = height;
	clear_img(img);
	ft_putstr("post bzero...\n");
	return (img);
}
