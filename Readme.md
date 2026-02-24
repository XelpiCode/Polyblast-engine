<p align="center">
  <img src="resources/Logo/Polyblast_full_logo.svg" width="450" alt="Polyblast">
</p>

<p align="center">
  Polyblast is a game engine in development, and also my passion project built with OpenGL :)
</p>

<br>

<h3 align="center">Why the name "Polyblast"?</h3>

<p align="center">
  <b>Poly</b> = versatility &nbsp; • &nbsp; <b>Blast</b> = speed & performance  
  <br>
  A fast, flexible game engine.
</p>

## 🔧 Building Polyblast

Polyblast uses **CMake** as its build system, so you can compile it with any IDE or from the terminal.

### Requirements

Make sure you have these installed:

* CMake (3.20 or newer recommended)
* A C++ compiler, eg: gcc, clang

### Clone the repository

```bash
git clone https://github.com/XelpiCode/Polyblast-engine.git
cd Polyblast-engine
```

### Build with CMake (Terminal)

```bash
mkdir build
cd build

cmake ..
cmake --build . --config Release
```

After building, the executable will be inside the `build` folder.

### Windows (Visual Studio)

You can also open the project folder directly in Visual Studio:

1. Open Visual Studio
2. Click **Open Folder**
3. Select the Polyblast directory
4. Visual Studio will automatically detect the CMake project

### VS Code

If you use VS Code:

1. Install the **CMake Tools** extension
2. Open the project folder
3. Click **Configure**
4. Click **Build**

---

If you run into issues, make sure your compiler and CMake are properly installed and available in your system PATH.
