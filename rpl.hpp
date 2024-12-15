#pragma once

#include <string>

#define CRLF "\r\n"

//-------------------- RPLS --------------------------------------------------//
#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_TOPIC(nickname, channelName, topic) (": 332 " + nickname + " " + channelName + " :" + topic + CRLF)
#define RPL_CHANGEMODE(hostname, channelname, mode, arguments) (":" + hostname + " MODE " + channelname + " " + mode + " " + arguments + CRLF)

//---------- /INVITE
#define RPL_INVITE(user_id, invited, channel) (user_id + " INVITE " + invited + " :" + channel + "\r\n")
#define RPL_INVITING(client, nick, channel) (":localhost 341 " + client + " " + nick + " " + channel + "\r\n")
#define RPL_INVITINGCHANMSG(client, chan) (":localhost 341 " + client + " " + chan + " :HEYYYYYYY" + CRLF)
#define RPL_INVITING2(inviter, invitee, channel) (":localhost 341 " + inviter + " " + invitee + " " + channel + "\r\n")
#define RPL_INVITENOTICE(client, channel) (":localhost NOTICE " + channel + " :" + client + " has been invited the channel" + CRLF)

//---------- /JOIN
#define RPL_JOIN(nick, channelName) (":" + nick + "!" + nick + "@" + "localhost" + " JOIN " + channelName + CRLF)
#define RPL_NAMREPLY(client, channel, list) (":localhost 353 " + client + " = " + channel + " :" + list + CRLF)
#define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list" + CRLF)

//---------- /PRIVMSG
#define RPL_PRIVMSG(nick, user, target, msg) (":" + nick + "!" + user + "@localhost PRIVMSG " + target + " :" + msg + CRLF)

//---------- /CAP
#define RPL_CAPLS()(":localhost 451 * :You have not registered \r\n")

//---------- /PART
#define RPL_PART(user_id, channel, reason) (user_id + " PART " + channel + " " + reason + "\r\n")
#define RPL_PARTNOTICE1(client, channel) (":localhost NOTICE " + channel + " :" + client + " has left the channel" + CRLF)
#define RPL_PARTNOTICE2(client, channel) (":localhost NOTICE " + client + " :You're not in the channel " + channel + CRLF)

//---------- /MODES
#define RPL_MODE(user_id, channel, modeset, target) (user_id + " MODE " + channel + " " + modeset + " " + target + "\r\n")

//---------- /QUIT
#define RPL_QUIT(user_id, reason) (user_id + " QUIT " + reason + "\r\n")

//---------- /KICK
# define RPL_KICK(user_id, channel, kicked, reason) (user_id + " KICK " + channel + " " + kicked + " " + reason + "\r\n")

//-------------------- RPLS ERR ----------------------------------------------//
#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + CRLF)
#define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters given" + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )
#define ERR_NOTOPERATOR(nickname) (": 482 " + nickname + " :You're not a channel operator" + CRLF)
#define ERR_NOSUCHCHANNEL(channel) (":localhost 403 " + channel + " :No such channel" + "\r\n")
#define ERR_CHANNELNOTFOUND(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel" + CRLF)
#define ERR_CHANOPRIVSNEEDED(nickname, channelname) (": 482 " + nickname + " " + channelname + " :You're not channel operator" + CRLF)
#define ERR_NEEDMOREPARAMS(nickname, cmd) (": 461 " + nickname + " " + cmd + " :Not enough parameters" + CRLF)
#define ERR_NOTOPIC(nickname, channelname) (": 331 " + nickname + " " + channelname + " :No topic is set" + CRLF)
#define ERR_NOSUCHNICK(nickname, nonUser) (":localhost 401 " + nickname + " " + nonUser + " :no such nickname" + CRLF)
#define ERR_USERONCHANNEL(client, nick, channel) (":localhost 343 " + client + " " + nick + " " + channel + " :is already on channel" + CRLF)
#define ERR_INVITEONLYCHAN(nickname, channel) (":localhost 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + CRLF)
#define ERR_BADCHANNELKEY(client, channel) (":localhost 475 " + client + " " + channel + " :Cannot join channel (+k)" + CRLF)
#define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)" + "\r\n")
#define ERR_USERNOTINCHANNEL(client, nickname, channel) (":localhost 441 " + client + " " + nickname + " " + channel + " :They aren't on that channel" + CRLF)
#define userID(nickname, username) (":" + nickname + "!" + username + "@localhost")
#define NICKNAMEINUSE_ERR(username) (":localhost 433 * " + username + " :Nickname is already in use." + CRLF)