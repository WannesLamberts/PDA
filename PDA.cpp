//
// Created by wannes on 04.10.20.
//

#include "PDA.h"


PDA::PDA(const std::vector<std::string> &inputAlphabet,
         const std::vector<std::string> &stackAlphabet,
         const std::string &startStackSymbol)
    : inputAlphabet(inputAlphabet), stackAlphabet(stackAlphabet),
      startStackSymbol(startStackSymbol) {}
bool PDA::addTransition(std::string from, std::string input, std::string to,std::vector<std::string> pop,std::vector<std::string> push) {
  Transition t(input,findState(to),pop,push);
  findState(from)->transitions.push_back(t);
  return true;
}
State *PDA::findState(std::string name) {
  for (int i = 0; i < states.size(); ++i) {
    if(name==states[i].name){
      return &states[i];
    }
  }
  return nullptr; }
bool PDA::addState(std::string name,bool isFinal,bool isStart) {
  State state(name,isFinal);
  states.push_back(state);
  if(isStart)
    startState=&states[states.size()-1];
  return true;
}
bool PDA::runInput(std::vector<std::string> input) {
  return false;
}

State::State(const std::string &name, bool isFinal)
    : name(name), isFinal(isFinal) {}

Transition::Transition(const std::string &input, State *state,
                       const std::vector<std::string> &pop,
                       const std::vector<std::string> &push)
    : input(input), state(state), pop(pop), push(push) {}
