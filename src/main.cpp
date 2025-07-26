#include "mainwindow.h"
#include "addinginventory.h"

#include <QApplication>
#include <QLabel>
#include <QGridLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600,400);
    w.setWindowTitle("StockSmart Home");
    w.setWindowIcon(QIcon("C:\\Users\\saira\\Desktop\\C++ Projects\\Inventory-mangement-system\\images\\icon1.png"));
    w.show();
    return a.exec();
}
