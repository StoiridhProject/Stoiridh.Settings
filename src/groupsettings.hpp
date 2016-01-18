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
#ifndef STOIRIDH_SETTINGS_GROUPSETTINGS_HPP
#define STOIRIDH_SETTINGS_GROUPSETTINGS_HPP

#include "settings.hpp"

#include <QQmlListProperty>

class GroupSettings : public Settings
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Settings> settings READ settings)
    Q_CLASSINFO("DefaultProperty", "settings")

public:
    explicit GroupSettings(Settings *parent = nullptr);

    QQmlListProperty<Settings> settings();

    void load(QSettings &settings) override;
    void save(QSettings &settings) override;

private:
    static void append(QQmlListProperty<Settings> *property, Settings *settings);
    static Settings *at(QQmlListProperty<Settings> *property, int index);
    static void clear(QQmlListProperty<Settings> *property);
    static int count(QQmlListProperty<Settings> *property);

private:
    Q_DISABLE_COPY(GroupSettings)

    QList<Settings *> m_settings{};
};

#endif // STOIRIDH_SETTINGS_GROUPSETTINGS_HPP
