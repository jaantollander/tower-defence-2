# Tower Defence 2
## Description
This is project is part of C++ programming course at Aalto University. This project implements [tower defense](https://en.wikipedia.org/wiki/Tower_defense) game.


## Project Structure
This is an initial git repository for your programming project.
It contains an initial directory structure that we wish you could
use as follows:

  * `plan/` -- Here is your project plan. You may use different sources,
    but we hope to get the pan **also as pdf file**.

  * `doc/` -- here are the documentation sources related to your project.
    You may use different tools for documentation (e.g. latex),
    but we hope to get the final version of the document
    **also as pdf file**.

  * `src/` -- here are the C++ source files. You can have subfolders as needed.

  * `index.md` -- This file that you should modify to represent
    your project.

You may also add other new directories as needed, for example
for testing tools.


## Installation and Developement
[CLion](https://www.jetbrains.com/clion/) is powerful C and C++ editor from JetBrains recommended for this project. As a student you can apply for their [student program](https://www.jetbrains.com/student/) to get access to pro version of their products.

----

[CMake](https://cmake.org/) is used to control the compilation process.

----

Documentation is generated using [Doxygen](https://www.stack.nl/~dimitri/doxygen/index.html). Doxygen creates static `HTML` and `latex` files using supplied input markdown files and docstring found inside the source code.

Install Doxygen using
```
sudo apt-get install doxygen.
```

Documentation is created into `doc` directory. Create `HTML` and `latex` files using
```
doxygen Doxyfile.ini
```

Creating pdf requires installing LaTeX. Create pdf using
```
cd doc/latex &&
pdflatex refman.tex &&
cd ../..
```


----

The graphics of this game depend on **Simple and Fast Multimedia Library (SFML)**. Install this library using

```
sudo apt-get install libsfml-dev
```




## Authors

- Jaan Tollander de Balsch
- Jussi Hietanen
- Martti Hallipelto
- Roni Hytönen
- Tero Hyytiäinen
