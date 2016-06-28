Settings
====================================================================================================

.. Copyright 2015-2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>

----------------------------------------------------------------------------------------------------

Introduction
------------

The Settings item uses its properties as setting fields in order to save and restore the state of an
item or an object in an application.

The ``name`` property can be set so as to prevent from accidental writing of settings.

.. highlight:: qml

Example::

   import QtQuick 2.5
   import QtQuick.Controls 1.4
   import Stoiridh.Settings 1.0

   ApplicationWindow {
      id: mainWindow

      Settings {
         name: "MainWindow"

         property alias x: mainWindow.x
         property alias y: mainWindow.y
         property alias width: mainWindow.width
         property alias height: mainWindow.height
         property alias visible: mainWindow.visible
      }
   }

.. note::

   It is recommended to use *alias* properties as fields for the Settings item.
