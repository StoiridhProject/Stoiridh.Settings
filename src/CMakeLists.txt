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
##                                      - Stòiridh.Settings -                                     ##
####################################################################################################
set(STOIRIDH_PROJECT_NAME "StoiridhSettingsPlugin")

####################################################################################################
##  Configuration                                                                                 ##
####################################################################################################
stoiridh_include("Stoiridh.Qt.Qml.ExtensionPlugin")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

####################################################################################################
##  Packages                                                                                      ##
####################################################################################################
find_package(Qt5 5.6 COMPONENTS Core Gui Qml Quick REQUIRED)

####################################################################################################
##  Sources and Headers                                                                           ##
####################################################################################################
set(SOURCES
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/groupsettings.cpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/groupsettings.hpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/plugin.cpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/plugin.hpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/settings.cpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/settings.hpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/settingsmanager.cpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/settingsmanager.hpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/windowsettings.cpp"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/windowsettings.hpp"
)
####################################################################################################
##  QML                                                                                           ##
####################################################################################################
set(QML_SOURCES
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/qml/plugins.qmltypes"
    "${STOIRIDH_SETTINGS_SOURCE_DIR}/qml/qmldir"
)
####################################################################################################
##  Library                                                                                       ##
####################################################################################################
stoiridh_qt_qml_add_extension_plugin(${STOIRIDH_PROJECT_NAME}
    URI               "Stoiridh.Settings"
    ALIAS             StoiridhSettings
    SOURCES           ${SOURCES}
    QML_SOURCES       ${QML_SOURCES}
    QML_PATH_SUFFIXES "qml"
    DEPENDS           Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)
