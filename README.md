Math for Game Developers Sample Code
====================================

This is the sample code that is used in [Math for Game Developers YouTube series](http://www.youtube.com/playlist?list=PLW3Zl3wyJwWOpdhYedlD-yCB7WQoHf-My). It has been modified to run on GLFW 3 and glad, the original source code can be found at [MathForGameDevelopers](https://github.com/BSVino/MathForGameDevelopers). 

Building and Running
--------------------

### Using Homebrew:

1. Git clone or download the MFGD project files.
2. Install GLFW using homebrew with `brew install glfw`.
2. Open a terminal and navigate to this directory, eg `cd ~/dev/mfgd`.
3. Type `make`.
4. Type `./mfgd`.

### Using Nix:

1. Type `nix run github:FrothyMarrow/mfgd# –extra-experimental-features 'nix-command flakes'`
2. Now that you have noticed the difference in number of instructions, install [nix](https://nixos.org/download).

Tinker
------

This code is built on top of Tinker, Lunar Workshop's internal game engine. I ripped out a bunch of stuff so that it's much simpler. As MFGD progresses and new things are learned, I'll add those things back into the engine.

If you want the actual thing you can find it in the [SMAK source code](https://github.com/BSVino/SMAK), it's much more fully featured. It has materials and a console and a GUI and lots of other neat stuff.

Licenses
--------

Tinker is licensed under a permissive MIT-style license, meaning you may use it to build your own projects with no requirement to distribute the source code, but you must give credit to the original author somewhere in your program, like on the "About" or "Credits" page.

The full text of the license is included in the file ```LICENSE.Tinker``` and at the top of every source code file to which it applies.
