/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:54:37 by jetan             #+#    #+#             */
/*   Updated: 2024/12/10 14:54:37 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int				type;
	int				index;
	int				herefd[2];
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_pair
{
	t_token	*ob;
	t_token	*cb;
}	t_pair;

typedef struct s_tree
{
	int				type;
	int				*pipe;
	int				terminate;
	t_token			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_shell
{
	char	*input;
	t_env	*env;
	t_token	*token;
	t_tree	*tree;
	int		cmd_exit_no;
}	t_shell;

#endif