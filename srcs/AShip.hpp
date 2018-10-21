/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AShip.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:41:20 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/07 22:41:22 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASHIP_HPP
# define ASHIP_HPP

# include "AShip.hpp"
# include "../include/ft_retro.hpp"

typedef struct 	s_bullet {
	int x;
	int y;
} 				t_bullet;

class AShip
{
	
public:
	AShip(int lives, int x, int y, int sizeX, int sizeY);
	AShip(AShip const &ship);
	AShip & operator= (AShip const &ship);
	virtual ~AShip(void);

	virtual void		move(int direction) = 0;

	int				getScore(void) const;
	void			setScore(int score);

	int				getLives(void) const;
	int 			getX(void) const;
	int				getY(void) const;
	int 			getSizeX(void) const;
	int 			getSizeY(void) const;
	int				getShots(void) const;
	void			setPosition(int x, int y);
	void			setLives(int lives);
	bool			isWall(int x, int y) const;
	void			createBullets(void);
	void			addBullet(void);

	std::string		_name;
	int				_score;
	static t_bullet	_bullet[50];
	
private:
	int				_lives;
	int				_x;
	int				_y;
	int				_sizeX;
	int				_sizeY;
	
};

std::ostream & operator<<(std::ostream &s, AShip const & soc);

#endif
