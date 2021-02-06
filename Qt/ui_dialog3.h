/********************************************************************************
** Form generated from reading UI file 'dialog3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG3_H
#define UI_DIALOG3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog3
{
public:
    QLabel *label;

    void setupUi(QDialog *Dialog3)
    {
        if (Dialog3->objectName().isEmpty())
            Dialog3->setObjectName(QString::fromUtf8("Dialog3"));
        Dialog3->resize(400, 120);
        Dialog3->setFixedSize(400, 120);
        label = new QLabel(Dialog3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 40, 91, 20));

        retranslateUi(Dialog3);

        QMetaObject::connectSlotsByName(Dialog3);
    } // setupUi

    void retranslateUi(QDialog *Dialog3)
    {
        Dialog3->setWindowTitle(QCoreApplication::translate("Dialog3", "Login effettuato", nullptr));
        label->setText(QCoreApplication::translate("Dialog3", "Login effettuato!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog3: public Ui_Dialog3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG3_H
