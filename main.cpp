#include <iostream>

#include "PDA.h"
int main() {
  std::vector<std::string> inputAlphabet={"a","b"};
  std::vector<std::string> stackAlphabet={"a","Z"};
  PDA p(inputAlphabet,stackAlphabet,"Z");
  p.addState("q0",false,true);
  p.addState("q1",false,false);
  p.addState("qf",true,false);
  p.addTransition("q0","a","q0",{"a"},{"a","a","a"});
  p.addTransition("q0","a","q0",{"Z"},{"a","a","Z"});
  p.addTransition("q0","b","q1",{"a"},{"epsilon"});
  p.addTransition("q1","b","q1",{"a"},{"epsilon"});
  p.addTransition("q1","b","qf",{"Z"},{"Z"});
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
