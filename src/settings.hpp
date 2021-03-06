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
#ifndef STOIRIDH_SETTINGS_SETTINGS_HPP
#define STOIRIDH_SETTINGS_SETTINGS_HPP

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged RESET resetName FINAL)

public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings() override;

    QString name() const;
    void setName(QString name);
    void resetName();

    virtual void load(QSettings &settings);
    virtual void save(QSettings &settings);

signals:
    void nameChanged(QString name);

private:
    Q_DISABLE_COPY(Settings)

    QString m_name;
};

//--------------------------------------------------------------------------------------------------

inline QString Settings::name() const
{ return m_name; }

//--------------------------------------------------------------------------------------------------

#endif // STOIRIDH_SETTINGS_SETTINGS_HPP
