# Compile Matrix.cpp
g++ -c sources/Matrix.cpp -o obj/Matrix.o

# Compile Matrix_no_threads.cpp
g++ -c sources/Matrix_openmp.cpp -fopenmp -o obj/Matrix_openmp.o

# Compile main.cpp
g++ -c sources/main.cpp -o obj/main.o

# Link the object files to create the executable
g++ obj/Matrix.o obj/Matrix_openmp.o obj/main.o -fopenmp -o my_program
