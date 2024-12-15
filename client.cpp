/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/05/14 11:16:04 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//-------------------- Cons/Des ---------------------------------------------//
IRC::client::client()
{
	this->sock = 0;
	this->setup = 0;
};

IRC::client::client(int sock)
{
	//std::cout << "Default client constructor called" << std::endl;
	this->sock = sock;
	this->setup = 0;
};

//-------------------- Getters ---------------------------------------------//
int 		IRC::client::GetSock()
{
	return (this->sock);
}

std::string IRC::client::GetPass()
{
	return (this->pass);
}

std::string IRC::client::GetNick()
{
	return (this->nick);
}

std::string IRC::client::GetUser()
{
	return (this->user);
}

std::string	IRC::client::GetBuffer() const
{
	return this->buffer;
}

int			IRC::client::GetSetup() const
{
	return this->setup;
}

//-------------------- Setters ---------------------------------------------//
void 		IRC::client::SetBuffer(std::string buf)
{
	this->buffer = buf;
}

void 		IRC::client::SetPass(std::string pas)
{
	this->pass = pas;
}

void 		IRC::client::SetNick(std::string nic)
{
	this->nick = nic;
}

void 		IRC::client::SetUser(std::string use)
{
	this->user = use;
}

void 		IRC::client::SetSetup(int x)
{
	this->setup = x;
}

int			IRC::client::getFlag(){
	return (this->flag);
};
void			IRC::client::setFlag(int fl){
	this->flag = fl;
};
std::string		IRC::client::getoldnick(){
	return this->oldNick;	
};
			
void			IRC::client::setoldnick(std::string fl){
	this->oldNick = fl;
};
