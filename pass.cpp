/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:26 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 18:02:55 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::pass(client &client, std::string cmd)
{
	if (cmd != this->mdp || client.GetSetup() != 1)
		return (0);
	client.SetPass(cmd);
	client.SetSetup(2);
	return (1);
}
