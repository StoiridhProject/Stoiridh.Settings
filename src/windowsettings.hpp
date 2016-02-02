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
#ifndef STOIRIDH_SETTINGS_WINDOWSETTINGS_HPP
#define STOIRIDH_SETTINGS_WINDOWSETTINGS_HPP

#include "settings.hpp"

#include <QPointer>
#include <QRect>
#include <QQuickWindow>

class WindowSettings : public Settings, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QQuickWindow *window READ window WRITE setWindow NOTIFY windowChanged FINAL)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(PreferredPosition preferredPosition READ preferredPosition
                                                   WRITE setPreferredPosition
                                                   NOTIFY preferredPositionChanged FINAL)
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit WindowSettings(Settings *parent = nullptr);

    enum class PreferredPosition
    {
        Centred,
        User
    };
    Q_ENUM(PreferredPosition)

    QQuickWindow *window() const;
    void setWindow(QQuickWindow *window);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    PreferredPosition preferredPosition() const;
    void setPreferredPosition(PreferredPosition preferredPosition);

    void load(QSettings &settings) override;
    void save(QSettings &settings) override;

    void classBegin() override;
    void componentComplete() override;

signals:
    void windowChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void preferredPositionChanged();

private slots:
    void updateGeometry(QWindow::Visibility visibility);

private:
    void movePositionToCentre();

private:
    Q_DISABLE_COPY(WindowSettings)

    QPointer<QQuickWindow> m_window{};
    QRect m_geometry{};
    QRect m_userGeometry{};
    PreferredPosition m_preferredPosition{PreferredPosition::Centred};
};

//--------------------------------------------------------------------------------------------------

inline QQuickWindow *WindowSettings::window() const
{
    return m_window;
}

inline int WindowSettings::x() const
{
    return m_geometry.x();
}

inline int WindowSettings::y() const
{
    return m_geometry.y();
}

inline int WindowSettings::width() const
{
    return m_geometry.width();
}

inline int WindowSettings::height() const
{
    return m_geometry.height();
}

inline WindowSettings::PreferredPosition WindowSettings::preferredPosition() const
{
    return m_preferredPosition;
}

//--------------------------------------------------------------------------------------------------

#endif // STOIRIDH_SETTINGS_WINDOWSETTINGS_HPP
