/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** my_irc server source file
*/

#include "../include/server.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/** Self explanatory (here is the main())
* @param ac the number of received args
* @param av the received args, av[1] must be the server port
*/
int	main(int ac, char **av)
{
	int rt = 0;
	char *endptr = NULL;
	char *port = NULL;
	int val = 0;

	if (ac == 2) {
		port = av[1];
		val = strtol(port, &endptr, 10);
		signal(SIGINT, sig_handler);
		if (endptr != port  && val >= 1024)
			rt = server(av);
		else
			rt = 84;
	} else {
		fprintf(stderr, "%s: [port]\n", av[0]);
		rt = 84;
	}
	return (rt);
}
