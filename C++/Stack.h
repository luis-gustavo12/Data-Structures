#pragma once



// I'm using LinkedLists to store values to the stack, since Singly Linked Lists

#include <string>
#include <iostream>
#include <exception>

#include "LinkedList.h"




namespace Stack {


	template <typename T>
	class Stack {

	private:

		int size = 0;

		LinkedList::Node<T>* top;



	public: 

		Stack() {

			this->size = 0;
			this->top = nullptr;

		}

		Stack(T initialValue) {

			this->size = 1;
			LinkedList::Node<T>* auxNode = new LinkedList::Node<T>(initialValue);
			this->top = auxNode;
			this->top->SetNext(nullptr);

		}

		~Stack() {

			while (this->top) {

				LinkedList::Node<T>* auxNode = this->top;
				this->top = this->top->GetNext();
				delete auxNode;

			}

		}

		int GetSize() {
			return this->size;
		}

		void Push(T content) {

			LinkedList::Node<T>* auxNode = new LinkedList::Node<T>(content);
			if (this->size == 0) {
				auxNode->SetNext(nullptr);
			} else {
				auxNode->SetNext(this->top);
			}
			this->top = auxNode;
			this->size += 1;

		}

		void Pop() {

			if (this->size == 0) {
				throw std::exception("Invalid value!!!");
			}

			LinkedList::Node<T>* removeNode = this->top;
			this->top = this->top->GetNext();
			delete removeNode;
			this->size -= 1;

		}

		T Peek() {
			return this->top->GetContent();
		}
		
		std::string Print() {

			if (this->size == 0) {
				throw std::exception("Invalid value!!!");
			}

			std::string output;

			for (LinkedList::Node<T>* iterNode = this->top; iterNode; iterNode = iterNode->GetNext()) {

				// Had to this way because I was getting C2665 compilation error. Probably because of the using of another namespace Template
				std::string value= static_cast<std::string>(iterNode->GetContent());
				output += value;

				if (iterNode->GetNext()) {
					output += " ";
				}

			}

			return output;

		}

	};


}
