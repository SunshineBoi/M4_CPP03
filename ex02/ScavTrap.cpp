/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 15:00:02 by kong              #+#    #+#             */
/*   Updated: 2026/08/30 16:18:07 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	_hp = 100;
	_ep = 50;
	_dmg = 20;
	std::cout
		<< "ScavTrap Default constructor called"
		<< std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
{
	_hp = 100;
	_ep = 50;
	_dmg = 20;
	std::cout
		<< "ScavTrap Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout
		<< "ScavTrap Copy Constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	ClapTrap::operator=(other);
	std::cout
		<< "ScavTrap Copy assignment operator called" << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout
		<< "ScavTrap Destructor called"
		<< std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout
		<< "ScavTrap "
		<< _name
		<< " is now in Gate Keeper Mode!" << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	
	if (_hp <= 0 )
	{
		std::cout
			<< "ScavTrap "
			<< _name
			<< " has passed out! Cannot attack.." << std::endl;
		return ;
	}
	else if (_ep <= 0 )
	{
		std::cout
			<< "ScavTrap "
			<< _name
			<< " has no more energy left to attack!" << std::endl;
		return ;
	}
	_ep -= 1;
	std::cout
		<< "ScavTrap "
		<< _name
		<< " attacks "
		<< target
		<< ", causing "
		<< _dmg
		<< " points of damage!" << std::endl;
}

