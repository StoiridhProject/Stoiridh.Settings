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
#include "groupsettings.hpp"

#include "settings.hpp"
#include "settingsmanager.hpp"


/*! \qmltype GroupSettings
    \instantiates GroupSettings
    \inherits Settings
    \inqmlmodule Stoiridh.Settings
    \ingroup stoiridh_settings
    \since Stoiridh.Settings 1.0

    \brief GroupSettings provides a way to group several settings.

    A GroupSettings item can be used to group several Settings items.

    Using the \l{Settings::}{name} property prevents from accidental writing during a call to the
    \l{SettingsManager::}{save()} function from the SettingsManager.

    Example:

    \qml
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
    \endqml

    As a GroupSettings item inherits from Settings, so it can also be a child of another
    GroupSettings item.
*/


GroupSettings::GroupSettings(Settings *parent)
    : Settings{parent}
{

}

/*! \qmlproperty list<Settings> Stoiridh.Settings::GroupSettings::settings
    \default

    This default property holds a list of settings in the group.
*/
QQmlListProperty<Settings> GroupSettings::settings()
{
    return {this,
            nullptr,
            &GroupSettings::append,
            &GroupSettings::count,
            &GroupSettings::at,
            &GroupSettings::clear};
}

void GroupSettings::load(QSettings &settings)
{
    Settings::load(settings);

    settings.beginGroup(name());
    {
        for (auto *setting : m_settings)
        {
            if (setting)
                setting->load(settings);
        }
    }
    settings.endGroup();
}

void GroupSettings::save(QSettings &settings)
{
    Settings::save(settings);

    settings.beginGroup(name());
    {
        for (auto *setting : m_settings)
        {
            if (setting)
                setting->save(settings);
        }
    }
    settings.endGroup();
}

void GroupSettings::append(QQmlListProperty<Settings> *property, Settings *settings)
{
    auto *groupSettings = qobject_cast<GroupSettings *>(property->object);

    if (groupSettings)
    {
        if (settings)
        {
            groupSettings->m_settings.append(settings);
            SettingsManager::unregisterSettings(settings);
        }
    }
}

Settings *GroupSettings::at(QQmlListProperty<Settings> *property, int index)
{
    const auto *groupSettings = qobject_cast<GroupSettings *>(property->object);

    if (groupSettings)
    {
        return groupSettings->m_settings.at(index);
    }

    return nullptr;
}

void GroupSettings::clear(QQmlListProperty<Settings> *property)
{
    auto *groupSettings = qobject_cast<GroupSettings *>(property->object);

    if (groupSettings)
    {
        groupSettings->m_settings.clear();
    }
}

int GroupSettings::count(QQmlListProperty<Settings> *property)
{
    const auto *groupSettings = qobject_cast<GroupSettings *>(property->object);

    if (groupSettings)
    {
        return groupSettings->m_settings.count();
    }

    return 0;
}
