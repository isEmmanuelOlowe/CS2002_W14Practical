/*
 * Stack.c
 *
 * Fixed-size generic array-based Stack implementation.
 *
 */

#include <stddef.h>
#include "Stack.h"
#include <stdlib.h>

/*
 * This functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Stack module interface as documented in Stack.h.
 */

 /*
  * Creates a new Stack for at most max_size void* elements.
  * Returns a pointer to valid Stack* on success and NULL on failure.
  */
Stack *new_Stack(int max_size) {
	if (max_size > 0) {
		Stack* stack = (Stack *) malloc (sizeof (Stack));
		stack->size = 0;
		stack->max_size = max_size;
		stack->items = (void**) malloc (sizeof (void*) * max_size);
		return stack;
	}
	return NULL;
}

/*
 * Pushes the given void* element onto this Stack.
 * Returns true on success and false on push failure when element is NULL or stack is full.
 */
bool Stack_push(Stack* this, void* element) {
	if (this->size != this->max_size) {
		if (element != NULL) {
			this->items[this->size] = element;
			this->size++;
			return true;
		}
	}
	return false;
}

/*
 * Pops the top element from this Stack.
 * Returns popped void* element on success or NULL if stack is empty.
 */
void* Stack_pop(Stack* this) {
	if (this->size != 0) {
		this->size--;
		return this->items[this->size];
	}
	return NULL;
}

/*
 * Returns the number of elements currently on this Stack.
 */
int Stack_size(Stack* this) {
	if (this != NULL) {
		return this->size;
	}
	return -1;
}

/*
 * Returns true is this Stack is empty, false otherwise.
 */
bool Stack_isEmpty(Stack* this) {
	if (this->size == 0) {
		return true;
	}
	return false;
}

/*
 * Clears this Stack returning it to an empty state.
 */
void Stack_clear(Stack* this) {
	this->size = 0;
}

/*
 * Destroys this Stack by freeing the memory used by the Stack.
 */
void Stack_destroy(Stack* this) {
	free(this->items);
	free(this);
}
