/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:36:55 by jiskim            #+#    #+#             */
/*   Updated: 2022/04/06 16:58:07 by jiskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(t_token *token, t_ast *ptr)
{
	if (!(token->next) || token->next->type == PIPE
		|| !(ptr->left || ptr->right))
		return (-1);
	ptr->right = subtree_pipeseq();
	return (0);
}

static int	check_rdr(t_list *env_list, t_token *token, t_ast *ptr)
{
	char	*word;
	char	*filename;

	if (!(token->next) || token->next->type != WORD)
		return (-1);
	word = remove_quote(env_list, token->type, token->next->data);
	if (token->type == SYMBOL_HERE)
	{
		filename = launch_heredoc(env_list, word);
		free(word);
		word = filename;
	}
	if (ptr->left)
	{
		ptr = ptr->left;
		while (ptr->right != NULL)
			ptr = ptr->right;
		ptr->right = subtree_rdr(token->data, word);
	}
	else
		ptr->left = subtree_rdr(token->data, word);
	return (0);
}

static int	check_word(t_list *env_list, t_token *token, t_ast *ptr)
{
	char	*word;

	word = remove_quote(env_list, token->type, token->data);
	while (ptr->right != NULL)
		ptr = ptr->right;
	if (ptr->type == CMD)
	{
		ptr->data = word;
		ptr->right = subtree_simple_command(SIMPLE_CMD, word);
	}
	else
		ptr->right = subtree_simple_command(ARGV, word);
	return (0);
}

int	check_syntax(t_list *env_list, t_token **head, t_ast **ptr)
{
	int		result;

	if ((*head)->type == PIPE)
	{
		result = check_pipe(*head, *ptr);
		*ptr = (*ptr)->right;
	}
	else if ((*head)->type == SYMBOL || (*head)->type == SYMBOL_HERE)
	{
		result = check_rdr(env_list, *head, (*ptr)->left);
		if (!result)
			*head = (*head)->next;
	}
	else
		result = check_word(env_list, *head, (*ptr)->left);
	return (result);
}
