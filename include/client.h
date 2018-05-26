/*
** EPITECH PROJECT, 2018
**
** File description:
**
*/

typedef struct s_client_epoll
{
	int epollfd;
	struct epoll_event event;
	struct epoll_event events[10];
} t_client_epoll;

typedef struct s_client_data
{
	t_client_epoll *client;
        char name[10];
} t_client_data;
