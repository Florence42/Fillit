/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:35:57 by frivaton          #+#    #+#             */
/*   Updated: 2018/12/13 15:46:28 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			g_mat[106][106];
int			g_nb_piece = 0;
t_piece		g_tetris[26];
int			g_x_max;
int			g_y_max;

void		determine_square_min(void)
{
	int	val;
	int	i;
	int	tmp;

	tmp = g_nb_piece * 4;
	val = ft_sqrt(tmp);
	if (!val)
	{
		i = 1;
		while (!val)
		{
			val = ft_sqrt(tmp + i);
			i++;
		}
	}
	g_x_max = val;
	g_y_max = val;
}

int			parse_buffer(char *sline, int ind)
{
	char	**stmp;
	int		i;
	int		j;
	int		k;
	int		pos;

	if ((stmp = ft_strsplit(sline, '\n')) == NULL)
		return (-1);
	g_nb_piece++;
	i = 0;
	pos = 0;
	while (i < 4)
	{
		if (stmp[0][i] == '.' && stmp[1][i] == '.' && stmp[2][i] == '.'
				&& stmp[3][i] == '.')
			pos++;
		else
			break ;
		i++;
	}
	i = 0;
	k = 0;
	while (k < 4)
	{
		j = 0;
		if (ft_strchr(stmp[k], '#'))
		{
			while (j + pos < 4)
			{
				if (stmp[k][pos + j] != '.')
					g_tetris[ind].tab[i][j] = 'A' + ind;
				j++;
			}
			i++;
		}
		k++;
	}
	g_tetris[ind].letter = 'A' + ind;
	//print_tetris(&g_tetris[ind]);
	i = 0;
	while (stmp[i])
	{
		ft_strdel(&stmp[i]);
		i++;
	}
	ft_memdel((void **)&stmp);
	stmp = NULL;
	return (2);
}

int			ft_display_file(char *sfile)
{
	int		fd;
	int		ret;
	char	*stmp = NULL;
	int		ind;

	if ((fd = open(sfile, O_RDONLY)) <= 0)
		return (0);
	if ((stmp = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	ind = 0;
	while ((ret = read(fd, (void *)stmp, BUFF_SIZE)) > 0)
	{
		stmp[ret] = '\0';
		ret = parse_buffer(stmp, ind++);
		if (ret != 2)
		{
			ft_strdel(&stmp);
			close(fd);
			return (ret);
		}
	}
	close(fd);
	ft_strdel(&stmp);
	if (ret < 0)
		return (ret);
	return (ret);
}

void		print_tetris(t_piece *g_tetris)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (g_tetris->tab[i][j])
				ft_putchar(g_tetris->tab[i][j]);
			else
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

int			main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	clean_tetris();
	ft_display_file(argv[1]);
	if (g_nb_piece > 26)
	{
		ft_putstr("error.\n");
		return (0);
	}
	determine_square_min();
	initialize_matrice();
	if (!i_check_solution())
	{
		ft_putstr("error.\n");
		return (0);
	}
	print_matrice();
	return (0);
}
