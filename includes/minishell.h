/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:42 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/23 11:53:15 by hbenazza         ###   ########.fr       */
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

typedef struct shell
{
	char			**cmd;
	char			*file_name;
	int				input_fd;
	int				output_fd;
	t_token			*token;
	char			*mask;
	struct shell	*next;
}	t_shell;

typedef struct s_env
{
	char			*env_var;
	struct s_env	*next;
}	t_env;

//reading from the prompt and passing the envirement
int		reading_promp(char **env);

//libft function
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
t_shell	*ft_lstnew(char *str);
void	ft_lstadd_back(t_shell **lst, t_shell *new);

//to create a linked list for the envirement
t_env	*ft_lstnew2(char *str);
void	ft_lstadd_back2(t_env **lst, t_env *new);

//parcings
t_shell	*create_list(char *input);
t_shell	*parsing(char *inputs);
int		parcing_pipe(t_token *token, char *mask);
void	parser_error(void);

//lexer with masking
t_shell	*lexer(char *inputs);
void	masking(char *str, int i, char c);
int		len_token(char *m);
char	*cmd_mask(char *str);
void	cmd_tokens(char mask, t_token *t, int i);

//execution
int		history(char *str);
void	*execute(t_shell *cmds, char **env);
int		ft_pwd(t_shell *shell);
int		ft_exit(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_strcount(char *s, char chr);
int		excute_cmd(t_shell *cmds);

//clean up memory
void	clean_up(t_shell *shell);
void	free_array(char **v);

#endif
