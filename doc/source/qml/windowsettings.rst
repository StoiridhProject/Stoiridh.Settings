WindowSettings
====================================================================================================

.. Copyright 2015-2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>

----------------------------------------------------------------------------------------------------

Introduction
------------

The WindowSettings item saves and restores both the window's geometry and the window's state.

.. warning::

    WindowSettings doesn't accept user-defined properties.

Geometry
--------

The WindowSettings's geometry represents the default window's geometry that can be saved instead
of the window's geometry. This happens when the current window's state is either *FullScreen* or
*Maximized* [1]_.

.. note::

   It is recommended to always set the WindowSettings's geometry even if the preferred position is
   ``WindowSettings.Centred``.

Preferred position
------------------

While the settings is loading, the window can be restored either at the centre or at the latest
position known in relation to the screen where the window is shown during the previous save.

For this, it exists two flags to control this behaviour:

- *WindowSettings.Centred* allows to centre the window in relation to the screen.
- *WindowSettings.User* allows to place the window at the desired position.

.. highlight:: qml

Example::

   import QtQuick 2.5
   import QtQuick.Controls 1.4
   import Stoiridh.Settings 1.0

   ApplicationWindow {
      id: mainWindow

      WindowSettings {
         name: "MainWindow"
         window: mainWindow
         preferredPosition: WindowSettings.Centred
         x: 120
         y: 120
         width: 800
         height: 600
      }
   }

.. rubric:: Footnotes

.. [1] Window's visibility: https://doc.qt.io/qt-5/qwindow.html#Visibility-enum
