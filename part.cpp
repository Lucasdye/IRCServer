/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:09 by jquil             #+#    #+#             */
/*   Updated: 2024/05/03 15:37:11 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
bool	IRC::part(client &client, std::string cmd)
{
	std::cout << BLUE << BOLD << "In part(): " <<  END_C << "cmd: " << cmd << std::endl;
	std::string chan;
	std::string arg = "";
	size_t idxChan = 0;

	if (cmd.find("#") == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetNick()), client.GetSock()), false);
	if (cmd.find(":") != std::string::npos)
		chan = cmd.substr(cmd.find("#"), cmd.find(":") - cmd.find("#") - 1);
	else
		chan = cmd.substr(cmd.find("#"), cmd.size());
	arg = cmd.substr(cmd.find(":") + 1, cmd.size());
	std::cout << "chan: " << chan << std::endl;
	// do channels exit ?
	if (!this->channels.size())
		return ((void)sendRPL(ERR_NOSUCHCHANNEL(chan), client.GetSock()), false);
	// find channel
	while (idxChan < this->channels.size())
	{
		if (chan == this->channels[idxChan].getName())
			break;
		idxChan++;
	}
	if (idxChan == this->channels.size())
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(client.GetNick(), chan), client.GetSock()), false);
	size_t i = 0;
	while (i < this->channels[idxChan].getClients().size())
	{
		if (client.GetSock() == this->channels[idxChan].getClients()[i])
		{
			this->channels[idxChan].getClients().erase(this->channels[idxChan].getClients().begin() + i);
			sendRPL(RPL_PART(userID(client.GetNick(), client.GetNick()), chan, arg), client.GetSock());
			// Broadcasting msg to all clients in channel
			for (size_t j = 0; j < this->channels[idxChan].getClients().size(); j++)
				if (this->channels[idxChan].getClients()[j] != client.GetSock())
					sendRPL(RPL_PART(userID(client.GetNick(), client.GetNick()), chan, arg), this->channels[idxChan].getClients()[j]);
			break;
		}
		i++;
	}
	if (i == this->channels[idxChan].getClients().size())
		sendRPL(RPL_PARTNOTICE2(client.GetNick(), chan), client.GetSock());
	std::cout << "returning false" << std::endl;
	return (false);
}
