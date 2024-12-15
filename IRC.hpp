/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:32:05 by jquil             #+#    #+#             */
/*   Updated: 2024/05/14 11:13:29 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

#include "colors.hpp"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ios>
#include <algorithm>
#include <signal.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <map>
#include <sstream>
#include <ctime>
#include <stack>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
#include <arpa/inet.h> // hton*, ntoh*, inet_addr
#include <unistd.h>  // close
#include <cerrno>
#include <poll.h>
// #include <sys/epoll.h>
#include "rpl.hpp"

class Channel;

class IRC
{	
	private :
	class client
	{
		private :
			int 						flag;
			std::string					pass;
			std::string					nick;
			std::string					user;
			std::string					buffer;
			int							setup;
			int							sock;
			std::vector<std::string>	current_channel;
			std::string 				oldNick;

		public :
		//------------------- Getters ---------------------------------------//
			int				getFlag();
			void			setFlag(int fl);
			std::string		getoldnick();
			void			setoldnick(std::string fl);
			int				GetSock();
			int				GetSetup() const;
			std::string 	GetPass();
			std::string 	GetNick();
			std::string 	GetUser();
			std::string		GetBuffer() const;
			std::string		GetCurrentChannel() const;

		//------------------- Setters ---------------------------------------//
			void			SetPass(std::string pas);
			void 			SetNick(std::string nic);
			void 			SetUser(std::string use);
			void			SetSetup(int x);
			void			SetCurrentChannel(std::string str);
			void			SetBuffer(std::string buf);

		//------------------- Cons/Des --------------------------------------//
							client();
							client(int sock);
	};
	class Channel
	{
		private:
			std::string				topic;
			std::string				name;
			std::string				modes;
			std::vector<int> 		invitations;
			std::vector<int>		operators;
			std::vector<int>		clients;
			std::string				channelPassword;
			int						limitClients;
			static bool				_signal;
			Channel(void);

		public:
		//------------------- Getters ---------------------------------------//
			std::string				getName(void);
			std::string				getTopic(void);
			std::vector<int>&		getOperators(void);
			std::vector<int>&		getClients(void);
			int&					getLimitClients(void);
			std::vector<int>&		getInvitations(void);
			std::string 			getModes(void);
			std::string&			getChannelPassword();

		//------------------- Setters ---------------------------------------//
			void					setInvitations(int& socket);
			void					setLimitClients(int limit);
			void 					setModes(char c);
			void					setName(std::string& name);
			void 					setPassword(std::string password);
			void					setTopic(std::string& topic);
			void					setClients(client& client);
			void					setOperators(int operateur);
			void 					delModes(char c);
			void					delOperators(int operateur);

		//------------------- Utils -----------------------------------------//
			bool					isOperator(int socket, std::vector<int> operators);
			bool					isClient(int sock);
			bool					isOperator(client &client);
			bool					isInvitation(int sock);
			//bool					isOperator(int sock);
			bool					remove_client(int sock);
			void					send_topic_rpl(std::string rpl);
			void					SignalHandler(int signum);
			Channel(std::string name, client &creator);
			~Channel();
	};
	class IrcException: public std::exception
	{
		private:
			const std::string 		_errMsg;
		
		public:
			IrcException(const std::string& msg): _errMsg(msg) {};
			virtual ~IrcException() throw() {};
			const char *what() const throw();
	};
		int							poll_count;
		int							poll_size;
		int							port;
		int							serv_sock;
		int							bind_sock;
		int							lstn;
		std::string 				oldNick;
		std::string 				mdp;
		socklen_t					peer_addr_size;
		struct sockaddr_in 			serv_struc, peer_addr;
		std::map<int, client>		users;
		std::map<std::string, bool (IRC::*)(client&, std::string)>	cmd;
		std::vector<struct pollfd>	poll_fds;
		std::vector<Channel> 		channels;
		bool						secure;
		static bool					_signal;
		std::string 				tmp;
		
	//------------------- SubClasses -----------------------------------------//
	
	
	public :
		void						setChannels(Channel &channels);
		void						ClearClients(int fd);
		std::vector<Channel>		*getChannel(void);
		IRC::client					getclientfromsock(int sock);

		//------------------- Modes -----------------------------------------//
		bool						capLs(client &client, std::string cmd);//OK
		bool						pass(client &client, std::string cmd);//OK
		bool						nick(client &client, std::string cmd);//OK
		bool						user(client &client, std::string cmd);//OK
		bool						privmsg(client &client, std::string cmd); // OK, a re-test
		bool						topic(client &client, std::string cmd); // Pb lie a join ?->initialisation du vector clients
		bool						mode(client &client, std::string cmd); // Pas fini
		bool						ping(client &client, std::string cmd); // OK
		bool						join(client &client, std::string cmd); // Bientot fini
		bool						part(client &client, std::string cmd); // Fait dans l'idee mais je m'en sors pas avec le msg pour que irssi reagisse
		bool						kick(client &client, std::string cmd); // fait MAIS a verifier + RPL a ajouter -> marche pas
		bool						quit(client &client, std::string cmd); // fait
		bool						invite(client &clients, std::string cmd); // RPL a ajouter
		
		//------------------- Funcs -----------------------------------------//
		void 						launch_serv(void);
		void						private_msg_chan(std::string msg, client &sender, std::string channelName);
		void 						manage_input(int fd);
		void						initCommand(void);
		void 						sendRPL(std::string rpl, int fd);
		int							cmd_used_name(std::string &name, int mode);
		bool						ChannelExist(std::string name);
		void						add_options(char c, int sign, std::string channelName);
		int							getSockFromName(std::string name);
		std::string					getNameFromSock(int fd);
		void						CloseFds();
		static void						SignalHandler(int signum);
		//	MODE
		bool						mode_opt(size_t idxChan, int sign , std::string pit , client &_client, char op);
		void 						handle_mode(client &_client, std::vector<char> &opt_vector, std::string channelName, std::vector<std::string> &param);
		void						private_msg_user(std::string msg, client &sender, std::string clients);
		//------------------- Cons/Des --------------------------------------//
									IRC(int port, std::string mdp);
									~IRC();
};
#endif
