#include "mainwindow.h"
#include "addinginventory.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QColor>
#include <QLinearGradient>
#include <QLayout>
#include <QPixmap>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setUpDatabase();
    QPalette bgPalette = this->palette();
    bgPalette.setColor(QPalette::Window, QColor(85, 0, 0));
    setAutoFillBackground(true);
    setPalette(bgPalette);

    title = new QLabel("StockSmart Home", this);

    QFont titlefont("Arial Black", 24, QFont :: Bold);
    titlefont.setLetterSpacing(QFont :: PercentageSpacing, 110);
    title-> setFont(titlefont);
    title->setStyleSheet("color:rgb(51, 51, 51);");
    title -> setAlignment(Qt :: AlignCenter);

    subtitle = new QLabel("Manage your inventory easy and efficiently.",  this);
    QFont subtitleFont("Arial", 14);
    subtitle->setFont(subtitleFont);
    subtitle->setStyleSheet("color : rgb(85, 85, 85)");
    subtitle->setAlignment(Qt :: AlignCenter);

    QPushButton *startButton = new QPushButton("Add Inventory", this);
    QPushButton *exitButton = new QPushButton("Exit", this);

    startButton->setFixedSize(180, 50);
    exitButton->setFixedSize(180, 50);

    connect(startButton, &QPushButton :: clicked, this, &MainWindow :: addinventory);
    connect(exitButton, &QPushButton :: clicked, this, &QWidget :: close);
    exitButton->setShortcut(QKeySequence(Qt :: Key_Escape));

    startButton->setStyleSheet("QPushButton {"
                               "background-color: rgb(255, 175, 80);"
                               "color: white;"
                               "border-radius: 15px;"
                               "padding: 12px 24px;"
                               "font-size: 16px;"
                               "font-weight: bold;"
                               "min-width: 200px;"
                               "}"
                               "QPushButton:hover{"
                               "background-color: rgb(69, 160, 73);"
                               "}"
                               );

    exitButton->setStyleSheet("QPushButton {"
                              "background-color: rgb(244, 67, 54);"
                              "color: white;"
                              "border-radius: 15px;"
                              "padding: 12px 24px;"
                              "font-size: 16px;"
                              "font-weight: bold;"
                              "min-width: 200px;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: rgb(211, 47, 47);"
                              "}");


    QWidget *central = new QWidget(this);
    QVBoxLayout *mainlayout = new QVBoxLayout(central);

    mainlayout->addWidget(title);
    mainlayout->insertWidget(1, subtitle);
     mainlayout->setSpacing(40);
    mainlayout->insertSpacing(2, 30);
    mainlayout->addWidget(startButton, 0, Qt :: AlignCenter);
     mainlayout->setSpacing(20);
    mainlayout->addWidget(exitButton, 0, Qt :: AlignCenter);

    mainlayout->setContentsMargins(50, 50, 50, 50);
    mainlayout->setAlignment(Qt :: AlignCenter);

    setMinimumSize(400, 300);
    central->setLayout(mainlayout);
    setCentralWidget(central);

}

void MainWindow::addinventory()
{
    addinginventory *Addinginventory = new addinginventory();
    Addinginventory->show();
}

void MainWindow::setUpDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("inventory.db");
    if(!db.open())
    {
        qDebug() << "Failed to connect to " << db.lastError().text();
        return;
    }

    QSqlQuery Query;
    QString createtable = R"(
                    CREATE TABLE IF NOT EXISTS InventoryInfo
                    (
                        ID INTEGER PRIMARY KEY AUTOINCREMENT,
                        ProductName TEXT NOT NULL,
                        Quantity INTEGER,
                        Price INTEGER
                    )
                )";
    if(!Query.exec(createtable))
    {
        qDebug() << "Table doesn't exists";
    }
    else
    {
        qDebug() << "Tabel exits";
    }
}




MainWindow::~MainWindow()
{

}
