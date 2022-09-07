/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:48:05 by mochan            #+#    #+#             */
/*   Updated: 2022/09/07 16:17:32 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

time_t get_time_ms(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000)+(tv.tv_usec / 1000));
}
