/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:32:59 by frivaton          #+#    #+#             */
/*   Updated: 2018/12/13 11:04:07 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define BUFF_SIZE 21 
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft/libft.h"


typedef struct s_tetris
{
	char tab[4][4];
	char letter;
	int  posx;
	int posy;
} t_piece;

//in main
void		determine_square_min(void);
int			parse_buffer(char *sline, int ind);
int			ft_display_file(char *sfile);
void		print_tetris(t_piece *tetris);

//position.c
void		clean_matrice_from(int value);
int			i_check_tetris(t_piece *tetris, int *ref_col, int *ref_lin);

//in solution.c
int         i_check_solution(void);

//in general.c
int			ft_sqrt(int nb);
void        clean_tetris(void);
void        initialize_matrice(void);
void        print_matrice(void);
int			next_position(t_piece *tetris);

#endif
