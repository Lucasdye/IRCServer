/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:25 by jquil             #+#    #+#             */
/*   Updated: 2024/05/13 17:38:32 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hpp/IRC.hpp"

bool	IRC::user(client &client, std::string cmd)
{
		// if (cmd.size() == 0)
		// {
		// 	// std::string err = "localhost";
		// 	// sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		// 	return (0);
		// }
	std::string err = "localhost";
	if(client.GetSetup() == 2 && client.GetNick() == "")
		client.setFlag(42);
	std::cout << "flag: " << client.getFlag() << std::endl;
	this->tmp = cmd;
	if (client.GetSetup() != 3)
		return (0);
	if (cmd_used_name(cmd, 1) == 1)
	{
		sendRPL(ERR_ALREADYREGISTERED(cmd), client.GetSock());
		cmd.insert(cmd.end(), '_');
		user(client, cmd);
		return (1);
	}
	else
	{
		client.SetUser(cmd);
		client.SetSetup(4);
		std::string					msg;
		std::string					name;
		msg = ":localhost 001 " + client.GetNick() + " :Welcome to SUUUUUServer " + client.GetNick() + "!~" + client.GetUser() + "@127.0.0.1\r\n";
		client.setFlag(42);
		if (send(client.GetSock(), msg.c_str(), msg.size(), 0) < 1)
		{
			//del_user(client.getFd());
			return (0);
		}
	}
		return (1);
}
