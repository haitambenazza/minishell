/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:45:07 by tkoulal           #+#    #+#             */
/*   Updated: 2024/05/25 02:01:30 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

typedef enum s_token
{
	CMD = 0,
	ESPACE = 1,
	PIPE = 2,
	RED_IN = 3,
	RED_OUT = 4,
	QUOTE = 5,
	SINGEL_Q = 6,
	FILE_NAME = 7,
	AND = 8,
	DOLLAR = 9,
	EQUAL = 10
}	t_token;

typedef	struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct shell
{
	char			**cmd;
	char			*file_name;
	int				input_fd;
	int				output_fd;
	int				pipe[2];
	t_token			*token;
	char			*mask;
	struct shell	*next;
	struct s_env	*env;
}	t_shell;

/*------- parsing --------*/
t_shell	*parsing(char *inputs);
int		parcing_pipe(t_token *token, char *mask);
void	parser_error(void);
int		len_token(char *m);
void	cmd_tokens(char mask, t_token *t, int i);
t_shell	*lexer(char *inputs);
void	masking(char *str, int i, char c);
char	*cmd_mask(char *str);
/*------------------------*/

/*--------excution--------*/
void	*execute(t_shell *cmds);
int		history(char *str);
int		reading_promp(char **env);
int		execute_cmd(t_shell *cmds);
/*------------------------*/

/*--------built-in--------*/
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_exit(t_shell *shell);
int		ft_env(t_env *shell);
int		ft_export(t_shell *shell);
/*------------------------*/

/*--------clean-up--------*/
void	clean_up(t_shell *shell);
void	clean_lst(t_env *shell);
void	free_array(char **v);
/*------------------------*/

/*--------help_fct--------*/
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	**ft_split(char *s, char c);
t_shell	*ft_lstnew(char *str);
t_env	*ft_lstnew2(char *str);
t_shell	*create_list(char *input);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
void	ft_lstadd_back2(t_env **lst, t_env *new);
int 	lstsize(t_shell *cmd);
int		ft_strncmp(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
int		ft_strcount(char *s, char chr);
/*------------------------*/

#endif
