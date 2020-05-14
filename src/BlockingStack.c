/*
 * BlockingStack.c
 *
 * Fixed-size generic array-based BlockingStack implementation.
 *
 */

#include <stddef.h>
#include "BlockingStack.h"
#include <stdlib.h>
#include <semaphore.h>

/*
 * This functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Stack module interface as documented in BlockingStack.h.
 */


BlockingStack *new_BlockingStack(int max_size) {
	if (max_size > 0) {
		Stack* stack = (Stack *) malloc (sizeof (Stack));
		stack->size = 0;
		stack->max_size = max_size;
		stack->items = (void**) malloc (sizeof (void*) * max_size);
		BlockingStack* blockingStack = (BlockingStack *) malloc (sizeof (BlockingStack));
		blockingStack->stack = stack;
		if (pthread_mutex_init(&(blockingStack->mutex), NULL) != 0) {
			return NULL;
		}
		if (sem_init(&(blockingStack->semaphore), NOT_SHARED, 0) != 0) {
			return NULL;
		}
		return blockingStack;
	}
	return NULL;
}


bool BlockingStack_push(BlockingStack* this, void* element) {
	return false;
}


void* BlockingStack_pop(BlockingStack* this) {
	return NULL;
}


int BlockingStack_size(BlockingStack* this) {
	return -1;
}


bool BlockingStack_isEmpty(BlockingStack* this) {
	return false;
}


void BlockingStack_clear(BlockingStack* this) {
}


void BlockingStack_destroy(BlockingStack* this) {
	free(this->stack->items);
	free(this->stack);
	pthread_mutex_destroy(&(this->mutex));
	sem_destroy(&(this->semaphore));
	free(this);
}
