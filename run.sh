#!/bin/bash

buildAndRun(){
	gcc enigma.c -o enigma  && ./enigma
}

buildAndRun
