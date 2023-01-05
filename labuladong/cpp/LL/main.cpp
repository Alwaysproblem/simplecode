#include <iostream>
#include <unordered_map>
#include <vector>
#include "common_types/LinkedList/LinkedList.h"

using namespace std;

template<typename T>
void printLL(LinkedListNode<T> *head){
  if (nullptr == head) return;
  printLL<T>(head->next);
  cout << head->val << " ";
}

int main()
{
  LinkedListNode<int> n1(1);
  LinkedListNode<int> n2(2);
  LinkedListNode<int> n3(3);
  LinkedListNode<int> n4(4);
  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  LinkedListNode<int> *head = &n1;
  cout << n1.next << endl;
  printLL<int>(head);
}
