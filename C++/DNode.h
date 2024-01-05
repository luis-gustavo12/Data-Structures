#pragma once




template <typename T>
class DNode {


private:

	T content;
	DNode<T>* prev;
	DNode<T>* next;

public:

	DNode (T content) : content(content), prev(nullptr), next(nullptr) {
	}

	T GetContent() { return this->content; }

	T& GetContentReference() { return this->content;  }

	void SetContent(T content) {
		this->content = content;
	}

	void SetNext(DNode<T>* node) {
		this->next = node;
	}

	DNode<T>* GetNext() {
		return this->next;
	}

	DNode<T>* GetPrev() {
		return this->prev;
	}

	void SetPrev(DNode<T>* node) {
		this->prev = node;
	}





};