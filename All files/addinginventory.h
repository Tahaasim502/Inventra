#ifndef ADDINGINVENTORY_H
#define ADDINGINVENTORY_H

#include "mainwindow.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QBoxLayout>

class addinginventory : public QWidget
{
    Q_OBJECT
    public:
        explicit addinginventory(QWidget *parent = nullptr);
        ~addinginventory();
        void addinventory();
    private slots:
        void addtoDatabase();
        void confirmclick(bool checked);
    private:
        QLineEdit * productname;
        QSpinBox * productquantity;
        QSpinBox * productprice;
};

#endif // ADDINGINVENTORY_H
