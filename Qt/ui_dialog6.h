/********************************************************************************
** Form generated from reading UI file 'dialog6.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG6_H
#define UI_DIALOG6_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog6
{
public:
    QLabel *label;

    void setupUi(QDialog *Dialog6)
    {
        if (Dialog6->objectName().isEmpty())
            Dialog6->setObjectName(QString::fromUtf8("Dialog6"));
        Dialog6->resize(400, 120);
        Dialog6->setFixedSize(400, 120);
        label = new QLabel(Dialog6);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 50, 211, 16));

        retranslateUi(Dialog6);

        QMetaObject::connectSlotsByName(Dialog6);
    } // setupUi

    void retranslateUi(QDialog *Dialog6)
    {
        Dialog6->setWindowTitle(QCoreApplication::translate("Dialog6", "Impossibile recupero password", nullptr));
        label->setText(QCoreApplication::translate("Dialog6", "Mail o telefono non presenti nel database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog6: public Ui_Dialog6 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG6_H
