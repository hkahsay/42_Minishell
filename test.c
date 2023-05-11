/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:58:55 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/11 13:02:15 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main()
{
	for (int i = 0; i < 1000; i++ )
	{
		int fd = open("b", O_RDONLY);
		int fd2 = open("a", O_RDONLY);
		printf("%i %i\n", fd, fd2);
		close(fd);
		close(fd2);
	}
}