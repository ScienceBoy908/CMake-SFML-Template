
# CMake-SFML-Template
This repository is a template for SFML projects using CMake and C++. It also includes a Python script to create an embedded resource header.

## Installation Instructions

1. **Clone the Repository**  
   Begin by cloning this repository into a new folder on your local machine.

2. **Configure Python Version**  
   Update the Python reference in the `CMakeLists.txt` file to match the Python version available in your command prompt. This could be `python`, `python3`, or a specific version like `python3.12`.

3. **Generate Build Files**  
   Create a `build` folder within the project directory. Open a command prompt, navigate to this folder, and run:
   ```
   cmake ..
   ```
   If you encounter an error about Python not being found, revisit step 2 or ensure that Python is installed on your system.

4. **Visual Studio Setup** (if using Visual Studio)  
   After opening the project in Visual Studio, right-click the main project in the Solution Explorer and select "Set as Startup Project".
