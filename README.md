# Solving Sudoku with Genetic Algorithms

C++11 genetic algorithm implementation which solves Sudokus  

## Sudoku Representation

Since the well-known game consists on filling the board with integers
from 1 to 9, it is not necessary to use the most common binary representation
for genetic algorithms. Instead, the algorithm works directly with integers and
each individual in the population is represented by a 9x9 matrix or a board. 

In order ti initialize each individual in the population, we start with the
initial board (Sudoku_Sample.txt) and an empty board:

<br>
<img height="200" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura1.jpg">
<br>

Since it is known that each row must have numbers from 1 to 9, we randomly
generate sequences to initialize al the board row wise (it can be also done
column wise) and fit the in the board. Then we readjust the members if applies to
fit the initial board. For instance, the first row of the previous figure will 
become:

<br>
<img height="200" src="https://github.com/rnavares/Solving-Sudoku-with-Genetic-Algortihms-/blob/master/Figures/Figura2.jpg">
<br>



## Getting Started

A Perl5 wrapper to Lingua-EN-Tagger and Tree-Tagger 

### Prerequisites

Perl is a high-level programming language that comes installed by default in Linux.

```
sh sudo cpan
cpan[1]> upgrade
```

or 

```
sh sudo perl -MCPAN -e 'upgrade'
```


Install the Tree-Tagger, also available in http://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/

```
sh install-tagger.sh
```

Install Lingua-EN-Tagger, also available in http://search.cpan.org/dist/Lingua-EN-Tagger/Tagger.pm

```
sh cpan Lingua::EN::Tagger
```


## Running the wrapper

```
sh sudo chmod +x wrapper.pl
sh perl wrapper.pl
```

### Results

Go to guide.pdf to check the results and licences 

