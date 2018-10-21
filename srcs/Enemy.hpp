/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:28:19 by gvynogra          #+#    #+#             */
/*   Updated: 2018/10/07 21:28:22 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "AShip.hpp"

typedef struct 	s_enemy {
	AShip 	*enem;
}				t_enemy;

class Enemy : public AShip
{
public:
	Enemy(int x, int y, int sizeX, int sizeY);
	Enemy(Enemy const &enemy);
	using AShip::operator= ;
	~Enemy(void);

	void move(int direction);
	
};

#endif
