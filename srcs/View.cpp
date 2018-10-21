/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   View.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:19:29 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/06 18:19:30 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "View.hpp"

int 		View::timer = 0;
int 		View::menu = 0;
int  		View::game = 0;
std::string	View::game_lvl = "MEDIUM";

inline static void		initNcurses(void) {
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	clear();
	curs_set(0);
	start_color();
	init_color(COLOR_MAGENTA, 300, 300, 300);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLACK);
	init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
}

View::View(void) {
	initNcurses();
	this->_speed = 10000;
	this->win = newwin(HEIGHT, WIDTH, 0, 0);
	this->drawBorder();
	this->drawMenu();
	refresh();
	this->reFreshWin();
}

View::View(View const &prev) {
	*this = prev;
}

View::~View(void) {
	endwin();
	exit(0);
}

void		View::updateWin(AShip const &player, t_enemy *enemies) {
	this->clearWin(2, INFO_X - 3);
	this->drawStars();
	this->drawBulletsPlayer(player);
	this->drawShipPlayer(player);
	this->drawShipEnemies(enemies);
	this->reFreshWin();
}

void		View::reFreshWin(void) const {
	wrefresh(this->win);
}

View 		&View::operator=(View const &prev) {
	this->_speed = prev.getSpeed();
	this->win = prev.getWindow();
	return (*this);
}

// =======================| DRAW INFO |========================= //

void		View::drawFinal(int score) {
	this->clearWin(2, WIDTH - 3);
	wattron(this->win, COLOR_PAIR(3));
	mvwprintw(this->win, HEIGHT/4, WIDTH/4/2, " ______    ______   __       __  ________         ______   __     __  ________  _______  ");
	mvwprintw(this->win, HEIGHT/4 + 1, WIDTH/4/2, " /      \\  /      \\ |  \\     /  \\|        \\       /      \\ |  \\   |  \\|        \\|       \\ ");
	mvwprintw(this->win, HEIGHT/4 + 2, WIDTH/4/2, "|  $$$$$$\\|  $$$$$$\\| $$\\   /  $$| $$$$$$$$      |  $$$$$$\\| $$   | $$| $$$$$$$$| $$$$$$$\\");
	mvwprintw(this->win, HEIGHT/4 + 3, WIDTH/4/2, "| $$ __\\$$| $$__| $$| $$$\\ /  $$$| $$__          | $$  | $$| $$   | $$| $$__    | $$__| $$");
	mvwprintw(this->win, HEIGHT/4 + 4, WIDTH/4/2, "| $$|    \\| $$    $$| $$$$\\  $$$$| $$  \\         | $$  | $$ \\$$\\ /  $$| $$  \\   | $$    $$");
	mvwprintw(this->win, HEIGHT/4 + 5, WIDTH/4/2, "| $$ \\$$$$| $$$$$$$$| $$\\$$ $$ $$| $$$$$         | $$  | $$  \\$$\\  $$ | $$$$$   | $$$$$$$\\");
	mvwprintw(this->win, HEIGHT/4 + 6, WIDTH/4/2, "| $$__| $$| $$  | $$| $$ \\$$$| $$| $$_____       | $$__/ $$   \\$$ $$  | $$_____ | $$  | $$");
 	mvwprintw(this->win, HEIGHT/4 + 7, WIDTH/4/2, " \\$$    $$| $$  | $$| $$  \\$ | $$| $$     \\       \\$$    $$    \\$$$   | $$     \\| $$  | $$");
	mvwprintw(this->win, HEIGHT/4 + 8, WIDTH/4/2, "  \\$$$$$$  \\$$   \\$$ \\$$      \\$$ \\$$$$$$$$        \\$$$$$$      \\$     \\$$$$$$$$ \\$$   \\$$");
	wattroff(this->win, COLOR_PAIR(3));
	wattron(this->win, COLOR_PAIR(1));
	mvwprintw(this->win, HEIGHT/2 + 2, WIDTH/2 - 9, "YOUR SCORE: %d", score);
	wattroff(this->win, COLOR_PAIR(1));
	wattron(this->win, COLOR_PAIR(2));
	mvwprintw(this->win, HEIGHT/2 + 10, WIDTH/2 - 10, "PRESS ESC FOR EXIT");
	wattroff(this->win, COLOR_PAIR(2));
	this->reFreshWin();
}

void		View::drawInfo(AShip const &player) {
	this->clearWin(INFO_X + 2, HEIGHT - 4);
	wattron(this->win, COLOR_PAIR(2) | A_BOLD);
	mvwprintw(this->win, 3, INFO_X + 4, "PLAYER: %s", player._name.c_str());
	wattroff(this->win, COLOR_PAIR(2) | A_BOLD);
	wattron(this->win, COLOR_PAIR(1) | A_BOLD);
	mvwprintw(this->win, 4, INFO_X + 4, "LIVES: %d", player.getLives());
	wattroff(this->win, COLOR_PAIR(1) | A_BOLD);
	wattron(this->win, COLOR_PAIR(4) | A_BOLD);
	mvwprintw(this->win, 5, INFO_X + 4, "SCORE: %d", player.getScore());
	wattroff(this->win, COLOR_PAIR(4) | A_BOLD);
	this->reFreshWin();
}

// =======================| DRAW GAME |========================= //

void		View::drawGame(AShip const &player, t_enemy *enemies) {
	wattron(this->win, COLOR_PAIR(8));
	mvwvline(this->win, 0, INFO_X, '*', HEIGHT);
	wattroff(this->win, COLOR_PAIR(8));
	this->genericStars();
	this->drawShipPlayer(player);
	this->drawShipEnemies(enemies);
}

void		View::drawBorder(void) {
	wattron(this->win, COLOR_PAIR(8));
	wborder(this->win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(this->win, COLOR_PAIR(8));
}

void		View::drawBulletsPlayer(AShip const &player) {
	int i = -1;
	if (!(this->timer % 2))
	{
		while (++i < 50)
		{
			if (player._bullet[i].x && player._bullet[i].y)
				player._bullet[i].y--;
			if (player._bullet[i].y == 0)
			{
				player._bullet[i].x = 0;
				player._bullet[i].y = 0;
			}
		}
	}
	i = -1;
	wattron(this->win, COLOR_PAIR(1));
	while (++i < 50)
	{
		if (player._bullet[i].x && player._bullet[i].y)
			mvwprintw(this->win, player._bullet[i].y, player._bullet[i].x, "*");
	}
	wattroff(this->win, COLOR_PAIR(1));
}

void		View::drawStars(void) {
	int i = -1;
	if (!(this->timer % 10))
	{
		while (++i < 100)
		{
			this->stars[i].y++;
			if (this->stars[i].y == HEIGHT - 2)
			{
				this->stars[i].y = 1;
				this->stars[i].x = rand() % (INFO_X - 4) + 2;
			}
		}
	}
	i = -1;
	wattron(this->win, COLOR_PAIR(6));
	while (++i < 100)
		mvwprintw(this->win, this->stars[i].y, this->stars[i].x, ".");
	wattroff(this->win, COLOR_PAIR(6));
}

void		View::genericStars(void) {
	int i = -1;
	while (++i < 100)
	{
		this->stars[i].x = rand() % (INFO_X - 4) + 2;
		this->stars[i].y = rand() % (HEIGHT - 4) + 2;
	}
}

// =================| DRAW PLAYER & ENEMIES |======================== //

void	View::drawShipPlayer(AShip const &player) {
	wattron(this->win, COLOR_PAIR(6));
	mvwprintw(this->win, player.getY(), player.getX(), "   _   ");
	mvwprintw(this->win, player.getY() + 1, player.getX(), "  |||  ");
	mvwprintw(this->win, player.getY() + 2, player.getX(), " //|\\\\");
	wattron(this->win, COLOR_PAIR(6));
	wattron(this->win, COLOR_PAIR(4));
	mvwprintw(this->win, player.getY() + 3, player.getX(), "*******");
	wattron(this->win, COLOR_PAIR(4));	
}

void	View::drawShipEnemies(t_enemy *enemies) {
	int i = -1;
	wattron(this->win, COLOR_PAIR(3));
	while (++i < 10)
	{
		if (enemies[i].enem->getLives())
		{
			mvwprintw(this->win, enemies[i].enem->getY(), enemies[i].enem->getX(), "\\*_*/");
			mvwprintw(this->win, enemies[i].enem->getY() + 1, enemies[i].enem->getX(), " =|= ");
		}
	}
	wattron(this->win, COLOR_PAIR(3));
}

// =======================| DRAW MENU |========================= //

void		View::drawMenu(void) {
	wattron(this->win, COLOR_PAIR(1));
	mvwprintw(this->win, HEIGHT/6, WIDTH/4 + 7, "|       \\ |        \\|        \\|       \\  /      \\"); 
	mvwprintw(this->win, HEIGHT/6 + 1, WIDTH/4 + 7, "| $$$$$$$\\| $$$$$$$$ \\$$$$$$$$| $$$$$$$\\|  $$$$$$\\");
	mvwprintw(this->win, HEIGHT/6 + 2, WIDTH/4 + 7, "| $$__| $$| $$__       | $$   | $$__| $$| $$  | $$");
	mvwprintw(this->win, HEIGHT/6 + 3, WIDTH/4 + 7, "| $$    $$| $$  \\      | $$   | $$    $$| $$  | $$");
	mvwprintw(this->win, HEIGHT/6 + 4, WIDTH/4 + 7, "| $$$$$$$\\| $$$$$      | $$   | $$$$$$$\\| $$  | $$");
	mvwprintw(this->win, HEIGHT/6 + 5, WIDTH/4 + 7, "| $$  | $$| $$_____    | $$   | $$  | $$| $$__/ $$");
	mvwprintw(this->win, HEIGHT/6 + 6, WIDTH/4 + 7, "| $$  | $$| $$     \\   | $$   | $$  | $$ \\$$    $$");
 	mvwprintw(this->win, HEIGHT/6 + 7, WIDTH/4 + 7, " \\$$   \\$$ \\$$$$$$$$    \\$$    \\$$   \\$$  \\$$$$$$ ");
	wattroff(this->win, COLOR_PAIR(2));

	drawMenuAddition();
}

void		View::drawMenuAddition(void) const {
	int n1 = 6;
	int n2 = 6;
	int n3 = 6;
	switch (menu)
	{
		case 0:
		{
			n1 = 5;
			break;
		}
		case 1:
		{
			n2 = 5;
			break;
		}
		case 2:
		{
			n3 = 5;
			break;
		}
	}
	wattron(this->win, COLOR_PAIR(n1) | A_BOLD);
	mvwprintw(this->win, HEIGHT/2, WIDTH/2 - 5, "START GAME");
	wattroff(this->win, COLOR_PAIR(n1) | A_BOLD);
	wattron(this->win, COLOR_PAIR(n2) | A_BOLD);
	mvwprintw(this->win, HEIGHT/2 + 3, WIDTH/2 - 6, "LEVEL: %s", game_lvl.c_str());
	wattroff(this->win, COLOR_PAIR(n2) | A_BOLD);
	wattron(this->win, COLOR_PAIR(n3) | A_BOLD);
	mvwprintw(this->win, HEIGHT/2 + 6, WIDTH/2 - 2, "EXIT");
	wattroff(this->win, COLOR_PAIR(n3) | A_BOLD);
}

void		View::clearWin(int x, int width) const {
	int y = 0;
	while (++y < HEIGHT - 1)
		mvwprintw(this->win, y, x, "%*c", width, ' ');
}

void		View::clearLine(int y, int x, int width) const {
	mvwprintw(this->win, y, x, "%*c", width, ' ');
}

// ===============| GETTER FUNCTIONS |================= //

WINDOW 	*View::getWindow(void) const {
	return (this->win);
}

int 	View::getSpeed(void) const {
	return (this->_speed);
}

// ===============| SETTER FUNCTION |================= //

void	View::setSpeed(int speed) {
	this->_speed = speed;
}

