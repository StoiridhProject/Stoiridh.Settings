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
    name: "GroupSettings"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    GroupSettings {
        id: groupSettings
        name: "MainWindow"

        property int activeEditor: 1

        GroupSettings {
            id: defaultProjectSettings
            name: "DefaultProject"

            property string mapOrientation: "Isometric"
            property vector2d mapSize: Qt.vector2d(512, 512)
            property vector2d tileSize: Qt.vector2d(64, 32)
        }

        GroupSettings {
            id: animationSetting
            name: "Animation"

            property real framerate: 1.0 / 60.0

            Setting {
                id: colourSetting
                name: "Colours"

                property color blue: Qt.rgba(0.04, 0.54, 0.78, 1.0)
                property color green: Qt.rgba(0.05, 0.67, 0.19, 1.0)
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Functions                                                                                 //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function reset() {
        groupSettings.activeEditor = 1

        defaultProjectSettings.mapOrientation = "Isometric"
        defaultProjectSettings.mapSize = Qt.vector2d(512, 512)
        defaultProjectSettings.tileSize = Qt.vector2d(64, 32)

        animationSetting.framerate = 1.0 / 60.0

        colourSetting.blue = Qt.rgba(0.04, 0.54, 0.78, 1.0)
        colourSetting.green = Qt.rgba(0.05, 0.67, 0.19, 1.0)
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Test                                                                                      //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function init() {
        reset()
        SettingManager.save()
    }

    function test_save() {
        compare(groupSettings.name, "MainWindow")
        compare(defaultProjectSettings.name, "DefaultProject")
        compare(animationSetting.name, "Animation")
        compare(colourSetting.name, "Colours")
        SettingManager.load()

        compare(groupSettings.activeEditor, 1)

        compare(defaultProjectSettings.mapOrientation, "Isometric")
        compare(defaultProjectSettings.mapSize, Qt.vector2d(512, 512))
        compare(defaultProjectSettings.tileSize, Qt.vector2d(64, 32))

        compare(animationSetting.framerate, (1.0 / 60.0))

        compare(colourSetting.blue, Qt.rgba(0.04, 0.54, 0.78, 1.0))
        compare(colourSetting.green, Qt.rgba(0.05, 0.67, 0.19, 1.0))
    }

    function test_load() {
        groupSettings.activeEditor = 2

        defaultProjectSettings.mapOrientation = "Orthogonal"
        defaultProjectSettings.mapSize = Qt.vector2d(1024, 1024)
        defaultProjectSettings.tileSize = Qt.vector2d(128, 128)

        animationSetting.framerate = 1.0 / 30.0

        colourSetting.blue = Qt.rgba(0.19, 0.48, 1.0, 1.0)
        colourSetting.green = Qt.rgba(0.1, 0.43, 0.01, 1.0)

        SettingManager.save()
        reset()
        SettingManager.load()

        compare(groupSettings.activeEditor, 2)

        compare(defaultProjectSettings.mapOrientation, "Orthogonal")
        compare(defaultProjectSettings.mapSize, Qt.vector2d(1024, 1024))
        compare(defaultProjectSettings.tileSize, Qt.vector2d(128, 128))

        compare(animationSetting.framerate, (1.0 / 30.0))

        compare(colourSetting.blue, Qt.rgba(0.19, 0.48, 1.0, 1.0))
        compare(colourSetting.green, Qt.rgba(0.1, 0.43, 0.01, 1.0))
    }
}
