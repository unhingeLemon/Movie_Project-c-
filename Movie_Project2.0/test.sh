clear
g++ -c MovieADT.cpp
ar cr MovieADT2.a
ar cr MovieADT2.a MovieADT.o
g++ -c customerADT.cpp
ar cr customerADT2.a
ar cr customerADT2.a customerADT.o
g++ -o Main main.cpp MovieADT2.a customerADT2.a
./Main