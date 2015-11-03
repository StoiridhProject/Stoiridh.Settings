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
#include "setting.hpp"

#include <QMetaProperty>


/*!
  \qmltype Setting
  \instantiates Setting
  \inqmlmodule Stoiridh.Settings
  \ingroup stoiridh_settings
  \since Stoiridh.Settings 1.0

  \brief Provides a way to use the properties as setting

  Example:
  \qml
  import QtQuick 2.5
  import QtQuick.Controls 1.4
  import Stoiridh.Settings 1.0

  ApplicationWindow {
      id: mainWindow

      Setting {
          name: "Options"
          property bool saveOnExit: true
      }
  }
  \endqml
 */

/*!
  \qmlproperty string Setting::name

  Gets or sets a name for \c this setting in order to group all properties rather than in the global
  scope or in the \l{GroupSettings} scope.

  \sa QSettings::beginGroup(), QSettings::endGroup()
*/


Setting::Setting(AbstractSetting *parent)
    : AbstractSetting{parent}
{

}

QString Setting::name() const
{
    return m_name;
}

void Setting::resetName()
{
    setName(QString{});
}

void Setting::setName(QString name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}

void Setting::load(QSettings &settings)
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

void Setting::save(QSettings &settings) const
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
