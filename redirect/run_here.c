/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaul <jpaul@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:59:48 by jpaul             #+#    #+#             */
/*   Updated: 2024/11/29 11:12:48 by jpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	prompt_heredoc(int *fd, char *delimiter);
static int	check_heredoc_signal(pid_t *pid, t_shell *data);

/* >>>run_heredoc
Purpose: Responsible to run through the tree and get heredoc input 
*/
int	run_here(t_tree *node, t_shell *data)
{
	t_token	*current;
	pid_t	pid;

	if (!node)
		return (0);
	current = node->token;
	while (current)
	{
		if (current->type == HERE)
		{
			if (pipe(current->herefd) < 0)
				err_exit("pipe", errno);
			pid = fork();
			if (pid < 0)
				err_exit("fork", errno);
			else if (pid == 0)
				prompt_heredoc(current->herefd, current->content);
			close(current->herefd[1]);
			if (check_heredoc_signal(&pid, data))
				return (1);
		}
		current = current->next;
	}
	return (run_here(node->left, data) || run_here(node->right, data));
}

static int	check_heredoc_signal(pid_t *pid, t_shell *data)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(*pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WTERMSIG(status) == SIGINT)
	{
		ft_printf("\n");
		data->cmd_exit_no = WTERMSIG(status) + 128;
		return (1);
	}
	return (0);
}

static void	prompt_heredoc(int *fd, char *delimiter)
{
	char	*input;

	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			err_msg_5(delimiter);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		if (!ft_strcmp(input, delimiter))
		{
			free(input);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
}
/*
int main()
{
	int herefd[2];
	int bytes_read;
	char buffer[1024];

	prompt_heredoc(herefd, "Hello");

	printf("Print Output\n=============\n");
	close(herefd[1]);
	while ((bytes_read = read(herefd[0], buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes_read);
	close(herefd[0]);
}
*/

/*
int main()
{
	t_shell data;

	char s[] = "<< EOF cat | echo \"Hello\" || 
		(echo Nice << DOOM) > file/out << YES  && ls << DONE  << OK";

	data.input = s;
	tokenize(&data);
	build_ast(&data);
	show_tree(data.tree, 0);
	run_heredoc(data.tree);
	destroy_tree(data.tree);
}
*/