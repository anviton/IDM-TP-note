CLHEP_DIR=/home/viton/Documents/ISIMA/ZZ3/IDM/Random/

g++ -fopenmp $PWD/src/*.cpp -o TP5 -I$CLHEP_DIR/include -L$CLHEP_DIR/lib -Wl,-Bstatic -lCLHEP-Random-2.1.0.0 -Wl,-Bdynamic
