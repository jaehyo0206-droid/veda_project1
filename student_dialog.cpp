#include "student_dialog.h"
#include <QMessageBox>
#include <QHBoxLayout>
studentdialog::studentdialog(const QStringList &existingIds, QWidget *parent)
    : QDialog(parent), m_existingIds(existingIds)
{
    setWindowTitle("학생 정보 추가");
    QFormLayout *form = new QFormLayout(this);

    nameEdit = new QLineEdit();
    phoneEdit = new QLineEdit();
    birthEdit = new QLineEdit();

    idEdit = new QLineEdit();
    QPushButton *btnCheck = new QPushButton("중복 확인");
    QHBoxLayout *idLayout = new QHBoxLayout();
    idLayout->addWidget(idEdit);
    idLayout->addWidget(btnCheck);

    pwEdit = new QLineEdit();
    pwEdit->setEchoMode(QLineEdit::Password);
    noteEdit = new QLineEdit();

    form->addRow("이름:", nameEdit);
    form->addRow("전화번호:", phoneEdit);
    form->addRow("생년월일:", birthEdit);
    form->addRow("ID:", idLayout);
    form->addRow("Password:", pwEdit);
    form->addRow("비고:", noteEdit);

    connect(btnCheck, &QPushButton::clicked, [this]()
            {
                if (m_existingIds.contains(idEdit->text()))
                {
                    QMessageBox::warning(this, "경고", "이미 사용 중인 ID입니다.");
                    m_isIdChecked = false;
                }
                else
                {
                    QMessageBox::information(this, "알림", "사용 가능한 ID입니다.");
                    m_isIdChecked = true;
                }
            });

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, [this](){
        if(!m_isIdChecked) QMessageBox::warning(this, "알림", "중복 확인을 먼저 수행하세요.");
        else accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    form->addWidget(buttons);
}

void studentdialog::setStudentData(const QString& name, const QString& phone, const QString& birth, const QString& id, const QString& pw, const QString& note)
{
    nameEdit->setText(name);
    phoneEdit->setText(phone);
    birthEdit->setText(birth);
    idEdit->setText(id);
    pwEdit->setText(pw);
    noteEdit->setText(note);

    idEdit->setEnabled(false); // ID는 수정 불가
    m_isIdChecked = true;      // 기존 ID이므로 중복 확인 통과로 간주
    setWindowTitle("학생 정보 수정");
}