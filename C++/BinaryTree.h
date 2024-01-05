#pragma once


/**
* 
* 
* NOTE: From now on, I'm going to defining the node inside the Data Structure header file, and use it from inside. Otherwise, I'll have to keep
* creating a different kind of node for every DS, and name it differently from only "Node" (for instance, DoublyLinkedList, had to call it DNode).
* 
* 
*/


template <typename T>
class Node {


private:

	Node<T>* left;
	Node<T>* right;
	T data;


public:

	Node(T data) {

		this->data = data;
		this->left = nullptr;
		this->right = nullptr;

	}

	void SetRight(Node<T>* node) {
		this->right = node;
	}

	Node<T>* GetRight() {
		return this->right;
	}

	void SetLeft(Node<T>* node) {
		this->left = node;
	}

	Node<T>* GetLeft() {
		this->left = left;
	}





	

};


template <typename T>
class BinaryTree {




private:


	DNode<T>* root;
	int degrees;









};

