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
#include "plugin.hpp"

#include "groupsettings.hpp"
#include "settings.hpp"
#include "settingsmanager.hpp"
#include "windowsettings.hpp"

#include <qqml.h>

void StoiridhSettingsPlugin::registerTypes(const char *uri)
{
    // @uri Stoiridh.Settings
    qmlRegisterType<GroupSettings>(uri, 1, 0, "GroupSettings");
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<WindowSettings>(uri, 1, 0, "WindowSettings");

    qmlRegisterSingletonType<SettingsManager>(uri,
                                             1, 0,
                                             "SettingsManager", &SettingsManager::provider);
}
