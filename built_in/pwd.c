/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetan <jetan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:36:36 by jetan             #+#    #+#             */
/*   Updated: 2024/11/02 16:10:16 by jetan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	else
		return (perror("pwd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
// int main()
// {
// 	ft_pwd();
// }