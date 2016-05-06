####################################################################################################
##                                                                                                ##
##            Copyright (C) 2015-2016 William McKIE                                               ##
##                                                                                                ##
##            This program is free software: you can redistribute it and/or modify                ##
##            it under the terms of the GNU General Public License as published by                ##
##            the Free Software Foundation, either version 3 of the License, or                   ##
##            (at your option) any later version.                                                 ##
##                                                                                                ##
##            This program is distributed in the hope that it will be useful,                     ##
##            but WITHOUT ANY WARRANTY; without even the implied warranty of                      ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       ##
##            GNU General Public License for more details.                                        ##
##                                                                                                ##
##            You should have received a copy of the GNU General Public License                   ##
##            along with this program.  If not, see <http://www.gnu.org/licenses/>.               ##
##                                                                                                ##
####################################################################################################
cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

####################################################################################################
##  Project                                                                                       ##
####################################################################################################
project("Stòiridh.Settings" VERSION 0.1.0)

####################################################################################################
##  Configuration                                                                                 ##
####################################################################################################
set(STOIRIDH_PROJECT_NAME "StoiridhSettings")
set(STOIRIDH_CONFIGURATION_ROOT "${PROJECT_SOURCE_DIR}/config/cmake")

include("${STOIRIDH_CONFIGURATION_ROOT}/StoiridhConfiguration.cmake")
stoiridh_project_initialise()

# Subproject source directory
set(STOIRIDH_SETTINGS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

####################################################################################################
##  Subdirectories                                                                                ##
####################################################################################################
add_subdirectory("src")

if(STOIRIDH_PROJECT_TESTING_ENABLE)
    enable_testing()
    add_subdirectory("tests")
endif()
