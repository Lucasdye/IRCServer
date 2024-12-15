/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:23 by jquil             #+#    #+#             */
/*   Updated: 2024/05/13 17:18:55 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hpp/IRC.hpp"

bool						IRC::topic(client &client, std::string cmd)
{
	std::string 			topicNam;
	std::string 			chanNam;
	std::string::size_type 	posHash = cmd.find('#');
	std::string::size_type 	posColon = cmd.find(':');



	std::cout << BOLD << BLUE << "\tIn topic :" << END_C << std::endl;
	if (channels.size() == 0)
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(cmd, chanNam), client.GetSock()), false);
	chanNam = cmd.substr(posHash,  posColon - posHash - 1);
	std::cout <<"Found channel name: \"" << MAGENTA << chanNam << END_C <<"\""<< std::endl;
	// Checking existence of channel
	size_t					i = 0;
	while (i < this->channels.size())
	{
		if (chanNam == this->channels[i].getName())
			break;
		i++;
	}
	// Channel not found
	if (i == this->channels.size())
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(cmd, chanNam), client.GetSock()), false);

	//No topic specified in client msg
	if (posColon == std::string::npos)
	{
		// No topic set in channel
		if (this->channels[i].getName().empty())
			return ((void)sendRPL(ERR_NOTOPIC(cmd, chanNam), client.GetSock()), false);
		else
		{
			std::cout << "OUI\n" << std::endl;
			return ((void)sendRPL(RPL_TOPIC(client.GetNick(), this->channels[i].getName(), this->channels[i].getTopic()), client.GetSock()), false);
		}
	}

	// Extracting topic name from cmd
	topicNam = cmd.substr(posColon + 1, cmd.find("\r") - posColon - 1);

	// Checking if the channel's topic is protected
	if (this->channels[i].getModes().find('t') != std::string::npos)
	{
		//if Yes, does the client has the right to change the topic ?
		for (size_t t = 0; t < this->channels[i].getOperators().size(); t++)
		{
			//if Yes, change the channel's topic
			if (this->channels[i].getOperators()[t] == client.GetSock())
			{
				this->channels[i].setTopic(topicNam);
				this->channels[i].send_topic_rpl(RPL_TOPIC(client.GetNick(), this->channels[i].getName(), this->channels[i].getTopic()));
				return (true);
			}
		}
		return ((void)sendRPL(ERR_CHANOPRIVSNEEDED(client.GetNick(), this->channels[i].getName()), client.GetSock()), false);
	}
	else
	{
		this->channels[i].setTopic(topicNam);
		//Send new topic to all clients
		for (size_t j = 0; j < this->channels[i].getClients().size(); j++)
		{	
			std::cout << "Sending topic... " << std::endl;
			sendRPL(RPL_TOPIC(getNameFromSock(this->channels[i].getClients()[j]), this->channels[i].getName(), this->channels[i].getTopic()), this->channels[i].getClients()[j] );
		}
		//sendRPL(RPL_TOPIC(client.GetNick(), this->channels[i].getName(), this->channels[i].getTopic()), client.GetSock());
		return (true);
	}
	std::cout << BLUE << "CHECK 3"  << std::endl;
	return (false);
}
