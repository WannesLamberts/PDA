//
// Created by wannes on 04.10.20.
//

#ifndef PDA_PDA_H
#define PDA_PDA_H
#include <string>
#include <vector>
struct State;
struct Transition{
  std::string input;
  State* state;
  std::string pop;
  Transition(const std::string &input, State *state,
            std::string pop,
             const std::vector<std::string> &push);
  std::vector<std::string> push;

};
struct State{
  std::string name;
  std::vector<Transition> transitions;
  bool isFinal;
  bool isStart;
  State(const std::string &name, bool isFinal, bool isStart);
};
class PDA {
  std::vector<State> states;
  std::vector<std::string> inputAlphabet;
  std::vector<std::string> stackAlphabet;
  std::string startStackSymbol;
  std::vector<State*> finalStates;
public:
  PDA(const std::vector<std::string> &inputAlphabet,
      const std::vector<std::string> &stackAlphabet,
      const std::string &startStackSymbol);
  bool addState(std::string name,bool isFinal,bool isStart);
  bool addTransition(std::string from,std::string input,std::string to,std::string pop,std::vector<std::string> push);
  State* findState(std::string name);
  bool runInput(std::vector<std::string> input);

};

#endif // PDA_PDA_H
