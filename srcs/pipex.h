/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:03:44 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 16:47:41 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#  define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

/*ERRORS_HANDLER_C*/
int		malloc_err();
int		fork_err();
int		pipe_err();
int		error_input(char *arg, int i, int n_cmd);

/*MAIN_C*/
void close_waitall(int n_cmd, int *wait_list, int *fd_io);
int classic_manager(int argc, char **argv, char **env);
int heredoc_manager(int argc, char **argv, char **env);
int main(int argc, char **argv, char **env);

/*PATH_CMD_C*/
char	*allocate_path(int i,char *str, char *cmd);
char	*set_path(char *selected_path, int i, int j, char *cmd);
char	*find_accessible_path(char *str, char *cmd);
int		check_cmd_validity(char **env, char *cmd);
int		execute_cmd(char *cmd, char **env);

/*REDIRECT_CMD_C*/
int create_pipe(char *command, char **env);
void put_in_pipe(char **argv, int *pipe_fd);
int create_here_doc_pipe(char **argv);
int last_command(int argc,char **argv, char **env, int fd_out);

/*UTILS_C*/
int get_cmd_size(char *cmd);
char *srchstrsn(char **lst_haystack, char *needle, int len);
int str_cmp(char *str1, char *str2);
int get_n_cmd(int argc, char **argv);

# endif