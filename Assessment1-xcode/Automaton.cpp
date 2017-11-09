/*
 * Automaton.cpp
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */
#include <iostream>
#include <string>
#include "Automaton.h"

Automaton::Automaton() :
automatonName { "" }, arrayOfStates { nullptr }, arrayOfTransitions {
    nullptr }, numberStates { 0 }, numberTransitions { 0 }, capacityOfState {
        INITSIZEOFSTATES }, capacityOfTransitions { INITSIZETRANSITIONS } {
            arrayOfStates = new State[capacityOfState];
            arrayOfTransitions = new Transition[capacityOfTransitions];
        }

Automaton::Automaton(const std::string& name) :
automatonName { name }, arrayOfStates { nullptr }, arrayOfTransitions {
    nullptr }, numberStates { 0 }, numberTransitions { 0 }, capacityOfState {
        INITSIZEOFSTATES }, capacityOfTransitions { INITSIZETRANSITIONS } {
            arrayOfStates = new State[capacityOfState];
            arrayOfTransitions = new Transition[capacityOfTransitions];
        }

// verifier suivant le commentaire
Automaton::Automaton(const Automaton& other) {
    automatonName = other.automatonName;
    numberStates = other.numberStates;
    numberTransitions = other.numberTransitions;
    capacityOfState = other.capacityOfState;
    capacityOfTransitions = other.capacityOfTransitions;
    
    arrayOfStates = new State[capacityOfState];
    arrayOfTransitions = new Transition[capacityOfTransitions];
    
    for (int i = 0; i < numberStates; i++) {
        arrayOfStates[i] = other.arrayOfStates[i];
    }
    
    for (int j = 0; j < numberTransitions; j++) {
        arrayOfTransitions[j] = other.arrayOfTransitions[j];
    }
    
}

Automaton::Automaton(Automaton&& other) :
automatonName { other.automatonName }, arrayOfTransitions {
    other.arrayOfTransitions }, arrayOfStates { other.arrayOfStates }, numberStates {
        other.numberStates }, numberTransitions {
            other.numberTransitions }, capacityOfTransitions {
                other.capacityOfTransitions }, capacityOfState {
                    other.capacityOfState } {
                        other.automatonName = "";
                        other.arrayOfTransitions = nullptr;
                        other.arrayOfStates = nullptr;
                        
                        other.numberStates = 0;
                        other.numberTransitions = 0;
                        other.capacityOfState = 0;
                        other.capacityOfTransitions = 0;
                    }

Automaton::~Automaton() {
    if (arrayOfStates) {
        delete[] arrayOfStates;
    }
    if (arrayOfTransitions) {
        delete[] arrayOfTransitions;
    }
}

void Automaton::setName(const std::string& name) {
    automatonName = name;
}

std::string Automaton::getName() const {
    return automatonName;
}

bool Automaton::addState(const std::string& stateName, State*& state) {
    
    for (int i=0;i<numberStates;i++){
        if (arrayOfStates[i].getName()==stateName){
            return false;
        }
    }
    if (numberStates==capacityOfState){
        capacityOfState=capacityOfState*2;
        State* temp = new State[capacityOfState];
        for (int i = 0; i < numberStates;  i++) {
            temp[i] = arrayOfStates[i];
        }
        delete [] arrayOfStates;
        arrayOfStates=temp;
    }
    arrayOfStates[numberStates]=*state;
    numberStates++;
    return true;
}

bool Automaton::getState(const std::string& stateName, State*& state) {
    for (int i =0;i<numberStates;i++){
        if (arrayOfStates[i].getName()==stateName){
            state = &arrayOfStates[i];
            return true;
        }
    }
    return false;
}

bool Automaton::getState(int i, State*& st) {
    if (i>=0 && i<numberStates){
        st=&arrayOfStates[i];
        return true;
    }
    return false;
}

bool Automaton::getState(int i, const State*& st) const {
    if (i>=0 && i<numberStates){
        st=&arrayOfStates[i];
        return true;
    }
    return false;
}

int Automaton::numberOfStates() const {
    return numberStates;
}

bool Automaton::addTransition(const std::string& nameSt1,
                              const std::string& nameSt2, Transition*& trans) {
    // If this transition between the two states already exists in
    // the automaton return false.
      // we can use getTransition ()
    for (int j = 0; j<numberTransitions;j++){
        State* st1;
        arrayOfTransitions[j].getState1(st1);
        State* st2;
        arrayOfTransitions[j].getState2(st2);
        if (st1->getName()==nameSt1 && st2->getName() == nameSt2){
            return false;
        }
    }
    
    
    // If one of the states does not exist in the automaton return
    // false.
    
  
    bool stOK1 = false;
    State* start = nullptr;
    bool stOK2 = false;
    State* end = nullptr;
    
    for (int i = 0; i<numberStates;i++){
        if (arrayOfStates[i].getName()==nameSt1){
            stOK1 = true;
            start = &arrayOfStates[i];
        }
        if (arrayOfStates[i].getName()==nameSt2)
        {
            stOK2 = true;
            end = &arrayOfStates[i];
        }
    }
    if (stOK1 && stOK2){
        //new transition
        Transition t(start,end);
        // transition to pointer
        trans = &t;
        if (numberTransitions==capacityOfTransitions) {
            capacityOfTransitions=capacityOfTransitions*2;
            Transition* temp = new Transition[capacityOfTransitions];
            for (int i = 0; i < numberOfTransitions();  i++) {
                temp[i]=arrayOfTransitions[i];
            }
            delete [] arrayOfTransitions;
            arrayOfTransitions=temp;
        }
        arrayOfTransitions[numberTransitions] = t;
        numberTransitions++;
        return true;
    }else{
        return false;}
}

bool Automaton::getTransition(const std::string& nameSt1,
                              const std::string& nameSt2, Transition*& trans) {
    for (int j = 0; j<numberTransitions;j++){
        State* st1;
        arrayOfTransitions[j].getState1(st1);
        State* st2;
        arrayOfTransitions[j].getState2(st2);
        if (st1->getName()==nameSt1 && st2->getName() == nameSt2){
            trans = &arrayOfTransitions[j];
            return true;
        }
    }
    return false;
}

bool Automaton::getTransition(int location, Transition*& trans) {
    if (location >=0 && location < numberTransitions){
        trans = &arrayOfTransitions[location];
        return true;
    }
    return false;
}

bool Automaton::getTransition(int location, const Transition*& trans) const {
    if (location >=0 && location < numberTransitions){
        trans = &arrayOfTransitions[location];
        return true;
    }
    return false;
}

int Automaton::numberOfTransitions() const {
    return numberTransitions;
}

void Automaton::print(std::ostream& stream) const {
    stream << "Automaton(" << getName() << "):" << std::endl;
    if (numberOfStates() > 0) {
        stream << "States:" << std::endl;
        for (int i = 0; i < numberOfStates(); i++) {
            const State* s = nullptr;
            getState(i, s);
            stream << *s << std::endl;
        }
        
        if (numberOfTransitions() > 0) {
            stream << "Transitions:" << std::endl;
            for (int j = 0; j < numberOfTransitions(); j++) {
                const Transition* t = nullptr;
                getTransition(j, t);
                stream << *t << std::endl;
            }
        }
    }
}

Automaton& Automaton::operator=(const Automaton& other) {
    if (this != &other) {
        if (arrayOfStates)
            delete[] arrayOfStates;
        if (arrayOfTransitions)
            delete[] arrayOfTransitions;
        
        automatonName = other.automatonName;
        numberStates = other.numberStates;
        numberTransitions = other.numberTransitions;
        capacityOfState = other.capacityOfState;
        capacityOfTransitions = other.capacityOfTransitions;
        
        arrayOfTransitions = new Transition[capacityOfTransitions];
        arrayOfStates = new State[capacityOfState];
        
        for (int i = 0; i < numberTransitions; i++) {
            arrayOfTransitions[i] = other.arrayOfTransitions[i];
        }
        for (int j = 0; j < numberStates; j++) {
            arrayOfStates[j] = other.arrayOfStates[j];
        }
    }
    return *this;
}

Automaton& Automaton::operator=(Automaton&& other) {
    if (this != &other) {
        State* temps { arrayOfStates };
        arrayOfStates = other.arrayOfStates;
        other.arrayOfStates = temps;
        
        Transition* tempt { arrayOfTransitions };
        arrayOfTransitions = other.arrayOfTransitions;
        other.arrayOfTransitions = tempt;
        
        std::string tempn { automatonName };
        automatonName = other.automatonName;
        other.automatonName = tempn;
        
        int tempnl { numberStates };
        numberStates = other.numberStates;
        other.numberStates = tempnl;
        
        int tempnt { numberTransitions };
        numberTransitions = other.numberTransitions;
        other.numberTransitions = tempnt;
        
        int tempcl { capacityOfState };
        capacityOfState = other.capacityOfState;
        other.capacityOfState = tempcl;
        
        int tempct { capacityOfTransitions };
        capacityOfTransitions = other.capacityOfTransitions;
        other.capacityOfTransitions = tempct;
    }
    return *this;
}

bool Automaton::operator==(const Automaton& other) const {
    if (automatonName == other.automatonName) {
        for (int i = 0; i < numberStates; i++) {
            if (numberStates == other.numberStates
                && arrayOfStates[i] == other.arrayOfStates[i]) {
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

bool Automaton::operator!=(const Automaton& other) const {
    if (automatonName == other.automatonName) {
        for (int i = 0; i < numberStates; i++) {
            if (numberStates == other.numberStates
                && arrayOfStates[i] == other.arrayOfStates[i]) {
                for (int j = 0; j < numberTransitions; j++) {
                    if (numberTransitions == other.numberTransitions
                        && arrayOfTransitions[j]
                        == other.arrayOfTransitions[j]) {
                        return false;
                    }
                }
                
            }
        }
        
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const Automaton& aut) {
    aut.print(stream);
    return stream;
}

