# PW_Project


## **Introduction**
Projekt ma na celu przetestowania możliwości zrównoleglenia podstawowych operacji na macierzach.


## **Features**
- Dodawanie macierzy
- Mnożenie macierzy
- Potęgowanie macierzy
- Obliczanie wyznacznika macierzy

## **Changed / Created files**
Najważniejszymi plikami, w których znajduje się implementacja to:
- `/src/sources/Matrix_no_threads.cpp`
- `/src/sources/Matrix_openmp.cpp`
- `/src/sources/Matrix_threads.cpp`

Opis folderów:

- `/src/headers` - główna deklaracja klasy **Matrix**
- `/src/obj` - pomocniczy folder podczas kompilacji
- `/src/plots` - generator wykresów na podstawie wygenerowanych testów
- `/src/souces/Matrix.cpp` - częściowa implementacja klasy **Matrix**
- `/src/sources/Matrix_*.cpp` - **implementacja algorytmów ze względu na użytą bilbiotekę**
- `/src/tests_src` - generator testów
- `tests_description.md` - opis testów

## How to use
Należy uruchomić ./run.sh, który automatycznie uruchamia wszystkie testy na różnych ilościach wątków (1, 4, 8, 16, 32, 64) i dla różnych iplementacji.

UWAGA - średni czas trwania programu (~2h)
```
./run.sh
```