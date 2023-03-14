/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:48:47 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 20:57:48 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char	hash;
	int		left;
	char	filled;
	char	sign;
	int		width;
	char	dot;
	int		percision;
	int		conv;
	int		len;
}		t_info;

int		ft_printf_init(const char **str, va_list *ap);
void	ihatenorm(int *len, int *result);
int		pferror(int result, int *len);
int		ft_printf(const char *str, ...);
void	info_init(t_info *info);

int		flag_init(const char **str, t_info *info);
int		flag_atoi(const char **str, t_info *info, char w);
int		flag_conversion(const char **str, t_info *info);

int		ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, int n);
void	dtoh(unsigned long p, char *temp_string, int *len, int option);
void	dtoa(long long nbr, char *temp, int *len);
int		print_init(t_info *info, va_list *ap);

int		p_c(t_info *info, va_list *ap);
int		p_c_value(char c);
int		p_c_filled(t_info *info);

int		p_s(t_info *info, va_list *ap);
int		p_s_filled(t_info *info);
int		p_s_value(t_info *info, char *s);

int		p_p(t_info *info, va_list *ap);
int		p_p_return(t_info *info, char *temp);
int		p_p_value(t_info *info, char *temp);
int		p_p_filled(t_info *info);

int		p_id(t_info *info, va_list *ap);
int		p_id_return(t_info *info, char *temp);
void	p_id_abs(long long *nbr, t_info *info);
int		p_id_filled(t_info *info);
int		p_id_value(t_info *info, char *temp);

int		p_u(t_info *info, va_list *ap);
int		p_u_return(t_info *info, char *temp);
int		p_u_value(t_info *info, char *temp);
int		p_u_filled(t_info *info);

int		p_x(t_info *info, va_list *ap);
int		p_xu(t_info *info, va_list *ap);
int		p_x_return(t_info *info, unsigned long x, char *temp, int option);
int		p_x_value(t_info *info, unsigned long x, char *temp, int option);
int		p_x_value2(t_info *info, char *temp, int option);
int		p_x_filled(t_info *info);

int		p_per(t_info *info);
#endif