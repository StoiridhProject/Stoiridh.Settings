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

#include "setting.hpp"

#include <QQmlListProperty>

class GroupSettings : public Setting
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<AbstractSetting> settings READ settings)
    Q_CLASSINFO("DefaultProperty", "settings")

public:
    explicit GroupSettings(AbstractSetting *parent = nullptr);
    ~GroupSettings() = default;

    QQmlListProperty<AbstractSetting> settings();

    void load(QSettings &settings) override;
    void save(QSettings &settings) const override;

private:
    static void append(QQmlListProperty<AbstractSetting> *property, AbstractSetting *setting);
    static AbstractSetting *at(QQmlListProperty<AbstractSetting> *property, int index);
    static void clear(QQmlListProperty<AbstractSetting> *property);
    static int count(QQmlListProperty<AbstractSetting> *property);

private:
    QList<AbstractSetting *> m_settings{};
};

#endif // STOIRIDH_SETTINGS_GROUPSETTINGS_HPP
