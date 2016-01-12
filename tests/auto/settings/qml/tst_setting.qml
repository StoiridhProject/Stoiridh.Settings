////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2015-2016 William McKIE                                               //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
import QtQuick 2.5
import QtTest 1.1
import Stoiridh.Settings 1.0

TestCase {
    id: root
    name: "Setting"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Setting {
        id: generalSetting

        property string projectsPath: "$HOME/StoiridhProjects"
        property string theme: "Dark"
    }

    Setting {
        id: recentProjectsSetting
        name: "RecentProjects"

        property variant recentProjects: [
            "projectA.stoiridhproj",
            "projectB.stoiridhproj",
            "projectC.stoiridhproj"
        ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Functions                                                                                 //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function reset() {
        generalSetting.projectsPath = "$HOME/StoiridhProjects"
        generalSetting.theme = "Dark"

        recentProjectsSetting.recentProjects = [
                    "projectA.stoiridhproj", "projectB.stoiridhproj", "projectC.stoiridhproj"
                ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Test                                                                                      //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function init() {
        reset()
        SettingManager.save()
    }

    function test_save() {
        compare(generalSetting.name, "")
        compare(recentProjectsSetting.name, "RecentProjects")
        SettingManager.load()

        compare(generalSetting.projectsPath, "$HOME/StoiridhProjects")
        compare(generalSetting.theme, "Dark")

        compare(recentProjectsSetting.recentProjects, [
                    "projectA.stoiridhproj", "projectB.stoiridhproj", "projectC.stoiridhproj"
                ])
    }

    function test_load() {
        generalSetting.projectsPath = "$HOME/Documents/StoiridhProjects"
        generalSetting.theme = "Light"

        recentProjectsSetting.recentProjects = [
                    "projectC.stoiridhproj", "projectA.stoiridhproj", "projectB.stoiridhproj"
                ]

        SettingManager.save()
        reset()
        SettingManager.load()

        compare(generalSetting.projectsPath, "$HOME/Documents/StoiridhProjects")
        compare(generalSetting.theme, "Light")

        compare(recentProjectsSetting.recentProjects, [
                    "projectC.stoiridhproj", "projectA.stoiridhproj", "projectB.stoiridhproj"
                ])
    }
}
