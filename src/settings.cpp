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
#include "settings.hpp"

#include "settingsmanager.hpp"

#include <QMetaProperty>


Settings::Settings(QObject *parent)
    : QObject{parent}
{
    SettingsManager::registerSettings(this);
}

Settings::~Settings()
{
    SettingsManager::unregisterSettings(this);
}

/*! \qmlproperty string Stoiridh.Settings::Settings::name

    This property holds the name that will be used in the same way as a group where all properties
    set in the Settings item will be in the scope of \c name.
*/
void Settings::setName(QString name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}

void Settings::resetName()
{
    setName(QString{});
}

void Settings::load(QSettings &settings)
{
    settings.beginGroup(m_name);
    {
        const auto *metaObject = this->metaObject();

        for (auto i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
        {
            const auto property = metaObject->property(i);

            if (property.isWritable())
            {
                const auto key = QString::fromLatin1(property.name());
                const auto value = settings.value(key);

                if (value.isValid())
                    property.write(this, value);
            }
        }
    }
    settings.endGroup();
}

void Settings::save(QSettings &settings)
{
    settings.beginGroup(m_name);
    {
        const auto *metaObject = this->metaObject();

        for (auto i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
        {
            const auto property = metaObject->property(i);

            if (property.isReadable())
            {
                const auto key = QString::fromLatin1(property.name());
                const auto value = QVariant::fromValue(property.read(this));

                if (value.isValid())
                {
                    if (value.canConvert(property.type()))
                    {
                        settings.setValue(key, value);
                    }
                    else if (value.canConvert<QStringList>())
                    {
                        settings.setValue(key, value.toStringList());
                    }
                    else if (value.canConvert<QVariantList>())
                    {
                        settings.setValue(key, value.toList());
                    }
                }
            }
        }
    }
    settings.endGroup();
}
