#pragma once

/**
* 
* 
* 
*  Here's the file I've separated to declare all the tests functions. Instead of creating a main file for every Data Structure class,
*  I'll divide them into modules for each DS test function, and main file will call of them. Ex.: LinkedList will have a function called 
*  TestLinkedList(), which will assure every method, or expected result. Double LinkedList will have one called TestDoubleLinkedList(), and so on.
*  
* 
*  For this exceptions, the functions are intended to return 1 when they catch an exception. This will assure they will be working when smth wrong is done.
*  Whenever a method might throw an exception, the case scenario where this exception could be thrown is tested, having one specific funciton for it
* 
* 
* 
* 
* 
*/

#include <iostream>
#include <vector>
#include <cassert>

#include "Node.h"
#include "LinkedList.h"
#include "DNode.h"
#include "DoublyLinkedList.h"



int TestNode();



/************************************** Tests for LinkedLists **************************************/

template <typename T>
int TestEmptyListException(LinkedList<T> list);

template <typename T>
int TestInsertionException(LinkedList<T> list);

template <typename T>
int TestRemoveException(LinkedList<T> list);


// This test is a very specific one. When you're deleting a list that has only one member, it must be ensure that the head and last nodes point to null and size == 1
int TestRemoveDeletePositionZero();


int TestLinkedList();



/************************************** Tests for DoublyLinkedLists **************************************/


// DoublyLinkedLIsts will have a different type of node, DNode, which is and heritage from Node class
int TestDNodes();

// list can't insert at a posiiton that does not exist
template <typename T>
int TestInsertException(DoublyLinkedList<T>list);

template <typename T>
int TestRemoveException(DoublyLinkedList<T>list);

int TestDoublyLinkedList();