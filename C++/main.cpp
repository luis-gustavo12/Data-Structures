#include <iostream>
#include <cassert>

#include "Node.h"

#include "Tests.h"


#define PRINT_SUCCESS(X) std::cout << (X) << " passed!!!" << std::endl











int main() {

	assert (TestNode() == 1);

	PRINT_SUCCESS("TestNode");

	assert (TestLinkedList() == 1);

	PRINT_SUCCESS("TestLinkedList");

	assert(TestDoublyLinkedList() == 1);

	PRINT_SUCCESS("TestDoublyLinkedList");

	return 1;

}