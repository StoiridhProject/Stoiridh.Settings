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
//            but WITHOUT ANY WARRANTY without even the implied warranty of                       //
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
    id: testCase
    name: "GroupSettings"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Component {
        id: groupSettingsItem
        GroupSettings {
            name: "Test/GroupSettings"

            // Settings A
            Settings {
                objectName: "settingsA"
                name: "MainWindow"

                property int x: -1
                property int y: -1
                property int width: -1
                property int height: -1
            }

            // Settings B
            Settings {
                objectName: "settingsB"
                name: "Preferences"

                property string theme
            }

            // Settings C
            Settings {
                objectName: "settingsC"
                name: "Projects"
                property var recents
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Tests                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function init_data() {
        return [
                    {
                        tag: "1",
                        settingsA: { x: 200, y: 200, width:  800, height: 600 },
                        settingsB: { theme: "Light" },
                        settingsC: { recents: ["project01", "project02"] }
                    },
                    {
                        tag: "2",
                        settingsA: { x: 300, y:  30, width:  600, height: 300 },
                        settingsB: { theme: "Dark" },
                        settingsC: { recents: ["project05", "project01", "project02"] }
                    },
                    {
                        tag: "3",
                        settingsA: { x: 125, y:  50, width:  450, height: 680 },
                        settingsB: { theme: "Blue" },
                        settingsC: { recents: ["project02", "project01", "project05"] }
                    },
                    {
                        tag: "4",
                        settingsA: { x: 475, y: 500, width:  512, height: 512 },
                        settingsB: { theme: "Zen" },
                        settingsC: { recents: ["project01", "project02", "project03", "project04"] }
                    },
                    {
                        tag: "5",
                        settingsA: { x: 500, y: 250, width: 1280, height: 720 },
                        settingsB: { theme: "Yün" },
                        settingsC: { recents: ["project02", "project01"] }
                    },
                ]
    }

    function test_1_save(data) {
        var groupSettings = groupSettingsItem.createObject(testCase)
        verify(groupSettings)

        groupSettings.name = "Test/GroupSettings/" + data.tag

        var settingsA = findChild(groupSettings, "settingsA")
        verify(settingsA)
        var settingsB = findChild(groupSettings, "settingsB")
        verify(settingsB)
        var settingsC = findChild(groupSettings, "settingsC")
        verify(settingsC)

        // Settings A: MainWindow
        settingsA.x = data.settingsA.x
        settingsA.y = data.settingsA.y
        settingsA.width = data.settingsA.width
        settingsA.height = data.settingsA.height

        // Settings B: Preferences
        settingsB.theme = data.settingsB.theme

        // Settings C: Projects
        settingsC.recents = data.settingsC.recents

        SettingsManager.save()

        // Settings A
        compare(settingsA.x, data.settingsA.x)
        compare(settingsA.y, data.settingsA.y)
        compare(settingsA.width, data.settingsA.width)
        compare(settingsA.height, data.settingsA.height)

        // Settings B
        compare(settingsB.theme, data.settingsB.theme)

        // Settings C
        compare(settingsC.recents, data.settingsC.recents)

        groupSettings.destroy()
    }

    function test_2_load(data) {
        var groupSettings = groupSettingsItem.createObject(testCase)
        verify(groupSettings)

        groupSettings.name = "Test/GroupSettings/" + data.tag

        var settingsA = findChild(groupSettings, "settingsA")
        verify(settingsA)
        var settingsB = findChild(groupSettings, "settingsB")
        verify(settingsB)
        var settingsC = findChild(groupSettings, "settingsC")
        verify(settingsC)

        SettingsManager.load()

        // Settings A
        compare(settingsA.x, data.settingsA.x)
        compare(settingsA.y, data.settingsA.y)
        compare(settingsA.width, data.settingsA.width)
        compare(settingsA.height, data.settingsA.height)

        // Settings B
        compare(settingsB.theme, data.settingsB.theme)

        // Settings C
        compare(settingsC.recents, data.settingsC.recents)

        groupSettings.destroy()
    }
}
