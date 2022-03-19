/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:48:52 by jiskim            #+#    #+#             */
/*   Updated: 2022/03/16 08:55:16 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_box	box;
	char	*line_read;

	initiate_env_lst(&(box.env_lst), envp);
	line_read = (char *)NULL;
	if (argc > 1)
		exit_with_err(argv[1], strerror(ENOENT), 127);
	while (1)
	{
		if (line_read)
		{
			free(line_read);
			line_read = (char *)NULL;
		}
		line_read = readline("딸기쉘🍓$ ");
		if (line_read == NULL)
			printf("null returned.");
		if (line_read && *line_read)
		{
			if (!ft_strncmp(line_read, "exit", 5))
				break ;
			add_history(line_read);
			// printf("%s\n", line_read);
			parse(line_read, envp);
		}
	}
	free(line_read);
	line_read = (char *)NULL;
    return (0);
}
