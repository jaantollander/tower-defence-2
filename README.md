# Tower Defence 2
## Introduction
This is project is part of C++ programming course at Aalto University. 

**Goal of the project**: implement a 2D tower defense game.

"Tower defense (or informally TD) is a subgenre of strategy video game where the
 goal is to defend a player's territories or possessions by obstructing enemy 
 attackers, usually achieved by placing defensive structures on or along their 
 path of attack." ([Wikipedia](https://en.wikipedia.org/wiki/Tower_defense))

In a tower defense game, the enemies move in waves from some position of the map 
to another. The goal of the player is to place towers on their path in order to 
block, impede, attack or destroy the enemies before they are able to reach 
their goal. The primary object is the survival of the base.


## Minimum Requirements
- [ ] Basic graphics.
- [ ] A functioning tower defense game.
- [ ] At least three different types of towers.
- [ ] At least three different types of enemies.
- [ ] Non-hardcoded maps, i.e. they have to be read from some file in some format.
- [ ] The player has to be able to build, repair (if the gameplay supposes that the towers can be damaged) and upgrade towers during the game, either between waves of enemies or without restrictions.
- [ ] Controlling the game with mouse.
- [ ] Simple user interface that shows information such as resources, number of waves/enemies etc.
- [ ] A list of high scores (decide yourself how to calculate points). High scores must be saved between game sessions!
- [ ] Fun and overall pleasant gaming experience.


## Extra Requirements
- [ ] Sounds
- [ ] Multiple paths of the enemies
- [ ] Dynamic paths that can be altered with the placement of towers
- [ ] Special attack types, e.g. ranged
- [ ] Special abilities of the towers, e.g. slowing down the enemies
- [ ] Special movements of the enemies, e.g. jumping over the towers
- [ ] Different attack and defense types for both the towers and the enemies. For example, some attack types may be more effective against some defense types.
- [ ] Multiplayer mode (local or networked)
- [ ] Your own ideas for increasing the maximum fun!



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
- Roni Hytönen
- Tero Hyytiäinen
- Martti Hallipelto
