/*
** EPITECH PROJECT, 2018
** MALLOC
** File description:
**      Criterion assert tests for void *malloc(size_t) function
*/

#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../include/server.h"

Test(tests_USERLIST_FUNCTIONS, get_new_user)
{
	char *MOCKARGS[MAXARGS] = {"USER", "Mockme", "0", "*", ":Mock User"};
	t_user *mockuser = NULL;

	mockuser = get_new_user(2, MOCKARGS);
	cr_assert_neq(mockuser, NULL, "Assert new user to be not NULL");
	cr_assert_str_not_empty(mockuser->nick, "Assert usr->nick to be a non empty string");
	cr_assert_str_not_empty(mockuser->rname, "Assert usr->rname to be a non empty string");
	cr_assert_eq(mockuser->clifd, 2, "Assert usr->clifd = 2");
	cr_assert_str_eq(mockuser->nick, "Mockme", "Assert usr->nick = \"Mockme\"");
	cr_assert_str_eq(mockuser->rname, ":Mock User""Assert usr->rname = \":Mock User\"");
}

Test(tests_USERLIST_FUNCTIONS, get_new_user_node)
{
	char *MOCKARGS[MAXARGS] = {"USER", "Mockme", "0", "*", ":Mock User"};
	t_user *mockuser = NULL;
	t_userlist *chk = NULL;

	mockuser = get_new_user(2, MOCKARGS);
	chk = get_new_userlist(mockuser);
	cr_assert_neq(chk, NULL);
	cr_assert_eq(chk->prev, NULL);
	cr_assert_eq(chk->next, NULL);
	cr_assert_neq(chk->user, NULL);
	free_userlist(chk);
}

Test(tests_USERLIST_FUNCTIONS, insert_back_user)
{
	char *MOCKARGS[MAXARGS] = {"USER", "Mockme", "0", "*", ":Mock User"};
	char *MOCK2[MAXARGS] = {"USER", "Momo", "0", "*", ":Momo User"};
	t_user *mockuser = NULL;
	t_user *mock2 = NULL;
	t_userlist *chk = NULL;
	t_userlist *tmp = NULL;

	mockuser = get_new_user(2, MOCKARGS);
	mock2 = get_new_user(2, MOCK2);
	chk = get_new_userlist(mockuser);
	tmp = get_new_userlist(mock2);
	chk = insert_back_user(chk, tmp);
	cr_assert_neq(chk, NULL);
	cr_assert_eq(chk->prev, NULL);
	cr_assert_neq(chk->next, NULL);
	cr_assert_neq(chk->user, NULL);
	cr_assert_neq(chk->next->user, NULL);
	free_userlist(chk);
}
