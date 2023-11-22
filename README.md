Math for Game Developers Sample Code
====================================

This is the source code for the sample code that is used in [Math for Game Developers YouTube series](http://www.youtube.com/playlist?list=PLW3Zl3wyJwWOpdhYedlD-yCB7WQoHf-My). It has been modified to run on GLFW 3 and glad, the original source code can be found at [MathForGameDevelopers](https://github.com/BSVino/MathForGameDevelopers). If you want to follow along with the videos, you can download by clicking the 'ZIP' button in the header near the top of this page.

Overview
--------

You'll find these directories:

**game** - This is where the main.cpp is, which is the primary bit of code that we'll be modifying.

**math** - This is where all of the math stuff that we'll be implementing lives.

**content** - When the game is run, it's run in this directory, even though there's no .exe in here. That means it looks for its textures, models, shaders, etc files here.

**renderer** - Shaders and rendering are carried out here. All OpenGL code is contained in these files. To render something, first create a rendering context:

	CRenderingContext c(Application()->GetRenderer(), true):

If there's already a rendering context open then use that one, don't create two contexts in the same method.

Shaders are loaded from text files in the ```shaders``` directory in the SMAK distribution. The shader library will read every .txt file in this directory and compile it as a new shader. The .txt file specifies which file should be used as the vertex and fragment shaders, so files can be reused between shaders. It also specifies parameters which can be specified in the material .mat files. The files ```header.si``` and ```functions.si``` are imported for you at the beginning of every shader. Some attributes and uniforms are hard-coded. For vertex shaders:

* ```uniform mat4x4 mProjection```
* ```uniform mat4x4 mView```
* ```uniform mat4x4 mGlobal```

And for fragment shaders:

* ```out vec4 vecOutputColor```

```vecOutputColor``` is the value to which the output value for a fragment shader should be assigned. The rest are up to you.

**datamanager** - Sometimes data needs to be serialized to and from the hard drive. data.h contains a CData class that is a generic data container, and dataserializer.h can serialize any CData to and from a stream. Data is stored in a simple format that looks like this:

	key: value
	{
		// Sub-datas
		key: value
		key2: value

		// Values are optional
		key3
		{
			subdata
		}
	}

This format is used for things like shader .txt files.

**include** and **lib** - This code depends on some third party libraries, and they can be found here.

Compiling
---------

1. Download the MFGD project files and unpack them somewhere on your hard drive.
2. Open a terminal and navigate to this directory, eg "cd ~/mfgd"
3. Type "make"
4. Type "./scripts/run_mfgd"

Tinker
------

This code is built on top of Tinker, Lunar Workshop's internal game engine. I ripped out a bunch of stuff so that it's much simpler. As MFGD progresses and new things are learned, I'll add those things back into the engine.

If you want the actual thing you can find it in the [SMAK source code](https://github.com/BSVino/SMAK), it's much more fully featured. It has materials and a console and a GUI and lots of other neat stuff.

Licenses
--------

Tinker is licensed under a permissive MIT-style license, meaning you may use it to build your own projects with no requirement to distribute the source code, but you must give credit to the original author somewhere in your program, like on the "About" or "Credits" page.

The full text of the license is included in the file ```LICENSE.Tinker``` and at the top of every source code file to which it applies.
