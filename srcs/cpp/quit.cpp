/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:16 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 19:07:15 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hpp/IRC.hpp"

bool	IRC::quit(client &client, std::string cmd)
{
	(void)cmd;

	// Deleting sockets in channels
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		// from operators
		for (size_t j = 0; j < this->channels[i].getOperators().size(); j++)
		{
			if (this->channels[i].getOperators()[j] == client.GetSock())
			{
				this->channels[i].getOperators().erase(this->channels[i].getOperators().begin() + j);
				break;
			}
		}
		// from clients channel
		for (size_t j = 0; j < this->channels[i].getClients().size(); j++)
		{
			if (this->channels[i].getClients()[j] == client.GetSock())
			{
				this->channels[i].getClients().erase(this->channels[i].getClients().begin() + j);
				break;
			}
		}
	}
	ClearClients(client.GetSock());
	return (0);
}
