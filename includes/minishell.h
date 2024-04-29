/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:42 by hbenazza          #+#    #+#             */
/*   Updated: 2024/04/29 17:20:14 by hbenazza         ###   ########.fr       */
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
	REDIRECTION_IN,
	REDIRECTION_OUT,
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
int		parsing(char *inputs);
char	**ft_split(char const *s, char c);
t_shell	*ft_lstnew(void);
t_shell	*create_list(int len);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
int		history(char *str);
t_shell	*lexer(char *inputs);

#endif
