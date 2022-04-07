/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:07:41 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/08 03:28:21 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TC_SIGNAL_H
# define TC_SIGNAL_H

void	sigint_handler_p(int signum);
void	sigint_handler_c(int signum);

// void	sigquit_handler(int signum);

/* 커서 제어 관련 함수 -> 안쓸것같음...ㅠㅠ
void	initial_config(void);
void	get_cursor_pos(int *x, int *y);
void	action_for_eof(void);
*/

void	off_echoctl(void);
void	on_echoctl(void);

#endif