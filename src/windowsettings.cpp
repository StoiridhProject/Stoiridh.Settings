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
#include "windowsettings.hpp"

#include <QQuickWindow>
#include <QScreen>


WindowSettings::WindowSettings(Settings *parent)
    : Settings{parent}
{

}

/*! \qmlproperty Window Stoiridh.Settings::WindowSettings::window

    This property holds a window so as to save and restore the window state.
*/
void WindowSettings::setWindow(QQuickWindow *window)
{
    if (m_window != window)
    {
        if (m_window)
            m_window->disconnect(this);

        m_window = window;

        if (m_window)
        {
            connect(m_window, &QWindow::visibilityChanged, this, &WindowSettings::updateGeometry);
            updateGeometry(m_window->visibility());
        }

        emit windowChanged();
    }
}

/*! \qmlproperty int Stoiridh.Settings::WindowSettings::x

    This property holds the x position of the default window's geometry.
 */
void WindowSettings::setX(int x)
{
    if (m_geometry.x() != x)
    {
        m_geometry.moveLeft(x);
        emit xChanged();
    }
}

/*! \qmlproperty int Stoiridh.Settings::WindowSettings::y

    This property holds the y position of the default window's geometry.
 */
void WindowSettings::setY(int y)
{
    if (m_geometry.y() != y)
    {
        m_geometry.moveTop(y);
        emit yChanged();
    }
}

/*! \qmlproperty int Stoiridh.Settings::WindowSettings::width

    This property holds the width of the default window's geometry.
 */
void WindowSettings::setWidth(int width)
{
    if (m_geometry.width() != width)
    {
        m_geometry.setWidth(width);
        emit widthChanged();
    }
}

/*! \qmlproperty int Stoiridh.Settings::WindowSettings::height

    This property holds the height of the default window's geometry.
 */
void WindowSettings::setHeight(int height)
{
    if (m_geometry.height() != height)
    {
        m_geometry.setHeight(height);
        emit heightChanged();
    }
}

/*! \qmlproperty enumeration Stoiridh.Settings::WindowSettings::preferredPosition

    This property defines the preferred position of the window when the settings will be restored.

    \list
    \li WindowSettings.Centred - The window will be positioned at the centre of the screen.
    \li WindowSettings.User - The window will be positioned at the latest position known of
                                     the previous session.
    \endlist

    The default value is \c{WindowSettings.Centred}.
*/
void WindowSettings::setPreferredPosition(WindowSettings::PreferredPosition preferredPosition)
{
    if (m_preferredPosition != preferredPosition)
    {
        m_preferredPosition = preferredPosition;
        emit preferredPositionChanged();
    }
}

void WindowSettings::load(QSettings &settings)
{
    if (m_window)
    {
        settings.beginGroup(name());
        {
            m_geometry = settings.value("geometry", QRect{}).toRect();

            bool ok{false};
            int v = settings.value("visibility", -1).toInt(&ok);

            if (ok)
            {
                auto visibility = (v < 0) ? m_window->visibility()
                                          : static_cast<QWindow::Visibility>(v);

                if (visibility != QWindow::FullScreen && visibility != QWindow::Maximized)
                {
                    if (m_geometry.isValid())
                    {
                        m_window->setGeometry(m_geometry);
                    }
                    else
                    {
                        m_window->setGeometry(m_userGeometry);
                        m_geometry = m_userGeometry;
                    }
                }

                m_window->setVisibility(visibility);
            }
        }
        settings.endGroup();
    }
}

void WindowSettings::save(QSettings &settings)
{
    if (m_window)
    {
        settings.beginGroup(name());
        {
            auto visibility = m_window->visibility();

            if (visibility != QWindow::FullScreen && visibility != QWindow::Maximized)
                m_geometry = m_window->geometry();

            movePositionToCentre();

            settings.setValue("geometry", m_geometry);
            settings.setValue("visibility", visibility);
        }
        settings.endGroup();
    }
}

void WindowSettings::classBegin()
{
    // nothing to do here
}

void WindowSettings::componentComplete()
{
    // save the geometry defined by the user
    m_userGeometry = m_geometry;
}

void WindowSettings::updateGeometry(QWindow::Visibility visibility)
{
    if (visibility != QWindow::FullScreen && visibility != QWindow::Maximized)
    {
        if (m_window)
        {
            const auto geometry = m_window->geometry();

            if (geometry.isValid())
            {
                m_geometry = geometry;
            }
            else
            {
                m_window->setGeometry(m_geometry);
            }
        }
    }
    movePositionToCentre();
}

void WindowSettings::movePositionToCentre()
{
    if (m_window && m_preferredPosition == PreferredPosition::Centred)
    {
        const auto *screen = m_window->screen();

        if (screen)
        {
            const auto desktopGeometry = screen->availableGeometry();
            const int x = (desktopGeometry.width() - m_geometry.width()) / 2;
            const int y = (desktopGeometry.height() - m_geometry.height()) / 2;

            setX(x);
            setY(y);
        }
    }
}
