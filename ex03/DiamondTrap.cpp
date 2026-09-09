/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamonTrap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:42:16 by kong              #+#    #+#             */
/*   Updated: 2026/08/30 20:56:07 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap()
{
	_name = "Diamond Default";
	_hp = 100;
	_ep = 50;
	_dmg = 30;
	std::cout
		<< "DiamondTrap Default Constructor called"
		<< std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
	_name = name;  // this setup for DiamondTrap's member
	_hp = 100;
	_ep = 50;
	_dmg = 30;
	std::cout
		<< "DiamondTrap Constructor called"
		<< std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
	: ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout
		<< "DiamondTrap Copy Constructor called"
		<< std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	ClapTrap::operator=(other);
	_name = other._name;
	std::cout
		<< "DiamondTrap Copy assignment operator called"
		<< std::endl;
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout
		<< "DiamondTrap Destructor called"
		<< std::endl;
}

void	DiamondTrap::whoAmI()
{
	std::cout
		<< "My name is "
		<< _name
		<< ", my grandfather name is "
		<< ClapTrap::_name << std::endl;
}

void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

/*
The flow for inheritance follows init list.
When the base class is set virtual, it will omit to construct its' parent class.

Child: run Grandpa() -> run Parent1() -> run Parent2() -> child himself
Inside Virtual Parent1: Grandpa() is omitted, but Parent1 body is ran.
Inside Virtual Parent2: Grandpa() is omitted, but Parent2 body is ran.

*/
