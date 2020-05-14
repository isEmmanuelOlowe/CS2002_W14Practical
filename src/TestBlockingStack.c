/*
 * TestStack.c
 *
 * Very simple unit test file for BlockingStack functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include "BlockingStack.h"
#include "myassert.h"


#define MAX_STACK_SIZE 20

/*
 * The stack to use during tests
 */
static BlockingStack *stack;

/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test
 */
void setup(){
	stack = new_BlockingStack(MAX_STACK_SIZE);
	total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
	BlockingStack_destroy(stack);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
	setup();

	if (testFunction()) success_count++;

	teardown();
}


/*
 * Two sample user-defined tests included below.
 * You will have to write many more tests.
 *
 * Each test function should return TEST_SUCCESS at the end.
 * Test functions can contain more than one assertion.
 *
 * If any assertion fails, the function name and line number
 * will be printed and the test will return a failure value.
 *
 * You will have to call runTest on your test functions in main below.
 */


/*
 * Checks that the BlockingStack constructor returns a non-NULL pointer.
 */
int newStackIsNotNull() {
	assert(stack != NULL);
	return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty blocking stack is 0.
 */
int newStackSizeZero() {
	assert(BlockingStack_size(stack) == 0);
	return TEST_SUCCESS;
}

/*
 * Write more of your own test functions below (such as pushOneElement, pushAndPopOneElement, ...)
 * to help you verify correctness of your BlockingStack
 */


/*
 * Main function for the BlockingStack tests which will run each user-defined test in turn.
 */

int main() {
	runTest(newStackIsNotNull);
	runTest(newStackSizeZero);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(pushOneElement);
     * runTest(pushAndPopOneElement);
     *
     */

	printf("\nBlockingStack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
