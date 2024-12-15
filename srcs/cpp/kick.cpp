/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/05/13 18:33:42 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hpp/IRC.hpp"

bool	IRC::kick(client &client, std::string cmd)
{
	std::cout << BOLD << BLUE << "In kick()" << END_C << std::endl;
	std::string chanNam = "";
	std::string	targetNam = "";
	std::string	reason = "";
	size_t		idxChan = 0;
	int			targSock = 0;

	//----- Parsing 
	if (cmd.find("#") == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetUser()), client.GetSock()), false);
	if (cmd.find(":") == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(cmd.substr(cmd.find(" "), cmd.find("\r") - cmd.find(" "))), client.GetSock()), false);
	//----- Extract
	chanNam = cmd.substr(cmd.find("#"), cmd.find(" ") - cmd.find("#"));
	reason	= cmd.substr(cmd.find(":") + 1, cmd.find("\r") - cmd.find(":"));
	targetNam	= cmd.substr(cmd.find(" ") + 1, cmd.find(":") - cmd.find(" ") - 2);
	//----- Defining channel idx
	for (size_t i = 0; i <= this->channels.size(); i++)
	{
		if (i == this->channels.size())
			return (void(sendRPL(ERR_NOSUCHCHANNEL(chanNam), client.GetSock())), false);
		if (chanNam == this->channels[i].getName())
		{	
			idxChan = i;
			break ;
		}
	}
	if (this->channels[idxChan].isOperator(client) == false)
		return (sendRPL(ERR_NOTOPERATOR(client.GetNick() ), client.GetSock()), false);
		
		
	//----- Defining target sock
	for (size_t i = 0; i <= this->channels[idxChan].getClients().size(); i++)
	{
		if (i == this->channels[idxChan].getClients().size())
			return (void(sendRPL(ERR_USERNOTINCHANNEL(client.GetNick(), client.GetNick(), chanNam), client.GetSock())), false);
		if (targetNam == getNameFromSock(this->channels[idxChan].getClients()[i]))
		{	
			targSock = this->channels[idxChan].getClients()[i];
			break ;
		}
	}
	//----- Erasing sock from channel
	//----- IRC server validation answer
	for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
	{
		//clean the socket user from the channel
		sendRPL(RPL_KICK(userID(client.GetNick(), client.GetNick()), chanNam, targetNam, reason), this->channels[idxChan].getClients()[i]);
	}
	this->channels[idxChan].remove_client(targSock);
	return (true);
}
