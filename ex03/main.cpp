/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
	std::cout << "\n=== DiamondTrap ===" << std::endl;

	std::cout << "\n--- construction/destruction chaining ---" << std::endl;
	std::cout << "(expect ClapTrap, then ScavTrap, then FragTrap, then DiamondTrap ctor msgs;" << std::endl;
	std::cout << " reverse order on scope exit)" << std::endl;
	{
		DiamondTrap dt("Poly");
	}

	std::cout << "\n--- default constructor chaining ---" << std::endl;
	{
		DiamondTrap def;
	}

	std::cout << "\n--- blended stats (100 hp / 50 ep / 30 dmg) ---" << std::endl;
	{
		DiamondTrap dt("Blend");
		dt.attack("wall");
		dt.takeDamage(30);
		dt.beRepaired(10);
	}

	std::cout << "\n--- whoAmI (own name vs ClapTrap's suffixed name) ---" << std::endl;
	{
		DiamondTrap dt("Poly");
		dt.whoAmI();
	}

	std::cout << "\n--- attack() resolves to ScavTrap's version, no ambiguity ---" << std::endl;
	{
		DiamondTrap dt("Poly");
		dt.attack("target");
	}

	std::cout << "\n--- inherited special abilities from both parents ---" << std::endl;
	{
		DiamondTrap dt("Poly");
		dt.guardGate();
		dt.highFivesGuys();
	}

	std::cout << "\n--- energy points run out (50 attacks) ---" << std::endl;
	{
		DiamondTrap dt("Drainer");
		for (int i = 0; i < 51; i++)
			dt.attack("target");
	}

	std::cout << "\n--- hit points run out (KO, 100 hp) ---" << std::endl;
	{
		DiamondTrap dt("Tank");
		dt.takeDamage(60);
		dt.takeDamage(60);
		dt.attack("enemy");
		dt.beRepaired(5);
	}

	std::cout << "\n--- copy constructor / assignment ---" << std::endl;
	{
		DiamondTrap dt("Origin");
		DiamondTrap dtCopy(dt);
		dtCopy.whoAmI();
		dtCopy.attack("target");

		DiamondTrap dt2("Other");
		dt2 = dt;
		dt2.whoAmI();
		dt2.attack("target");
	}

	std::cout << "\n--- end of main ---" << std::endl;
	return (0);
}
