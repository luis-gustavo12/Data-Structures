#include <iostream>
#include <cassert>


#include "Tests.h"


#define PRINT_SUCCESS(X) std::cout << (X) << " passed!!!" << std::endl











int main() {

	assert (TestNode() == 1);

	PRINT_SUCCESS("TestNode");

	assert (TestLinkedList() == 1);

	PRINT_SUCCESS("TestLinkedList");

	assert(TestDoublyLinkedList() == 1);

	PRINT_SUCCESS("TestDoublyLinkedList");

	assert(TestBinaryTree() == 1);

	PRINT_SUCCESS("BinaryTree");

	assert(TestStack() == 1);

	PRINT_SUCCESS("Stack");

	assert(TestQueue() == 1);

	PRINT_SUCCESS("Queue");

	assert(TestPriorityQueue() == 1);

	PRINT_SUCCESS("PriorityQueue");

	assert(TestGenericTree() == 1);

	PRINT_SUCCESS("GenericTree");

	assert(TestHash());

	PRINT_SUCCESS("HashTable");

	return 1;

}