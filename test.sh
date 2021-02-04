clear
g++ -c Implementation.cpp
ar cr Implementation2.a
ar cr Implementation2.a Implementation.o
g++ -o Main Main.cpp Implementation2.a
./Main