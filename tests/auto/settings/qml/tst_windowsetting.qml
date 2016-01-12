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
import QtQuick.Window 2.2
import QtTest 1.1
import Stoiridh.Settings 1.0

TestCase {
    id: root
    name: "WindowSetting"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Properties                                                                                //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    property Component component: Window {}
    property alias window: ws.window

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    WindowSetting { id: ws; name: "Window" }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Functions                                                                                 //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function createWindow() {
        return component.createObject(root, {
                                          "x": 64,
                                          "y": 64,
                                          "width": 800,
                                          "height": 600,
                                          "visibility": Window.Hidden
                                      })
    }

    function reset() {
        ws.window = createWindow()
        verify(window !== null, "Failed to create the Window")
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Test                                                                                      //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function initTestCase() {
        compare(ws.name, "Window")
    }
    function init() {
        reset()
        SettingManager.save()
    }

    function test_save() {
        SettingManager.load()

        compare(window.x, 64)
        compare(window.y, 64)
        compare(window.width, 800)
        compare(window.height, 600)
        compare(window.visible, false)
        compare(window.visibility, Window.Hidden)
    }

    function test_load() {
        reset()
        window.x = 120
        window.y = 150
        window.showNormal()

        SettingManager.save()
        reset()
        SettingManager.load()

        compare(window.x, 120)
        compare(window.y, 150)
        compare(window.width, 800)
        compare(window.height, 600)
        compare(window.visible, true)
        compare(window.visibility, Window.Windowed)
    }

    function test_load_maximised() {
        reset()
        window.x = 200
        window.y = 200
        window.width = 1280
        window.height = 720
        window.showMaximized()

        SettingManager.save()
        reset()
        SettingManager.load()

        compare(window.x, 200)
        compare(window.y, 200)
        compare(window.width, 1280)
        compare(window.height, 720)
        compare(window.visible, true)
        compare(window.visibility, Window.Maximized)
    }

    function test_load_fullscreen() {
        reset()
        window.x = 200
        window.y = 200
        window.width = 1280
        window.height = 720
        window.showFullScreen()

        SettingManager.save()
        reset()
        SettingManager.load()

        compare(window.x, 200)
        compare(window.y, 200)
        compare(window.width, 1280)
        compare(window.height, 720)
        compare(window.visible, true)
        compare(window.visibility, Window.FullScreen)
    }
}
