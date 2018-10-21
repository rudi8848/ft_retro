/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retro.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:35:36 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/07 22:35:38 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RETRO_HPP
# define FT_RETRO_HPP

# include <iostream>
# include <unistd.h>
# include <ctime>

# define PLAYER_LIVES 	3
# define PLAYER_STARTX	40
# define PLAYER_STARTY	45
# define PLAYER_SIZEX	7
# define PLAYER_SIZEY	4

# define NUM_ENEM		10
# define ENEMY_SIZEX	3
# define ENEMY_SIZEY	3

# define LEFT	0
# define RIGHT	1
# define UP		2
# define DOWN	3

# define LIVES_ENEM enemies[n].enem->getLives()
# define ENEM_X enemies[n].enem->getX()
# define ENEM_Y enemies[n].enem->getY()

// NCURSES //

# define START_X 3
# define START_Y 2

# define INFO_X 80

# define HEIGHT 50
# define WIDTH 130

# define KEY_ENTR	10
# define KEY_Q		113
# define KEY_W		119
# define KEY_E		101
# define KEY_R		114
# define KEY_S		115
# define KEY_SPACE	32
# define RESIZE		410

#endif
