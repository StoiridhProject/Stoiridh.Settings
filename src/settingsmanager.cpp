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
#include "settingsmanager.hpp"

#include "settings.hpp"

#include <QQmlEngine>
#include <QSettings>
#include <QVector>


/*! \qmltype SettingsManager
    \instantiates SettingsManager
    \inherits QtObject
    \inqmlmodule Stoiridh.Settings
    \ingroup stoiridh_settings
    \since Stoiridh.Settings 1.0

    \brief Saves and restores the application settings.

    SettingsManager item is a singleton type allowing the save and load of the application settings.

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
                        SettingsManager.save()
                        Qt.quit()
                    }
                }
            }
        }

        onClosing: SettingsManager.save()
        Component.onCompleted: SettingsManager.load()
    }
    \endqml
*/

/*! \qmlmethod void Stoiridh.Settings::SettingsManager::load()

    Loads the application settings.
*/

/*! \qmlmethod void Stoiridh.Settings::SettingsManager::save()

    Saves the application settings.
*/


QVector<QPointer<Settings>> SettingsManager::m_settings{};


SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
{
}

SettingsManager::~SettingsManager()
{
    m_settings.clear();
}

QObject *SettingsManager::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return new SettingsManager{};
}

void SettingsManager::registerSettings(Settings *settings)
{
    if (!m_settings.contains(settings))
        m_settings.push_back(settings);
}

void SettingsManager::unregisterSettings(Settings *settings)
{
    m_settings.removeOne(settings);
}

void SettingsManager::load()
{
    QSettings settings{};

    m_settings.removeAll(nullptr);

    for (const auto setting : m_settings)
    {
        if (setting)
            setting->load(settings);
    }
}

void SettingsManager::save()
{
    QSettings settings{};

    m_settings.removeAll(nullptr);

    for (const auto setting : m_settings)
    {
        if (setting)
            setting->save(settings);
    }
}
