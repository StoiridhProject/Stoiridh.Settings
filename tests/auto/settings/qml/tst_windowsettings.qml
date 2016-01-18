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
import QtQuick.Window 2.2
import QtTest 1.1
import Stoiridh.Settings 1.0

TestCase {
    id: testCase
    name: "WindowSettings"

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Child objects                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Component {
        id: windowSettingsItem
        WindowSettings {
            name: "Test/WindowSettings"
        }
    }

    Component {
        id: windowItem
        Window {}
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Signals spies                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SignalSpy {
        id: windowSignalSpy
        signalName: "windowChanged"
    }

    SignalSpy {
        id: xSignalSpy
        signalName: "xChanged"
    }

    SignalSpy {
        id: ySignalSpy
        signalName: "yChanged"
    }

    SignalSpy {
        id: widthSignalSpy
        signalName: "widthChanged"
    }

    SignalSpy {
        id: heightSignalSpy
        signalName: "heightChanged"
    }

    SignalSpy {
        id: preferredPositionSignalSpy
        signalName: "preferredPositionChanged"
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Tests                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    function init() {
        verify(!windowSignalSpy.target)
        compare(windowSignalSpy.count, 0)

        verify(!xSignalSpy.target)
        compare(xSignalSpy.count, 0)

        verify(!ySignalSpy.target)
        compare(ySignalSpy.count, 0)

        verify(!widthSignalSpy.target)
        compare(widthSignalSpy.count, 0)

        verify(!heightSignalSpy.target)
        compare(heightSignalSpy.count, 0)

        verify(!preferredPositionSignalSpy.target)
        compare(preferredPositionSignalSpy.count, 0)
    }

    function cleanup() {
        windowSignalSpy.target = null
        windowSignalSpy.clear()

        xSignalSpy.target = null
        xSignalSpy.clear()

        ySignalSpy.target = null
        ySignalSpy.clear()

        widthSignalSpy.target = null
        widthSignalSpy.clear()

        heightSignalSpy.target = null
        heightSignalSpy.clear()

        preferredPositionSignalSpy.target = null
        preferredPositionSignalSpy.clear()
    }

    function init_data() {
        return [
                    {
                        tag: "1 - Windowed, Centred",
                        properties:
                        {
                            window:
                            {
                                x: 250, y: 250, width: 1280, height: 720,
                                visible: true,
                                visibility: Window.Windowed
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/1/Centred",
                                x: 120, y: 150, width: 800, height: 600,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 250, y: 250, width: 1280, height: 720,
                                    visibility: Window.Windowed
                                },
                                load:
                                {
                                    width: 1280, height: 720,
                                    visibility: Window.Windowed
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                width: 1280, height: 720,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                    {
                        tag: "2 - Maximized, Centred",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.Maximized
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/2/Centred",
                                x: 64, y: 64, width: 1024, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Maximized
                                },
                                load:
                                {
                                    width: 800, height: 600,
                                    visibility: Window.Maximized
                                }
                            },
                            settings:
                            {
                                width: 1024, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        check:
                        {
                            window: false,
                            settings: true
                        }
                    },
                    {
                        tag: "3 - FullScreen, Centred",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.FullScreen
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/3/Centred",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.FullScreen
                                },
                                load:
                                {
                                    width: 800, height: 600,
                                    visibility: Window.FullScreen
                                }
                            },
                            settings:
                            {
                                width: 640, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        check:
                        {
                            window: false,
                            settings: true
                        }
                    },
                    {
                        tag: "4 - Minimized, Centred",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.Minimized
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/4/Centred",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Minimized
                                },
                                load:
                                {
                                    width: 800, height: 600,
                                    visibility: Window.Minimized
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                width: 800, height: 600,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                    {
                        tag: "5 - Hidden, Centred",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visibility: Window.Hidden
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/5/Centred",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Hidden
                                },
                                load:
                                {
                                    width: 800, height: 600,
                                    visibility: Window.Hidden
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                width: 800, height: 600,
                                preferredPosition: WindowSettings.Centred
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                    ////////////////////////////////////////////////////////////////////////////////
                    //////////////////////////     USER DEFINED DATA     ///////////////////////////
                    ////////////////////////////////////////////////////////////////////////////////
                    {
                        tag: "1 - Windowed, User",
                        properties:
                        {
                            window:
                            {
                                x: 250, y: 250, width: 1280, height: 720,
                                visible: true,
                                visibility: Window.Windowed
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/1/User",
                                x: 120, y: 150, width: 800, height: 600,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 250, y: 250, width: 1280, height: 720,
                                    visibility: Window.Windowed
                                },
                                load:
                                {
                                    x: 250, y: 250, width: 1280, height: 720,
                                    visibility: Window.Windowed
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                x: 250, y: 250, width: 1280, height: 720,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                    {
                        tag: "2 - Maximized, User",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.Maximized
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/2/User",
                                x: 64, y: 64, width: 1024, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Maximized
                                },
                                load:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Maximized
                                }
                            },
                            settings:
                            {
                                x: 64, y: 64, width: 1024, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        check:
                        {
                            window: false,
                            settings: true
                        }
                    },
                    {
                        tag: "3 - FullScreen, User",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.FullScreen
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/3/User",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.FullScreen
                                },
                                load:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.FullScreen
                                }
                            },
                            settings:
                            {
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        check:
                        {
                            window: false,
                            settings: true
                        }
                    },
                    {
                        tag: "4 - Minimized, User",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visible: true,
                                visibility: Window.Minimized
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/4/User",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Minimized
                                },
                                load:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Minimized
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                x: 120, y: 120, width: 800, height: 600,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                    {
                        tag: "5 - Hidden, User",
                        properties:
                        {
                            window:
                            {
                                x: 120, y: 120, width: 800, height: 600,
                                visibility: Window.Hidden
                            },
                            settings:
                            {
                                name: "Test/WindowSettings/5/User",
                                x: 120, y: 120, width: 640, height: 480,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        expected:
                        {
                            window:
                            {
                                save:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Hidden
                                },
                                load:
                                {
                                    x: 120, y: 120, width: 800, height: 600,
                                    visibility: Window.Hidden
                                }
                            },
                            settings:
                            {
                                // during the save, width and height properties will are the same
                                // size than the window.
                                x: 120, y: 120, width: 800, height: 600,
                                preferredPosition: WindowSettings.User
                            }
                        },
                        check:
                        {
                            window: true,
                            settings: true
                        }
                    },
                ]
    }

    function test_property_window() {
        var window = windowItem.createObject(testCase)
        verify(window)

        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        windowSignalSpy.target = windowSettings
        verify(windowSignalSpy.valid)

        compare(windowSettings.window, null)
        compare(windowSignalSpy.count, 0)

        windowSettings.window = window
        compare(windowSignalSpy.count, 1)

        windowSettings.window = null
        compare(windowSignalSpy.count, 2)

        windowSettings.destroy()
        window.destroy()
    }

    function test_property_x() {
        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        xSignalSpy.target = windowSettings
        verify(xSignalSpy.valid)

        compare(windowSettings.x, 0)
        compare(xSignalSpy.count, 0)

        windowSettings.x = 120
        compare(windowSettings.x, 120)
        compare(xSignalSpy.count, 1)

        windowSettings.x = 0
        compare(windowSettings.x, 0)
        compare(xSignalSpy.count, 2)

        windowSettings.destroy()
    }

    function test_property_y() {
        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        ySignalSpy.target = windowSettings
        verify(ySignalSpy.valid)

        compare(windowSettings.y, 0)
        compare(ySignalSpy.count, 0)

        windowSettings.y = 120
        compare(windowSettings.y, 120)
        compare(ySignalSpy.count, 1)

        windowSettings.y = 0
        compare(windowSettings.y, 0)
        compare(ySignalSpy.count, 2)

        windowSettings.destroy()
    }

    function test_property_width() {
        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        widthSignalSpy.target = windowSettings
        verify(widthSignalSpy.valid)

        compare(windowSettings.width, 0)
        compare(widthSignalSpy.count, 0)

        windowSettings.width = 800
        compare(windowSettings.width, 800)
        compare(widthSignalSpy.count, 1)

        windowSettings.width = 0
        compare(windowSettings.width, 0)
        compare(widthSignalSpy.count, 2)

        windowSettings.destroy()
    }

    function test_property_height() {
        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        heightSignalSpy.target = windowSettings
        verify(heightSignalSpy.valid)

        compare(windowSettings.height, 0)
        compare(heightSignalSpy.count, 0)

        windowSettings.height = 600
        compare(windowSettings.height, 600)
        compare(heightSignalSpy.count, 1)

        windowSettings.height = 0
        compare(windowSettings.height, 0)
        compare(heightSignalSpy.count, 2)

        windowSettings.destroy()
    }

    function test_property_preferredPosition() {
        var windowSettings = windowSettingsItem.createObject(testCase)
        verify(windowSettings)

        preferredPositionSignalSpy.target = windowSettings
        verify(preferredPositionSignalSpy.valid)

        compare(windowSettings.preferredPosition, WindowSettings.Centred)
        compare(preferredPositionSignalSpy.count, 0)

        windowSettings.preferredPosition = WindowSettings.User
        compare(windowSettings.preferredPosition, WindowSettings.User)
        compare(preferredPositionSignalSpy.count, 1)

        windowSettings.preferredPosition = WindowSettings.Centred
        compare(windowSettings.preferredPosition, WindowSettings.Centred)
        compare(preferredPositionSignalSpy.count, 2)

        windowSettings.destroy()
    }

    function test_enum_preferredPosition_centred_data() {
        return [
                    { tag: "1", properties: { x: 120, y: 120, width: 800, height: 600, preferredPosition: WindowSettings.Centred } },
                    { tag: "2", properties: { x: 250, y: 175, width: 640, height: 480, preferredPosition: WindowSettings.Centred } },
                    { tag: "3", properties: { x:  64, y:  64, width: 320, height: 240, preferredPosition: WindowSettings.Centred } },
                    { tag: "4", properties: { x: 175, y:  64, width: 640, height: 600, preferredPosition: WindowSettings.Centred } },
                    { tag: "5", properties: { x: 300, y: 150, width: 768, height: 480, preferredPosition: WindowSettings.Centred } },
                ]
    }

    function test_enum_preferredPosition_centred(data) {
        var window = windowItem.createObject(testCase)
        verify(window)

        var windowSettings = windowSettingsItem.createObject(testCase, data.properties)
        verify(windowSettings)

        windowSettings.window = window

        var x = parseInt((Screen.desktopAvailableWidth - windowSettings.width) / 2, 10)
        var y = parseInt((Screen.desktopAvailableHeight - windowSettings.height) / 2, 10)

        compare(windowSettings.x, x)
        compare(windowSettings.y, y)
        compare(windowSettings.width, data.properties.width)
        compare(windowSettings.height, data.properties.height)
        compare(windowSettings.preferredPosition, data.properties.preferredPosition)

        windowSettings.destroy()
        window.destroy()
    }

    function test_enum_preferredPosition_user_data() {
        return [
                    { tag: "1", properties: { x: 120, y: 120, width: 800, height: 600, preferredPosition: WindowSettings.User } },
                    { tag: "2", properties: { x: 250, y: 175, width: 640, height: 480, preferredPosition: WindowSettings.User } },
                    { tag: "3", properties: { x:  64, y:  64, width: 320, height: 240, preferredPosition: WindowSettings.User } },
                    { tag: "4", properties: { x: 175, y:  64, width: 640, height: 600, preferredPosition: WindowSettings.User } },
                    { tag: "5", properties: { x: 300, y: 150, width: 768, height: 480, preferredPosition: WindowSettings.User } },
                ]
    }

    function test_enum_preferredPosition_user(data) {
        var window = windowItem.createObject(testCase)
        verify(window)

        var windowSettings = windowSettingsItem.createObject(testCase, data.properties)
        verify(windowSettings)

        windowSettings.window = window

        compare(windowSettings.x, data.properties.x)
        compare(windowSettings.y, data.properties.y)
        compare(windowSettings.width, data.properties.width)
        compare(windowSettings.height, data.properties.height)
        compare(windowSettings.preferredPosition, data.properties.preferredPosition)

        windowSettings.destroy()
        window.destroy()
    }

    function test_1_save(data) {
        var window = windowItem.createObject(testCase, data.properties.window)
        verify(window)

        var windowSettings = windowSettingsItem.createObject(testCase, data.properties.settings)
        verify(windowSettings)

        var expectedWindow = data.expected.window.save
        var expectedSettings = data.expected.settings

        windowSettings.window = window
        verify(windowSettings.window)

        SettingsManager.save()

        if (windowSettings.preferredPosition === WindowSettings.Centred)
        {
            if (data.check.window)
            {
                compare(window.x, expectedWindow.x)
                compare(window.y, expectedWindow.y)
                compare(window.width, expectedWindow.width)
                compare(window.height, expectedWindow.height)
                compare(window.visibility, expectedWindow.visibility)
            }

            if (data.check.settings)
            {
                var x = parseInt((Screen.desktopAvailableWidth - expectedSettings.width) / 2, 10)
                var y = parseInt((Screen.desktopAvailableHeight - expectedSettings.height) / 2, 10)

                compare(windowSettings.x, x)
                compare(windowSettings.y, y)
                compare(windowSettings.width, expectedSettings.width)
                compare(windowSettings.height, expectedSettings.height)
                compare(windowSettings.preferredPosition, expectedSettings.preferredPosition)
            }
        }
        else
        {
            if (data.check.window)
            {
                compare(window.x, expectedWindow.x)
                compare(window.y, expectedWindow.y)
                compare(window.width, expectedWindow.width)
                compare(window.height, expectedWindow.height)
                compare(window.visibility, expectedWindow.visibility)
            }

            if (data.check.settings)
            {
                compare(windowSettings.x, expectedSettings.x)
                compare(windowSettings.y, expectedSettings.y)
                compare(windowSettings.width, expectedSettings.width)
                compare(windowSettings.height, expectedSettings.height)
                compare(windowSettings.preferredPosition, expectedSettings.preferredPosition)
            }
        }

        windowSettings.destroy()
        window.destroy()
    }

    function test_2_load(data) {
        var window = windowItem.createObject(testCase, data.properties.window)
        verify(window)

        var windowSettings = windowSettingsItem.createObject(testCase, data.properties.settings)
        verify(windowSettings)

        var expectedWindow = data.expected.window.load
        var expectedSettings = data.expected.settings

        windowSettings.window = window
        verify(windowSettings.window)

        SettingsManager.load()

        if (windowSettings.preferredPosition === WindowSettings.Centred)
        {
            if (data.check.window)
            {
                var x = parseInt((Screen.desktopAvailableWidth - expectedWindow.width) / 2, 10)
                var y = parseInt((Screen.desktopAvailableHeight - expectedWindow.height) / 2, 10)

                compare(window.x, x)
                compare(window.y, y)
                compare(window.width, expectedWindow.width)
                compare(window.height, expectedWindow.height)
                compare(window.visibility, expectedWindow.visibility)
            }

            if (data.check.settings)
            {
                x = parseInt((Screen.desktopAvailableWidth - expectedSettings.width) / 2, 10)
                y = parseInt((Screen.desktopAvailableHeight - expectedSettings.height) / 2, 10)

                compare(windowSettings.x, x)
                compare(windowSettings.y, y)
                compare(windowSettings.width, expectedSettings.width)
                compare(windowSettings.height, expectedSettings.height)
                compare(windowSettings.preferredPosition, expectedSettings.preferredPosition)
            }
        }
        else
        {
            if (data.check.window)
            {
                compare(window.x, expectedWindow.x)
                compare(window.y, expectedWindow.y)
                compare(window.width, expectedWindow.width)
                compare(window.height, expectedWindow.height)
                compare(window.visibility, expectedWindow.visibility)
            }

            if (data.check.settings)
            {
                compare(windowSettings.x, expectedSettings.x)
                compare(windowSettings.y, expectedSettings.y)
                compare(windowSettings.width, expectedSettings.width)
                compare(windowSettings.height, expectedSettings.height)
                compare(windowSettings.preferredPosition, expectedSettings.preferredPosition)
            }
        }

        windowSettings.destroy()
        window.destroy()
    }
}
