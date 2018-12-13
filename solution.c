/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:16:25 by frivaton          #+#    #+#             */
/*   Updated: 2018/12/13 10:05:40 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

extern int		g_mat[106][106];
extern int		g_nb_piecee;
extern t_piece	g_tetris[26];
extern int		g_nb_piece;
extern int		g_x_max;
extern int		g_y_max;
int				g_xstart;
int				g_ystart;
int				g_k;

static void			make_iter(void)
{
	g_xstart = g_tetris[g_k].posx;
	g_ystart = g_tetris[g_k].posy;
	clean_matrice_from(g_tetris[g_k].letter);
	if (g_xstart < g_x_max - 1)
		g_xstart++;
	else if (g_ystart < g_y_max - 1)
	{
		g_xstart = 0;
		g_ystart++;
	}
	else
	{
		g_xstart = 0;
		g_ystart = 0;
		next_position(&g_tetris[g_k]);
	}
}

static void			make_move(void)
{
	if (g_k == 0)
	{
		g_xstart = 0;
		g_ystart = 0;
		next_position(&g_tetris[g_k]);
		return ;
	}
	if (g_k)
		g_k--;
	make_iter();
}

static void			make_init(void)
{
	g_tetris[g_k].posx = g_xstart;
	g_tetris[g_k].posy = g_ystart;
	g_xstart = 0;
	g_ystart = 0;
	g_k++;
}

int					i_check_solution(void)
{
	int ret;

	g_k = 0;
	g_xstart = 0;
	g_ystart = 0;
	ret = 1;
	while (1)
	{
		while (g_k < g_nb_piece)
		{
			while ((ret = i_check_tetris(&g_tetris[g_k], &g_xstart, &g_ystart)))
			{
				make_init();
				if (g_k == g_nb_piece && ret)
					break ;
			}
			if (g_k == g_nb_piece && ret)
				return (1);
			if (!ret)
				make_move();
		}
	}
	return (1);
}
