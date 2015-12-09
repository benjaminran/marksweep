#include "object.h"

std::size_t idCounter = 1;

Object::Object(std::string objName) {
  id = idCounter++;
  name = &objName;
  objectsReferenced = new std::vector<Object*>;
}

std::size_t Object::getId() {
  return id;
}
