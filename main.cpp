#include "admin_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Adminwindow w;
    w.show();
    return QCoreApplication::exec();
}
