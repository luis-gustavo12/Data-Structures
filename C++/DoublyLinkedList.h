#pragma once


#include <string>
#include <exception>


#include "DNode.h"





template <typename T>
class DoublyLinkedList {





private:

	DNode<T>* head;
	DNode<T>* last;
	int size;


public:

	DoublyLinkedList() {

		this->head = nullptr;

		this->last = nullptr;

		this->size = 0;

	}


	void PushFront(T content) {

		DNode<T>* node = new DNode<T>(content);

		if (this->size == 0) {

			

			this->head = node;
			this->last = node;
			this->size += 1;
			return;


		}

		// copy of the old head node
		DNode<T>* nextNode = this->head;


		this->head = node;
		node->SetNext(nextNode);
		node->SetPrev(nullptr);

		nextNode->SetPrev(node);
		this->size += 1;




	}

	void PushBack(T content) {

		if (this->size == 0) {
			// not going to throw an exception. easier to call push front.
			PushFront(content);
			return;
		}


		DNode<T>* node = new DNode<T>(content);
		DNode<T>* auxNode = this->last;

		this->last = node;
		auxNode->SetNext(node);
		node->SetPrev(auxNode);
		this->size += 1;

	}

	void Insert(int pos, T content) {


		if (pos > size) {

			throw std::out_of_range("Invalid Position!!");
			return;

		}


		if (pos == 0) {
			PushFront(content);
			return;
		} else if (pos == size) {
			PushBack(content);
			return;
		}

		// indexes start at 0
		int i = 0;
		for (DNode<T>* iterNode = this->head; iterNode != nullptr; iterNode = iterNode->GetNext()) {

			if (i == pos) {

				DNode<T>* newNode = new DNode<T>(content);
				DNode<T>* nextNode = iterNode->GetNext();

				iterNode->GetPrev()->SetNext(newNode);
				newNode->SetPrev(iterNode->GetPrev());
				newNode->SetNext(iterNode);
				iterNode->SetPrev(newNode);

				this->size += 1;
				return;
			}


			i++;

		}

		throw std::exception("Should not be able to reach here!!");

	}

	void Remove(int pos) {



		if (pos >= size) {

			throw std::out_of_range("Exceeded size of list!!");

		}

		if (size == 1) {

			DNode<T>* removeNode = this->head;
			this->head = nullptr;
			this->last = nullptr;
			this->size = 0;

			delete removeNode;
			return;
		}

		// Remove head
		else if (pos == 1) {

			DNode<T>* head = this->head;
			this->head = head->GetNext();
			this->size -= 1;
			delete head;
			return;
		}

		// Remove last
		else if (pos == size - 1) {

			DNode<T>* last = this->last;
			this->last = last->GetPrev();
			this->size -= 1;
			delete last;
			return;

		}

		// In this loop, we have no need to iterate over the first node, and no need to iterate over the last, since we already
		// checked them above, for being special cases, where it would be necessary to move the pointers of this class (last and head).
		int i = 1;
		for (DNode<T>* iterNode = this->head->GetNext(); iterNode != this->last; iterNode = iterNode->GetNext()) {

			if (i == pos) {

				// Now we make the previous node of iterNode to point to iterNode's next node
				iterNode->GetPrev()->SetNext(iterNode->GetNext());
				iterNode->GetNext()->SetPrev(iterNode->GetPrev());
				this->size -= 1;

				delete iterNode;
				return;

			}

			i++;

		}

		throw std::out_of_range("Should not reach here!!");
		
	}

	T GetContent(int index) {

		if (index >= this->size) {
			throw std::out_of_range("Invalid index!!!");
		}

		if (index == size - 1) {
			return this->last->GetContent();
		}

		
		int i = 0;
		for (DNode<T>* iterNode = this->head; iterNode != this->last; iterNode = iterNode->GetNext()) {

			if (i == index) {
				return iterNode->GetContent();
			}

			i++;

		}

		throw std::exception("Should not reach here!!!");

	}

	void Update(T content, int pos) {


		if (pos >= size) {
			throw std::exception("Position out of range!!!");
			return;
		}

		else if (pos == 0) {
			this->head->SetContent(content);
			return;
		}

		else if (pos == this->size - 1) {
			this->last->SetContent(content);
			return;
		}

		int i = 1;
		for (DNode<T>* iterNode = this->head->GetNext(); iterNode != this->last; iterNode = iterNode->GetNext()) {

			if (i == pos) {
				iterNode->SetContent(content);
				return;
			}

			i++;

		}


	}

	T& operator [] (int index) {

		if (index >= this->size) {
			throw std::out_of_range("Index not valid!!");

		}

		DNode<T>* iterNode = this->head;
		for (int i = 0; i < index; i++) {
			iterNode = iterNode->GetNext();
		}

		return iterNode->GetContentReference();

	}


	std::string Print() {

		if (this->size == 1) {

			return std::to_string(this->head->GetContent());

		}

		// iteration over all nodes;
		std::string output;
		int i = 0;
		for (DNode<T>* iterNode = this->head; iterNode != nullptr; iterNode = iterNode->GetNext()) {

			output += std::to_string(iterNode->GetContent());

			if (iterNode != this->last) {
				output += " ";
			}

		}

		return output;

	}

	std::string PrintReverse() {


		if (this->size == 1) {
			return std::to_string(this->head->GetContent());
		}

		std::string output;
		for (DNode<T>* iterNode = this->last; iterNode != nullptr; iterNode = iterNode->GetPrev()) {

			output += std::to_string(iterNode->GetContent());

			if (iterNode != this->head) {

				output += " ";

			}

		}

		return output;

	}


	int GetSize() {
		return this->size;
	}

};



