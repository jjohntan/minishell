/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:46:56 by jetan             #+#    #+#             */
/*   Updated: 2024/11/13 17:46:56 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_env_node(t_env *env);

/* >>> unset
Description: Remove var from env listed-list
*/
int	ft_unset(char **arg, t_shell *data)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 0;
	while (arg[++i])
	{
		current = data->env;
		previous = NULL;
		while (current)
		{
			if (!ft_strcmp(arg[i], current->key))
			{
				if (previous)
					previous->next = current->next;
				else
					data->env = current->next;
				free_env_node(current);
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

static void	free_env_node(t_env *env)
{
	free(env->key);
	free(env->val);
	free(env);
}
/* Test
int main()
{
	t_shell data;

	t_env *n1 = (t_env *)malloc(sizeof(t_env));
	t_env *n2 = (t_env *)malloc(sizeof(t_env)); 
	t_env *n3 = (t_env *)malloc(sizeof(t_env));
	t_env *n4 = (t_env *)malloc(sizeof(t_env)); 
	t_env *n5 = (t_env *)malloc(sizeof(t_env));

	n1->key = strdup("HOME");
	n1->val = strdup("/home/jpaul");
	n1->next = n2;

	n2->key = strdup("USER");
	n2->val = strdup("Jason");
	n2->next = n3;

	n3->key = strdup("SHELL");
	n3->val = strdup("/bash/");
	n3->next = n4;

	n4->key = strdup("SHLVL");
	n4->val = strdup("1");
	n4->next = n5;

	n5->key = strdup("PWD");
	n5->val = strdup("/home/usr/Desktop");
	n5->next = NULL;

	data.env = n1;
	// char *a0[] = {"unset", NULL};
	// char *a1[] = {"unset", "SHELL=", NULL};
	// char *a2[] = {"unset", "3413423", "ewqeeq", NULL};

	char *a4[] = {"unset", "HOME", "SHELL", "3343242", NULL};
	// char *a5[] = {"unset", "SHELL", NULL};
	//char *a6[] = {"unset", "PWD", NULL};
	
	t_env *current = data.env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->val);
		current = current->next;
	}
	printf("\n======================\n");
	ft_unset(a4, &data);
	current = data.env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->val);
		current = current->next;
	}
	destroy_env(&data);
}*/