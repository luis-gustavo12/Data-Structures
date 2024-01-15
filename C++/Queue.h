#pragma once



#include <string>
#include <exception>

#include "LinkedList.h"


namespace Queue {


	template <typename T>
	class Queue {

	private:

		int size = 0;
		LinkedList::Node<T>* first;
		LinkedList::Node<T>* last;

	public:

		Queue() {

			this->first = nullptr;
			this->last = nullptr;


		}

		Queue(T value) {

			LinkedList::Node<T>* auxNode = new LinkedList::Node<T>(value);
			this->first = auxNode;
			this->last = auxNode;
			this->size += 1;

		}

		int GetSize() { return this->size; }

		void Enqueue(T value) {

			if (size == 0) {
				throw std::exception("Empty Queue!!!");
			}

			LinkedList::Node<T>* newNode = new LinkedList::Node<T>(value);

			if (last == first) {
				this->first->SetNext(newNode);
				this->last = newNode;
			} else {
				this->last->SetNext(newNode);
				this->last = newNode;
			}

			this->size += 1;


		}

		void Dequeue() {

			if (size == 0) {
				throw std::exception("Empty Queue!!!");
			}

			if (last == first) {

				delete this->first;
				this->first = nullptr;
				this->last = nullptr;
				this->size -= 1;

			}

			LinkedList::Node<T>* auxNode = this->first;
			this->first = auxNode->GetNext();
			delete auxNode;
			this->size -= 1;

		}

		T Peek() {
			return this->first->GetContent();
		}

		T PeekBack() {
			return this->last->GetContent();
		}

		std::string Print() {

			std::string output;

			if (this->first == this->last) return std::to_string(this->first->GetContent());

			for (LinkedList::Node<T>* iterNode = this->first; iterNode; iterNode = iterNode->GetNext()) {

				output += std::to_string(iterNode->GetContent());

				if ( !(iterNode == this->last) ) output += " ";

			}

			return output;

		}


	};




}