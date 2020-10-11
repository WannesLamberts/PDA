#include <iostream>
#include <fstream>

#include "PDA.h"
int main() {
  std::vector<std::string> inputAlphabet={"a","b"};
  std::vector<std::string> stackAlphabet={"a","Z"};
  PDA p(inputAlphabet,stackAlphabet,"Z");
  p.addState("q0",false,true);
  p.addState("q1",false,false);
  p.addState("qf",true,false);
  p.addTransition("q0","a","q0",{"Z"},{"a","a","Z"});
  p.addTransition("q0","a","q0",{"a"},{"a","a","a"});
  p.addTransition("q0","b","q1",{"a"},{"epsilon"});
  p.addTransition("q1","b","q1",{"a"},{"epsilon"});
  p.addTransition("q1","epsilon","qf",{"Z"},{"Z"});
  std::vector<std::string> test={"a","a","b","b","b","b"};
  std::vector<std::string> input1={"a","a","b"};
  std::vector<std::string> input0={"a","a","b","b","b","b"};
  std::cout<<"run aabbbb"<<std::endl;
  std::cout<<p.runInput(input0)<<std::endl;
  std::cout<<"run aab"<<std::endl;
  std::cout<<p.runInput(input1)<<std::endl;
  p.toDot("pda.dot");
  return 0;
}
