# Compile Matrix.cpp with thread support
g++ -pthread -DN_THREADS=8 -c sources/Matrix.cpp -o obj/Matrix.o

# Compile Matrix_threads.cpp with thread support
g++ -pthread -DN_THREADS=8 -c sources/Matrix_threads.cpp -o obj/Matrix_threads.o

# Compile main.cpp
g++ -c sources/main.cpp -o obj/main.o

# Link the object files to create the executable
g++ -pthread obj/Matrix.o obj/Matrix_threads.o obj/main.o -o my_program
