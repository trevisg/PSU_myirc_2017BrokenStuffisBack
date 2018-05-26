/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** my_irc server command parser source file
*/

#include "../include/server.h"
#include <stdlib.h>
#include <regex.h>

/** Free the token list */
static void free_tokens(cmdargs tkns)
{
	int i;

	for (i = 0; tkns[i]; ++i) {
		if (tkns[i][0])
			free(tkns[i]);
	}
}

/** Split received command(s) buffer in token(s)
* @note must implement circular buffer instead of 2d char array
* see [this ref](https://bit.ly/2s86kKz) for explanations and code exemple
*/
static char **get_tokens(char *req)
{
	int i = 0;
	char *str = NULL;
	char *arg = NULL;
	char **tokens = malloc(MAXARGS * sizeof(*tokens));

	str = strdup(req);
	arg = strtok(str, " \r\n");
	while (arg) {
		tokens[i] = malloc(MAXARGSIZE * sizeof(*tokens[i]));
		strncpy(tokens[i], arg, MAXARGSIZE);
		arg = strtok(NULL, " \r\n");
		++i;
	}
	free(str);
	return (tokens);
}

static char **get_commands(char *req)
{
	int i = 0;
	char *str = NULL;
	char *com = NULL;
	char **command = calloc(0, MAXARGS * sizeof(*command));

	str = strdup(req);
	com = strtok(str, "\r\n");
	while (com) {
		printf("comandParser :::%s\n", com);
		command[i] = malloc(MAXARGSIZE * sizeof(*command[i]));
		strncpy(command[i], com, MAXARGSIZE);
		com = strtok(NULL, "\r\n");
		i++;
	}
	//command[i + 1] = NULL; // to remoove
	free(str);
	return command;
}

/** Match all methods in G_CMDS for a given req command string
* @param req the requested command on format 'CMD <space> [ARGS]'
* @param clifd the client socket fd
*/
int	get_methods(char *req, int clifd)
{
	int index = 0;
	cmdargs args;
	char **tmp = NULL;
	int j = 0;

	tmp = get_commands(req);
	while (tmp[j])
	{
	args = get_tokens(tmp[j]);
	//print_arg(args);
	for (index = 0; G_PROTOS[index]; ++index) {
		if ((strcasestr(args[0], G_PROTOS[index]))) {
			if (G_CMDS[index] != NULL) {
				index = G_CMDS[index](args, clifd);
				break;
			}
		}
	}
	j++;
	}
	memset(req, 0, BUF_SIZE);
	free_tokens(args);
	return ((index == REF_NB) ? (0) : (index));
}
