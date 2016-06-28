GroupSettings
====================================================================================================

.. Copyright 2015-2016 Stòiridh Project.
.. This file is under the FDL licence, see LICENCE.FDL for details.

.. sectionauthor:: William McKIE <mckie.william@hotmail.co.uk>

----------------------------------------------------------------------------------------------------

Introduction
------------

The GroupSettings item can be used to group several Settings items.

Using the ``name`` property prevents from accidental writing during a call to the ``save()``
function from the Qml Singleton, ``SettingsManager``.

.. highlight:: qml

Example::

   import QtQuick 2.5
   import QtQuick.Controls 1.4
   import Stoiridh.Settings 1.0

   ApplicationWindow {
      id: mainWindow

      GroupSettings {
         name: "MainWindow"

         GroupSettings {}
         Settings {}
         WindowSettings {}

         // ...
      }
   }

As a GroupSettings item inherits from Settings, so it can also be a child of another GroupSettings
item.
