/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:17:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/05 03:19:03 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

t_list	*ft_lstadd(t_list *lst, void *content)
{
	t_list	*newlist;

	newlist = ft_lstnew(content);
	if (!newlist)
		return (0);
	ft_lstadd_front(&lst, newlist);
	return (lst);
}
