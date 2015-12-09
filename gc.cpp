#include <iostream>
#include <vector>
#include <string>
#include "object.h"


std::vector<Object*>* heap;
std::vector<Object*>* rootset;

/* mark an object and those it references */
void mark(Object* obj) {
  obj->marked = true;
  for(auto iter = obj->objectsReferenced->begin(); iter != obj->objectsReferenced->end(); ++iter) {
    mark(*iter);
  }
}

/* delete any unmarked objects in the heap */
void sweep() {
  unsigned int i = 0;
  while(true) {
    if(i==heap->size()) break;
    if(heap->at(i)->marked) i++;
    else heap->erase(heap->begin()+i);
  }
}

/* run mark sweep GC algorithm */
void gc() {
  // initialize heap unmarked
  for(auto heapIter = heap->begin(); heapIter != heap->end(); ++heapIter){
    (*heapIter)->marked = false;
  }
  // recursively mark rootset objects and objects they reference
  for(auto rootIter = rootset->begin(); rootIter != rootset->end(); ++rootIter) {
    mark(*rootIter);
  }
  // sweep
  sweep();
}

/* static for now: root set {a, b, c} with a->{d, e}, b->{a, c}, and f<->g */
void initHeap() {
  heap = new std::vector<Object*>;
  rootset = new std::vector<Object*>;
  Object* a = new Object("a");
  Object* b = new Object("b");
  Object* c = new Object("c");
  Object* d = new Object("d");
  Object* e = new Object("e");
  Object* f = new Object("f");
  Object* g = new Object("g");
  // a references {d, e}
  a->objectsReferenced->push_back(d);
  a->objectsReferenced->push_back(e);
  // b references {a{d, e}, c}
  b->objectsReferenced->push_back(a);
  b->objectsReferenced->push_back(c);
  // f and g reference each other
  f->objectsReferenced->push_back(g);
  g->objectsReferenced->push_back(f);
  // heap: {a, b, c, d, e, f, g}
  heap->push_back(a);
  heap->push_back(b);
  heap->push_back(c);
  heap->push_back(d);
  heap->push_back(e);
  heap->push_back(f);
  heap->push_back(g);
  // root set: {a, b, c}
  rootset->push_back(a);
  rootset->push_back(b);
  rootset->push_back(c);
}

void printHeap() {
  for(auto iter = heap->begin(); iter != heap->end(); ++iter) {
    std::cout<< ((iter != heap->begin()) ? " " : "")  << *((*iter)->name);
  }
  std::cout << std::endl;
}

int main() {
  initHeap();
  printHeap();
  gc();
  printHeap();
}
