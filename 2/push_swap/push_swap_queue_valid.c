/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_queue_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:03:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 08:28:45 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//sa  : 0
//sb  : 1
//ss  : 2
//pa  : 3
//pb  : 4
//ra  : 5
//rb  : 6
//rr  : 7
//rra : 8
//rrb : 9
//rrr : 10
int	op_valid(int op1, int op2)
{
	if (op1 == 0 && (op2 == 0 || op2 == 1 || op2 == 2))
		return (0);
	else if (op1 == 1 && (op2 == 0 || op2 == 1 || op2 == 2))
		return (0);
	else if (op1 == 2 && (op2 == 0 || op2 == 1 || op2 == 2))
		return (0);
	else if (op1 == 3 && (op2 == 4))
		return (0);
	else if (op1 == 4 && (op2 == 3))
		return (0);
	else if (op1 == 5 && (op2 == 8 || op2 == 10))
		return (0);
	else if (op1 == 6 && (op2 == 9 || op2 == 10))
		return (0);
	else if (op1 == 7 && (op2 == 8 || op2 == 9 || op2 == 10))
		return (0);
	else if (op1 == 8 && (op2 == 5 || op2 == 7))
		return (0);
	else if (op1 == 9 && (op2 == 6 || op2 == 7))
		return (0);
	else if (op1 == 10 && (op2 == 5 || op2 == 6 || op2 == 7))
		return (0);
	return (1);
}
