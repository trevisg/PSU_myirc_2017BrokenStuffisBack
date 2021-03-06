/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** my_irc server t_userlist and t_channel lists helpers functions
*/

#include "../include/server.h"
#include <stdlib.h>

unsigned int get_size(cmdargs args)
{
	unsigned int i = 0;
	while (args[i])
		++i;
	return (i);
}


/** Find a t_user structure pointer if clientfd exist inside
* @param list the full userlist
* @param clifd the 'to find' client fd
* @return user if clientfd exist in the list
* @return NULL pointer if nothing found
*/
t_user	*find_user_by_fd(t_userlist *list, int clifd)
{
	t_user *usr = NULL;

	for (t_userlist *tmp = list; tmp; tmp = tmp->next) {
		if (tmp->user->clifd == clifd) {
			usr = tmp->user;
			break;
		}
	}
	return (usr);
}

/** Get the t_channel pointer by its name
* @param list the channel list
* @param channame the resquested channel
* @return a t_channel pointer if exists , NULL otherwise
*/
t_channel	*get_chan_by_name(t_channel *list, char *channame)
{
	t_channel *rt = NULL;

	for (t_channel *tmp = list; tmp; tmp = tmp->next) {
		if (!strcmp(tmp->channame, channame)) {
			rt = tmp;
			break;
		}
	}
	return (rt);
}

unsigned int	is_user_in_chan(int clifd, t_channel *chans)
{
	for (t_userlist *usrs = chans->users; usrs; usrs = usrs->next) {
		if (clifd == usrs->user->clifd) {
			printf("Chan name [%s] Is in list ? [%s]\n",
			chans->channame, usrs->user->nick);
			usrs->user->isco = false;
		}
	}
	return (1);
}

/** Find a user by name literaly
* @param name the name to find
*/
t_user	*find_user_by_name(const char *name, t_userlist *usrs)
{
	t_user *needle = NULL;

	for (t_userlist *foo = usrs; foo; foo = foo->next) {
		if (!strcmp(name, foo->user->nick) ||
		!strcmp(name, foo->user->rname)) {
			needle = foo->user;
			break;
		}
	}
	return (needle);
}
