
 Introduction:
===============
Proteus VSM is an electronic circuit simulator best known for its reach digital
component library. It comes with a CAD program, named ARES, that allows you to
design PCB boards based on schematics.

Unfortunately, Proteus does not have any ILI9325 TFT LCD component. The only way
to simulate this component is to provide a custom-made library. In this project,
thanks to Proteus VSM C++ SDK, I wrote an ILI9325 library.


 How to Build and Install:
===========================
 * You have to provide a `VSM.hpp` header file.
 * Place the SDK header file in the `ProteusVSM-ILI9325\ILI9325\ILI9325`
   directory.
 * Open visual studio and build the project.
 * Open the `install.bat` script and update the `PROTEUS_PATH` variable to point
   to your Proteus installation path.
 * Run the `install.bat` script to copy the .dll file into the destination
   directory.

I provided a documentation [here](Docs/HowToBuildLCD/HowToBuildLCD-20240610-Mon.pdf?raw=true "HowToBuildLCD-20240610-Mon.pdf").


 Screenshots:
==============
Screenshot captured from Proteus 7.7 SP2 (Build 9089):

 ![Demo1](Images/ILI9325-Demo-1.png?raw=true "ILI9325 Demo 1")
 ![Demo2](Images/ILI9325-Demo-2.png?raw=true "ILI9325 Demo 2")

 ![Tetris1](Images/ILI9325-Tetris-1.png?raw=true "ILI9325 Tetris 1")
 ![Tetris2](Images/ILI9325-Tetris-2.png?raw=true "ILI9325 Tetris 2")

