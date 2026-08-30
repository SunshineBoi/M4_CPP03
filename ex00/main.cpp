/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	std::cout << "--- default constructor ---" << std::endl;
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

	std::cout << "\n--- end of main, destructors fire ---" << std::endl;
	return (0);
}
