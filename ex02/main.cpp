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
	std::cout << "=== ClapTrap ===" << std::endl;

	std::cout << "\n--- default constructor ---" << std::endl;
	{
		ClapTrap def;
		def.attack("dummy");
	}

	std::cout << "\n--- normal attack / repair ---" << std::endl;
	{
		ClapTrap bob("Bob");
		bob.attack("enemy");
		bob.beRepaired(5);
	}

	std::cout << "\n--- takeDamage prints the right amount ---" << std::endl;
	{
		ClapTrap alice("Alice");
		alice.takeDamage(4);
	}

	std::cout << "\n--- energy points run out ---" << std::endl;
	{
		ClapTrap carl("Carl");
		for (int i = 0; i < 11; i++)
			carl.attack("target");
	}

	std::cout << "\n--- hit points run out (KO) ---" << std::endl;
	{
		ClapTrap dave("Dave");
		dave.takeDamage(6);
		dave.takeDamage(6);
		dave.attack("enemy");
		dave.beRepaired(5);
	}

	std::cout << "\n--- copy constructor / assignment ---" << std::endl;
	{
		ClapTrap eve("Eve");
		ClapTrap eveCopy(eve);
		eveCopy.attack("target");

		ClapTrap frank("Frank");
		frank = eve;
		frank.attack("target");
	}

	std::cout << "\n=== ScavTrap ===" << std::endl;

	std::cout << "\n--- construction/destruction chaining ---" << std::endl;
	std::cout << "(expect ClapTrap ctor msg, then ScavTrap ctor msg;" << std::endl;
	std::cout << " on scope exit, ScavTrap dtor msg, then ClapTrap dtor msg)" << std::endl;
	{
		ScavTrap goliath("Goliath");
	}

	std::cout << "\n--- default constructor chaining ---" << std::endl;
	{
		ScavTrap def;
	}

	std::cout << "\n--- inherited stats (100 hp / 50 ep / 20 dmg) + overridden attack ---" << std::endl;
	{
		ScavTrap rocky("Rocky");
		rocky.attack("wall");
		rocky.takeDamage(30);
		rocky.beRepaired(10);
	}

	std::cout << "\n--- guardGate ---" << std::endl;
	{
		ScavTrap gatekeeper("Gatekeeper");
		gatekeeper.guardGate();
	}

	std::cout << "\n--- energy points run out (50 attacks) ---" << std::endl;
	{
		ScavTrap sam("Sam");
		for (int i = 0; i < 51; i++)
			sam.attack("target");
	}

	std::cout << "\n--- hit points run out (KO, 100 hp) ---" << std::endl;
	{
		ScavTrap tank("Tank");
		tank.takeDamage(60);
		tank.takeDamage(60);
		tank.attack("enemy");
		tank.beRepaired(5);
	}

	std::cout << "\n--- copy constructor / assignment ---" << std::endl;
	{
		ScavTrap rocky("Rocky");
		ScavTrap rockycopy(rocky);
		rockycopy.attack("target");

		ScavTrap victor("Victor");
		victor = rocky;
		victor.attack("target");
	}

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
