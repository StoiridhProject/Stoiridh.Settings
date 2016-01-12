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
#include "abstractsetting.hpp"
#include "settingmanager.hpp"


/*!
  \qmltype AbstractSetting
  \inherits QtObject
  \qmlabstract
  \internal
  \since Stoiridh.Settings 1.0

  \brief Base class to make new QML types.

  The AbstractSetting class is a base class to make new QML types to handle different type of
  settings from QML
 */


/*!
  \brief Constructs an AbstractSetting object with an optional \a parent as parent and registers
         it into the \l{SettingManager}.
 */
AbstractSetting::AbstractSetting(QObject *parent)
    : QObject{parent}
{
    SettingManager::registerSetting(this);
}

/*!
  \brief Destroys an AbstractSetting object and unregisters it from the \l{SettingManager}.
 */
AbstractSetting::~AbstractSetting()
{
    SettingManager::unregisterSetting(this);
}
