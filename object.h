#ifndef __OBJ_CPP__
#define __OBJ_CPP__
#include <string>
#include <vector>

class Object {
 private:
  std::size_t id;
 public:
  bool marked;
  std::string* name;
  Object(std::string name);
  std::size_t getId();
  std::vector<Object*>* objectsReferenced;
};

#endif
