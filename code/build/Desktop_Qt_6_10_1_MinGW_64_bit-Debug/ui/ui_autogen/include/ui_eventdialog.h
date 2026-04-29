/********************************************************************************
** Form generated from reading UI file 'eventdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDIALOG_H
#define UI_EVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EventDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelTitle;
    QLineEdit *titleEdit;
    QLabel *labelStart;
    QDateTimeEdit *startDateTime;
    QCheckBox *hasEndCheck;
    QDateTimeEdit *endDateTime;
    QLabel *labelCategory;
    QComboBox *categoryCombo;
    QLabel *labelLocation;
    QLineEdit *locationEdit;
    QLabel *labelNotes;
    QPlainTextEdit *notesEdit;
    QComboBox *reminderCombo;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EventDialog)
    {
        if (EventDialog->objectName().isEmpty())
            EventDialog->setObjectName("EventDialog");
        EventDialog->resize(376, 394);
        verticalLayout = new QVBoxLayout(EventDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelTitle = new QLabel(EventDialog);
        labelTitle->setObjectName("labelTitle");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelTitle);

        titleEdit = new QLineEdit(EventDialog);
        titleEdit->setObjectName("titleEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, titleEdit);

        labelStart = new QLabel(EventDialog);
        labelStart->setObjectName("labelStart");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelStart);

        startDateTime = new QDateTimeEdit(EventDialog);
        startDateTime->setObjectName("startDateTime");
        startDateTime->setCalendarPopup(true);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, startDateTime);

        hasEndCheck = new QCheckBox(EventDialog);
        hasEndCheck->setObjectName("hasEndCheck");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, hasEndCheck);

        endDateTime = new QDateTimeEdit(EventDialog);
        endDateTime->setObjectName("endDateTime");
        endDateTime->setEnabled(false);
        endDateTime->setCalendarPopup(true);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, endDateTime);

        labelCategory = new QLabel(EventDialog);
        labelCategory->setObjectName("labelCategory");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelCategory);

        categoryCombo = new QComboBox(EventDialog);
        categoryCombo->setObjectName("categoryCombo");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, categoryCombo);

        labelLocation = new QLabel(EventDialog);
        labelLocation->setObjectName("labelLocation");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelLocation);

        locationEdit = new QLineEdit(EventDialog);
        locationEdit->setObjectName("locationEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, locationEdit);

        labelNotes = new QLabel(EventDialog);
        labelNotes->setObjectName("labelNotes");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, labelNotes);

        notesEdit = new QPlainTextEdit(EventDialog);
        notesEdit->setObjectName("notesEdit");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, notesEdit);

        reminderCombo = new QComboBox(EventDialog);
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->addItem(QString());
        reminderCombo->setObjectName("reminderCombo");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, reminderCombo);

        label = new QLabel(EventDialog);
        label->setObjectName("label");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(EventDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EventDialog);

        QMetaObject::connectSlotsByName(EventDialog);
    } // setupUi

    void retranslateUi(QDialog *EventDialog)
    {
        EventDialog->setWindowTitle(QCoreApplication::translate("EventDialog", "Event", nullptr));
        labelTitle->setText(QCoreApplication::translate("EventDialog", "Title*", nullptr));
        labelStart->setText(QCoreApplication::translate("EventDialog", "Start", nullptr));
        startDateTime->setDisplayFormat(QCoreApplication::translate("EventDialog", "yyyy-MM-dd HH:mm ", nullptr));
        hasEndCheck->setText(QCoreApplication::translate("EventDialog", "Has end time", nullptr));
        endDateTime->setDisplayFormat(QCoreApplication::translate("EventDialog", "yyyy-MM-dd hh:mm", nullptr));
        labelCategory->setText(QCoreApplication::translate("EventDialog", "Category", nullptr));
        labelLocation->setText(QCoreApplication::translate("EventDialog", "Location", nullptr));
        labelNotes->setText(QCoreApplication::translate("EventDialog", "Notes", nullptr));
        reminderCombo->setItemText(0, QCoreApplication::translate("EventDialog", "None", nullptr));
        reminderCombo->setItemText(1, QCoreApplication::translate("EventDialog", "1 minute before", nullptr));
        reminderCombo->setItemText(2, QCoreApplication::translate("EventDialog", "5 minutes before", nullptr));
        reminderCombo->setItemText(3, QCoreApplication::translate("EventDialog", "15 minutes before", nullptr));
        reminderCombo->setItemText(4, QCoreApplication::translate("EventDialog", "30 minutes before", nullptr));
        reminderCombo->setItemText(5, QCoreApplication::translate("EventDialog", "1 hour before", nullptr));
        reminderCombo->setItemText(6, QCoreApplication::translate("EventDialog", "2 hours before", nullptr));
        reminderCombo->setItemText(7, QCoreApplication::translate("EventDialog", "1 day before", nullptr));
        reminderCombo->setItemText(8, QCoreApplication::translate("EventDialog", "2 days before ", nullptr));

        label->setText(QCoreApplication::translate("EventDialog", "Set Reminder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDialog: public Ui_EventDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDIALOG_H
