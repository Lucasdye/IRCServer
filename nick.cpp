/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:57 by jquil             #+#    #+#             */
/*   Updated: 2024/05/14 11:25:25 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "IRC.hpp"

int IRC::cmd_used_name(std::string &name, int mode)
{
	if(mode == 1)
	{
		for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
		{
			if(name == it->second.GetUser())
				return (1);
		}
	}
	if(mode == 0)
	{
		for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
		{
			if(name == it->second.GetNick())
				return (1);
		}
	}
	return(0);
}

bool	IRC::nick(client &client, std::string cmd)
{
	std::string err = "localhost";
	std::cout << BLUE << BOLD << client.GetSetup() <<  END_C << std::endl;
	if (cmd.size() == 0)
	{
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		return (0);
	}
	if(client.GetSetup() != 2 && client.GetSetup() != 4)
		sendRPL(ERR_NOTREGISTERED(err), client.GetSock());
	else if(cmd == "")
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
	else if(cmd_used_name(cmd, 0) == 1)
	{
		this->oldNick = cmd;
		sendRPL(NICKNAMEINUSE_ERR(cmd), client.GetSock());
		// cmd.insert(cmd.end(), '_');
		// nick(client, cmd);
		return (1);
	}
	else if(client.getFlag() == 42 )
	{
		if(!client.GetNick().empty())
			client.setoldnick(client.GetNick());
		std::string newNickname = cmd;
		std::string msg = ":" + client.getoldnick()  + " NICK " + newNickname + "\r\n";
		client.SetNick(cmd);	
		if(client.GetSetup()  < 4){
			client.SetSetup(3);
			user(client, this->tmp);	
		}
		sendRPL(msg, client.GetSock());
		return (1);
	}
	// else if (flag != 42 && client.GetSetup() == 4)
	// {
	// 	std::string newNickname = cmd;
	// 	std::string msg = ":" + client.GetNick() + " NICK " + newNickname + "\r\n";
	// 	client.SetNick(cmd);
	// 	sendRPL(msg, client.GetSock());		
	// 	return (1);
	// }
	else if((cmd)[0] == '#')
		sendRPL(ERR_ERRONEUSNICK(err), client.GetSock());
	else{
		client.SetNick(cmd);
		client.SetSetup(3);
		return (1);
	}
	return (1);
}
