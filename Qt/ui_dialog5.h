/********************************************************************************
** Form generated from reading UI file 'dialog5.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG5_H
#define UI_DIALOG5_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog5
{
public:
    QLabel *label;

    void setupUi(QDialog *Dialog5)
    {
        if (Dialog5->objectName().isEmpty())
            Dialog5->setObjectName(QString::fromUtf8("Dialog5"));
        Dialog5->resize(400, 120);
        Dialog5->setFixedSize(400, 120);
        label = new QLabel(Dialog5);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 50, 171, 16));

        retranslateUi(Dialog5);

        QMetaObject::connectSlotsByName(Dialog5);
    } // setupUi

    void retranslateUi(QDialog *Dialog5)
    {
        Dialog5->setWindowTitle(QCoreApplication::translate("Dialog5", "Recupero password", nullptr));
        label->setText(QCoreApplication::translate("Dialog5", "Password spedita con successo!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog5: public Ui_Dialog5 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG5_H
