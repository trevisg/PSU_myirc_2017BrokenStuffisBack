/*
** EPITECH PROJECT, 2018
** MALLOC
** File description:
**      Criterion output params
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <errno.h>

#define BANNER "./tests/baneer.txt"

bool 	print_ascii()
{
	FILE	*f = fopen(BANNER, "r");
	char	c = 0;

	printf("\033[34m");
	if (f != NULL) {
		while ((c = getc(f)) != EOF) {
			printf("%c", c);
		}
	}
	printf("\033[0m");
	f ? fclose(f) : c;
	return true;
}

ReportHook(POST_TEST)(struct criterion_test_stats *stats)
{
	printf("For [\033[34m%s\033[0m] in category \033[1m%s\033[0m]\n",
		stats->test->name, stats->test->category);
	printf("%s ==> [%d passed, %d failed, %d total]\n\n",
		"\t[\033[1mAsserts:\033[0m]",
		stats->passed_asserts, stats->failed_asserts,
		stats->passed_asserts + stats->failed_asserts);
}

ReportHook(PRE_ALL)(struct criterion_test_set *tests)
{
	(void) tests;
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	puts("\n\n\t###### \033[1mTESTING\033[0m ######\n\t\t######");
}

ReportHook(POST_ALL)(struct criterion_global_stats *stats)
{
	print_ascii();
	printf("\t\tAll: \033[32m%li\033[0m, passed: \033[32m%li\033[0m, \
	Failed: \033[32m%li\033[0m\n",
		stats->nb_tests, stats->tests_passed, stats->tests_crashed);
}
