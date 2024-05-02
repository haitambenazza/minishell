/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:42 by hbenazza          #+#    #+#             */
/*   Updated: 2024/05/02 15:10:21 by hbenazza         ###   ########.fr       */
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
# include <signal.h>

typedef enum s_token
{
	CMD = 0,
	ESPACE = 1,
	PIPE = 2,
	REDIRECTION_IN = 3,
	REDIRECTION_OUT = 4,
	QUOTE = 5,
	SINGEL_Q = 6,
	FILE_NAME = 7,
	AND = 8,
}	t_token;

typedef struct shell
{
	char			**cmd;
	struct shell	*next;
	char			*file_name;
	int				input_output;
	int				number_cmd;
	t_token			*token;
}	t_shell;

int		reading_promp(void);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
t_shell	*parsing(char *inputs);
char	**ft_split(char const *s, char c);
t_shell	*ft_lstnew(char **cmd);
t_shell	*create_list(int len, char *input);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
int		history(char *str);
t_shell	*lexer(char *inputs);
void	*taha(t_shell *cmds);
void	masking(char *str, int i, char c);
char	*cmd_mask(char *str);
int		len_token(char *m);
void	cmd_tokens(char mask, t_token *t, int i);

#endif
