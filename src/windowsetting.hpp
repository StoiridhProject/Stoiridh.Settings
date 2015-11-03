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
#ifndef STOIRIDH_SETTINGS_WINDOWSETTING_HPP
#define STOIRIDH_SETTINGS_WINDOWSETTING_HPP

#include "setting.hpp"

#include <QPointer>
#include <QRect>
#include <QQuickWindow>

class WindowSetting : public Setting
{
    Q_OBJECT
    Q_PROPERTY(QQuickWindow *window READ window WRITE setWindow NOTIFY windowChanged)

public:
    explicit WindowSetting(AbstractSetting *parent = nullptr);
    ~WindowSetting() = default;

    QQuickWindow *window() const;
    void setWindow(QQuickWindow *window);

    void load(QSettings &settings) override;
    void save(QSettings &settings) const override;

signals:
    void windowChanged();

private:
    bool canUpdateGeometry() const;
    bool useWindowGeometry() const;

private:
    QPointer<QQuickWindow> m_window{nullptr};
    QRect m_geometry{64, 64, 800, 600};
    QWindow::Visibility m_visibility{QWindow::Hidden};
};

#endif // STOIRIDH_SETTINGS_WINDOWSETTING_HPP
