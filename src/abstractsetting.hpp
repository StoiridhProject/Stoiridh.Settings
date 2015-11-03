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
#ifndef STOIRIDH_SETTINGS_ABSTRACTSETTING_HPP
#define STOIRIDH_SETTINGS_ABSTRACTSETTING_HPP

#include <QObject>
#include <QSettings>

class AbstractSetting : public QObject
{
    Q_OBJECT

public:
    explicit AbstractSetting(QObject *parent = nullptr);
    virtual ~AbstractSetting();

    virtual void load(QSettings &settings) = 0;
    virtual void save(QSettings &settings) const = 0;
};

#endif // STOIRIDH_SETTINGS_ABSTRACTSETTING_HPP
