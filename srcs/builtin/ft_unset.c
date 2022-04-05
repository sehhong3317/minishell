/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 08:21:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/04 19:20:27 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_node(t_list **ptr)
{
	if (*ptr)
	{
		free((*ptr)->content);
		(*ptr)->content = NULL;
		free(*ptr);
		*ptr = NULL;
	}
}

static	void	delete_node(t_list **env_list, char *key)
{
	t_list	*curr;
	t_list	*del_node;

	curr = *env_list;
	if (!*env_list)
		return ;
	if (is_same_key(curr->content, key))
	{
		*env_list = curr->next;
		free_node(&curr);
		return ;
	}
	while (curr->next)
	{
		if (is_same_key(curr->next->content, key))
		{
			del_node = curr->next;
			curr->next = del_node->next;
			free_node(&del_node);
			return ;
		}
		curr = curr->next;
	}
}

// TODO 특수기호 $ 최종확인 필요
int	ft_unset(t_list **env_list, char **argv)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	argv++;
	if (*argv && is_option(*argv, "unset"))
		return (2);
	while (*argv)
	{
		if (!is_valid_key(*argv) || ft_strchr(*argv, '='))
		{	
			print_err2("unset", *argv, "not a valid identifier");
			exit_code = EXIT_FAILURE;
		}
		else
			delete_node(env_list, *argv);
		argv++;
	}
	return (exit_code);
}
