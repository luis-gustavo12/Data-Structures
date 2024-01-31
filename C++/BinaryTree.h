#pragma once





#include <string>
#include <iostream>
#include <exception>



namespace BinaryTree {

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



		void SetData(T data) {
			this->data = data;
		}

		T GetData() {
			return this->data;
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
			return this->left = left;
		}

	};



	template <typename T>
	class BinaryTree {




	private:

		Node<T>* root;
		int nodeCount = 0; // Might be useful

	public:


		// I'm giving the possibility to both initialize them with a value, or without

		BinaryTree(T data) {

			this->root = new Node<T>(data);
			this ->nodeCount += 1;
		}

		BinaryTree() {

			this->root = nullptr;


		}

		T GetRootContent() {
			return this->root->GetData();
		}

		Node<T>* GetRoot() {
			return this->root;
		}

		int GetNodeCount() {
			return this->nodeCount;
		}


		void Insert(T data) {

			if (!this->root) {
				root = new Node<T>(data);
				nodeCount += 1;
				return;
			}


			InsertNode(this->root, data);
			return;



		}

		// Recursive
		void InsertNode(Node<T>* node, T data) {

			// Duplicates will be put in the left side

			if ( data <= node->GetData() ) {

				// If the left node is empty, here's where we put it
				if (!node->GetLeft()) {

					Node<T>* newNode = new Node<T>(data);
					node->SetLeft(newNode);
					nodeCount += 1;
					return;
				} else {

					InsertNode(node->GetLeft(), data);
					return;

				}


			}

			else if (data > node->GetData() ) {


				if (!node->GetRight()) {
					Node<T>* newNode = new Node<T>(data);
					nodeCount += 1;
					node->SetRight(newNode);
					return;
				}

				InsertNode(node->GetRight(), data);
				return;

			}

			throw std::exception("Should not reach here!!!");


		}


		// For printing the tree, it's a complicated task. I'll leave it for later
		std::string PrettyPrint() {
			return "";
		}

		//  Why the overload? Since in the test file I wouldn't like user to be creating their own nodes, but just passing the value they want as argument,
		// It's easier to have a Contains() with only the value as parameters that calls Contains() overload with the root node and value as parameters, 
		// and so the recursion starts.

		bool Contains(T value) {

			if (this->nodeCount == 0) {
				throw std::out_of_range("Empty tree!!!");
				return false;
			}

			// has only the root node
			if (this->nodeCount == 1) {
				return (this->root->GetData() == value);

			}

			return Contains(this->root, value);

		}


		bool Contains(Node<T>* node, T value) {


			// If the node is a nullptr, it means we wen't recursively until all last leaf, that had either a left or right node with a nullptr.

			if (!node) return false;

			// First, compare with the current node

			else if (node->GetData() == value) return true;

			// Then, if it's less than the current, calls recursively Contains for left node, if greater, calls recursively for right node

			else if (value <= node->GetData()) {

				return Contains(node->GetLeft(), value);

			} 

			return Contains(node->GetRight(), value);

		}


		// Not going to make an overload on this one, since I just created this method to implement the pseudo coude from the book. I didn't like the recursion approach for
		// everything
		Node<T>* FindNodeRecursive(Node<T>* root, T value) {

			if (this->nodeCount == 0) {
				throw std::out_of_range("Empty list!!!");
				return nullptr;
			}
		
			else if (!root) return nullptr;

			if (root->GetData() == value) {
				return root;
			}

			else if (value < root->GetData()) return this->FindNodeRecursive(root->GetLeft(), value);


			else if (value > root->GetData()) return this->FindNodeRecursive(root->GetRight(), value);


		}

		Node<T>* FindNode(T value) {

			if (this->nodeCount == 0) {
				throw std::out_of_range("Empty list!!!");
				return nullptr;
			}

			Node<T>* iterNode = this->root;

			// Not going to recursive this time
			while (iterNode) {

				if (value == iterNode->GetData()) {
					return iterNode;
				}

				else if (value < iterNode->GetData()) {
					iterNode = iterNode->GetLeft();
					continue;
				}

				// If it isn't equal, less than, its greater than
				iterNode = iterNode->GetRight();
				continue;

			}

			// If we reach here, it means that GetRight() or GetLeft() found a  nullptr, and we left the while loop

			return nullptr;

		}


		Node<T>* FindParentRecursive(Node<T>* root, T value) {

			if (this->nodeCount == 0) throw std::out_of_range("Empty list!!!");

			else if (value == this->root->GetData()) return nullptr;

			// If any of the nodes equals T value, root (which is every recursive node being passed as parameter, and is the name given by the book's author and I don't like it)
			// is the parent node 
			if (root->GetLeft()->GetData() == value || root->GetRight()->GetData() == value) {
				return root;
			}

			else if (value < root->GetData()) {

				return FindParentRecursive(root->GetLeft(), value);

			} else if (value > root->GetData()) {

				return FindParentRecursive(root->GetRight(), value);

			}


		}



		// Non recursive, with overload
		Node<T>* FindParent(T value) {

			if (this->nodeCount == 0) throw std::out_of_range("Empty list!!!");

			else if (this->root->GetData() == value) return nullptr;

			Node<T>* iterNode = this->root;

			while (iterNode) {

				if (iterNode->GetLeft()->GetData() == value || iterNode->GetRight()->GetData() == value) {
					return iterNode;
				}

				if (value < iterNode->GetData()) {
					iterNode = iterNode->GetLeft();
					continue;
				}

				iterNode = iterNode->GetRight();

			}


			// If we reach here, at some point, iterNode received nullptr, which means, FindParent() didn't manage to find anything, and loop broke
			return nullptr;

		}





	
		// same as Contains()

		void Remove(T value) {


			Node<T>* removeNode = FindNode(value);

			if (removeNode == nullptr) throw std::exception("Invalid value!!!");

			// Has only the root

			if (this->nodeCount == 1) {

				this->root = nullptr;
				this->nodeCount -= 1;
				return;

			}

			// Case which is a leaf

			Node<T>* parentNode = FindParent(value);

			if (!removeNode->GetLeft() || !removeNode->GetRight()) {

				if (value <= parentNode->GetData()) parentNode->SetLeft(nullptr);
				else if (value > parentNode->GetData()) parentNode->SetRight(nullptr);

				delete removeNode;
			}

			// Case which has no subtree on the left

			else if (!removeNode->GetLeft() && removeNode->GetRight()) {

				if (value < parentNode->GetData()) {

					parentNode->SetLeft(removeNode->GetRight());

				}

				else if (value > parentNode->GetData()) {

					parentNode->SetRight(removeNode->GetRight());

				}

				delete removeNode;

			}

			// Case which has no subtree on the right

			else if (removeNode->GetLeft() && !removeNode->GetRight()) {

				if (value < parentNode->GetData()) {

					parentNode->SetLeft(removeNode->GetLeft());

				}

				else if (value > parentNode->GetData()) {

					parentNode->SetRight(removeNode->GetLeft());

				}

				delete removeNode;

			}

			// Case where removeNode has both left and right subtree. We'll find the maximum value from the left node of the RemoveNode
			// and replace it on the node suposed to be removed

			else {


				Node<T>* largestValueNode = removeNode->GetLeft();

				while (largestValueNode->GetRight()) {

					largestValueNode = largestValueNode->GetRight();

				}

				Node<T>* parent = FindParent(largestValueNode->GetData());
				delete parent->GetRight(); // delete old node
				parent->SetRight(nullptr);

				removeNode->SetData(largestValueNode->GetData());
			}

			this->nodeCount -= 1;


		}

		Node<T>* FindLargestValueNode() {

			if (nodeCount == 1) {
				return this->root;
			}


			Node<T>* iterNode = this->root->GetRight();

			while (iterNode->GetRight()) {
				iterNode = iterNode->GetRight();
			}

			return iterNode;



		}


		// Searching algorithms

		std::string PreOrder() {


			if (nodeCount == 1) {
				return std::to_string(this->root->GetData());
			}

			

			std::string output;
			PreOrder(this->root, output);
			
			return output;

		}


		// this preorder function will get the nodes, the other one is just for calling in the test file
		void PreOrder(Node<T>* node, std::string& output) {

			// i'm creating this variable because I want to know when the last node is passed. So, if preOrderCount == nodeCount,
			// it means we've got to the last node, and don't need to do output += " ", so the string gets to the right shape
			static int preOrderCount = 0;

			if (node) {

				// Summing for every time it's called
				preOrderCount++;

				output += std::to_string(node->GetData());

				if (preOrderCount != nodeCount) {
					output += " ";
				}

				PreOrder(node->GetLeft(), output);
				PreOrder(node->GetRight(), output);

			}


		}

		std::string PostOrder() {

			if (nodeCount == 1) {
				return std::to_string(this->root->GetData());
			}


			std::string output;

			PostOrder(this->root, output);

			return output;

		}

		void PostOrder(Node<T>* node, std::string& output) {


			if (node) {



				PostOrder(node->GetLeft(), output);
				PostOrder(node->GetRight(), output);
				output += std::to_string(node->GetData());
				output += " ";

			} 

			return;

		}

		std::string InOrder() {

			if (nodeCount == 1) {
				return std::to_string(this->root->GetData());
			}

			std::string output;
			
			InOrder(this->root, output);

			return output;

		}


		void InOrder(Node<T>* node, std::string& output) {


			if (node) {

				InOrder(node->GetLeft(), output);
				output += std::to_string(node->GetData());
				output += " ";
				InOrder(node->GetRight(), output);


			}



		}



	};

}