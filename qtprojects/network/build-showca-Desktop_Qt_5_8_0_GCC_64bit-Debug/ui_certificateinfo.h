/********************************************************************************
** Form generated from reading UI file 'certificateinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CERTIFICATEINFO_H
#define UI_CERTIFICATEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CertificateInfo
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QComboBox *certificationPathView;
    QLabel *label_2;
    QListWidget *certificateInfoView;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CertificateInfo)
    {
        if (CertificateInfo->objectName().isEmpty())
            CertificateInfo->setObjectName(QStringLiteral("CertificateInfo"));
        CertificateInfo->resize(400, 397);
        vboxLayout = new QVBoxLayout(CertificateInfo);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(CertificateInfo);
        label->setObjectName(QStringLiteral("label"));

        vboxLayout->addWidget(label);

        certificationPathView = new QComboBox(CertificateInfo);
        certificationPathView->setObjectName(QStringLiteral("certificationPathView"));
        certificationPathView->setMinimumContentsLength(3);

        vboxLayout->addWidget(certificationPathView);

        label_2 = new QLabel(CertificateInfo);
        label_2->setObjectName(QStringLiteral("label_2"));

        vboxLayout->addWidget(label_2);

        certificateInfoView = new QListWidget(CertificateInfo);
        certificateInfoView->setObjectName(QStringLiteral("certificateInfoView"));
        QFont font;
        font.setPointSize(8);
        certificateInfoView->setFont(font);
        certificateInfoView->setWordWrap(true);

        vboxLayout->addWidget(certificateInfoView);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(CertificateInfo);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        hboxLayout->addWidget(buttonBox);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(CertificateInfo);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), CertificateInfo, SLOT(accept()));

        QMetaObject::connectSlotsByName(CertificateInfo);
    } // setupUi

    void retranslateUi(QDialog *CertificateInfo)
    {
        CertificateInfo->setWindowTitle(QApplication::translate("CertificateInfo", "Display Certificate Information", Q_NULLPTR));
        label->setText(QApplication::translate("CertificateInfo", "Certification Path", Q_NULLPTR));
        label_2->setText(QApplication::translate("CertificateInfo", "Certificate Information", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CertificateInfo: public Ui_CertificateInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CERTIFICATEINFO_H
