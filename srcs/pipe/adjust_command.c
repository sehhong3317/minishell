/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:30:48 by sehhong           #+#    #+#             */
/*   Updated: 2022/03/19 22:22:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    adjust_command(t_box *box, t_ast *tree)
{
	if (tree->type == IO_HERE || tree->type == IO_RDR)
		redirect_files(tree);
	else if (tree->type == NAME)
		save_path(&box, tree);
	else if (tree->type == ARG)
		make_argv();
	adjust_command(box, tree->left);
	adjust_command(box, tree->right);
}