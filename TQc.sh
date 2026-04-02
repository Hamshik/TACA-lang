#!bin
./bin/Complier "@$"

llc -filetype=obj out.ll -o out.o

clang out.o -o tarkiq-out -Wl,-e,tq_main
