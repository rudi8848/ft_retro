/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:28:51 by gvynogra          #+#    #+#             */
/*   Updated: 2018/10/07 21:28:53 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "AShip.hpp"

class Player : public AShip
{
public:

	Player(std::string name);
	Player(Player const &player);
	Player & operator= (Player const &player);
	~Player(void);

	void 	move(int direction);

};

std::ostream & operator<<(std::ostream &s, Player const & soc);

#endif
