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
#ifndef STOIRIDH_SETTINGS_SETTINGMANAGER_HPP
#define STOIRIDH_SETTINGS_SETTINGMANAGER_HPP

#include <QObject>

QT_BEGIN_NAMESPACE
class QQmlEngine;
class QJSEngine;
QT_END_NAMESPACE

class AbstractSetting;

class SettingManager final : public QObject
{
    Q_OBJECT

public:
    explicit SettingManager(QObject *parent = nullptr);
    ~SettingManager();

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

    static void registerSetting(AbstractSetting *setting);
    static void unregisterSetting(AbstractSetting *setting);

    Q_INVOKABLE void load();
    Q_INVOKABLE void save();

private:
    static QVector<AbstractSetting *> m_settings;
};

#endif // STOIRIDH_SETTINGS_SETTINGMANAGER_HPP
