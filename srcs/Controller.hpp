/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controller.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:58:47 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/07 11:58:48 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include "View.hpp"
# include "AShip.hpp"
# include "Enemy.hpp"

class Controller {

public:

	Controller(View & view, AShip & player);
	Controller(Controller const & prev);
	~Controller(void);

	Controller &operator=(Controller const & prev);

	void		switchKeys(int key);
	void		switchMenu(int key);
	void		switchGame(int key);

	void		generateEnemies(void);
	void		addEnemy(void);

	void		checkSpeed(void);
	void		checkScore(void);
	void		checkBulletsPlayers(void);
	void		checkPlayersTouch(void);

	void	 	freeAll(void);

	View &getView(void) const;
	AShip &getPlayer(void) const;

	t_enemy 	enemies[NUM_ENEM];
	static int 	lives_enem;

private:

	View	&view;
	AShip	&player;
};

#endif
