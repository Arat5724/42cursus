/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:05:58 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:23:37 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LMSHELL_H
# define LMSHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

# define APPEND
# define OVERWRITE

extern char	**g_envp;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_word	*words;
	struct s_cmd	*subshell;
	struct s_redir	*redirs;
	char			lflag;
	char			rflag;
	char			is_builtin;
	pid_t			pid;
}		t_cmd;

typedef struct s_word
{
	struct s_word	*next;
	char			*word;
}		t_word;

typedef struct s_redir
{
	struct s_redir	*next;
	char			*filename;
	char			info;
}		t_redir;

typedef struct s_redirio
{
	struct s_redir	*in;
	struct s_redir	*out;
}		t_redirio;

typedef struct s_token
{
	struct s_token	*next;
	struct s_char	*chars;
}		t_token;

typedef struct s_char
{
	struct s_char	*next;
	char			c;
}		t_char;

typedef struct s_stat
{
	int	quote;
	int	info;
	int	bracket;
}		t_stat;

int		ft_strlen2(char **words);

char	**ft_split_set(char const *s, char const *set);
void	free3(char ***str);
void	free2(char **str);

void	free_cmds(t_cmd *head);
void	free_words(t_word *words);
void	free_redirs(t_redir *redirs);

t_word	*word_new(char *word);
void	word_add_back(t_word **head, t_word *new);
t_redir	*redir_new(char *filename, char info);
void	redir_add_back(t_redir **head, t_redir *new);
t_cmd	*cmd_new(t_word *words, t_redir *redirs, char lflag, char rflag);
void	cmd_add_back(t_cmd **head, t_cmd *new);
t_char	*char_new(char c);
void	char_add_back(t_char **head, t_char *new);
t_token	*token_new(t_char *chars);
void	token_add_back(t_token **head, t_token*new);

void	free_char(t_char *c);
void	free_token(t_token *token);
void	parse_char_redir_pipe(
			char **str, t_stat *status, t_token **head, t_token **tail);
void	parse_char_and(
			char **str,	t_stat *status, t_token **head, t_token **tail);
void	parse_char_bracket(
			char **str,	t_stat *status, t_token **head, t_token **tail);
void	parse_char_quote(
			char **str,	t_stat *status, t_token **head, t_token **tail);
void	parse_char_space(
			char **str,	t_stat *status, t_token **head, t_token **tail);

t_cmd	*parse_cmds(char ***str);
int		parse_cmds_end(char ***str, char info, t_cmd **head, t_cmd **tail);
int		parse_cmds_bracket_open(char ***str,
			char info, t_cmd **head, t_cmd **tail);
int		parse_cmds_bracket_close(char ***str,
			char info, t_cmd **head, t_cmd **tail);
int		parse_cmds_word(char ***str, char info, t_cmd **head, t_cmd **tail);
int		parse_cmds_close(char ***str, t_cmd **head, t_cmd **tail);

void	parse_env(char **str, int exit_status);
void	parse_env_insert(char **str, int *i, int len, char *insert);

void	parse_wc(char **str);
void	parse_wc_join(char **result, char *filename);
int		parse_wc_suetent(char *wc, const char **words,
			const int wordslen, char *filename);
int		parse_wc_end(char *wc, const char **words,
			const int wordslen, char *filename);
int		parse_wc_end2(char *word, char *filename);
void	ft_reverse_str(char *str);

t_cmd	*cmd_init(void);
void	cmd_print(t_cmd *head);
void	cmd_free(t_cmd *head);

char	**join_token(t_token *token);

void	find_cmd(char **cmd);
void	execute_head(t_cmd *head, int *exit_status);
void	execute_cmd(t_cmd *cmds, int *fd, int *exit_status);

void	close_fd(int fd1, int fd2);
void	close_fd2(int *fd);

t_token	*parse_char(char **str);
void	free_token(t_token *token);

t_cmd	*parse(char *str, int *exit_status);

//builtin
void	ft_export1(char **words, int *exit_status);
void	ft_cd(char **words, int *exit_status);
void	ft_exit(char **words, int *exit_status);
void	ft_unset(char **words, int *exit_status);

void	ft_export_print(void);
int		get_key_size(char *str);
int		ft_export_find_key(char *key, int key_size);

void	ft_export2(char **words);
void	ft_echo(char **words);
void	ft_env(char **words);
void	ft_pwd(char **word);

void	handler(int signal);

//execute
int		execute_heredoc(char *eof);
int		execute_builtin_cmd(t_cmd *cmds, char **words, int *exit_status);
void	execute_is_builtin(t_cmd *cmds, char *result, int size);
void	execute_child_builtin(char **words);
void	execute_cmd_not_found(char *cmd);
int		if_end(t_cmd *cmds, int *exit_status);
void	execute_open_pipe(t_cmd *cmds, int *fd2);
void	execute_close_pipe(t_cmd *cmds, int *fd);
void	execute_waitpid(t_cmd *cmds);
void	execute_join_redir(t_redir *head, t_redirio *inout);
void	execute_redir_io(t_cmd *cmds, int *fd, int *fd2, t_redirio *inout);
char	**execute_join_words(t_cmd *cmds, t_word *head);
void	execute_subshell(t_cmd *cmds, int *exit_status);
#endif