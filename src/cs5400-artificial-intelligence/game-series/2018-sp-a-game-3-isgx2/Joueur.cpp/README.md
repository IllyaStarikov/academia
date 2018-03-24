# Chess C++ Client

This is the root of you AI. Stay out of the `joueur/` folder, it does most of the heavy lifting to play on our game servers. Your AI, and the game objects it manipulates are all in `games/chess/`, with your very own AI living in `games/chess/ai.hpp` and `games/chess/ai.cpp` files for you to make smarter.

## How to Run

This client has been tested and confirmed to work on the Campus rc##xcs213 Linux machines, but it can work on your own Windows/Linux/Mac machines if you desire.

Also make sure **NOT** to try to compile this in your Missouri S&T S-Drive. This is not a fault with the client, but rather the school's S-Drive implementation changing some file permissions during run time. We cannot control this. Instead, we recommend cloning your repo outside the S-Drive and use an SCP program like [WinSCP][winscp] to edit the files in Windows using whatever IDE you want if you want to code in Windows, but compile in Linux.

### Linux

    make
    ./testRun MyOwnGameSession

Linux does not have any dependencies beyond a C++ compiler and build system. You will need `make` and `cmake` to build, and `gcc` for compiling.

### Windows

There are two ways to get this client working on Windows.

#### Visual Studio

1. You will need to install a recent version of [Visual Studio][vs] with VC++.
2. Add VC++ to the command line by running `vcvarsall.bat`. By default this is found at `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat`.
3. Install [CMake][cmake] for Windows, and during installation have it added to your PATH.
4. If you make a make system, you can now just run `make` to build the project, or...
5. If you want to work **in** Visual Studio run the script `make_vs_proj.bat`, then, in the newly created `build/` directory use that `sln` file generated.

You'll also need to use the following command line arguments when running the client to connect to our game server:

`Chess -s r99acm.device.mst.edu`

#### MinGW

MinGW is another solution on Windows if you do not wish to use Visual Studio or VC++ compilers, and instead would prefer a compiler like GCC (but then why are you not on Linux?).

1. Install [MinGw][mingw]
2. Have the MinGW Installation Manager, and install the base, make, and gcc packages.
3. Ensure the `MinGW/bin/` directory is added to your PATH so you can use the packages from the command line
4. Install [CMake][cmake]
5. Compile this client by navigating to where you cloned this repo and running `make` or `ming32-make`.

Notes: You may have to set the `cc` environmental variable to the C++ compiler of your choice (gcc.exe probably)

## Other notes

Always use the `->` operator to access member variables and functions of each class instead of the dot operator `.`.

The only file you should ever modify to create your AI are the `ai.cpp` and `ai.hpp` files. All the other files are needed for the game to work. In addition, you should never be creating your own instances of the Game's classes, nor should you ever try to modify their variables. Instead, treat the Game and its members as a read only structure that represents the game state on the game server. You interact with it by calling the game functions.

Most importantly, **stay out of the impl/ directories**.

[vs]: https://www.visualstudio.com/downloads/
[cmake]: http://cmake.org/
[mingw]: http://www.mingw.org/
[winscp]: https://winscp.net/eng/download.php
[vagrant]: https://www.vagrantup.com/downloads.html
[virtualbox]: https://www.virtualbox.org/wiki/Downloads
[vagrant-guide]: https://www.vagrantup.com/docs/getting-started/up.html
[virtualbox]: https://www.virtualbox.org/wiki/Downloads
[gitbash]: https://git-scm.com/downloads
