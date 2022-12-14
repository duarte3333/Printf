/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:47:17 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/10/22 12:47:17 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int i)
{
	if ((i >= 0 && i <= 127))
		return (1);
	return (0);
}

// int main(void)
// {
//     printf("%i", ft_isascii(65));
// } 