#include "addinginventory.h"


#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QColor>
#include <QTabletEvent>
#include <QFormLayout>
#include <QDateTime>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMargins>
#include <QShortcutEvent>

addinginventory::addinginventory(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("background-color: rgb(26, 17, 16)");
    this->setFont(QFont("Arial", 12));

    setWindowTitle("Add Inventory");
    setFixedSize(600, 400);
    productname = new QLineEdit(this);
    productprice = new QSpinBox(this);
    productquantity = new QSpinBox(this);


    productquantity->setRange(0, 100000);
    productprice->setRange(0, 100000);
    productname->setPlaceholderText("eg: HP Laptop");

    QString inputstyle = "QLineEdit, QSpingBox{"
                         "background-color: white;"
                         "border: 2px solid: rgb(209, 209, 209);"
                         "border-raidus: 8px;"
                         "padding: 8px;"
                         "font-size: 14px;"
                         "}";

    productname->setStyleSheet(inputstyle);
    productquantity->setStyleSheet(inputstyle);
    productprice->setStyleSheet(inputstyle);


    QPushButton *savebutton = new QPushButton("Save", this);
    QPushButton *confirmbutton = new QPushButton("Confirm", this);
    savebutton->setStyleSheet("QPushButton {"
                              "background-color: rgb(76, 175, 80);"
                              "color: white;"
                              "border-radius: 10px;"
                              "padding: 12px 24px;"
                              "font-weight: bold;"
                              "font-size: 16px;"
                              "min-width: 200px;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: rgb(69, 160, 73);"
                              "}");

    confirmbutton->setStyleSheet("QPushButton {"
                                 "background-color: rgb(244, 67, 54);"
                                 "color: white;"
                                 "border-radius: 10px;"
                                 "padding: 12px 24px;"
                                 "font-weight: bold;"
                                 "font-size: 16px;"
                                 "min-width: 200px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: rgb(69, 160, 73);"
                                 "}");

    savebutton ->setFixedSize(180, 50);
    confirmbutton ->setFixedSize(180, 50);

    connect(confirmbutton, &QPushButton::clicked, this, &addinginventory::confirmclick);

    QFormLayout *tableform = new QFormLayout();

    tableform ->addRow("Product Name: ", productname);
    tableform ->addRow("Quantity: ", productquantity);
    tableform ->addRow("Price: ", productprice);


    QVBoxLayout *mainlayout = new QVBoxLayout(this);

    mainlayout ->addLayout(tableform);
    mainlayout ->setSpacing(20);
    mainlayout ->addWidget(savebutton, 0, Qt::AlignCenter);
    mainlayout ->addWidget(confirmbutton, 0, Qt::AlignCenter);
    mainlayout ->setContentsMargins(50, 50, 50, 50);
    mainlayout ->setAlignment(Qt::AlignCenter);

    connect(savebutton, &QPushButton :: clicked, this, &addinginventory::addtoDatabase);
}


void addinginventory::addtoDatabase()
{
    QString name = productname->text();
    int quantity = productquantity->value();
    int price = productprice->value();
    QSqlQuery query;

    // Adding values from the user to the database
    query.prepare("INSERT INTO InventoryInfo (ProductName, Quantity, Price) VALUES(?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(quantity);
    query.addBindValue(price);

    if(!query.exec())
    {
        QMessageBox::warning(this, "Error", "Failed to add this to the inventory");
    }
    else
    {
        QMessageBox::information(this, "Success", "added this to the inventory");
    }
}

void addinginventory::confirmclick(bool checked)
{
    // Selecting all the items in table
    QSqlQuery query("SELECT ProductName, Quantity, Price FROM InventoryInfo");
    if(!query.exec())
    {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    // Making A document
    QString filelocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Inventory_Report.txt";

    QFile file(filelocation);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "File Error", "Could not create the file");
        return;
    }

    QTextStream out(&file);
    out << "INVENTORY REPORT\n";
    out << QDateTime::currentDateTime().toString() << "\n\n";
    out << QString("%1\t%2\t%3\n").arg("Product Name", -20).arg("Quantity", -10).arg("Price");

    while (query.next())
    {
        out << QString("%1\t%2\t%3\n")
        .arg(query.value(0).toString(), -20)
        .arg(query.value(1).toString(), -10)
        .arg(query.value(2).toString());
    }

    file.close();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filelocation));

    QMessageBox::information(this, "Exported", "Inventory exported to text file.");

    // Ask to delete
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Records",
                                                              "Do you want to delete all inventory records now?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlQuery clear("DELETE FROM InventoryInfo");
        if (!clear.exec()) {
            QMessageBox::critical(this, "Error", "Failed to clear the inventory table.");
        } else {
            QMessageBox::information(this, "Deleted", "All inventory records deleted.");
        }
    }

}

addinginventory::~addinginventory()
{

}
