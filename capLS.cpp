/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capLS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:11:56 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 18:09:48 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::capLs(client &client, std::string cmd)
{
	std::cout << BLUE << "In capls(): " << END_C << std::endl;
	if (cmd.find("LS") == std::string::npos)
		return (0);
	if (client.GetSetup() == 0)
	{	
		std::cout << "Setting up" << std::endl;
		client.SetSetup(1);
	}
	return (1);
}
