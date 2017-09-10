# Solving Sudoku with Genetic Algorithms

C++11 genetic algorithm implementation which solves Sudokus  

## 1. Sudoku Representation

Since the well-known game consists on filling the board with integers
from 1 to 9, it is not necessary to use the most common binary representation
for genetic algorithms. Instead, the algorithm works directly with integers and
each individual in the population is represented by a 9x9 matrix or a board. 

In order ti initialize each individual in the population, we start with the
initial board (Sudoku_Sample.txt) and an empty board:

<p align="center">
<img height="300" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura1.jpg">
</p>

Since it is known that each row must have numbers from 1 to 9, we randomly
generate sequences to initialize al the board row wise (it can be also done
column wise) and fit the in the board. Then we readjust the members if applies to
fit the initial board. For instance, the first row of the previous figure will 
become:

<p align="center">
<img height="200" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura2.jpg">
</p>


## 2. Genetic Operators

### Crossover

A one and two-point crossover operator was implemented. This is implemented by
taking to individual candidates as parents and exchange their rows using as
a reference a random crossover point (point_CO). 

A 1-point crossover:

<p align="center">
<img height="400" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura3.jpg">
</p>

a two-point crossover:

<p align="center">
<img height="400" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura4.jpg">
</p>

### Mutation

Swap and Insert mutation was implemented as described in [1]

### Selection

Selection implementation was based on [2]. On each generation two populations are
generated one population \lambda which is generated by recombination of the original
population \mu. Then a the resulting population is obtained by selecting
individuals from each \mu and \lambda population to keep diversity:

<p align="center">
<img height="300" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/algorithm.png">
</p>

### Fitness function

Fitness function consits on penalizing those individuals with repeated elements
in their rows, columns and boxes (3x3). Thus, the fitnes function is defined by 
counting the number of unique members:

<p align="center">
<img height="400" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/fitness0.png">
</p>

the for each row, column and box we substract the number of unique members
to 9 Having a fitness equal to 0 the Sudoku solved:

<p align="center">
<img height="400" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/fitness.png">
</p>

### Parameter control

Two parameter control were implemented over the mutation operator. The first
one consists on incrementing the mutation probability if the fitness of the 
best individual has not change in 50 generations. The second is a selective
mutation which selects which rows to mutate (instead of randomly selection)
if the fitness of the best individual has not change in 200 generations. 

<p align="center">
<img height="300" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/algo2.png">
</p>

### Putting all together

<p align="center">
<img height="500" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura5.jpg">
</p>

## 3. Parameters tested

<p align="center">
<img height="400" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/tab.png">
</p>

## 4. Code Diagram

<p align="center">
<img height="500" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura6.jpg">
</p>

### Prerequisites
```
GNU GCC C++11 ISO C++ 
```
## Inputs

Input file with the parameters of the genetic algorithm

```
Parameters.txt
```

A Sudoku initial state

```
Sudoku_Sample.txt
```


### Execution

Run the main program

```
sh ./main
```

which shows in console 3 options: (1) to test the parameters and
the resutls are provided in a csv file. (2) run 10 executions
of the algorithm to obtain the success rates using 1000 generations.
(3) solve the sudoku outputting "solution.txt"

## References

[1] A.E. Eiben "Introduction to evolutionary computing". Springer. DOI: 10.1007/978-3-662-05094-1
[2] K.N. Das, S. Bhatia, S. Puri and K. Deep. "A retrievable GA for solving Sudoku puzzles"
