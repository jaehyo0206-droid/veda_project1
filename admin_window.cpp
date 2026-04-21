/*
json 모듈화 해야함
 */
#include "admin_window.h"
#include <QHeaderView>
#include <QMouseEvent>
//json
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

Adminwindow::Adminwindow(QWidget *parent) : QWidget(parent)
{
    setupUI();
    loadData();
    setWindowTitle("관리자 모드");
    resize(1100, 700);
}
void Adminwindow::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    // 1. 사이드바
    QWidget *sidebar = new QWidget();
    sidebar->setStyleSheet("background-color: #2c3e50;");
    sidebar->setFixedWidth(200);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    QStringList menus = {"학생 정보 관리","일별 출결 현황","학생 출결 정보 관리","로그아웃"};
    stackedWidget = new QStackedWidget();

    for(int i=0; i<menus.size(); ++i)
    {
        QPushButton *btn = new QPushButton(menus[i]);
        btn->setStyleSheet("color: white; background: transparent; text-align: left; padding: 15px; border: none;");
        sidebarLayout->addWidget(btn);

        if(i == 0)
        {
            stackedWidget->addWidget(createStudentPage());
        }
        else if(i == 2)
        {
            stackedWidget->addWidget(createAttendanceStatusPage());
        }
        else
        {
            stackedWidget->addWidget(new QLabel(menus[i] + " 페이지", this));
        }

        connect(btn, &QPushButton::clicked, [this, i]()
                {
                    stackedWidget->setCurrentIndex(i);
                });
    }
    sidebarLayout->addStretch();

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
}
//학생 정보 관리 페이지
QWidget* Adminwindow::createStudentPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    QHBoxLayout *actionToolbar = new QHBoxLayout();

    searchOpt = new QComboBox();
    searchOpt->addItems({"이름", "전화번호", "ID"});
    searchEdit = new QLineEdit();
    QPushButton *btnSearch = new QPushButton("조회");

    actionToolbar->addWidget(searchOpt);
    actionToolbar->addWidget(searchEdit);
    actionToolbar->addWidget(btnSearch);
    actionToolbar->addStretch();

    QPushButton *btnAdd = new QPushButton("추가");
    QPushButton *btnEdit = new QPushButton("수정");
    QPushButton *btnDelete = new QPushButton("삭제");
    QPushButton *btnSave =new QPushButton("저장");

    actionToolbar->addWidget(btnAdd);
    actionToolbar->addWidget(btnEdit);
    actionToolbar->addWidget(btnDelete);
    actionToolbar->addWidget(btnSave);

    layout->addLayout(actionToolbar);

    // 테이블 설정
    studentTable = new QTableWidget(0, 6);
    studentTable->setHorizontalHeaderLabels({"이름", "전화번호", "생년월일", "ID", "Password", "비고"});

    // 이벤트 필터 설치
    studentTable->viewport()->installEventFilter(this);

    // [시각적 개선] 선택 행 하이라이트 및 스타일 설정
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentTable->setStyleSheet(
        "QTableWidget::item:selected {"
        "   background-color: #3498db;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QTableWidget { alternate-background-color: #f2f2f2; }"
        );
    studentTable->setAlternatingRowColors(true);

    studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(studentTable);

    // 슬롯 연결
    connect(btnSearch, &QPushButton::clicked, this, &Adminwindow::on_btnSearch_clicked);
    connect(btnAdd, &QPushButton::clicked, this, &Adminwindow::on_btnAdd_clicked);
    connect(btnEdit, &QPushButton::clicked, this, &Adminwindow::on_btnEdit_clicked);
    connect(btnSave, &QPushButton::clicked, this, &Adminwindow::on_btnSave_clicked);
    connect(btnDelete, &QPushButton::clicked, this, &Adminwindow::on_btnDelete_clicked);

    return page;
}
QWidget* Adminwindow::createAttendanceStatusPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 1. 조회 툴바 추가
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("학생명 또는 전화번호 검색...");
    QPushButton *btnSearch = new QPushButton("🔍 조회");

    searchLayout->addWidget(new QLabel("검색:"));
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(btnSearch);
    searchLayout->addStretch();
    layout->addLayout(searchLayout);

    // 2. 테이블 구성 (컬럼을 10개로 증가)
    // 순서: 학생명, 전화번호, 진도/전체, 출석, 지각, 조퇴, 외출, 결석, 출석률, 진행률
    attendanceTable = new QTableWidget(0, 10);
    attendanceTable->setHorizontalHeaderLabels({"학생명", "전화번호", "진도/전체", "출석", "지각", "조퇴", "외출", "결석", "출석률", "진행률"});
    attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // 편집 비활성화
    layout->addWidget(attendanceTable);

    // 4. 조회 기능 연결 (람다 함수 사용)
    connect(btnSearch, &QPushButton::clicked, [this, searchEdit]() {
        QString keyword = searchEdit->text().trimmed();
        for (int i = 0; i < attendanceTable->rowCount(); ++i) {
            bool match = attendanceTable->item(i, 0)->text().contains(keyword, Qt::CaseInsensitive) ||
                         attendanceTable->item(i, 1)->text().contains(keyword);
            attendanceTable->setRowHidden(i, !match); // 조건에 맞지 않으면 행 숨기기
        }
    });

    return page;
}
bool Adminwindow::eventFilter(QObject *obj, QEvent *event)
{
    // 테이블의 뷰포트에서 마우스 클릭 이벤트가 발생했는지 확인
    if (obj == studentTable->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // 클릭한 위치에 아이템이 있는지 확인
        if (!studentTable->indexAt(mouseEvent->pos()).isValid()) {
            // 아이템이 없는 빈 공간이면 선택 해제
            studentTable->clearSelection();
            studentTable->setCurrentCell(-1, -1);
        }
    }
    // 부모 클래스의 이벤트 처리 유지
    return QWidget::eventFilter(obj, event);
}
// --- 아래는 모든 슬롯 함수 구현입니다 (adminwindow 클래스 소속) ---
// 1. 조회 기능 (선택된 옵션과 검색어에 따라 테이블 필터링)
void Adminwindow::on_btnSearch_clicked()
{
    QString keyword = searchEdit->text().trimmed();
    int targetColumn = 0; // "이름" (기본값)

    if (searchOpt->currentText() == "전화번호") targetColumn = 1;
    else if (searchOpt->currentText() == "ID") targetColumn = 4;

    for (int i = 0; i < studentTable->rowCount(); ++i) {
        QTableWidgetItem *item = studentTable->item(i, targetColumn);
        bool match = (item && item->text().contains(keyword, Qt::CaseInsensitive));
        studentTable->setRowHidden(i, !match);
    }
}
// 2. 추가 기능 (행 추가)
void Adminwindow::on_btnAdd_clicked()
{
    QStringList existingIds = studentDatabase.keys();

    // 2. 수집된 목록을 다이얼로그로 전달
    Addstudentdialog dialog(existingIds, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        Student s;
        s.name = dialog.getName();
        s.phone = dialog.getPhone();
        s.birth = dialog.getBirth();
        s.id = dialog.getID();
        s.pw = dialog.getPW();
        s.note = dialog.getNote();

        studentDatabase[s.id] = s;

        refreshStudentTable();
        refreshAttendanceTable();
    }
}
//데이터 수정
void Adminwindow::on_btnEdit_clicked()
{
    int row = studentTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "수정할 학생을 먼저 선택하세요.");
        return;
    }

    QString id = studentTable->item(row, 3) ? studentTable->item(row, 3)->text() : "";
    if (!studentDatabase.contains(id)) return;

    Student s = studentDatabase[id];

    Addstudentdialog dialog(QStringList(), this);
    dialog.setStudentData(s.name, s.phone, s.birth, s.id, s.pw, s.note);

    if (dialog.exec() == QDialog::Accepted)
    {
        studentDatabase[id].name = dialog.getName();
        studentDatabase[id].phone = dialog.getPhone();
        studentDatabase[id].birth = dialog.getBirth();
        // ID는 변경 안함
        studentDatabase[id].pw = dialog.getPW();
        studentDatabase[id].note = dialog.getNote();

        refreshStudentTable();
        refreshAttendanceTable();
    }
}
//데이터 저장
void Adminwindow::on_btnSave_clicked()
{
    saveData();
    QMessageBox::information(this, "알림", "모든 데이터가 저장되었습니다.");
}
// 4. 삭제 기능 (선택된 행 삭제)
void Adminwindow::on_btnDelete_clicked() {
    int row = studentTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "삭제할 학생을 선택하세요.");
        return;
    }
    if (QMessageBox::question(this, "삭제 확인", "정말 삭제하시겠습니까?") == QMessageBox::Yes)
    {
        QString id = studentTable->item(row, 3) ? studentTable->item(row, 3)->text() : "";
        studentDatabase.remove(id);

        refreshStudentTable();
        refreshAttendanceTable();
    }
}
void Adminwindow::saveData()
{
    qDebug() << "save Data in json...";
    QJsonArray studentArray;

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        QJsonObject obj;
        obj["id"] = s.id;
        obj["pw"] = s.pw;
        obj["name"] = s.name;
        obj["phone"] = s.phone;
        obj["birth"] = s.birth;
        obj["note"] = s.note;

        QJsonObject attObj;
        attObj["totalDays"] = s.attendance.totalDays;
        attObj["completedDays"] = s.attendance.completedDays;
        attObj["present"] = s.attendance.present;
        attObj["late"] = s.attendance.late;
        attObj["early"] = s.attendance.early;
        attObj["out"] = s.attendance.out;
        attObj["abs"] = s.attendance.abs;

        obj["attendance_summary"] = attObj;
        studentArray.append(obj);
    }

    QJsonObject root;
    root["students"] = studentArray;

    QJsonDocument doc(root);
    QFile file("students.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}

/*
 * 설명: 저장된 JSON 파일에서 데이터를 읽어와 메모리(studentDatabase)에 적재하고 테이블 갱신
 */
void Adminwindow::loadData()
{
    qDebug() << "load..json";
    studentDatabase.clear();

    QFile file("students.json");
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        qDebug() << "There is no json named students.json";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray array;

    // 하위 호환성 (기존 students.json 배열 형태 지원)
    if (doc.isArray()) {
        array = doc.array();
    } else {
        array = root["students"].toArray();
    }

    for (const QJsonValue &value : std::as_const(array))
    {
        QJsonObject obj = value.toObject();
        Student s;
        s.id = obj["id"].toString();
        s.pw = obj["pw"].toString();
        s.name = obj["name"].toString();
        s.phone = obj["phone"].toString();
        s.birth = obj["birth"].toString();
        s.note = obj["note"].toString();

        if (obj.contains("attendance_summary")) {
            QJsonObject attObj = obj["attendance_summary"].toObject();
            s.attendance.totalDays = attObj["totalDays"].toInt(100);
            s.attendance.completedDays = attObj["completedDays"].toInt(0);
            s.attendance.present = attObj["present"].toInt(0);
            s.attendance.late = attObj["late"].toInt(0);
            s.attendance.early = attObj["early"].toInt(0);
            s.attendance.out = attObj["out"].toInt(0);
            s.attendance.abs = attObj["abs"].toInt(0);
        }

        studentDatabase[s.id] = s;
    }

    refreshStudentTable();
    refreshAttendanceTable();
}

void Adminwindow::refreshStudentTable()
{
    if (!studentTable) return;
    studentTable->setRowCount(0);

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        int row = studentTable->rowCount();
        studentTable->insertRow(row);

        studentTable->setItem(row, 0, new QTableWidgetItem(s.name));
        studentTable->setItem(row, 1, new QTableWidgetItem(s.phone));
        studentTable->setItem(row, 2, new QTableWidgetItem(s.birth));
        studentTable->setItem(row, 3, new QTableWidgetItem(s.id));
        studentTable->setItem(row, 4, new QTableWidgetItem(s.pw));
        studentTable->setItem(row, 5, new QTableWidgetItem(s.note));

        for(int i = 0; i < 6; ++i) {
            if(studentTable->item(row, i))
                studentTable->item(row, i)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void Adminwindow::refreshAttendanceTable()
{
    if (!attendanceTable) return;
    attendanceTable->setRowCount(0);

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        int row = attendanceTable->rowCount();
        attendanceTable->insertRow(row);

        double attendanceRate = 0;
        if (s.attendance.completedDays > 0)
            attendanceRate = (static_cast<double>(s.attendance.present) / s.attendance.completedDays) * 100.0;
        
        double progressRate = 0;
        if (s.attendance.totalDays > 0)
            progressRate = (static_cast<double>(s.attendance.completedDays) / s.attendance.totalDays) * 100.0;

        attendanceTable->setItem(row, 0, new QTableWidgetItem(s.name));
        attendanceTable->setItem(row, 1, new QTableWidgetItem(s.phone));
        attendanceTable->setItem(row, 2, new QTableWidgetItem(QString("%1 / %2").arg(s.attendance.completedDays).arg(s.attendance.totalDays)));
        attendanceTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.attendance.present)));
        attendanceTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.attendance.late)));
        attendanceTable->setItem(row, 5, new QTableWidgetItem(QString::number(s.attendance.early)));
        attendanceTable->setItem(row, 6, new QTableWidgetItem(QString::number(s.attendance.out)));
        attendanceTable->setItem(row, 7, new QTableWidgetItem(QString::number(s.attendance.abs)));
        attendanceTable->setItem(row, 8, new QTableWidgetItem(QString::number(attendanceRate, 'f', 1) + "%"));
        attendanceTable->setItem(row, 9, new QTableWidgetItem(QString::number(progressRate, 'f', 1) + "%"));

        for(int col = 0; col < 10; ++col) {
            if(attendanceTable->item(row, col))
                attendanceTable->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }
    }
}