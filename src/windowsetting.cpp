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
#include "windowsetting.hpp"

#include <QQuickWindow>


/*!
  \qmltype WindowSetting
  \instantiates WindowSetting
  \inherits Setting
  \inqmlmodule Stoiridh.Settings
  \ingroup stoiridh_settings
  \since Stoiridh.Settings 1.0

  \brief Handles the state and geometry of the window

  Example:
  \qml
  import QtQuick 2.5
  import QtQuick.Controls 1.4
  import Stoiridh.Settings 1.0

  ApplicationWindow {
      id: mainWindow

      WindowSetting {
          name: "MainWindow"
          window: mainWindow
      }
  }
  \endqml
*/

/*! \qmlproperty Window WindowSetting::window

  Gets or sets the window in order to handle its settings.

  Defaults to null window.
*/


/*!
  \brief Constructs a WindowSetting object with an optional \a parent as parent.
*/
WindowSetting::WindowSetting(AbstractSetting *parent)
    : Setting{parent}
{

}

QQuickWindow *WindowSetting::window() const
{
    return m_window;
}

void WindowSetting::setWindow(QQuickWindow *window)
{
    if (m_window != window)
    {
        if (m_window)
        {
            disconnect(m_window, nullptr, this, nullptr);
            m_window = nullptr;
        }

        if (window)
        {
            m_window = window;

            connect(m_window, &QWindow::xChanged, [this](int x)
            {
                if (canUpdateGeometry())
                    m_geometry.setX(x);
            });
            connect(m_window, &QWindow::yChanged, [this](int y)
            {
                if (canUpdateGeometry())
                    m_geometry.setY(y);
            });
            connect(m_window, &QWindow::widthChanged, [this](int width)
            {
                if (canUpdateGeometry())
                    m_geometry.setWidth(width);
            });
            connect(m_window, &QWindow::heightChanged, [this](int height)
            {
                if (canUpdateGeometry())
                    m_geometry.setHeight(height);
            });
            connect(m_window, &QWindow::visibilityChanged, [this](QWindow::Visibility visibility)
            {
                if (m_visibility != visibility)
                {
                    if (m_visibility == QWindow::Maximized
                            && (visibility != QWindow::Maximized
                                || visibility != QWindow::FullScreen))
                    {
                        m_geometry = m_window->geometry();
                        m_window->setGeometry(m_geometry);
                    }
                    m_visibility = visibility;
                }
            });
            emit windowChanged();
        }
    }
}

void WindowSetting::load(QSettings &settings)
{
    Setting::load(settings);

    if (m_window)
    {
        settings.beginGroup(m_name);
        {
            auto geometry = settings.value("geometry", QRect{64, 64, 800, 600}).toRect();
            int visibility = settings.value("visibility", -1).toInt();

            auto v = (visibility < 0) ? m_window->visibility()
                                      : static_cast<QWindow::Visibility>(visibility);

            m_window->setGeometry(geometry);
            m_window->setVisibility(v);
        }
        settings.endGroup();
    }
}

void WindowSetting::save(QSettings &settings) const
{
    Setting::save(settings);

    if (m_window)
    {
        settings.beginGroup(m_name);
        {
            settings.setValue("geometry", useWindowGeometry() ? m_window->geometry() : m_geometry);
            settings.setValue("visibility", m_window->visibility());
        }
        settings.endGroup();
    }
}

bool WindowSetting::canUpdateGeometry() const
{
    return (m_visibility != QWindow::Maximized && m_visibility != QWindow::FullScreen);
}

bool WindowSetting::useWindowGeometry() const
{
    return (m_window
            && m_window->visibility() != QWindow::Maximized
            && m_window->visibility() != QWindow::FullScreen);
}
