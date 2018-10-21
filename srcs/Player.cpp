/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:28:36 by gvynogra          #+#    #+#             */
/*   Updated: 2018/10/07 21:28:38 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(std::string name) : AShip(PLAYER_LIVES, 
	PLAYER_STARTX, PLAYER_STARTY, PLAYER_SIZEX, PLAYER_SIZEY) {
	this->_name = name;
	this->_score = 0;
}

Player::Player(Player const &player) : AShip(player) {}

Player & Player::operator= (Player const &player) {
	this->_name = player._name;
	this->_score = player.getScore();
	return *this;
}

Player::~Player(void) {
	std::cout << "destructor for player" << std::endl;
}


void 			Player::move(int direction) {
	int newX = this->getX();
	int newY = this->getY();

	if (direction == LEFT)
		newX -= 2;
	else if (direction == RIGHT)
		newX += 2;
	else if (direction == UP)
		newY -= 1;
	else
		newY += 1;
	if (!isWall(newX, newY))
		this->setPosition(newX, newY);
}

std::ostream & operator<<(std::ostream &s, Player const & ship) {
	s << "Name: " << ship._name << std::endl;
	s << "Lives: " << ship.getLives() << std::endl;
	s << "Score: " << ship.getScore() << std::endl;
	return s;
}
