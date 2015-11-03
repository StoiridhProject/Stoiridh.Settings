////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2015 William McKIE                                                    //
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

#include "setting.hpp"
#include "settingmanager.hpp"


/*!
  \qmltype GroupSettings
  \instantiates GroupSettings
  \inherits Setting
  \inqmlmodule Stoiridh.Settings
  \ingroup stoiridh_settings
  \since Stoiridh.Settings 1.0

  \brief Groups the settings together

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
          Setting {}
          WindowSetting {}
      }
  }
  \endqml
 */

/*! \qmlproperty list<Setting> GroupSettings::settings
    \default

    Gets or sets the settings containing in \c this group.
*/

/*!
  \brief Constructs a GroupSettings object with an optional \a parent as parent.
*/
GroupSettings::GroupSettings(AbstractSetting *parent)
    : Setting{parent}
{

}

QQmlListProperty<AbstractSetting> GroupSettings::settings()
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
    Setting::load(settings);

    settings.beginGroup(m_name);
    {
        for (auto *s : m_settings)
            s->load(settings);
    }
    settings.endGroup();
}

void GroupSettings::save(QSettings &settings) const
{
    Setting::save(settings);

    settings.beginGroup(m_name);
    {
        for (const auto *s : m_settings)
            s->save(settings);
    }
    settings.endGroup();
}

void GroupSettings::append(QQmlListProperty<AbstractSetting> *property, AbstractSetting *setting)
{
    if (auto *groupSetting = qobject_cast<GroupSettings *>(property->object))
    {
        if (setting)
        {
            groupSetting->m_settings.append(setting);
            SettingManager::unregisterSetting(setting);
        }
    }
}

AbstractSetting *GroupSettings::at(QQmlListProperty<AbstractSetting> *property, int index)
{
    if (auto *groupSetting = qobject_cast<GroupSettings *>(property->object))
        return groupSetting->m_settings.at(index);

    return nullptr;
}

void GroupSettings::clear(QQmlListProperty<AbstractSetting> *property)
{
    if (auto *groupSetting = qobject_cast<GroupSettings *>(property->object))
        groupSetting->m_settings.clear();
}

int GroupSettings::count(QQmlListProperty<AbstractSetting> *property)
{
    if (auto *groupSetting = qobject_cast<GroupSettings *>(property->object))
        return groupSetting->m_settings.count();

    return 0;
}
