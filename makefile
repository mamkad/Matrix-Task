CMP = g++
FLAG = -std=c++17

matrmult:
	$(CMP) -c ./matrix/matrix.cpp -o ./bin/matrix.o $(FLAG) 
	$(CMP) -c ./matrix_multiplication/matrix_multiplication.cpp -o ./bin/matrix_multiplication.o $(FLAG) 
	$(CMP) -c main.cpp -o ./bin/main.o $(FLAG)
	$(CMP) -o ./bin/matrmult ./bin/matrix.o ./bin/matrix_multiplication.o ./bin/main.o $(FLAG) -pthread
	rm ./bin/*.o


