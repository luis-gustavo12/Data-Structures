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

		Node<T>* GetChild() { return this->child; }

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

		// Possibilty to add a value given a T parentNodeValue
		void AddValue(T value, T parentNodeValue) {

			if (GetTreeHeight() == 0) throw std::exception("Empty tree!!!");

			Node<T>* auxNode = new Node<T>(value);

			// If it has only root node, no need to check for T parentNodeValue
			else if (GetTreeHeight() == 1) {
				
				this->root->SetFirstChild(auxNode);
				IncreaseTreeHeight();
				return;

			}






		}

	};





}