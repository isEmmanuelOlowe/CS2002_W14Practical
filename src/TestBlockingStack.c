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

/**
* The generic type
*/
typedef void genericType;

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
* Checks if the blocking stack is initially empty
*/
int newStackIsEmpty() {
  assert(BlockingStack_isEmpty(stack));
  return TEST_SUCCESS;
}

/*
* Can't push NULL Elemenents to the stack.
*/
int cantPushNull() {
	assert(BlockingStack_push(stack, NULL) == false);
	return TEST_SUCCESS;
}


/*
* Pushing a generic to the stack.
*/
int pushTest() {
	genericType* element = (genericType *) 1;
	assert(BlockingStack_push(stack, element) == true);
	return TEST_SUCCESS;
}

/*
* Checks if the size is one after adding 1 element.
*/
int sizeIsOne() {
	genericType* element = (genericType *) 1;
	BlockingStack_push(stack, element);
	assert(BlockingStack_size(stack) == 1);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is non empty after adding one element.
*/
int stackNonEmpty() {
	genericType* element = (genericType *) 1;
	BlockingStack_push(stack, element);
	assert(BlockingStack_isEmpty(stack) == false);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is empty as clearing it.
*/
int stackClearWorks() {
	genericType* element = (genericType *) 1;
	BlockingStack_push(stack, element);
	BlockingStack_clear(stack);
	assert(BlockingStack_isEmpty(stack) == true);
	return TEST_SUCCESS;
}

/*
* Checks if the Pop Works correctly as element is pushed.
*/
int stackPopWorks() {
	genericType* element = (genericType *) 1;
	BlockingStack_push(stack, element);
	assert(BlockingStack_pop(stack) == element);
	return TEST_SUCCESS;
}

/*
* Checks if the stack is empty after element is pushed and then popped from a new stack.
*/
int stackPopMakesStackEmpty() {
	genericType* element = (genericType *) 1;
	BlockingStack_push(stack, element);
	BlockingStack_pop(stack);
	assert(BlockingStack_isEmpty(stack) == true);
	return TEST_SUCCESS;
}

/*
* Checks if the stack can reach the full size
*/
int pushPastMaxSize() {
	genericType* element = (genericType *) 1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		BlockingStack_push(stack, element);
	}
	assert(BlockingStack_size(stack) == MAX_STACK_SIZE);
	return TEST_SUCCESS;
}

/*
* Checks LIFO order still preserved
*/
int orderPreserved() {
	bool correct = true;
	genericType* elements[MAX_STACK_SIZE];
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		elements[i] = (genericType *) i;
		BlockingStack_push(stack, elements[i]);
	}

	for (int i = MAX_STACK_SIZE - 1; i > 0; i--) {
		if (BlockingStack_pop(stack) != elements[i]) {
			correct = false;
		}
	}
	assert(correct == true);
	return TEST_SUCCESS;
}

/*
* Pops element using thread.
*/
void *threadPop(void *arg) {
  return BlockingStack_pop(stack);
}

/*
* Pushes elements using a thread.
*/
void *threadPush(void *arg) {
  BlockingStack_push(stack, arg);
  return NULL;
}

/*
* Checks if blocking has been correctly implemented for popping
*/
int blockedPop() {
  genericType* element = (void * )1;
  void* pop_r;
  pthread_t push, pop;
  pthread_create(&pop, NULL, threadPop, NULL);
  pthread_create(&push, NULL, threadPush, element);
  pthread_join(pop, &pop_r);
  pthread_join(push, NULL);
  assert(pop_r == element);
  return TEST_SUCCESS;
}

/*
* Checks if blocking has been correctly implemented for pushing
*/
int blockedPush() {
  genericType* element = (void * )1;
  genericType* expected = (void * )2;
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
		BlockingStack_push(stack, element);
	}
  pthread_t push, pop;
  pthread_create(&push, NULL, threadPush, expected);
  pthread_create(&pop, NULL, threadPop, NULL);
  pthread_join(pop, NULL);
  pthread_join(push, NULL);
  assert(BlockingStack_pop(stack) == expected);
  return TEST_SUCCESS;
}


/*
* Shows thread safety has been correctly implemented.
*/
int threadSafety() {
  pthread_t push[MAX_STACK_SIZE];
  pthread_t pop[MAX_STACK_SIZE];
  void* values[MAX_STACK_SIZE];
  int total = 0;
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    pthread_create(&(push[i]), NULL, threadPush, (void *)i + 1);
    total += i + 1;
  }

  //joins all the pushed threads
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    pthread_join(push[i], NULL);
  }

  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    pthread_create(&(pop[i]), NULL, threadPop, NULL);
  }

  //joins all popped threads
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    pthread_join(push[i], (&values[i]));
    total -= (int) values[i];
  }
  assert(total == 0);
  return TEST_SUCCESS;
}
/*
 * Main function for the BlockingStack tests which will run each user-defined test in turn.
 */

int main() {
	runTest(newStackIsNotNull);
	runTest(newStackSizeZero);
  runTest(newStackIsEmpty);
	runTest(cantPushNull);
	runTest(pushTest);
	runTest(sizeIsOne);
	runTest(stackNonEmpty);
	runTest(stackClearWorks);
	runTest(stackPopWorks);
	runTest(stackPopMakesStackEmpty);
	runTest(pushPastMaxSize);
	runTest(orderPreserved);
  runTest(blockedPop);
  runTest(blockedPush);
  runTest(threadSafety);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(pushOneElement);
     * runTest(pushAndPopOneElement);
     *
     */

	printf("\nBlockingStack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
