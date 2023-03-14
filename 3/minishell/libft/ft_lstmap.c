/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:34:40 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/08 15:47:44 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*back;
	t_list	*front;
	t_list	*temp;

	front = ft_lstnew(f(lst->content));
	if (!front)
		return (0);
	back = front;
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstnew(f((lst)->content));
		if (!temp)
		{
			ft_lstclear(&front, del);
			return (0);
		}
		back->next = temp;
		back = temp;
		lst = lst->next;
	}
	return (front);
}
