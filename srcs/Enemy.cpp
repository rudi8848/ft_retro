/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:28:06 by gvynogra          #+#    #+#             */
/*   Updated: 2018/10/07 21:28:08 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(int x, int y, int sizeX, int sizeY) : AShip(0, x, y,
 sizeX, sizeY) {
}

Enemy::Enemy(Enemy const &enemy) : AShip(enemy) {}

Enemy::~Enemy(void) {}

void Enemy::move(int direction) {
	
	int x = this->getX();
	int y = this->getY() + 1;
	int offset;

	if (direction % 2)
		 offset = 2;
	else
		offset = - 2;

	if (((x + offset) <= START_X - 1)|| ((x + offset) >= INFO_X - 8))
		offset = -offset;
	if (y > HEIGHT -5)
		this->setLives(0);
	this->setPosition(x + offset, y);
}
