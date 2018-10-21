/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:19:23 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/06 18:19:24 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_retro.hpp"
#include "AShip.hpp"
#include "Controller.hpp"
#include "View.hpp"

 void		winch_handler(int signum)
{
	endwin();
	std::cout << "\e[91mERROR:\e[93m *** DON'T CHANGE WINDOW SIZE !!!***\e[0m\n";
	exit(1);
}

int		main(void)
{
	signal(SIGWINCH, winch_handler);
	srand(time(NULL));

	View 		view;
	AShip 		*player = new Player("Ship");

	Controller controller(view, *player);

	int key;
	nodelay(stdscr, true);
	while ((key = getch()))
	{
		usleep(view.getSpeed());
		if (key != -1)
		{
			if (key != 3 && key != 27)
				controller.switchKeys(key);
			else
				break;
		}
		if (view.game == 1)
		{
			if (!(view.timer % 250))
				controller.addEnemy();
			if (!(view.timer % 50))
			{
				int num = -1;
				while (++num < 10)
				{
					if (controller.enemies[num].enem->getLives())
						controller.enemies[num].enem->move(rand() % 2 + 1);
				}
			}
			view.timer++;
			if (view.timer == 1000)
				view.timer = 0;
			controller.checkScore();
			view.updateWin(*player, &controller.enemies[0]);
			view.drawInfo(*player);
		}
	}

	return (0);
}
