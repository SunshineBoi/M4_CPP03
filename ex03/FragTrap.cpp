/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 15:00:02 by kong              #+#    #+#             */
/*   Updated: 2026/08/30 16:51:16 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	_hp = 100;
	_ep = 100;
	_dmg = 30;
	std::cout
		<< "FragTrap Default Constructor called"
		<< std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
	_hp = 100;
	_ep = 100;
	_dmg = 30;
	std::cout
		<< "FragTrap Constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout
		<< "FragTrap Copy Constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	ClapTrap::operator=(other);
	std::cout
		<< "FragTrap Copy assignment operator called" << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout
		<< "FragTrap Destructor called"
		<< std::endl;
}

void	FragTrap::highFivesGuys()
{
	std::cout
		<< "FragTrap "
		<< _name
		<< " is asking for high fives! 1, 2, 3, 4, HIGH FIVES!" << std::endl;
}

void	FragTrap::attack(const std::string& target)
{
	
	if (_hp <= 0 )
	{
		std::cout
			<< "FragTrap "
			<< _name
			<< " has passed out! Cannot attack.." << std::endl;
		return ;
	}
	else if (_ep <= 0 )
	{
		std::cout
			<< "FragTrap "
			<< _name
			<< " has no more energy left to attack!" << std::endl;
		return ;
	}
	_ep -= 1;
	std::cout
		<< "FragTrap "
		<< _name
		<< " attacks "
		<< target
		<< ", causing "
		<< _dmg
		<< " points of damage!" << std::endl;
}

