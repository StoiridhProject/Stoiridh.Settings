SettingsManager
====================================================================================================

.. Copyright 2015-2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>

----------------------------------------------------------------------------------------------------

Introduction
------------

The SettingsManager item is a singleton type allowing the save and restore the application settings.

.. highlight:: qml

Example::

   import QtQuick 2.5
   import QtQuick.Controls 1.4
   import Stoiridh.Settings 1.0

   ApplicationWindow {
      menuBar: MenuBar {
         Menu {
            title: qsTr("&File")

            MenuItem {
               text: qsTr("E&xit")
               onTriggered: {
                  SettingsManager.save()
                  Qt.quit()
               }
            }
         }
      }

      onClosing: SettingsManager.save()
      Component.onCompleted: SettingsManager.load()
   }
