/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_mail;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_password;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_logMail;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_logPassword;
    QPushButton *pushButton_recuperoPassword;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_accedi;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_nome;
    QLineEdit *lineEdit_cognome;
    QLineEdit *lineEdit_mail;
    QLineEdit *lineEdit_password;
    QLabel *label_data;
    QHBoxLayout *horizontalLayout_5;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_eta;
    QLabel *label_sesso;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *radioButton_uomo;
    QRadioButton *radioButton_donna;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_iscriviti;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(463, 329);
        MainWindow->setFixedSize(465, 330);

        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 441, 281));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_mail = new QLabel(verticalLayoutWidget_2);
        label_mail->setObjectName(QString::fromUtf8("label_mail"));

        horizontalLayout_2->addWidget(label_mail);

        horizontalSpacer_2 = new QSpacerItem(67, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_password = new QLabel(verticalLayoutWidget_2);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        horizontalLayout_2->addWidget(label_password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_logMail = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_logMail->setObjectName(QString::fromUtf8("lineEdit_logMail"));

        horizontalLayout->addWidget(lineEdit_logMail);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit_logPassword = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_logPassword->setObjectName(QString::fromUtf8("lineEdit_logPassword"));
        lineEdit_logPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEdit_logPassword);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_recuperoPassword = new QPushButton(verticalLayoutWidget_2);
        pushButton_recuperoPassword->setObjectName(QString::fromUtf8("pushButton_recuperoPassword"));
        pushButton_recuperoPassword->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_recuperoPassword);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_accedi = new QPushButton(verticalLayoutWidget_2);
        pushButton_accedi->setObjectName(QString::fromUtf8("pushButton_accedi"));
        pushButton_accedi->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(pushButton_accedi);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_nome = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_nome->setObjectName(QString::fromUtf8("lineEdit_nome"));

        horizontalLayout_4->addWidget(lineEdit_nome);

        lineEdit_cognome = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_cognome->setObjectName(QString::fromUtf8("lineEdit_cognome"));

        horizontalLayout_4->addWidget(lineEdit_cognome);


        verticalLayout_2->addLayout(horizontalLayout_4);

        lineEdit_mail = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_mail->setObjectName(QString::fromUtf8("lineEdit_mail"));

        verticalLayout_2->addWidget(lineEdit_mail);

        lineEdit_password = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Normal);

        verticalLayout_2->addWidget(lineEdit_password);

        label_data = new QLabel(verticalLayoutWidget_2);
        label_data->setObjectName(QString::fromUtf8("label_data"));

        verticalLayout_2->addWidget(label_data);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        dateEdit = new QDateEdit(verticalLayoutWidget_2);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(dateEdit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        label_eta = new QLabel(verticalLayoutWidget_2);
        label_eta->setObjectName(QString::fromUtf8("label_eta"));

        horizontalLayout_5->addWidget(label_eta);

        label_sesso = new QLabel(verticalLayoutWidget_2);
        label_sesso->setObjectName(QString::fromUtf8("label_sesso"));

        horizontalLayout_5->addWidget(label_sesso);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        radioButton_uomo = new QRadioButton(verticalLayoutWidget_2);
        radioButton_uomo->setObjectName(QString::fromUtf8("radioButton_uomo"));
        radioButton_uomo->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(radioButton_uomo);

        radioButton_donna = new QRadioButton(verticalLayoutWidget_2);
        radioButton_donna->setObjectName(QString::fromUtf8("radioButton_donna"));
        radioButton_donna->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(radioButton_donna);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        pushButton_iscriviti = new QPushButton(verticalLayoutWidget_2);
        pushButton_iscriviti->setObjectName(QString::fromUtf8("pushButton_iscriviti"));
        pushButton_iscriviti->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_iscriviti->setCheckable(false);

        horizontalLayout_6->addWidget(pushButton_iscriviti);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_6);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 463, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label_mail->setText(QCoreApplication::translate("MainWindow", "E-mail o telefono", nullptr));
        label_password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        lineEdit_logMail->setText(QString());
        lineEdit_logPassword->setText(QString());
        pushButton_recuperoPassword->setText(QCoreApplication::translate("MainWindow", "Non ricordi pi\303\271 come accedere all'account?", nullptr));
        pushButton_accedi->setText(QCoreApplication::translate("MainWindow", "Accedi", nullptr));
        lineEdit_nome->setText(QCoreApplication::translate("MainWindow", "Nome", nullptr));
        lineEdit_cognome->setText(QCoreApplication::translate("MainWindow", "Cognome", nullptr));
        lineEdit_mail->setText(QCoreApplication::translate("MainWindow", "Mail o numero di telefono", nullptr));
        lineEdit_password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_data->setText(QCoreApplication::translate("MainWindow", "Data di nascita", nullptr));
        label_eta->setText(QString());
        label_sesso->setText(QString());
        radioButton_uomo->setText(QCoreApplication::translate("MainWindow", "Uomo", nullptr));
        radioButton_donna->setText(QCoreApplication::translate("MainWindow", "Donna", nullptr));
        pushButton_iscriviti->setText(QCoreApplication::translate("MainWindow", "Iscriviti", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
