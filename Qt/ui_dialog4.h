/********************************************************************************
** Form generated from reading UI file 'dialog4.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG4_H
#define UI_DIALOG4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog4
{
public:
    QLabel *label;

    void setupUi(QDialog *Dialog4)
    {
        if (Dialog4->objectName().isEmpty())
            Dialog4->setObjectName(QString::fromUtf8("Dialog4"));
        Dialog4->resize(400, 120);
        Dialog4->setFixedSize(400, 120);
        label = new QLabel(Dialog4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 50, 191, 21));

        retranslateUi(Dialog4);

        QMetaObject::connectSlotsByName(Dialog4);
    } // setupUi

    void retranslateUi(QDialog *Dialog4)
    {
        Dialog4->setWindowTitle(QCoreApplication::translate("Dialog4", "Accesso negato", nullptr));
        label->setText(QCoreApplication::translate("Dialog4", "Email/telefono o password errati", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog4: public Ui_Dialog4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG4_H
