/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:30:43 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                LIBRARIES                                   */
/******************************************************************************/

/* Read Command */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Process and System Calls */
# include <sys/types.h>    /* For pid_t */
# include <sys/wait.h>     /* For wait() */
# include <unistd.h>       /* For pipe(), read(), write(), close(), fork() */

/* Memory Management */
# include <stdlib.h>       /* For exit(), free(), malloc() */

/* Error Handling */
# include <errno.h>        /* For errno variable */
# include <stdio.h>        /* For printf(), perror() */
# include <stdbool.h>

/* File Operations */
# include <fcntl.h>        /* For open(), O_RDONLY, O_WRONLY, etc. */

/* Custom Libraries */
# include "../libs/libft/include_libft/libft.h"
// # include "../libs/gnl/include_gnl/get_next_line.h"

// include pipes lib
# include "pipes.h"

/* Bool */
# include <stdbool.h>

/******************************************************************************/
/*                                CONSTANTS                                   */
/******************************************************************************/

# define ERROR_CODE 42      /* Generic error code */
# define ERROR_COMMAND 127  /* Command not found error code */
# define ENV_PARSING_ERROR 1
# define ENV_PARSING_OK 0
# define INIT_ERROR 1
# define INIT_OK 0

/******************************************************************************/
/*                                COLORS                                      */
/******************************************************************************/

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

/******************************************************************************/
/*                                STRUCTURES                                  */
/******************************************************************************/

typedef struct s_minishell
{
	char	*filename;
	int		fd_infile;
	int		fd_outfile;
	char	*path_name;
	char	**environnement;
	t_btree	*tree;
}	t_minishell;

typedef struct s_command
{
	char	*command;
	char	*flags; //lste de flags
	t_list	*arguments;
	bool	quotes;  // quotes == 1 (true) for "" or blank and quotes == 0 (false) for ''
}	t_command;

typedef struct s_envvar
{
	char	*name;
	char	*value;
}	t_envvar;

typedef	struct s_config {
	int		ac;
	char	**av;
	t_list	*environnement;
	t_list	*env_commands; // inutile ?
	char	*current_path;
	char	*prompt;
	int		last_error_code;
}	t_config;

// PARSING
typedef enum e_token
{
	PIPE, //
	R_LEFT, // <
	R_RIGHT, // >
	COMMAND,
}	t_token;

# define PIPECHAR		'|'
# define R_LEFTCHAR		'<'
# define R_RIGHTCHAR	'>'

# define SPECIALS_TOKEN	"|<>"
# define WHITESPACES	" \t\n\v\f\r"

typedef	struct s_cmd
{
	char	*cmd;
	bool	quotes;
}	t_cmd;

typedef struct s_node
{
	t_token	type;
	t_cmd	*cmd;
}	t_node;


/******************************************************************************/
/*                                PROTOTYPES                                  */
/******************************************************************************/

/* Add your function prototypes here */

// init
t_config	*init(int ac, char **av, char **env);
void		clear_minishell(t_config *minishell);
// // env
t_list		*init_environnement(char **env);
t_envvar	*ptr_to_envvar(void	*content);
char		*get_value_by_name(t_list *env, char *name);

// signals
void	init_signals(void);
t_btree	*arbre_bidon();

// parsing
t_btree	*parse_cmd(char *cmd);

// ast
void	construct_ast(t_btree **ast, char **cmd_split, int cmd_len);
t_btree	*create_special_node(t_token nodetype);
t_btree	*create_command_node(char **cmd_split);
void	clear_ast(t_btree *ast);

#endif /* MINISHELL_H */
