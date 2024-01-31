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
			this->firstChild = nullptr;
			this->lastChild = nullptr;
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
		int treeDepth;


	public:

		GenericTree() {

			this->root = nullptr;
			this->treeDepth = 0;

		}

		GenericTree(T value) {

			this->root = new Node<T>(value);
			this->treeDepth = 1;

		}

		int GetTreeDepth() { return this->treeDepth; }
		void IncreaseTreeDepth() { this->treeDepth += 1; }
		void DecreaseTreeDepth() { this->treeDepth -= 1; }

		Node<T>* GetRoot() {
			return this->root;
		}

		T GetRootContent() { return this->root->GetData(); }

		static bool IsLeafNode(Node<T>* node) {

			if ( (node->GetFirstChild() == nullptr) && (node->GetLastChild() == nullptr)) {
				return true;
			}
			return false;

		}

		// This function will calculate how many degrees are needed to reach the root node (so, the depth), and it is called
		// every time we need to add a new node to the tree. Onde we count how many nodes  were needed to reach root node 
		// (which is the only node that has no parent), we give back the count
		int CalculateDistanceToRoot(Node<T>* node) {

			if (!node->GetParent()) return 1;

			int count = 0;

			for (Node<T>* auxNode = node; auxNode; auxNode = auxNode->GetParent()) {
				count += 1;
			}

			return count;


		}

		// If we got here, we first need to look for the parent node which has parentNodeValue

		/*
		* 
		* Here's the search for the value we want in the tree. It's a greedy search.
		* 
		* It will always start from the root value, and will go through every single branch
		* 
		**/ 

		Node<T>* FindNode(T value) {

			Node<T>* parentNode = this->root; // This will be the parent node for every single iteration. It starts with the root node, but as the algorithm goes, it changes
			Node<T>* iterNode; // This one will be the node that will iterate over all parent node's children. E.g.: if parent node has 3 childs, at some point, iterNode "will be" those 3 child nodes.
			/*
			* This will be the marker for when we passed through every single node. There will be some cases where we will check for the condition, and swap it to true, meaning we went through
			* every tree node
			* 
			*/
			bool passedAllNodes = 0;


			while (!passedAllNodes) {

				for (iterNode = parentNode->GetFirstChild(); iterNode; iterNode = iterNode->GetNext()) {

					if (iterNode->GetData() == value) {
						return iterNode;
					}

				}

				/*
				* 
				* auxNode is the one we're going to check. I had to create this because if we keep changing
				* nodeParent for the next iteration, it might get a nullptr as a return, and nullptr has no
				* methods of a node, since it's a nullptr. So once auxNode assumes a suitable value to be
				* replaced by parentNode, parentNode get its value, and goes to the next iteration (the one of
				* while loop above). Basically, parentNode inside each iteration is a "backup" of a eventual nullptr
				* return from the comparisons.
				*/
				Node<T>* auxNode = parentNode;
				

				// If it hasn't found anything in the for loop, iterate over the children of the next node
				auxNode = parentNode->GetNext();

				if (auxNode) {
					parentNode = auxNode;
					continue;
				}

				//If it didn't manage to find a neighbour, try to get the child nodes
				auxNode = parentNode->GetFirstChild();

				if (auxNode) {
					parentNode = auxNode;
					continue;
				}

				//If still didn't manage to find a child node, we have to start going up to the parents of parentNode, until we find an upper node that has a next neighbour 
				// and then, start looking for child nodes again

				auxNode = parentNode; //Reset auxNode again, because auxNode might have turned into nullptr

				while (true) {

					// If auxNode node finds one that has no parent, it means we reached the root node
					if (!auxNode->GetParent()) return nullptr;

					else if (auxNode == nullptr) throw std::exception("Unexpected behaviour!!!");
					
					else if (auxNode->GetNext()) {
						parentNode = auxNode->GetNext();
						continue;
					}

					//If it has no neighbour, then move up
					auxNode = auxNode->GetParent();

				}

			}

		}

		// Possibilty to add a value given a T parentNodeValue
		void AddValue(T value, T parentNodeValue) {

			if (GetTreeDepth() == 0) throw std::exception("Empty tree!!!");
			
			// We're adding to the root node
			else if (parentNodeValue == this->root->GetData()) {

				Node<T>* auxNode = new Node<T>(value);

				if (!this->root->GetFirstChild()) {

					IncreaseTreeDepth();
					// No last child can be set while first child is nullptr
					if (this->root->GetLastChild()) throw std::exception("Unexpected behaviour!!!");
					
					this->root->SetFirstChild(auxNode);
					this->root->SetLastChild(auxNode);
					auxNode->SetParent(this->root);
					return;

				}

				else if (this->root->GetFirstChild() == this->root->GetLastChild()) {
					this->root->GetFirstChild()->SetNext(auxNode);
					this->root->SetLastChild(auxNode);
					auxNode->SetParent(this->root);
					return;
				}


				this->root->GetLastChild()->SetNext(auxNode);
				this->root->SetLastChild(auxNode);
				auxNode->SetParent(this->root);
				return;
		

			}

			// We first find the parent one to then assign the new node of it as a child
			Node<T>* parentNode = FindNode(parentNodeValue);

			if (!parentNode) throw std::exception("Parent Node does not exist!!!");

			Node<T>* newNode = new Node<T>(value);

			if (IsLeafNode(parentNode)) {
				parentNode->SetFirstChild(newNode);
				parentNode->SetLastChild(newNode);
			}

			else if (parentNode->GetFirstChild() == parentNode->GetLastChild()) {
				parentNode->SetLastChild(newNode);
				parentNode->GetFirstChild()->SetNext(newNode);
				parentNode->SetLastChild(newNode);
			}

			else {
				parentNode->GetLastChild()->SetNext(newNode);
				parentNode->SetLastChild(newNode);
			}

			newNode->SetParent(parentNode);
			//Now we check if the depth of the tree was increased, and change Tree member that counts the depth

			if (CalculateDistanceToRoot(newNode) > GetTreeDepth()) IncreaseTreeDepth();

		}

		std::string PrintChildren(Node<T>* parentNode) {

			if (IsLeafNode(parentNode)) throw std::exception("Invalid parameter!!!");

			std::string output;

			for (Node<T>* auxNode = parentNode->GetFirstChild(); auxNode; auxNode = auxNode->GetNext()) {

				output += static_cast<std::string>(auxNode->GetData());
				if ((auxNode == parentNode->GetLastChild()) == false) {
					output += " ";
				}

			}

			return output;

		}

	};





}