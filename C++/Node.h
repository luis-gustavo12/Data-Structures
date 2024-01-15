#pragma once


template <typename T>
class Node {


private:

    T content;
    Node<T>* next;





public:





    Node<T>(T content) : content(content), next(nullptr) {

    }



    Node<T>* GetNext() {
        return this->next;
    }


    void SetNext(Node<T>* node) {
        this->next = node;
    }

    T GetContent() {
        return this->content;
    }

    T& GetContentReference() {


        return this->content;
    }




    void UpdateValue(T value) {
        this->content = value;
    }






};