/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   View.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:19:34 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/06 18:19:35 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_HPP
# define VIEW_HPP

# include <iostream>
# include <ncurses.h>
# include "../include/ft_retro.hpp"
# include "Enemy.hpp"
# include "Player.hpp"

typedef struct 	s_stars
{
	int 			x;
	int 			y;
}				t_stars;

class View {

public:

	View(void);
	View(View const & prev);
	~View(void);

	View &operator=(View const & prev);

	void	drawMenu(void);
	void	drawMenuAddition(void) const;
	void	drawGame(AShip const &player, t_enemy *enemies);
	void	drawStars(void);
	void	drawShipPlayer(AShip const &player);
	void	drawShipEnemies(t_enemy *enemies);
	void	drawBulletsPlayer(AShip const &player);
	void	drawInfo(AShip const &player);
	void	drawFinal(int score);

	void	updateWin(AShip const &player, t_enemy *enemies);
	void	reFreshWin(void) const;
	void	clearWin(int x, int width) const;
	void	clearLine(int y, int x, int width) const;

	WINDOW 	*getWindow(void) const;

	int		getSpeed(void) const;
	void	setSpeed(int speed);

	static int			menu;
	static int			game;
	static std::string	game_lvl;

	static int			timer;

private:

	void	genericStars(void);
	void	drawBorder(void);

	WINDOW	*win;
	int		_speed;

	t_stars stars[100];

};

#endif
