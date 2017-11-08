#include <string>
#include <sstream>
#include <iostream>
// #include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;

State::State() :
		stateName { "" }, arrayOfLabels { nullptr }, arrayOfTransitions {
				nullptr }, numberLabels { 0 }, numberTransitions { 0 }, capacityOfLabels {
				INITSIZEOFLABELS }, capacityOfTransitions { INITSIZETRANSITIONS } {
	arrayOfTransitions = new Transition[capacityOfTransitions];
	arrayOfLabels = new string[capacityOfLabels];
}

State::State(const string& name) :
		stateName { name }, arrayOfLabels { nullptr }, arrayOfTransitions {
				nullptr }, numberLabels { 0 }, numberTransitions { 0 }, capacityOfLabels {
				INITSIZEOFLABELS }, capacityOfTransitions { INITSIZETRANSITIONS } {
	arrayOfTransitions = new Transition[capacityOfTransitions];
	arrayOfLabels = new string[capacityOfLabels];
}

State::State(const State& other) {
	stateName = other.stateName;
	numberLabels = other.numberLabels;
	numberTransitions = other.numberTransitions;
	capacityOfLabels = other.capacityOfLabels;
	capacityOfTransitions = other.capacityOfTransitions;

	arrayOfTransitions = new Transition[capacityOfTransitions];
	arrayOfLabels = new string[capacityOfLabels];

	for (int i = 0; i < numberTransitions; i++) {
		arrayOfTransitions[i] = other.arrayOfTransitions[i];
	}
	for (int j = 0; j < numberLabels; j++) {
		arrayOfLabels[j] = other.arrayOfLabels[j];
	}
}

State::State(State&& other) :
		stateName { other.stateName }, arrayOfTransitions {
				other.arrayOfTransitions }, arrayOfLabels { other.arrayOfLabels }, numberLabels {
				other.numberLabels }, numberTransitions {
				other.numberTransitions }, capacityOfTransitions {
					other.capacityOfTransitions}, capacityOfLabels {
				other.capacityOfLabels } {
	other.stateName = "";
	other.arrayOfTransitions = nullptr;
	other.arrayOfLabels = nullptr;

	other.numberLabels = 0;
	other.numberTransitions = 0;
	other.capacityOfLabels = 0;
	other.capacityOfTransitions = 0;
}

State::~State() {
	if (arrayOfLabels) {
		delete[] arrayOfLabels;
	}
	if (arrayOfTransitions) {
		delete[] arrayOfTransitions;
	}
}

void State::setName(const string& name) {
	stateName = name;
}

string State::getName() const {
	return "";
}

bool State::addTransition(Transition* trans) {

    for (int i = 0; i<numberTransitions;i++){
        if (*trans == arrayOfTransitions[i]){
            return false;
        }
    }
    
    if (numberTransitions == capacityOfTransitions){
        capacityOfTransitions=capacityOfTransitions*2;
        Transition* temp = new Transition[capacityOfTransitions];
        for (int i = 0; i < numberTransitions;  i++) {
            temp[i]=arrayOfTransitions[i];
        }
        delete [] arrayOfTransitions;
        arrayOfTransitions=temp;
    }
    
    //vraiment un pointeur?
    arrayOfTransitions[numberTransitions] = *trans;
    numberTransitions++;
	return true;
}

bool State::getTransition(const string& targetStateName, Transition*& result) {
    
    for(int i = 0; i<numberTransitions;i++){
        Transition trans;
        trans = arrayOfTransitions[i];
        
        State state;
        //trans.getState2(state);
        
        state.getName();
        
       
    }
	return false;
}

bool State::getTransition(const string& targetStateName,
		const Transition*& result) const {
	// implement me
	return false;
}
bool State::getTransition(int location, Transition*& result) {
    if (location >=0 && location < numberTransitions){
        result = &arrayOfTransitions[location];
        return true;
    }
	return false;
}

bool State::getTransition(int location, const Transition*& result) const {
    if (location >=0 && location < numberTransitions){
        result = &arrayOfTransitions[location];
        return true;
    }
    return false;
}

int State::numberOfTransitions() const {
	return numberTransitions;
}

bool State::addLabel(const string& label) {
	for (int i = 0; i < numberLabels; i++) {
		if (label == arrayOfLabels[i]) {
			return false;
		}
	}
	if (numberLabels == capacityOfLabels) {
		capacityOfLabels *= 2;
		string* temp = new string[capacityOfLabels];
		for (int i = 0; i < numberLabels; i++) {
			temp[i] = arrayOfLabels[i];
		}
		delete[] arrayOfLabels;
		arrayOfLabels = temp;
	}
	arrayOfLabels[numberLabels] = label;
	numberLabels++;
	return true;
}

int State::numberOfLabels() const {
	return numberLabels;
}

//on fait un set et pas un get
bool State::getLabel(int location, string& label) const {
	if (location >= 0 && location < numberLabels) {
		arrayOfLabels[location] = label;
        return true;
	} else {
		return false;
	}
}

State& State::operator=(const State& other) {
	if (this != &other) {
		if (arrayOfLabels)
			delete[] arrayOfLabels;
		if (arrayOfTransitions)
			delete[] arrayOfTransitions;

		stateName = other.stateName;
		numberLabels = other.numberLabels;
		numberTransitions = other.numberTransitions;
		capacityOfLabels = other.capacityOfLabels;
		capacityOfTransitions = other.capacityOfTransitions;

		arrayOfTransitions = new Transition[capacityOfTransitions];
		arrayOfLabels = new string[capacityOfLabels];

		for (int i = 0; i < numberTransitions; i++) {
			arrayOfTransitions[i] = other.arrayOfTransitions[i];
		}
		for (int j = 0; j < numberLabels; j++) {
			arrayOfLabels[j] = other.arrayOfLabels[j];
		}
	}
	return *this;

}

State& State::operator=(State&& other) {
	if (this != &other) {
		string* temps { arrayOfLabels };
		arrayOfLabels = other.arrayOfLabels;
		other.arrayOfLabels = temps;

		Transition* tempt { arrayOfTransitions };
		arrayOfTransitions = other.arrayOfTransitions;
		other.arrayOfTransitions = tempt;

		string tempn { stateName };
		stateName = other.stateName;
		other.stateName = tempn;

		int tempnl { numberLabels };
		numberLabels = other.numberLabels;
		other.numberLabels = tempnl;

		int tempnt { numberTransitions };
		numberTransitions = other.numberTransitions;
		other.numberTransitions = tempnt;

		int tempcl { capacityOfLabels };
		capacityOfLabels = other.capacityOfLabels;
		other.capacityOfLabels = tempcl;

		int tempct { capacityOfTransitions };
		capacityOfTransitions = other.capacityOfTransitions;
		other.capacityOfTransitions = tempct;

	}

	return *this;
}

bool State::operator==(const State& other) const {
	if (stateName == other.stateName) {
		for (int i = 0; i < numberLabels; i++) {
			if (numberLabels == other.numberLabels
					&& arrayOfLabels[i] == other.arrayOfLabels[i]) {
				for (int j = 0; j < numberTransitions; j++) {
					if (numberTransitions == other.numberTransitions
							&& arrayOfTransitions[j]
									== other.arrayOfTransitions[j]) {
						return true;
					}
				}

			}
		}

	}
	return false;
}

void State::print(ostream& stream) const {
	bool first = true;
	stream << getName() << "(";

	for (int i = 0; i < this->numberOfLabels(); i++) {
		if (first) {
			first = false;
		} else {
			stream << ",";
		}
		string s;
		getLabel(i, s);
		stream << s;
	}
	stream << ")";
}

ostream& operator<<(ostream& stream, const State& st) {
	st.print(stream);
	return stream;
}

