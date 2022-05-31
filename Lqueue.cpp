/*
** File:    Lqueue.cpp
** Project: CMSC 202 Project 5, Spring 2022
** Author:  Ben Maher
** Date:    5/7/22
** Section: 50/52
** E-mail:  bmaher1@umbc.edu
*/

#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// Templated node class used in templated linked list
template <class T> class Node {
public:
  Node(const T &data);         // Constructor
  T &GetData();                // Gets data from node
  void SetData(const T &data); // Sets data in node
  Node<T> *GetNext();          // Gets next pointer
  void SetNext(Node<T> *next); // Sets next pointer
private:
  T m_data;
  Node<T> *m_next;
};

// Overloaded constructor for Node
template <class T> Node<T>::Node(const T &data) {
  m_data = data;
  m_next = NULL;
}

// Returns the data from a Node
template <class T> T &Node<T>::GetData() { return m_data; }

// Sets the data in a Node
template <class T> void Node<T>::SetData(const T &data) { m_data = data; }

// Gets the pointer to the next Node
template <class T> Node<T> *Node<T>::GetNext() { return m_next; }

// Sets the next Node
template <class T> void Node<T>::SetNext(Node<T> *next) { m_next = next; }

template <class T> class Lqueue {
public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to
  // nullptr Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated
  // nodes)
  //                 to have no memory leaks!
  // Required
  ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue &);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T> &operator=(Lqueue &);
  // Name: Push
  // Preconditions: Takes in data. Creates new node.
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T &);
  // Name: Pop
  // Preconditions: Lqueue with at least one node.
  // Postconditions: Removes first node in the lqueue, returns data from first
  // node. Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T &);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At(int x);

private:
  Node<T> *m_head; // Node pointer for the head
  Node<T> *m_tail; // Node pointer for the tail
  int m_size;      // Number of nodes in queue
};

template <class T> Lqueue<T>::Lqueue() {
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

template <class T> Lqueue<T>::~Lqueue() { Clear(); }

template <class T> Lqueue<T>::Lqueue(const Lqueue &otherQueue) {
  Node<T> *temp = otherQueue.m_head;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  // create a deep copy of the data and store it in our other Queue
  while (temp != nullptr) {
    Push(temp->GetData());
    temp = temp->GetNext();
  }
}

template <class T> Lqueue<T> &Lqueue<T>::operator=(Lqueue &otherQueue) {
  // protect against self assignment
  if (this == &otherQueue) {
    return *this;
  }
  Clear();
  Node<T> *temp = otherQueue.m_head;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  while (temp != nullptr) {
    Push(temp->GetData());
    temp = temp->GetNext();
  }
  return *this;
}

template <class T> void Lqueue<T>::Push(const T &data) {
  // create node ptr of data that will be used to update the queue
  Node<T> *newNode = new Node<T>(data);
  m_size++;
  if (m_tail == nullptr) {
    m_head = newNode;
    m_tail = newNode;
  } else if (m_tail != nullptr) {
    m_tail->SetNext(newNode);
    m_tail = newNode;
  }
}
template <class T> T Lqueue<T>::Pop() {
  // check is queue is empty
  if (m_head == nullptr) {
    return T();
  }
  m_size--;
  // new var headData of type T
  T headData = m_head->GetData();
  Node<T> *temp = m_head;
  m_head = m_head->GetNext();
  delete temp;
  return headData;
}
template <class T> int Lqueue<T>::GetSize() 
{
  return m_size;
}
template <class T> void Lqueue<T>::Display() {
  Node<T> *temp = m_head;
  //loop through the queue and display data
  while (temp != nullptr) {
    cout << temp->GetData() << endl;
    temp = temp->GetNext();
  }
}
template <class T> T Lqueue<T>::Front() {
  //retrieve data from the front of the queue
  Node<T> *temp = m_head;
  if (temp == nullptr) {
    return T();
  }
  return m_head->GetData();
}
template <class T> bool Lqueue<T>::IsEmpty() {
  //return if the queue is empty
  if (m_head == nullptr) {
    return true;
  }
  return false;
}

template <class T> int Lqueue<T>::Find(T &userInput) {
  //find an index within our queue
  Node<T> *temp = m_head;
  int index = 0;
  while (temp != nullptr) {
    if (temp->GetData() == userInput) {
      return index;
    }
    temp = temp->GetNext();
    index++;
  }
  return -1;
}

template <class T> void Lqueue<T>::Swap(int index) {
  //swap the index of two queue positions
  if (index <= 0 || index >= GetSize()) {
    return;
  }
  Node<T> *curr = m_head;
  Node<T> *prev = m_head;

  for (int i = 0; i < index; i++) {
    prev = curr;
    curr = curr->GetNext();
  }
  prev->SetNext(curr->GetNext());
  curr->SetNext(prev);
}

template <class T> void Lqueue<T>::Clear() {
  while (m_head != nullptr) {
    Node<T> *temp = m_head;
    m_head = m_head->GetNext();
    delete temp;
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

template <class T> T Lqueue<T>::At(int x) {
  if (x < 0 || x >= GetSize()) {
    return T();
  }
  Node<T> *curr = m_head;

  for (int i = 0; i < x; i++) {
    curr = curr->GetNext();
  }
  return curr->GetData();
}

#endif
