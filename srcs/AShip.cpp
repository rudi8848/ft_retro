/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AShip.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:33:36 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/07 22:33:38 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AShip.hpp"

t_bullet AShip::_bullet[50];

AShip::AShip(int lives, int x, int y, int sizeX, int sizeY):
_lives(lives), _x(x), _y(y), _sizeX(sizeX), _sizeY(sizeY) {
	this->createBullets();
	return;
}

AShip::AShip(AShip const &ship) {
	
	*this = ship;
	return;
}

AShip & AShip::operator= (AShip const &ship) {
	
	this->_lives = ship.getLives();
	this->_x = ship.getX();
	this->_y = ship.getY();
	this->_sizeX = ship.getSizeX();
	this->_sizeY = ship.getSizeY();

	return *this;
}

AShip::~AShip(void) {}

int			AShip::getLives(void) const {
	return this->_lives;
}

int 		AShip::getX(void) const {
	return this->_x;
}

int			AShip::getY(void) const {
	return this->_y;
}

int 		AShip::getSizeX(void) const {
	return this->_sizeX;
}

int 		AShip::getSizeY(void) const {
	return this->_sizeY;
}

void		AShip::setPosition(int x, int y) {
	this->_x = x;
	this->_y = y;
}

void			AShip::setScore(int score) {
	this->_score = score;
}

int				AShip::getScore(void) const {
	return this->_score;
}


void		AShip::setLives(int lives) {
	this->_lives = lives;
}

bool			AShip::isWall(int x, int y) const {
	if (x < START_X - 1 || x > INFO_X - 8)
		return true;
	if (y < START_Y -1 || y > HEIGHT -5)
		return true;
	return false;
}

void			AShip::addBullet(void) {
	int i = -1;
	while (++i < 50)
	{
		if (!this->_bullet[i].x && !this->_bullet[i].y)
		{
			this->_bullet[i].x = this->_x + 3;
			this->_bullet[i].y = this->_y;
			return ;
		}
	}
}

void 			AShip::createBullets(void) {
	int i = -1;
	while (++i < 50)
	{
		this->_bullet[i].x = 0;
		this->_bullet[i].y = 0;
	}
}

std::ostream & operator<<(std::ostream &s, AShip const & ship) {

	s << "Lives: " << ship.getLives() << std::endl;
	s << "Position: " << ship.getX() << " , " << ship.getY() << std::endl;
	s << "Size : " << ship.getSizeX() << " * " << ship.getSizeY() << std::endl;
	return s;
}
