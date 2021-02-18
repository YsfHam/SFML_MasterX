workspace "SFML_MasterX"

architecture "x64"
configurations
{
  "Debug",
  "Release"
}

startproject "Sandbox"

Includes={}
Includes["SFML"]="%{wks.location}/SFML_MasterX/libs/SFML/include"
Includes["spdlog"]="%{wks.location}/SFML_MasterX/libs/spdlog/include"

include "SFML_MasterX"
include "Sandbox"
