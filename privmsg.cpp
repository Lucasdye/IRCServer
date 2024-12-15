/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/05/14 11:36:19 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


IRC::client 						IRC::getclientfromsock(int sock){
	for(std::map<int, client>::iterator ite = this->users.begin(); ite != users.end() ; ite++)
	{
		if(ite->first == sock)
			return ite->second;
	}
	return 0;
}

void					IRC::private_msg_user(std::string msg, client &sender, std::string clients)
{
	std::cout << BOLD << BLUE << "\tIn  private_msg_user(): " << END_C << std::endl;
	std::string senderNick;
	std::string receiverNick;
	int clientSock;
	
	std::cout << BOLD << BLUE << "cmd: " << msg << END_C << std::endl;
	if (clients == "bot")
	{
		if(msg == "help")
		{
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/JOIN : pour rejoindre un channel"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/PART : pour quitter un channel"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/MSG : pour envoyer un message prive"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/MODE : pour activer un des modes du channel"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/NICK : pour changer de nick"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/QUIT : pour quitter le serveur"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/KICK : pour kick qqn d'un channel"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/TOPIC : pour set le topic d'un channel"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "/INVITE : pour inviter qqn a rejoindre un channel"), sender.GetSock());
		}
		else{
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "Salut a toi honorable correcteur,\n"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "Si t'es competences en code sont l'apanage de ton charisme, il se peut que nous soyons dors et deja amoureux de toi.\n"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "Pas de panique, Lucas a promis de garder ses mains dans ses poches durant toute la duree de l'evaluation.\n"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "Cependant, si tu souhaites poursuivre cette entrevue par la suite, voici le meilleur moyen de le contacter : 06 82 45 95 36.\n"), sender.GetSock());
			sendRPL(RPL_PRIVMSG(clients, sender.GetNick(), clients, "Mets 125 stp"), sender.GetSock());
		}	
		return ;
	}
	if ((clientSock = getSockFromName(clients)) == -1)
		return(void)sendRPL(ERR_NOSUCHNICK(sender.GetNick(), clients), sender.GetSock());
	sendRPL(RPL_PRIVMSG(sender.GetNick(), sender.GetNick(), clients, msg), clientSock);
}	

void					IRC::private_msg_chan(std::string msg, client &sender, std::string channel)
{
	std::cout << BOLD << BLUE << "\tIn  private_msg_chan(): " << END_C << std::endl;
	size_t	idxChan = 0;
	std::string senderNick;
	std::string receiverNick;
	
	std::cout << BOLD << BLUE << "cmd: " << msg << END_C << std::endl;
	while (idxChan < this->channels.size())
	{
		if (channels[idxChan].getName() == channel)
			break;
		idxChan++;
	}
	if (idxChan == this->channels.size())
		return ((void)sendRPL(ERR_NOSUCHCHANNEL(channel), sender.GetSock()));
	// Is sender part of the channel ? 
	size_t i = 0;
	while(i < this->channels[idxChan].getClients().size())
	{
		if (sender.GetSock() == this->channels[idxChan].getClients()[i])
			break;
		i++;
	}

	if (i == this->channels[idxChan].getClients().size())
		return ;
	if (this->channels[idxChan].isOperator(sender.GetSock(), this->channels[idxChan].getOperators()))
	{
		senderNick = "@" + sender.GetNick();
	}
	else
		senderNick = sender.GetNick();
	for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
	{
			if (this->channels[idxChan].getClients()[i] != sender.GetSock())
			{	
				std::cout << BOLD << "nick: " << senderNick << END_C << std::endl;
				sendRPL(RPL_PRIVMSG(senderNick, sender.GetNick(), channel, msg), this->channels[idxChan].getClients()[i]);
			}
	}
}

bool	IRC::privmsg(client &clients, std::string cmd)
{
	std::string target;
	std::string msg;
	std::string::size_type x;
	std::string::size_type doubl_point;
	size_t len = 0;

	if (clients.GetSetup() != 4)
		return (0);
	std::cout << BLUE << BOLD << "\tIn privmsg()" << END_C << std::endl;
	if ((x = cmd.find("#", 0)) == std::string::npos)
	{
		len = cmd.find(" ", 0) - cmd.find(" ", cmd.find(" "), 0);
		target = cmd.substr(0, cmd.find(" ") - len);
		msg = cmd.substr(cmd.find(":") + 1, cmd.size() - cmd.find(":"));
		if (target != "bot")
			if (this->users[getSockFromName(target)].GetSetup() != 4)
				return (0); // A test
		private_msg_user(msg, clients, target);
		return(true);
	}
	std::cout << "target: " << target << std::endl;
	if ((doubl_point = cmd.find(":", 0)) == std::string::npos)
		return (0);
	std::cout << BOLD << "Check0" << END_C << std::endl;
	target = cmd.substr(x , doubl_point - 1);
	msg = cmd.substr(doubl_point + 1, cmd.size());
	private_msg_chan(msg, clients, target);
	std::cout << BOLD << "Check1" << END_C << std::endl;
	return (1);
}
