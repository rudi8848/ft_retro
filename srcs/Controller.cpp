/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controller.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:58:50 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/07 11:58:51 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Controller.hpp"

int		Controller::lives_enem = 10;

Controller::Controller(View & view, AShip &player): view(view), player(player) {
	this->generateEnemies();
}

Controller::Controller(Controller const & prev): view(prev.getView()), player(prev.getPlayer()) {
	*this = prev;
}

Controller::~Controller(void) {}

Controller 	&Controller::operator=(Controller const & prev) {
	if (&(*this) != &prev)
		*this = prev;
	return (*this);
}

void		Controller::switchKeys(int key) {
	if (this->view.game)
		this->switchGame(key);
	else
		this->switchMenu(key);
}

// =======================| CHECK SCORE |========================= //

void	Controller::freeAll(void) {
	int i = -1;
	while (++i < NUM_ENEM)
		delete enemies[i].enem;
}

void	Controller::checkScore(void) {
	this->checkBulletsPlayers();
	this->checkPlayersTouch();
	if (player.getLives() == 0)
	{
		nodelay(stdscr, false);
		this->view.drawFinal(player.getScore());
		this->freeAll();
		while (getch() != 27);
		this->view.View::~View();
		exit(0);
	}
}

void	Controller::checkBulletsPlayers(void) {
	int i = -1;
	int n;
	while (++i < 50)
	{
		n = -1;
		while (++n < NUM_ENEM)
		{
			if (this->LIVES_ENEM)
			{
				if (this->ENEM_Y == player._bullet[i].y &&
					(this->ENEM_X == player._bullet[i].x || this->ENEM_X + 1 == player._bullet[i].x
					|| this->ENEM_X + 2 == player._bullet[i].x || this->ENEM_X + 3 == player._bullet[i].x))
				{
					player.setScore(player.getScore() + 5);
					player._bullet[i].x = 0;
					player._bullet[i].y = 0;
					this->enemies[n].enem->setLives(this->enemies[n].enem->getLives() - 1);
				}
			}
		}
	}
}

void	Controller::checkPlayersTouch(void) {
	int n = -1;
	while (++n < NUM_ENEM)
	{
		if (this->LIVES_ENEM)
		{
			if ((this->ENEM_Y >= player.getY() && this->ENEM_Y < player.getY() + PLAYER_SIZEY &&
				this->ENEM_X >= player.getX()  && this->ENEM_X <= player.getX() + 6) ||
				(this->ENEM_Y + 1 >= player.getY() && this->ENEM_Y + 1 < player.getY() + PLAYER_SIZEY &&
				this->ENEM_X + 3 >= player.getX()  && this->ENEM_X + 3 <= player.getX() + 6))
			{
				player.setLives(0);
				return ;
			}
		}
	}
}

// ====================| WORK WITH ENEMIES |====================== //

void		Controller::addEnemy(void) {
	int n = -1;
	while (++n < NUM_ENEM)
	{
		if (!this->LIVES_ENEM)
		{
			this->enemies[n].enem->setLives(this->lives_enem);
			int x = rand() % (INFO_X - 8) + 2;
			this->enemies[n].enem->setPosition(x, START_Y - 1);
			return ;
		}
	}
}

void		Controller::generateEnemies(void) {
	int i = -1;
	while (++i < NUM_ENEM)
		this->enemies[i].enem = new Enemy(0, 0, ENEMY_SIZEX, ENEMY_SIZEY);
}

// =======================| GAME KEYS |=========================== //

void		Controller::checkSpeed(void) {
	if (this->view.game_lvl == "EASY")
	{
		this->view.setSpeed(10000);
		this->lives_enem = 10;
	}
	else if (this->view.game_lvl == "MEDIUM")
	{
		this->view.setSpeed(5000);
		this->lives_enem = 7;
	}
	else
	{
		view.setSpeed(2500);
		this->lives_enem = 4;
	}
}

void		Controller::switchGame(int key) {
	if (key == KEY_SPACE)
	{
		this->player.addBullet();
		return ;	
	}
	if (key == KEY_ENTR)
	{
		this->view.game = 0;
		this->view.clearWin(3, WIDTH - 6);
		this->view.drawMenu();
		this->view.reFreshWin();
		return ;
	}
	switch(key)
	{
		case KEY_UP:
		{
			this->player.move(UP);
			break ;
		}
		case KEY_LEFT:
		{
			this->player.move(LEFT);
			break ;
		}
		case KEY_RIGHT:
		{
			this->player.move(RIGHT);
			break ;
		}
		case KEY_DOWN:
		{
			this->player.move(DOWN);
			break ;
		}
		default:
			break ;
	}
}

// =======================| MENU KEYS |=========================== //

void		Controller::switchMenu(int key) {
	switch(key)
	{
		case KEY_UP:
		{
			if (this->view.menu == 0)
				this->view.menu = 2;
			else
				this->view.menu--;
			this->view.drawMenuAddition();
			break ;
		}
		case KEY_DOWN:
		{
			if (this->view.menu == 2)
				this->view.menu = 0;
			else
				this->view.menu++;
			this->view.drawMenuAddition();
			break ;
		}
		case KEY_ENTR:
		{
			if (this->view.menu == 0)
			{
				this->view.game = 1;
				this->view.clearWin(3, WIDTH - 6);
				this->checkSpeed();
				this->view.drawGame(this->player, &enemies[0]);
			}
			else if (this->view.menu == 2)
				this->view.View::~View();
			break;
		}
		case KEY_LEFT:
		{
			if (this->view.menu != 1)
				break ;
			std::string lvl[3] = {"EASY", "MEDIUM", "HARD"};			
			int i = -1;
			while (++i < 3)
			{
				if (this->view.game_lvl == lvl[i] && i == 0)
					this->view.game_lvl = lvl[2];
				else if (this->view.game_lvl == lvl[i])
					this->view.game_lvl = lvl[--i];
			}
			this->view.clearLine(HEIGHT/2 + 3, WIDTH/2 - 6, 20);
			this->view.drawMenuAddition();
			break ;
		}
		case KEY_RIGHT:
		{
			if (this->view.menu != 1)
				break ;
			std::string lvl[3] = {"EASY", "MEDIUM", "HARD"};			
			int i = -1;
			while (++i < 3)
			{
				if (this->view.game_lvl == lvl[i] && i == 2)
					this->view.game_lvl = lvl[0];
				else if (this->view.game_lvl == lvl[i])
					this->view.game_lvl = lvl[++i];
			}
			this->view.clearLine(HEIGHT/2 + 3, WIDTH/2 - 6, 20);
			this->view.drawMenuAddition();
			break ;
		}
		default:
			break ;
	}
	this->view.reFreshWin();
}

// ======================| GETTER FUNCTION |===================== //

View 		&Controller::getView(void) const {
	return (this->view);
}

AShip 		&Controller::getPlayer(void) const {
	return (this->player);
}
