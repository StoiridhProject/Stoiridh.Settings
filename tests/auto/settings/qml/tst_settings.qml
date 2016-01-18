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
    name: "Settings"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Component {
        id: settingsItem
        Settings {
            name: "Test/Settings/MainWindow"

            property int x: -1
            property int y: -1
            property int width: -1
            property int height: -1
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Signals spies                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SignalSpy {
        id: nameSignalSpy
        signalName: "nameChanged"
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Tests                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function init() {
        verify(!nameSignalSpy.target)
        compare(nameSignalSpy.count, 0)
    }

    function init_data() {
        return [
                    {tag: "1", x: 200, y: 200, width:  800, height: 600},
                    {tag: "2", x: 300, y:  30, width:  600, height: 300},
                    {tag: "3", x: 125, y:  50, width:  450, height: 680},
                    {tag: "4", x: 475, y: 500, width:  512, height: 512},
                    {tag: "5", x: 500, y: 250, width: 1280, height: 720},
                ]
    }

    function cleanup() {
        nameSignalSpy.target = null
        nameSignalSpy.clear()
    }

    function test_property_name() {
        var settings = settingsItem.createObject(testCase)
        verify(settings)

        nameSignalSpy.target = settings
        verify(nameSignalSpy.valid)

        compare(settings.name, "Test/Settings/MainWindow")
        compare(nameSignalSpy.count, 0)

        settings.name = ""
        compare(settings.name, "")
        compare(nameSignalSpy.count, 1)

        settings.destroy()
    }

    function test_1_save(data) {
        var settings = settingsItem.createObject(testCase)
        verify(settings)

        settings.name = "Test/Settings/MainWindow/" + data.tag

        settings.x = data.x
        settings.y = data.y
        settings.width = data.width
        settings.height = data.height

        SettingsManager.save()

        compare(settings.x, data.x)
        compare(settings.y, data.y)
        compare(settings.width, data.width)
        compare(settings.height, data.height)

        settings.destroy()
    }

    function test_2_load(data) {
        var settings = settingsItem.createObject(testCase)
        verify(settings)

        settings.name = "Test/Settings/MainWindow/" + data.tag

        SettingsManager.load()

        compare(settings.x, data.x)
        compare(settings.y, data.y)
        compare(settings.width, data.width)
        compare(settings.height, data.height)

        settings.destroy()
    }
}
