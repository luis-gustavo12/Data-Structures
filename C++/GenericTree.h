#pragma once


#include <string>
#include <exception>

namespace GenericTree {


	template <typename T>
	class Node {

	private:

		Node<T>* parent;
		Node<T>* firstChild;
		Node<T>* lastChild;
		T data;

		Node<T>* next;


	public:

		Node(T data) : data(data) {

			this->parent = nullptr;
			this->child = nullptr;
			this->next = nullptr;

		}

		void UpdateData(T value) {
			this->data = value;
		}

		void SetParent(Node<T>* node) {
			this->parent = node;

		}

		void SetFirstChild(Node<T>* node) {
			this->firstChild = node;
		}

		void SetLastChild(Node<T>* node) {
			this->lastChild = node;
		}

		void SetNext(Node<T>* node) {
			this->next = node;
		}

		T GetData() {
			return this->data;
		}

		Node<T>* GetParent() { return this->parent; }

		Node<T>* GetFirstChild() { return this->firstChild; }

		Node<T>* GetLastChild() { return this->lastChild; }

		Node<T>* GetNext() { return this->next; }


	};

	template <typename T>
	class GenericTree {

	private:

		Node<T>* root;
		int treeHeight;


	public:

		GenericTree() {

			this->root = nullptr;
			this->treeHeight = 0;

		}

		GenericTree(T value) {

			this->root = new Node<T>(value);
			this->treeHeight = 1;

		}

		int GetTreeHeight() { return this->treeHeight; }
		void IncreaseTreeHeight() { this->treeHeight += 1; }
		void DecreaseTreeHeight() { this->treeHeight -= 1; }

		Node<T>* GetRoot() {
			return this->root;
		}

		bool IsLeafNode(Node<T> node) {

			if (!node.GetFirstChild && !node.GetLastChild()) {
				return true;
			}
			return false;

		}

		// This function will calculate how many calls are needed to reach the root node (so, the height), and it is called
		// every time we need to add a new node to the tree. Onde we count how many nodes  were needed to reach root node 
		// (which is the only node that has no parent), we give back the count
		int CalculateDistanceToRoot(Node<T>* node) {

			static int count = 1;
			count += 1;
			
			if (node->GetParent()) {
				return CountNewNodeHeight(node->GetParent())
			} else {
				return count;
			}


		}

		// Possibilty to add a value given a T parentNodeValue
		void AddValue(T value, T parentNodeValue) {

			if (GetTreeHeight() == 0) throw std::exception("Empty tree!!!");
			
			
			else if (parentNodeValue == this->root->GetData()) {

				Node<T>* auxNode = new Node<T>(value);

				if (!this->root->GetFirstChild()) {

					IncreaseTreeHeight();
					// No last child can be set while first child is nullptr
					if (this->root->GetLastChild()) throw std::exception("Unexpected behaviour!!!");
					
					this->root->SetFirstChild(auxNode);
					auxNode->SetParent(this->root);
					return;

				}


				// If it's not the first node to be added, and it's not the second, it means it will be added to the last child

				this->root->GetLastChild()->SetNext(auxNode);
				this->root->SetLastChild(auxNode);
				auxNode->SetParent(this->root);

		

			}

			// If we got here, we first need to look for the parent node which has parentNodeValue

			// Iteration

			Node<T>* parentNode = this->root; // This will be the one compared
			Node<T>* iterNode; // This is the iterator that will iterate over the child nodes of parentNode. Name could be iterChildNode;
			bool visitedAllNodes = 0; // If we visited all nodes, no need to keep on doing it

			while (!visitedAllNodes) {


				for (iterNode = parentNode->GetFirstChild(); iterNode; iterNode = iterNode->GetNext()) {

					if (iterNode->GetData() == parentNodeValue) {
						Node<T>* newNode = new Node<T>(value);

						// Only makes sense to bother about increasing tree height, if the parent node is a leaf node. Other wise,
						// The tree height will already be higher thah the calculation of the distance of the parent node to the root.
						// but we also, adding a node to a leaf node is different from adding to a normal node. So this if statement, will handle them 
						// differently
						if (IsLeafNode(parentNode)) {

							if (CalculateDistanceToRoot(parentNode) > GetTreeHeight()) IncreaseTreeHeight();

							parentNode->SetFirstChild(newNode);
							newNode->SetParent(parentNode);
							return; // function ends here

						}

						parentNode->GetLastChild()->SetNext(newNode);
						newNode->SetParent(parentNode);
						parentNode->SetLastChild(parentNode);
						return;


					}

				}

				// If it reaches here, it means that any of the value above were the expected. Couple of things to consider about what are the next steps:

				// First we check if it has a next node

				parentNode = parentNode->GetNext();

				if (parentNode) continue; // If it has a new one, search again with the neightbour


			}



		}

	};





}