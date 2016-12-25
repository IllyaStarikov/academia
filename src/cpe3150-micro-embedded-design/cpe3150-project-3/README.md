# Project III — CpE 3150
This is the third and final project for Computer Engineering 3150, *Introduction to Microcontrollers and Embedded Systems* at Missouri University of Science and Technology. The formal description can be found under *assets/CpE 3150 - Project 3.pdf*. Although this can serve as a reference, because of the teacher’s transfer and hardware being replaced, this code verbatim cannot be used.

The hardware required to run the code is an [8051 microcontroller](https://en.wikipedia.org/wiki/Intel_MCS-51). The only required software is a GCC compiler; however, to alter code related to the microcontroller, [Kiel](https://www.keil.com) and [Flash Magic](http://www.flashmagictool.com) is required. 

Please note because this project is already evaluated, it will be treated as legacy. **Further support will be discontinued.**

## The Codebase
There are two, independently code bases, we will discuss them individually.
  
### Space Invaders
The original intention for Space Invaders was to serially communicate the game logic from the microcontroller to a computer monitor; however, the microcontroller only has 8k of memory. Our hex file was over 30k. Because of this, our game only runs in the terminal with [curses](https://en.wikipedia.org/wiki/Curses_(programming_library)).

![Space Invaders](/assets/game.png?raw=true “Space Invaders”)

There are *many* known issues with the game — namely, the aliens don’t shot nor move. We did not have enough time to fix these issues. 

### Penrose and Music
The Penrose and music portion of the code prints an elegant menu for selecting different actions that can be performed on microcontroller. The actions are as follows: 

- A musical keyboard that plays different notes that correspond to different buttons.
- A song (Hurricane’s Eye).
- A binary counter that uses the top three lights on the microcontroller.

![Penrose Menu](/assets/menu.png?raw=true “Penrose Menu”)
  
Assets contain all the documentation for the microcontroller, Kiel and Flashmagic. These documents are properties of Missouri S&T, no copyright infringement intended.

## The Report
The report details what occurred in the project, what struggles we faced, how we used the microcontroller, etc. Because it is in LaTeX, it requires some setup to alter. You can read the documentation [here](http://www.latex-project.org).

## Group Members
The following were the original members of this project:  

- Illya Starikov ([@IllyaStarikov](https://github.com/IllyaStarikov/))
- Michael Schoen ([@michaelschoen](https://github.com/michaelschoen))
- Abdirahman Ahmed Osman ([@Adobe-Osman](https://github.com/Adobe-Osman))
