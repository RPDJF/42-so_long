/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:03:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

static unsigned int	inputparser(int n)
{
	unsigned int	output;

	if (n < 0)
		output = -n;
	else
		output = n;
	return (output);
}

char	*ft_itoa_base(int n, const char *base)
{
	char			*p;
	unsigned int	temp;
	int				isneg;
	int				len;

	isneg = 0;
	if (n < 0)
		isneg = 1;
	temp = inputparser(n);
	len = 0;
	while (++len, temp >= ft_strlen(base))
		temp /= ft_strlen(base);
	p = (char *)ft_calloc(len + 1 + isneg, sizeof(char));
	if (!p)
		return (0);
	temp = inputparser(n);
	while (len-- > 0)
	{
		p[len + isneg] = base[temp % ft_strlen(base)];
		temp /= ft_strlen(base);
	}
	if (isneg)
		p[0] = '-';
	return (p);
}
