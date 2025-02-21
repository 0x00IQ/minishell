/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/15 17:51:45 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	tab_size(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	clean_env_vars(t_config *minishell)
{
	char	*oldpwd;
	char	pwd[MAX_PATH];
	char	**cmd;

	cmd = ft_calloc(sizeof(char *), 3);
	if (!minishell)
		return ;
	ft_bzero(pwd, MAX_PATH);
	cmd[0] = ft_strdup("export");
	if (getcwd(pwd, MAX_PATH) == pwd)
	{
		oldpwd = get_value_by_name(minishell->environnement, "PWD");
		cmd[1] = ft_strjoin("OLDPWD=", oldpwd);
		execute_export(cmd, minishell);
		ft_free_simple_ptr(&oldpwd);
		ft_free_simple_ptr(&cmd[1]);
		cmd[1] = ft_strjoin("PWD=", pwd);
		execute_export(cmd, minishell);
		ft_free_double_ptr(&cmd);
	}
}

void	execute_cd(char **cmd, t_config *minishell)
{
	if (!cmd || !minishell)
		return ;
	if (tab_size(cmd) >= 3)
	{
		minishell->last_error_code = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	else if (tab_size(cmd) == 1)
	{
		if (chdir(get_value_by_name(minishell->environnement, "HOME")) == -1)
		{
			ft_putstr_fd("bash: cd: HOME not set", 2);
			minishell->last_error_code = 1;
			return ;
		}
	}
	else if (tab_size(cmd) > 1 && chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		minishell->last_error_code = 1;
		return ;
	}
	else
	{
		minishell->last_error_code = 0;
		clean_env_vars(minishell);
	}
}
