#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
#include <string.h> /// 7aydha
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# define ERROR 1
# define SUCCESS 0

/*-------colors-------*/
#define RST "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BOLD_CYAN "\033[1;36m"
/*....................*/

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
	EQUAL = 10,
	APPEND = 11,
	DELIMET = 12,
	HERDOC = 13
}	t_token;

typedef struct t_data
{
	int		exit_status;
}	t_data;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	t_token				type;
	char				*file_name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct shell
{
	char				**cmd;
	char				**envp;
	int					pid;
	int					input_fd;
	int					output_fd;
	int					*list_quotes;
	struct shell		*next;
	struct s_redirect	*redirection;
	struct s_env		*env;
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
int 	handel_redirection(t_shell *cmds);
int		open_pipes(t_shell *cmd, int pipe_fd[2]);
int		run_execution(t_shell *cmds);
int		run_execution1(t_shell *cmds);
int		close_fd(int fd1, int fd2);
int		execute(t_shell *cmds);
char	*get_cmd(char *cmd, char **envp);
int		history(char *str);
int		reading_promp(char **env);
int		execute_cmd(t_shell *cmds);
char	**lst_arr(t_shell *shell);
/*------------------------*/

/*---------herdoc---------*/
int	handle_heredoc(t_shell *cmds);
/*........................*/
/*--------built-in--------*/
int		if_built_in_run(t_shell *tmp);
int		is_built_in(t_shell *tmp);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_exit(t_shell *shell);
int		ft_env(t_env *shell);
int		ft_export(t_shell *shell);
/*------------------------*/

/*--------clean-up--------*/
void	clean_up(t_shell *shell);
void	clean_lst(t_env *shell);
int		free_array(char **v);
void	clean_redirect(t_shell *shell);
/*------------------------*/

/*--------help_fct--------*/
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
char		**ft_split(char *s, char c);
t_shell		*ft_lstnew(char *str);
t_env		*ft_lstnew2(char *str);
t_shell		*create_list(char *input);
void		ft_lstadd_back(t_shell **lst, t_shell *new);
void		ft_lstadd_back2(t_env **lst, t_env *new);
int 		lstsize(t_env *cmd);
int			ft_strncmp(char *s1, char *s2);
int			ft_strnncmp(char *s1, char *s2, size_t len);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strchr(char *s, int c);
int			ft_strcount(char *s, char chr);
char		*ft_strjoin2(int size, char **strs, char *sep);
t_redirect	*ft_lstnew_redirect(char *str, char *file);
void		ft_lstadd_back3(t_redirect **lst, t_redirect *new);
void		redirections_lst(t_shell *shell);
t_redirect	*create_redirect_lst(char **cmd, int *i);
char		*ft_strjoin_no_free(char *s1, char *s2);
/*------------------------*/

#endif
