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
#include <QtQuickTest/QtQuickTest>

#define TEST_NAME(name) #name

int main(int argc, char **argv)
{
    QCoreApplication::setOrganizationName(QStringLiteral("StoiridhProject"));
    QCoreApplication::setApplicationName(QStringLiteral("test.stoiridh"));

#if defined(QUICK_TEST_SOURCE_DIR)
    return quick_test_main(argc, argv, TEST_NAME(Test.Stoiridh.Settings), QUICK_TEST_SOURCE_DIR);
#else
    return quick_test_main(argc, argv, TEST_NAME(Test.Stoiridh.Settings), nullptr);
#endif
}
