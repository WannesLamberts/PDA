//
// Created by wannes on 04.10.20.
//

#include "PDA.h"
#include <stack>
#include<tuple>
#include <iostream>
PDA::PDA(const std::vector<std::string> &inputAlphabet,
         const std::vector<std::string> &stackAlphabet,
         const std::string &startStackSymbol)
    : inputAlphabet(inputAlphabet), stackAlphabet(stackAlphabet),
      startStackSymbol(startStackSymbol) {}
bool PDA::addTransition(std::string from, std::string input, std::string to,std::string pop,std::vector<std::string> push) {
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
  State state(name,isFinal,isStart);
  states.push_back(state);
  return true;
}
void eclose(std::vector<std::tuple <State*, std::stack<std::string>>> &currentstate){
  for (int j = 0; j < currentstate.size(); ++j) {// pas de input toe op elke state waar je in zit
    for (int k = 0; k < std::get<0>(currentstate[j])->transitions.size(); ++k) {//loop over elke transitie van die states waar je in zit
      if(std::get<0>(currentstate[j])->transitions[k].input=="epsilon" &&
          (std::get<0>(currentstate[j])->transitions[k].pop==std::get<1>(currentstate[j]).top()
          ||std::get<0>(currentstate[j])->transitions[k].pop=="epsilon")){//kijken of er epsilon transities zijn en of de pop gelijk is aan de top of stack van de current state
        currentstate.push_back(make_tuple(std::get<0>(currentstate[j])->transitions[k].state,std::get<1>(currentstate[j])));
        if(std::get<0>(currentstate[j])->transitions[k].pop!="epsilon") {
          std::get<1>(currentstate[currentstate.size() - 1]).pop();
        }
        std::vector<std::string> pushcheck={"epsilon"};
        if(std::get<0>(currentstate[j])->transitions[k].push!=pushcheck){
          for (int i = std::get<0>(currentstate[j])->transitions[k].push.size()-1; i >=0 ; --i) {
            std::get<1>(currentstate[currentstate.size()-1]).push(std::get<0>(currentstate[j])->transitions[k].push[i]);
          }

        }
      }
    }
  }
}
bool PDA::runInput(std::vector<std::string> input) {
  State* startState;
  for (int i = 0; i < states.size(); ++i) {
    if(states[i].isStart){
      startState=&states[i];
    }
  }
  std::vector<std::tuple <State*, std::stack<std::string>>> currentstate;
  std::stack<std::string> begin;
  begin.push("Z");
  std::tuple <State*, std::stack<std::string>> start=make_tuple(startState, begin);
  currentstate.push_back(start);
  eclose(currentstate);
  for (int i = 0; i < input.size(); ++i) { //loop over elke input
    //input lezen
    std::vector<std::tuple <State*, std::stack<std::string>>> newStates;
    eclose(currentstate);
    for (int j = 0; j < currentstate.size(); ++j) {
      for (int k = 0; k < std::get<0>(currentstate[j])->transitions.size(); ++k) {
        if(std::get<0>(currentstate[j])->transitions[k].input==input[i] &&
           (std::get<0>(currentstate[j])->transitions[k].pop==std::get<1>(currentstate[j]).top()
            ||std::get<0>(currentstate[j])->transitions[k].pop=="epsilon"))
        {
          newStates.push_back(make_tuple(std::get<0>(currentstate[j])->transitions[k].state,std::get<1>(currentstate[j])));
          if(std::get<0>(currentstate[j])->transitions[k].pop!="epsilon"){
            std::get<1>(newStates[newStates.size()-1]).pop();
          }
          std::vector<std::string> pushcheck={"epsilon"};
          if(std::get<0>(currentstate[j])->transitions[k].push!=pushcheck){
            for (int i = std::get<0>(currentstate[j])->transitions[k].push.size()-1; i >=0 ; --i) {
              std::get<1>(newStates[newStates.size()-1]).push(std::get<0>(currentstate[j])->transitions[k].push[i]);
            }
          }
        }
      }
    }
    currentstate=newStates;
    eclose(currentstate);
  }
  for (int l = 0; l < currentstate.size(); ++l) {
    if(std::get<0>(currentstate[l])->isFinal){
      return true;
    }
  }
  return false;
}


Transition::Transition(const std::string &input, State *state,
                       std::string pop,
                       const std::vector<std::string> &push)
    : input(input), state(state), pop(pop), push(push) {}
State::State(const std::string &name, bool isFinal, bool isStart)
    : name(name), isFinal(isFinal), isStart(isStart) {}
