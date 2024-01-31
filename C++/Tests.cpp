#include "Tests.h"









// TEST NODES



int TestNode() {



	LinkedList::Node<int> node1(25);

	assert(node1.GetContent() == 25);

	LinkedList::Node<int> node2(122);

	node1.SetNext(&node2);

	assert(node1.GetNext() == &node2);

	node1.UpdateValue(122);

	assert(node1.GetContent() == 122);

	return 1;

}



// TESTS LINKED LIST

template<typename T>
int TestEmptyListException(LinkedList::LinkedList<T>& list) {

	try {
		list.Print();
	} catch (const std::exception&) {
		return 1;
	}


	return 1;
}

template<typename T>
int TestInsertionException(LinkedList::LinkedList<T>& list) {

	try {
		list.Insert(25, list.GetSize() + 1);
	} catch (const std::exception&) {
		return 1;
	}

	return 0;
}

template<typename T>
int TestRemoveException(LinkedList::LinkedList<T>& list) {

	try {

		list.Remove(list.GetSize() + 1);

	} catch (const std::exception&) {

		return 1;

	}

	

	return 0;
}


int TestRemoveDeletePositionZero() {

	LinkedList::LinkedList<int> list;

	list.PushFront(25);

	list.Remove(0);

	bool condition = ( (list.GetHead() == nullptr) && (list.GetLast() == nullptr) && list.GetSize() == 0 );

	return condition;
}

int TestLinkedList() {
	
	assert(TestRemoveDeletePositionZero() == 1);

	LinkedList::LinkedList<int> list;

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

	DoublyLinkedList::Node<int> node   (25);
	DoublyLinkedList::Node<int> node2  (12);
	DoublyLinkedList::Node<int> node3 (129);

	assert(node.GetContent() == 25);

	node.SetNext(&node2);

	assert(node.GetNext() == &node2);

	node.SetPrev(&node3);

	assert(node.GetPrev() == & node3);

	DoublyLinkedList::Node<int> node4(178);

	node.SetNext(&node4);

	//delete &node3;

	assert(node.GetNext() == &node4);

	return 1;

}

template <typename T>
int TestInsertException(DoublyLinkedList::DoublyLinkedList<T>& list) {
	

	int wrongPos = list.GetSize() + 1;

	try {
		list.Insert(wrongPos, 255);
	} catch (const std::exception&) {
		return 1;
	}

	return 0;


}

template<typename T>
int TestRemoveException(DoublyLinkedList::DoublyLinkedList<T>& list) {
	
	int wrongIndex = list.GetSize() + 1;

	try {

		list.Remove(wrongIndex);

	} catch (const std::exception&) {
		return 1;
	}

	return 0;


}

template<typename T>
int TestBinaryTreeRemoveException(BinaryTree::BinaryTree<T> tree, T invalidValue) {

	try {
		tree.Remove(invalidValue);
	} catch (const std::exception&) {
		return 1;
	}


	return 0;
}




int TestDoublyLinkedList() {

	assert(TestDNodes() == 1);

	DoublyLinkedList::DoublyLinkedList<int> list;

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

	assert(list.FindPos(999) == 0);

	assert(list.FindPos(13) == 1);

	assert(list.FindPos(123) == 3);

	assert(list.PrintReverse() == "123 35 13 999");

	return 1;
}

int TestBinaryTree() {

	BinaryTree::BinaryTree<int> tree(12);

	assert(tree.GetRootContent() == 12);

	assert(tree.GetNodeCount() == 1);

	assert(tree.Contains(25) == 0);

	tree.Insert(123);

	assert(tree.Contains(123) == 1);

	tree.Insert(3);

	assert(tree.GetNodeCount() == 3);

	assert(tree.FindNode(155) == nullptr);

	assert(tree.FindNodeRecursive(tree.GetRoot(), 155) == nullptr);

	/***
	* 
	* 
	*              12
	* 
	*      3                        123
	* 
	*  2         9               79
	*         8      11
	* 
	* This is how tree is suposed to look like, after inserts below. Better image can be found at the finle Binary Tree.png
	* 
	* 
	*/

	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(8);
	tree.Insert(11);
	tree.Insert(79);

	assert(tree.FindParent(3)->GetData() == 12);
	assert(tree.FindParent(8)->GetData() == 9);
	assert(tree.FindParent(79)->GetData() == 123);
	assert(tree.FindParent(2)->GetData() == 3);

	//Recursive assertions
	assert(tree.FindParentRecursive(tree.GetRoot(), 3)->GetData() == 12);
	assert(tree.FindParentRecursive(tree.GetRoot(), 8)->GetData() == 9);
	assert(tree.FindParentRecursive(tree.GetRoot(), 79)->GetData() == 123);
	assert(tree.FindParentRecursive(tree.GetRoot(), 2)->GetData() == 3);

	assert(tree.GetNodeCount() == 8);
	
	assert(TestBinaryTreeRemoveException(tree, 950) == 1);

	assert(tree.FindLargestValueNode()->GetData() == 123);

	// Before moving on with tests, it'd be better to implement the transversal algorithms, so it's easier to see the expected results
	assert(tree.PreOrder() == "12 3 2 9 8 11 123 79");

	assert(tree.PostOrder() == "2 8 11 9 3 79 123 12 ");

	assert(tree.InOrder() == "2 3 8 9 11 12 79 123 ");
	
	return 1;

}

// TESTS STACKS

template <typename T>
int TestStackPopException(Stack::Stack<T> stack) {

	try {

		stack.Pop();

	} catch (const std::exception&) {
		return 1;
	}

	return 0;
}

template <typename T>
int TestStackPrintException(Stack::Stack<T> stack) {

	try {

		stack.Print();

	} catch (const std::exception&) {

		return 1;

	}

	return 0;
}


int TestStack() {

	Stack::Stack<std::string> stack;

	assert(stack.GetSize() == 0);

	assert(TestStackPopException(stack) == 1);

	assert(TestStackPrintException(stack) == 1);

	stack.Push("Lina");

	stack.Push("Pudge");

	stack.Push("Rylai");

	stack.Push("Balanar");

	assert(stack.GetSize() == 4);

	assert(stack.Print() == "Balanar Rylai Pudge Lina");

	assert(stack.Peek() == "Balanar");

	stack.Pop();

	assert(stack.Print() == "Rylai Pudge Lina");

	assert(stack.GetSize() == 3);

	return 1;
}

// TEST QUEUES

int TestQueue() {

	Queue::Queue<int> queue (12);

	assert(queue.Print() == "12");

	queue.Enqueue(25);

	queue.Enqueue(133);

	queue.Enqueue(27);

	assert(queue.GetSize() == 4);

	assert(queue.Print() == "12 25 133 27");

	queue.Dequeue();

	assert(queue.GetSize() == 3);

	assert(queue.Print() == "25 133 27");

	assert(queue.Peek() == 25);

	assert(queue.PeekBack() == 27);

	return 1;
}

int TestPriorityQueue() {
	return 1;
}

// TEST GENERIC TREES

int TestGenericTreeFindNodeException() {
	return 0;
}

int TestGenericTree() {
	
	// I'm using Abraham Genealogic tree to test this DS. I'm using Portuguese names
	GenericTree::GenericTree<std::string> tree("Abraão");

	std::string rootValue = "Abraão";

	assert(tree.GetRootContent() == "Abraão");

	assert(tree.GetTreeDepth() == 1);

	tree.AddValue("Isaque", rootValue);

	tree.AddValue("Ismael", rootValue);

	tree.AddValue("Zinrã", rootValue);

	assert(tree.PrintChildren(tree.GetRoot()) == "Isaque Ismael Zinrã");

	tree.AddValue("Jacó", "Isaque");

	tree.AddValue("Esaú", "Isaque");

	GenericTree::Node<std::string>* isaacNode = tree.FindNode("Isaque");

	assert(isaacNode->GetParent() == tree.GetRoot());

	assert(tree.GetTreeDepth() == 3);

	tree.AddValue("Rúben", "Jacó");
	tree.AddValue("Simeão", "Jacó");
	tree.AddValue("Levi", "Jacó");
	tree.AddValue("Judá", "Jacó");
	tree.AddValue("Dã", "Jacó");
	tree.AddValue("Naftali", "Jacó");
	tree.AddValue("Gade", "Jacó");
	tree.AddValue("Aser", "Jacó");
	tree.AddValue("Issacar", "Jacó");
	tree.AddValue("Zebulom", "Jacó");
	tree.AddValue("José", "Jacó");
	tree.AddValue("Benjamim", "Jacó");

	assert(isaacNode->GetFirstChild()->GetData() == "Jacó");

	assert(tree.PrintChildren(isaacNode->GetFirstChild()) == "Rúben Simeão Levi Judá Dã Naftali Gade Aser Issacar Zebulom José Benjamim");

	assert(tree.GetTreeDepth() == 4);

	//TODO: indexing and serching algorithms


	return 1;
}

int TestHash() {

	// Table that stores the champions of Football World Cups, and the year that they did it
	HashTable::HashTable<std::string, std::string> tableWC("Uruguay", "1930");

	tableWC.Insert("1934", "Italy");
	tableWC.Insert("1938", "Italy");
	tableWC.Insert("1958", "Brazil");
	tableWC.Insert("1962", "Brazil");
	tableWC.Insert("1966", "England");
	tableWC.Insert("1970", "Brazil"); // THE DREAM TEAM BOY
	tableWC.Insert("1974", "Germany");
	tableWC.Insert("1978", "Argentina");
	tableWC.Insert("1982", "Italy");
	tableWC.Insert("1986", "Argentina");
	tableWC.Insert("1990", "Germany");
	tableWC.Insert("1994", "Brazil");
	tableWC.Insert("1998", "France");
	tableWC.Insert("2002", "Brazil");	
	tableWC.Insert("2006", "Italy");
	tableWC.Insert("2010", "Spain");
	tableWC.Insert("2014", "Germany");
	tableWC.Insert("2018", "France");
	tableWC.Insert("2022", "Argentina"); // A sad moment in world's history

	assert(tableWC.PrintKeys() == "1930 1934 1938 1950 1954 1958 1962 1966 \
1970 1974 1978 1982 1986 1990 1994 1998 2002 2006 2010 2014 2018");



	assert(tableWC["1934"] == "Italy");
	assert(tableWC["2002"] == "Brazil");
	assert(tableWC["2001"] == NULL);

	return 1;
}





