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

int main()
{
	std::cout << "\n=== FragTrap ===" << std::endl;

	std::cout << "\n--- construction/destruction chaining ---" << std::endl;
	std::cout << "(expect ClapTrap ctor msg, then FragTrap ctor msg;" << std::endl;
	std::cout << " on scope exit, FragTrap dtor msg, then ClapTrap dtor msg)" << std::endl;
	{
		FragTrap terminator("Terminator");
	}

	std::cout << "\n--- default constructor chaining ---" << std::endl;
	{
		FragTrap def;
	}

	std::cout << "\n--- inherited stats (100 hp / 100 ep / 30 dmg) + overridden attack ---" << std::endl;
	{
		FragTrap max("Max");
		max.attack("wall");
		max.takeDamage(30);
		max.beRepaired(10);
	}

	std::cout << "\n--- highFivesGuys ---" << std::endl;
	{
		FragTrap buddy("Buddy");
		buddy.highFivesGuys();
	}

	std::cout << "\n--- energy points run out (100 attacks) ---" << std::endl;
	{
		FragTrap grinder("Grinder");
		for (int i = 0; i < 101; i++)
			grinder.attack("target");
	}

	std::cout << "\n--- hit points run out (KO, 100 hp) ---" << std::endl;
	{
		FragTrap brick("Brick");
		brick.takeDamage(60);
		brick.takeDamage(60);
		brick.attack("enemy");
		brick.beRepaired(5);
	}

	std::cout << "\n--- copy constructor / assignment ---" << std::endl;
	{
		FragTrap gary("Gary");
		FragTrap garyCopy(gary);
		garyCopy.attack("target");

		FragTrap henry("Henry");
		henry = gary;
		henry.attack("target");
	}

	std::cout << "\n--- end of main ---" << std::endl;
	return (0);
}
