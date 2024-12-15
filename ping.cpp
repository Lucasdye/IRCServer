/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:36 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 18:02:46 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::ping(client &client, std::string cmd)
{
	if (cmd == "localhost")
	{
		std::string msg1 = "PONG localhost\r\n";
		if (send(client.GetSock(), msg1.c_str(), msg1.size(), 0) > 0)
			return (1);
		
		std::cout << "PING failed" << std::endl;
		return (0);
	}
	else
		return (1);
}
