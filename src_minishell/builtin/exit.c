/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:54:27 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/19 14:28:05 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_exit(char *cmd, t_config *ms_data)
{
	char	**cmds;
	int		size;
	long	error_code;

	cmds = ft_split_charset(cmd, WHITESPACES);
	if (!cmds)
	{
		perror("malloc");
		ms_data->last_error_code = ERROR_CODE;
		clear_minishell(ms_data);
	}
	size = 0;
	while (cmds[size])
		size++;
	if (size == 1)
	{
		ms_data->last_error_code = 0;
		ft_free_double_ptr(&cmds);
		clear_minishell(ms_data);
	}
	if (ft_strisnumber(cmds[1]) == false)
	{
		error_message(SHELL_NAME, cmds[1], ": numeric argument required");
		ft_free_double_ptr(&cmds);
		ms_data->last_error_code = 2;
		clear_minishell(ms_data);
	}
	else if (size > 2)
	{
		error_message(SHELL_NAME, cmds[1], ": too many arguments");
		ft_free_double_ptr(&cmds);
		ms_data->last_error_code = 1;
		clear_minishell(ms_data);
	}
	error_code = ft_atol(cmds[1]);
	error_code = error_code % 256;
	ft_free_double_ptr(&cmds);
	ms_data->last_error_code = (int)error_code;
	clear_minishell(ms_data);
}
