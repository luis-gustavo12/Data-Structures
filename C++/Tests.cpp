#include "Tests.h"









// TEST NODES



int TestNode() {


	Node<int> node1(25);

	assert(node1.GetContent() == 25);

	Node<int> node2(122);

	node1.SetNext(&node2);

	assert(node1.GetNext() == &node2);

	node1.UpdateValue(122);

	assert(node1.GetContent() == 122);

	return 1;

}



// TESTS LINKED LIST

template<typename T>
int TestEmptyListException(LinkedList<T> list) {

	try {
		list.Print();
	} catch (const std::exception&) {
		return 1;
	}


	return 1;
}

template<typename T>
int TestInsertionException(LinkedList<T> list) {

	try {
		list.Insert(25, list.GetSize() + 1);
	} catch (const std::exception&) {
		return 1;
	}

	return 0;
}

template<typename T>
int TestRemoveException(LinkedList<T> list) {

	try {

		list.Remove(list.GetSize() + 1);

	} catch (const std::exception&) {

		return 1;

	}

	

	return 0;
}


int TestRemoveDeletePositionZero() {

	LinkedList<int> list;

	list.PushFront(25);

	list.Remove(0);

	bool condition = ( (list.GetHead() == nullptr) && (list.GetLast() == nullptr) && list.GetSize() == 0 );

	return condition;
}

int TestLinkedList() {
	
	assert(TestRemoveDeletePositionZero() == 1);

	LinkedList<int> list;

	assert(TestEmptyListException(list) == 1);

	list.PushFront(25);

	assert(list.Print() == "25");

	list.Remove(0);

	assert(TestEmptyListException(list) == 1);

	list.PushBack(25);

	list.PushBack(12);

	assert(list.Print() == "25 12");

	list.PushBack(36);

	assert(list.Print() == "25 12 36");

	std::vector<int> numbersToBeAdded = { 123, 2567, 12, 36, 18 };

	for (auto i : numbersToBeAdded) {

		list.PushBack(i);

	}

	assert(list.Print() == "25 12 36 123 2567 12 36 18");

	list.Insert(127, 2);

	assert(list.Print() == "25 12 127 36 123 2567 12 36 18");

	assert(TestInsertionException(list) == 1);

	assert(list.GetSize() == 9);

	int sizeBeforeRemoving = list.GetSize();

	list.Remove(0);

	assert(list.Print() == "12 127 36 123 2567 12 36 18");

	assert(list.GetSize() == sizeBeforeRemoving - 1);

	assert(TestRemoveException(list) == 1);

	list.Remove(3);

	assert(list.Print() == "12 127 36 2567 12 36 18");

	list.Remove(5);

	assert(list.Print() == "12 127 36 2567 12 18");

	list.Update(40, 0);

	list.Update(40, 1);

	assert(list.Print() == "40 40 36 2567 12 18");

	assert(list[2] == 36);

	list[2] = 45;

	assert(list[2] == 45);

	list.PushBack(908);

	assert(list.Print() == "40 40 45 2567 12 18 908");

	return 1;

}




// TESTS DOUBLY LINKED LISTS



int TestDNodes() {

	DNode<int> node   (25);
	DNode<int> node2  (12);
	DNode<int> node3 (129);

	assert(node.GetContent() == 25);

	node.SetNext(&node2);

	assert(node.GetNext() == &node2);

	node.SetPrev(&node3);

	assert(node.GetPrev() == & node3);

	DNode<int> node4(178);

	node.SetNext(&node4);

	//delete &node3;

	assert(node.GetNext() == &node4);

	return 1;


}

template <typename T>
int TestInsertException(DoublyLinkedList<T> list) {
	

	int wrongPos = list.GetSize() + 1;

	try {
		list.Insert(wrongPos, 255);
	} catch (const std::exception&) {
		return 1;
	}

	return 0;


}

template<typename T>
int TestRemoveException(DoublyLinkedList<T> list) {
	
	int wrongIndex = list.GetSize() + 1;

	try {

		list.Remove(wrongIndex);

	} catch (const std::exception&) {
		return 1;
	}

	return 0;


}

int TestDoublyLinkedList() {

	assert(TestDNodes() == 1);

	DoublyLinkedList<int> list;

	list.PushBack(2);

	assert(list.Print() == "2");

	list.PushFront(25);

	assert(list.Print() == "25 2");

	assert(list.GetSize() == 2);

	list.PushFront(13);

	assert(list.Print() == "13 25 2");

	assert(list.GetSize() == 3);

	list.PushBack(123);

	assert(list.Print() == "13 25 2 123");

	assert(list.GetSize() == 4);

	assert(TestInsertException(list) == 1);

	list.Insert(2, 35);

	assert((list.Print() == "13 25 35 2 123") && (list.GetSize() == 5));

	assert(TestRemoveException(list) == 1);

	list.Remove(3);

	assert((list.Print() == "13 25 35 123") && (list.GetSize() == 4));

	assert(list.GetContent(2) == 35);

	assert(list.GetContent(0) == 13);

	list.Update(999, 0);

	list.Update(255, 1);

	assert(list.Print() == "999 255 35 123");

	assert(list[0] == 999);

	list[1] = 13;

	assert(list.Print() == "999 13 35 123");

	assert(list.PrintReverse() == "123 35 13 999");

	return 1;
}





