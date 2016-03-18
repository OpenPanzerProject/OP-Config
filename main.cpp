/* OPConfig 		Configuration program for the Open Panzer TCB (Tank Control Board)
 * Source: 			openpanzer.org
 * Authors:    		Luke Middleton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mainwindow.h"
#include "deviceselect.h"
#include <QApplication>
#include <QStyleFactory>

#include "winsparkle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // This is the deviceselect form. We're not using it for now, it was just for testing.
    // We may want to use something like it someday if we have multiple devices configured from
    // the same application. However, in that case, major other changes will need to be made to the
    // MainWindow.ui
    //deviceselect *dialog = new deviceselect();
    //dialog->exec();

    return a.exec();
}

