#include <iostream>
#include <fstream>

#include "PDA.h"
int main() {
  PDA pjson;
  pjson.read("jsons/voorbeeld.json");
  pjson.toDot("pdajson.dot");
  return 0;
}
