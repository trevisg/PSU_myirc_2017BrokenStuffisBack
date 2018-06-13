/*
** EPITECH PROJECT, 2018
** MALLOC
** File description:
**      Criterion assert tests for void *malloc(size_t) function
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../include/server.h"

Test(tests_SIGHANDLER_FUNCTION, sig_handler)
{
	pid_t cpid, w;
	int status;

	if (!(cpid = fork())) {
		signal(SIGINT, sig_handler);
		kill(getpid(), SIGINT);
	} else {
		w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		if (w != -1) {
			cr_assert_eq(WEXITSTATUS(status), 0);
		}
	}
}
