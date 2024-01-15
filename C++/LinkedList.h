

/**
 * @brief: This is the main file for LinkedList implementation. By browsing on the internet, I found that
 * generic templates give less headache if defined and implemented in the header file. So...
 *
 *
 *
 * TODO: it might be better if instead of iterating with a for loop, to use operator overloads to make something like
 *
 *  for (auto i : LinkedList). Still need to learn to do this
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


#pragma once


#include <string>
#include <iostream>
#include <exception> 




namespace LinkedList {

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



    template <typename T>
    class LinkedList {

    private:

        Node<T>* head;
        Node<T>* last;
        int size;


    public:


        LinkedList() {

            this->head = nullptr;
            this->last = nullptr;
            this->size = 0;


        }

        // Same as ~LinkedList(). But for reasons I don't know, vsCommunity does not debug correctly when using Deconstructors
        void DeleteItems() {

            while (this->head) {

                Node<T>* deleleteNode = this->head;

                this->head = this->head->GetNext();

                delete deleleteNode;


            }
        }

        int GetSize() {
            return this->size;
        }

        Node<T>* GetHead() {
            return this->head;
        }

        Node<T>* GetLast() {
            return this->last;
        }


        void PushBack(T content) {


            if (size == 0) {

                this->head = new Node<T>(content);
                this->last = this->head;
                this->size += 1;
                return;

            }


            Node<T>* node = new Node<T>(content);

            if (this->last == this->head) {


                // list has one element
                this->head->SetNext(node);
                this->last = node;
                this->size += 1;
                return;

            }

            Node<T>* auxNode = this->last;
            auxNode->SetNext(node);
            this->last = node;
            this->size += 1;




        }

        std::string Print() {

            if (this->size == 0) {
                throw std::out_of_range("Empty list!!!");
            }

            else if (this->last == this->head) {

                return std::to_string(this->head->GetContent());

            }

        

            std::string output;

            for (Node<T>* iterNode = this->head; iterNode != nullptr; iterNode = iterNode->GetNext()) {

                output += std::to_string(iterNode->GetContent());

                if (iterNode == this->last) {

                    return output;
                }

                output += " ";
                continue;

            

            }


            throw std::exception("Should not reach here!!");



        }

        void PushFront(T content) {

            Node<T>* newNode = new Node<T>(content);
            Node<T>* auxNode = this->head;

            this->head = newNode;
            this->head->SetNext(auxNode);

            if (this->size == 0) {
                this->last = this->head;
            }

            if (this->size == 1) this->last = auxNode;

            this->size += 1;

        }

        // Indexes start at 0
        void Insert(T content, int pos) {

            // 0  1  2
            // [] [] []

            // size == 3. pos == 3, == addlast

            if (pos > size) {
                throw std::out_of_range("Invalid position to insert!!");
            }

            else if (pos == 0) {
                PushFront(content);
                return;
            }

            // You're asking to Insert at the last one. Though it seems kind of controversial to insert at a position that "doesn't exist" yet,
            // I'm leaving an exception for the case when you want to insert at the last element. Size + 1, is invalid
            else if (pos == size) {

                PushBack(content);
                return;

            }


            int i = 0;

            for (Node<T>* iterNode = this->head; iterNode != nullptr; iterNode = iterNode->GetNext()) {

                // Since indexes start at 0, when I want to insert at the 3 position, once I get i == 2, the next node to which iterNode points,
                // is the Node with the new content, and the old 3 position node, is the 4th
                if (i == pos - 1) {

                    Node<T>* addNode = new Node<T>(content);
                    Node<T>* auxNode = iterNode->GetNext(); // Old node. In the example, old 3 position
                    iterNode->SetNext(addNode);
                    addNode->SetNext(auxNode);
                    size += 1;
                    return;


                }

                i++;
            }



        }

        void Remove(int pos) {

            // 0  1  2  3  4
            // [] [] [] [] []

            // rm 5 == wrong; size == 5


            if (pos >= this->size) {

                throw std::out_of_range("Invalid position value!!");
                return;
            }


            // Special cases that envolve head and tail operations

    

        
        
            else if (pos == 0) {


                // When there's only the head node, we must also make last and head point it to null. This MUST BE tested, for not having memory issues
                // By debugging when not making this procedure above, I could realise that this->kast (which wasn't being handled) was still pointing to another node
                if (this->size == 1) { 
                    this->head = nullptr;
                    this->last = nullptr;
                    this->size -= 1;
                    return;
                }

                Node<T>* node = this->head;
                this->head = this->head->GetNext();
                delete node;
                this->size -= 1;
                return;


            }




            int i = 0;
            for (Node<T>* iterNode = this->head; iterNode != nullptr; iterNode = iterNode->GetNext()) {

                // If it's asked to remove the last node, we must stop one node before it, since we don't have a previous node, just like double linked lists do
                // For deleting the last node, the one before the last, is now the last
                if (iterNode->GetNext() == this->last) {
                    Node<T>* auxNode = this->last;
                    this->last = iterNode;
                    delete auxNode;
                    this->size -= 1;
                    return;
                }

                else if (i == pos - 1) {

                    Node<T>* nodeToBeRemoved = iterNode->GetNext();
                    Node<T>* nodeToBeAttached = nodeToBeRemoved->GetNext();

                    iterNode->SetNext(nodeToBeAttached);
                    delete nodeToBeRemoved;
                    this->size -= 1;
                    return;
                }


                i++;
            }


        



        }

        void Update(T value, int pos) {

            int i = 0;


            for (Node<T>* auxNode = this->head; auxNode != nullptr; auxNode = auxNode->GetNext()) {

                if (i == pos) {
                    auxNode->UpdateValue(value);
                    return;
                }

                i++;
            }

            throw std::exception("Should not reach here!!!");

        }

        T GetValue(int pos) {

            if (this->size <= 0 || pos >= this->size) {
                throw std::out_of_range("Invalid position!!!");
            }

            else if (pos == 0) {

                return this->head->GetContent();

            }

            else if (pos == size - 1) {

                return this->head->GetContent();

            }

            Node<T>* iterNode = this->head->GetNext();

            // for i != this->size - 2, since we already handled size - 1, size - 2 is the last addressable content in this case
            for (int i = 1; i != this->size - 2; i++) {

                if (i == pos) {
                    return iterNode->GetContent();
                }

                iterNode = iterNode->GetNext();

            }


            throw std::exception("Should not reach here!!!");


        }


        //T operator [] (int index) {
        //    return this->GetValue(index);
        //}

        T& operator [] (size_t index) {

            if (index >= this->size) {
                throw std::out_of_range("Invalid index!!");
            }

            Node<T>* iterNode = this->head;
            for (std::size_t i = 0; i < index; ++i) {
            
                iterNode = iterNode->GetNext();
            }
        

            return iterNode->GetContentReference();


        }

    






    

   



    };


}