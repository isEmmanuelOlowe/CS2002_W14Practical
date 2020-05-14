/*
 * TestStack.c
 *
 * Very simple unit test file for Stack functionality.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Stack.h"
#include "myassert.h"


#define MAX_STACK_SIZE 20

/*
 * The stack to use during tests
 */
static Stack *stack;

/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;

/**
* The generic type
*/
typedef void genericType;

/*
 * Setup function to run prior to each test
 */
void setup(){
	stack = new_Stack(MAX_STACK_SIZE);
	total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
	Stack_destroy(stack);
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
 * Checks that the Stack constructor returns a non-NULL pointer.
 */
int newStackIsNotNull() {
	assert(stack != NULL);
	return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty stack is 0.
 */
int newStackSizeZero() {
	assert(Stack_size(stack) == 0);
	return TEST_SUCCESS;
}


/*
 * Write more of your own test functions below (such as pushOneElement, pushAndPopOneElement, ...)
 * to help you verify correctness of your Stack
 */

 /*
 * Checks the stack is empty on creation.
 */
 int newStackIsEmpty() {
	 assert(Stack_isEmpty(stack) == true);
	 return TEST_SUCCESS;
 }

/*
* Checks pop operation fails when the stack is empty.
*/
int newStackPopFails() {
	assert(Stack_pop(stack) == NULL);
	return TEST_SUCCESS;
}


/*
* Can't push NULL Elemenents to the stack.
*/
int cantPushNull() {
	assert(Stack_push(stack, NULL) == false);
	return TEST_SUCCESS;
}


/*
* Pushing a generic to the stack.
*/
int pushTest() {
	genericType* element = (genericType *) 1;
	assert(Stack_push(stack, element) == true);
	return TEST_SUCCESS;
}

/*
* Checks if the size is one after adding 1 element.
*/
int sizeIsOne() {
	genericType* element = (genericType *) 1;
	Stack_push(stack, element);
	assert(Stack_size(stack) == 1);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is non empty after adding one element.
*/
int stackNonEmpty() {
	genericType* element = (genericType *) 1;
	Stack_push(stack, element);
	assert(Stack_isEmpty(stack) == false);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is empty as clearing it.
*/
int stackClearWorks() {
	genericType* element = (genericType *) 1;
	Stack_push(stack, element);
	Stack_clear(stack);
	assert(Stack_isEmpty(stack) == true);
	return TEST_SUCCESS;
}

/*
* Checks if the Pop Works correctly as element is pushed.
*/
int stackPopWorks() {
	genericType* element = (genericType *) 1;
	Stack_push(stack, element);
	assert(Stack_pop(stack) == element);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is empty after element is pushed and then popped from a new stack.
*/
int stackPopMakesStackEmpty() {
	genericType* element = (genericType *) 1;
	Stack_push(stack, element);
	Stack_pop(stack);
	assert(Stack_isEmpty(stack) == true);
	return TEST_SUCCESS;
}

/*
* Pushes to a full stack.
*/
int pushPastFull() {
	genericType* element = (genericType *) 1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		Stack_push(stack, element);
	}
	assert(Stack_push(stack, element) == false);
	return TEST_SUCCESS;
}

/*
* Checks if the stack can reach the full size
*/
int pushPastMaxSize() {
	genericType* element = (genericType *) 1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		Stack_push(stack, element);
	}
	assert(Stack_size(stack) == MAX_STACK_SIZE);
	return TEST_SUCCESS;
}

int orderPreserved() {
	bool correct = true;
	genericType* elements[MAX_STACK_SIZE];
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		elements[i] = (genericType *) i;
		Stack_push(stack, elements[i]);
	}

	for (int i = MAX_STACK_SIZE - 1; i > 0; i--) {
		if (Stack_pop(stack) != elements[i]) {
			correct = false;
		}
	}
	assert(correct == true);
	return TEST_SUCCESS;
}
/*
 * Main function for the Stack tests which will run each user-defined test in turn.
 */

int main() {
	runTest(newStackIsNotNull);
	runTest(newStackSizeZero);
	runTest(newStackIsEmpty);
	runTest(newStackPopFails);
	runTest(cantPushNull);
	runTest(pushTest);
	runTest(sizeIsOne);
	runTest(stackNonEmpty);
	runTest(stackClearWorks);
	runTest(stackPopWorks);
	runTest(stackPopMakesStackEmpty);
	runTest(pushPastFull);
	runTest(pushPastMaxSize);
	runTest(orderPreserved);
	/*
	 * you will have to call runTest on all your test functions above, such as
	 *
	 * runTest(pushOneElement);
	 * runTest(pushAndPopOneElement);
	 *
	 */

	printf("Stack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
