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
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "settingmanager.hpp"

#include "abstractsetting.hpp"

#include <QQmlEngine>
#include <QSettings>
#include <QVector>


/*!
  \qmltype SettingManager
  \instantiates SettingManager
  \inherits QtObject
  \inqmlmodule Stoiridh.Settings
  \ingroup stoiridh_settings
  \since Stoiridh.Settings 1.0

  \brief Handles the application settings

  SettingManager is a QML singleton type providing two methods in order to \l{save} and \l{load}
  the application settings.

  Example:
  \qml
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
                      SettingManager.save()
                      Qt.quit()
                  }
              }
          }
      }

      onClosing: SettingManager.save()
      Component.onCompleted: SettingManager.load()
  }
  \endqml
 */


QVector<AbstractSetting *> SettingManager::m_settings{};


/*!
  \brief Constructs a SettingManager object with an optional \a parent as parent.
 */
SettingManager::SettingManager(QObject *parent)
    : QObject{parent}
{
}

/*!
  \brief Destroys a SettingManager object.
 */
SettingManager::~SettingManager()
{
    m_settings.clear();
}

/*!
  \brief Creates a new provider used as QML singleton type by the QML engine.
 */
QObject *SettingManager::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    auto settingManager = new SettingManager();
    return settingManager;
}

/*!
  \brief Registers a \a setting in the SettingManager to make the save and load of its settings.

  \sa SettingManager::unregisterSetting()
 */
void SettingManager::registerSetting(AbstractSetting *setting)
{
    if (!m_settings.contains(setting))
        m_settings << setting;
}

/*!
  \brief Unregisters a \a setting previously registered by the SettingManager.

  \sa SettingManager::registerSetting()
 */
void SettingManager::unregisterSetting(AbstractSetting *setting)
{
    m_settings.removeOne(setting);
}

/*!
  \qmlmethod void SettingManager::load()
  \brief Loads all application settings.
 */
void SettingManager::load()
{
    QSettings settings{};

    for (auto *s : m_settings)
        s->load(settings);
}

/*!
  \qmlmethod void SettingManager::save()
  \brief Saves all application settings.
 */
void SettingManager::save()
{
    QSettings settings{};

    for (auto *s : m_settings)
        s->save(settings);
}
