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
		Stack* stack = new_Stack(max_size);
		BlockingStack* blockingStack = (BlockingStack *) malloc (sizeof (BlockingStack));
		blockingStack->stack = stack;
		if (pthread_mutex_init(&(blockingStack->mutex), NULL) != 0) {
			return NULL;
		}
		if (sem_init(&(blockingStack->sem_pop), NOT_SHARED, 0) != 0) {
			return NULL;
		}
    if (sem_init(&(blockingStack->sem_push), NOT_SHARED, max_size) != 0) {
			return NULL;
		}
		return blockingStack;
	}
	return NULL;
}


bool BlockingStack_push(BlockingStack* this, void* element) {
  sem_wait(&(this->sem_push));
  pthread_mutex_lock(&(this->mutex));
  bool result = Stack_push(this->stack, element);
  pthread_mutex_unlock(&(this->mutex));
  sem_post(&(this->sem_pop));
  return result;
}


void* BlockingStack_pop(BlockingStack* this) {
  sem_wait(&(this->sem_pop));
  pthread_mutex_lock(&(this->mutex));
  void* item = Stack_pop(this->stack);
  pthread_mutex_unlock(&(this->mutex));
  sem_post(&(this->sem_push));
  return item;
}


int BlockingStack_size(BlockingStack* this) {
	return this->stack->size;
}


bool BlockingStack_isEmpty(BlockingStack* this) {
	return (this->stack->size == 0);
}


void BlockingStack_clear(BlockingStack* this) {
  //Clears the stack and returns the semaphores to their base values.
  pthread_mutex_lock(&(this->mutex));
  while (this->stack->size != 0) {
    sem_wait(&(this->sem_pop));
    this->stack->size--;
    sem_post(&(this->sem_push));
  }
  pthread_mutex_unlock(&(this->mutex));
}


void BlockingStack_destroy(BlockingStack* this) {
	Stack_destroy(this->stack);
	pthread_mutex_destroy(&(this->mutex));
	sem_destroy(&(this->sem_pop));
  sem_destroy(&(this->sem_push));
	free(this);
}
