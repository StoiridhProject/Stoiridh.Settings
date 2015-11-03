////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2015 William McKIE                                                    //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
import qbs 1.0

StoiridhQuickPlugin {
    name: "Stoiridh.Settings"
    targetName: "stoiridh-settings"
    uri: "Stoiridh.Settings"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Sources                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    files: [
        "src/abstractsetting.cpp",
        "src/abstractsetting.hpp",
        "src/groupsettings.cpp",
        "src/groupsettings.hpp",
        "src/setting.cpp",
        "src/setting.hpp",
        "src/settingmanager.cpp",
        "src/settingmanager.hpp",
        "src/stoiridhsettings_plugin.cpp",
        "src/stoiridhsettings_plugin.hpp",
        "src/windowsetting.cpp",
        "src/windowsetting.hpp",
    ]
}
