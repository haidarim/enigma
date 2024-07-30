#!/bin/bash

buildAndRun(){
	gcc generate_todays_rotor.c -o generate_todays_rotor && ./generate_todays_rotor
	gcc enigma.c -o enigma  && ./enigma
}

getPlain(){
	gcc enigma.c -o enigma && ./enigma
}

if [ $# -eq 0 ]; then
	buildAndRun

elif [ "$1" == "-p" ]; then
	getPlain
fi	
