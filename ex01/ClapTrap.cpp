/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 13:16:53 by kong              #+#    #+#             */
/*   Updated: 2026/08/30 20:56:29 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
	: _name("Default"), _hp(10), _ep(10), _dmg(0)
{
	std::cout
		<< "ClapTrap Default constructor called"
		<< std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
	: _name(name), _hp(10), _ep(10), _dmg(0)
{
	std::cout
		<< "ClapTrap Constructor called"
		<< std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
	: _name(other._name), _hp(other._hp), _ep(other._ep), _dmg(other._dmg)
{
	std::cout
		<< "ClapTrap Copy Constructor called"
		<< std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	if (this != &other)
	{
		_name = other._name;
		_hp = other._hp;
		_ep = other._ep;
		_dmg = other._dmg;
	}
	std::cout
		<< "ClapTrap Copy assignment operator called"
		<< std::endl;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout
		<< "ClapTrap Destructor called"
		<< std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (_hp <= 0 )
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " has passed out! Cannot attack.." << std::endl;
		return ;
	}
	else if (_ep <= 0 )
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " has no more energy left to attack!" << std::endl;
		return ;
	}
	_ep -= 1;
	std::cout
		<< "ClapTrap "
		<< _name
		<< " attacks "
		<< target
		<< ", causing "
		<< _dmg
		<< " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (_hp <= 0 )
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " has passed out!" << std::endl;
		return ;
	}
	std::cout
		<< "ClapTrap "
		<< _name
		<< " was attacked, causing "
		<< amount
		<< " points of damage!" << std::endl;
	_hp -= amount;
	if (_hp <= 0)
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " is KO!" << std::endl;
		return ;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_hp <= 0 )
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " has passed out! Cannot repair itself.." << std::endl;
		return ;
	}
	else if (_ep <= 0 )
	{
		std::cout
			<< "ClapTrap "
			<< _name
			<< " has no more energy left to repair itself!" << std::endl;
		return ;
	}
	_ep -= 1;
	std::cout
		<< "ClapTrap "
		<< _name
		<< " is repairing itself, regaining "
		<< amount
		<< " amount of hit points."
		<< std::endl;
}







