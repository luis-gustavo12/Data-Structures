#pragma once


#include <string>
#include <cstdio>
#include <exception>

#include "DoublyLinkedList.h"


namespace HashTable {



	template <typename K, typename V>
	class Pair {

	private:

		K key;
		V value;


	public:

		Pair(K key, V value) {
			this->key = key;
			this->value = value;
		}

		K GetKey() {
			return this->key;
		}

		V GetValue() {
			return this->value;
		}

		void SetKey(K newKey) {
			this->key = newKey;
		}

		void SetValue(V newValue) {
			this->value = newValue;
		}

	};



	template <typename K, typename V>
	class HashTable {


	private:

		DoublyLinkedList::DoublyLinkedList<Pair<K, V>>* table;


	public:

		HashTable() {

			table = new DoublyLinkedList::DoublyLinkedList<Pair<K, V>>();

		}

		HashTable(K key, V value) {
			table = new DoublyLinkedList::DoublyLinkedList<Pair<K, V>>();
			Pair<K, V> pair (key, value);
			table->PushBack(pair);

		}

		~HashTable() {
			delete table;
		}

		void Insert(K key, V value) {


			Pair<K, V> pair = Pair<K, V>(key, value);
			table->PushBack(pair);


		}

		void Delete(K key) {

			for (DoublyLinkedList::Node<Pair<K, V>>* iterNode = this->table->GetHead(); iterNode; iterNode->GetNext()) {

				Pair <K, V>* pair = iterNode->GetContent();

				if (pair->GetKey() == key) {
					int position = table->FindPos(pair);
					if (position) {
						table->Remove(position);
						return;
					}
					throw std::exception("Key unexistent!!!");
				}

			}

			throw std::exception("Key unexistent!!!");

		}

		int GetNumberOfKeys() {
			return this->table->Size();
		}

		V operator [] (K key) {

			for (DoublyLinkedList::Node<Pair <K, V>>* iterNode = this->table->GetHead(); iterNode;  iterNode = iterNode->GetNext()) {

				Pair<K, V> pair = iterNode->GetContent();

				if (pair.GetKey() == key) {
					return pair.GetValue();
				}

			}

			return NULL;

		}

		std::string PrintKeys() {

			if (table->GetSize() == 0) {
				throw std::exception("Not valid!!");
			}

			std::string output;

			for (DoublyLinkedList::Node<Pair<K, V>>* iterNode = this->table->GetHead(); iterNode; iterNode = iterNode->GetNext()) {

				Pair<K, V> pair = iterNode->GetContent();

				output += static_cast<std::string>(pair.GetKey());

				if (iterNode->GetNext()) {
					output += " ";
				}

			}

			return output;

		}

		std::string Print() {

			if (this->table->GetSize() == 0) {
				throw std::exception("Not valid!!");
			}

			std::string output;

			// format = [key, value]
			for (DoublyLinkedList::Node<Pair<K, V>>* iterNode = this->table->GetFirstValueReference(); iterNode; iterNode = iterNode->GetNext()) {
				
				Pair<K, V>* pair = iterNode->GetContent();
				output += std::string(std::sprintf("[%s, %s]", std::to_string(pair->GetKey()), std::to_string(pair->GetValue())) );

				if (iterNode->GetNext()) {
					output += ", ";
				}

				return output;

			}

			return output;

		}

		

	};




}