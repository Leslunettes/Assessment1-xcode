#include <string>
#include <sstream>
#include <iostream>
// #include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;

State::State()
{
	name = "";

	arrayOfTransitions = new Transition[SIZETRANSITIONS];
	arrayOfLabels = new string[SIZEOFLABELS];

	// initialiser arrays
	// implement me
}  

State::State(const string& name) {
	// implement me
	this->name = name;
	// initialiser arrays
}

State::State(const State& other) {
	// implement me
	&this->name = &other.name;

}

State::State(State&& other) {
	// implement me
}

State::~State() 
{
	// implement me
}

void State::setName(const string& name)
{
	this->name=name;

}

string State::getName() const
{
	// implement me
  return name;
}

bool State::addTransition(Transition* trans) 
{
	// implement me
    return false;
}

bool State::getTransition(const string& targetStateName, Transition*& result)
{
	// implement me
  return false;
}

bool State::getTransition(const string& targetStateName, const Transition*& result) const
{
	// implement me
  return false;
}
bool State::getTransition(int location, Transition*& result)
{
	// implement me
    return false;
}

bool State::getTransition(int location, const Transition*& result) const
{
	// implement me
    return false;
}

int State::numberOfTransitions() const
{
    int counter = 0;
    // Valeur à vérifier
    for (int i = 0; i<SIZETRANSITIONS;i++){
        while (arrayOfTransitions !=0){
            counter ++;
        }
    }
  return counter;
}

bool State::addLabel(const string& label) 
{
    
    int position = 0;
    while (arrayOfLabels == 0) {
        position++;
    }
    if (position== SIZEOFLABELS){
        arrayOfLabels [position]= label;
        return true;
    }
    return false;
}

int State::numberOfLabels() const
{
    int counter = 0;
    // Valeur à vérifier
    for (int i = 0; i<SIZEOFLABELS;i++){
        // par quelle string le tableau arrayOfLabel est il initialisatier ? 0 est un int !
        while (arrayOfLabels !=0){
            counter ++;
        }
    }
    return counter;
}

bool State::getLabel(int location, string& label) const
{
    if (location > 0 && location < SIZETRANSITIONS){
        // valeur 0 également à vérifier
        if (arrayOfLabels[location] == 0){
            arrayOfLabels[location]= label;
            return true;
        }else {
            return arrayOfLabels [location];
            // pour on retourne un label et pas un bool?
        }
    }
    return false;
}

State& State::operator=(const State& other)
{
	// implement me
	State removeMe;
	return removeMe;
}

State& State::operator=(State&& other)
{
	// implement me
	State removeMe;
	return removeMe;
}

bool State::operator==(const State& other) const {
	// implement me
    return false;
}

void State::print(ostream& stream) const
{
  bool first = true;
  stream << getName() << "(";
 
  for (int i=0 ; i<this->numberOfLabels() ; i++) {
    if (first) {
      first = false;
    }
    else {
      stream << ",";
    }
    string s;
    getLabel(i,s);
    stream << s;
  }
  stream << ")";
}

ostream& operator<< (ostream& stream, const State& st) 
{
  st.print(stream);
  return stream;
}

