/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:48:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/04/07 00:58:27 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiate_box(char **envp)
{
	g_box = (t_box *)ft_calloc(1, sizeof(t_box));
	while (*envp)
	{
		ft_lstadd_back(&(g_box->env_list), ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;

	initiate_box(envp);
	line_read = NULL;
	if (argc > 1)
		exit_with_err(argv[1], strerror(ENOENT), 127);
	while (1)
	{
		if (line_read)
			free_ptr((void **)&line_read);
		line_read = readline("딸기쉘🍓$ ");
		if (line_read && *line_read)
		{
			add_history(line_read);
			parse(line_read);
			printf("echo $? = %d\n", g_box->exit_code);
		}
	}
	free_ptr((void **)&line_read);
	return (0);
}
