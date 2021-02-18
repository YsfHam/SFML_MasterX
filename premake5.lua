workspace "SFML_MasterX"

architecture "x64"
configurations
{
  "Debug",
  "Release"
}

startproject "Sandbox"

Includes={}
Includes["SFML"]="%{wks.location}/SFML_MasterX/extlibs/SFML/include"
Includes["spdlog"]="%{wks.location}/SFML_MasterX/extlibs/spdlog/include"

include "SFML_MasterX"
include "Sandbox"
