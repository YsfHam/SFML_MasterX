
# SFML_MasterX

A 2D game framework created with **SFML**


## Used libraries

* [SFML](https://www.sfml-dev.org/)[( Github repo )](https://github.com/SFML/SFML) : 2D multimedia library. Version 2.5.1

* [Spdlog(Github)](https://github.com/gabime/spdlog) : Logging library

## Clone and build

To clone the project with git type : `git https://github.com/YsfHam/SFML_MasterX.git --recursive`.
The premake file can generate projects for mac, windows and linux.

**Note** : You must have [*premake5*](https://premake.github.io/) to generate the project

* **Build on mac(without xcode)**

If you have not install SFML in your mac run `./scripts/sfml_build` first,
then `premake5 gmake2`. Et voilà your project is generated.
Finally run the script `./scripts/build && ./scripts/run` to launch the executable.

* **Build on windows**

Not tested yet.

* **Build on linux**

Not tested yet

Feel free to try building the project on any other platform.
