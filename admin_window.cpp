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
/*
QWidget* Adminwindow::createAttendancePage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 1. Action Toolbar 구성
    QHBoxLayout *actionToolbar = new QHBoxLayout();

    // 날짜 선택기 추가 (사용성을 위해)
    actionToolbar->addWidget(new QLabel("날짜:"));
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    actionToolbar->addWidget(dateEdit);

    QPushButton *btnSearch = new QPushButton("조회");
    actionToolbar->addWidget(btnSearch);

    actionToolbar->addStretch();

    QPushButton *btnSave = new QPushButton("💾 일괄 저장");
    QPushButton *btnExport = new QPushButton("📤 내보내기");

    actionToolbar->addWidget(btnSave);
    actionToolbar->addWidget(btnExport);

    layout->addLayout(actionToolbar);

    // 2. 테이블 구성 (컬럼 9개로 증가)
    // 순서: 학생명, 전화번호, 입실 시간, 퇴실 시간, 출석, 결석, 지각, 조퇴, 외출
    QTableWidget *table = new QTableWidget(0, 9);
    table->setHorizontalHeaderLabels({"학생명", "전화번호", "입실 시간", "퇴실 시간", "출석", "결석", "지각", "조퇴", "외출"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    // 컬럼 비율 자동 조절
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);


    // [중요] 이 줄이 있어야 데이터가 들어갑니다!
    loadAttendanceData(table);

    return page;
}*/
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
    QTableWidget *table = new QTableWidget(0, 10);
    table->setHorizontalHeaderLabels({"학생명", "전화번호", "진도/전체", "출석", "지각", "조퇴", "외출", "결석", "출석률", "진행률"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    // 데이터 구조 정의
    struct StudentData {
        QString name, phone;
        int totalDays, completedDays, present, late, early, out, abs;
    };

    QList<StudentData> studentList = {
        {"김철수", "010-1234-5678", 100, 50, 45, 2, 0, 0, 3},
        {"이영희", "010-9876-5432", 100, 50, 40, 0, 4, 0, 6},
        {"박민수", "010-5555-4444", 100, 50, 30, 4, 4, 4, 8}
    };

    table->setRowCount(studentList.size());

    // 3. 데이터 입력
    for (int i = 0; i < studentList.size(); ++i) {
        StudentData s = studentList[i];

        double attendanceRate = (static_cast<double>(s.present) / s.completedDays) * 100.0;
        double progressRate = (static_cast<double>(s.completedDays) / s.totalDays) * 100.0;

        table->setItem(i, 0, new QTableWidgetItem(s.name));
        table->setItem(i, 1, new QTableWidgetItem(s.phone)); // 전화번호 추가
        table->setItem(i, 2, new QTableWidgetItem(QString("%1 / %2").arg(s.completedDays).arg(s.totalDays)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(s.present)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(s.late)));
        table->setItem(i, 5, new QTableWidgetItem(QString::number(s.early)));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(s.out)));
        table->setItem(i, 7, new QTableWidgetItem(QString::number(s.abs)));
        table->setItem(i, 8, new QTableWidgetItem(QString::number(attendanceRate, 'f', 1) + "%"));
        table->setItem(i, 9, new QTableWidgetItem(QString::number(progressRate, 'f', 1) + "%"));

        for(int col = 0; col < 10; ++col) table->item(i, col)->setTextAlignment(Qt::AlignCenter);
    }

    // 4. 조회 기능 연결 (람다 함수 사용)
    connect(btnSearch, &QPushButton::clicked, [table, searchEdit]() {
        QString keyword = searchEdit->text().trimmed();
        for (int i = 0; i < table->rowCount(); ++i) {
            bool match = table->item(i, 0)->text().contains(keyword, Qt::CaseInsensitive) ||
                         table->item(i, 1)->text().contains(keyword);
            table->setRowHidden(i, !match); // 조건에 맞지 않으면 행 숨기기
        }
    });

    return page;
}
/*
void Adminwindow::loadAttendanceData(QTableWidget *table) {
    table->setRowCount(3); // 3명의 데이터

    // 데이터 정의: {이름, 전화번호, 입실, 퇴실, 출석, 결석, 지각, 조퇴, 외출}
    // "O" 표시를 사용하여 출석 상태를 직관적으로 표현했습니다.
    QStringList student1 = {"김철수", "010-1234-5678", "09:00", "18:00", "O", "", "", "", ""};
    QStringList student2 = {"이영희", "010-9876-5432", "09:15", "18:00", "", "", "O", "", ""};
    QStringList student3 = {"박민수", "010-5555-4444", "08:50", "15:00", "", "", "", "O", ""};

    QList<QStringList> data = {student1, student2, student3};

    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < 9; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(data[i][j]);

            // 텍스트 가운데 정렬
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(i, j, item);
        }
    }
}*/
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
    // 1. 현재 테이블에서 기존 ID 목록 수집
    QStringList existingIds;
    for (int i = 0; i < studentTable->rowCount(); ++i)
    {
        if (studentTable->item(i, 3)) // ID는 3번 열
        {
            existingIds.append(studentTable->item(i, 3)->text());
        }
    }

    // 2. 수집된 목록을 다이얼로그로 전달
    Addstudentdialog dialog(existingIds, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        int newRow = studentTable->rowCount();
        studentTable->insertRow(newRow);

        studentTable->setItem(newRow, 0, new QTableWidgetItem(dialog.getName()));
        studentTable->setItem(newRow, 1, new QTableWidgetItem(dialog.getPhone()));
        //studentTable->setItem(newRow, 2, new QTableWidgetItem(dialog.getAge()));
        studentTable->setItem(newRow, 2, new QTableWidgetItem(dialog.getBirth()));
        studentTable->setItem(newRow, 3, new QTableWidgetItem(dialog.getID()));
        studentTable->setItem(newRow, 4, new QTableWidgetItem(dialog.getPW()));
        studentTable->setItem(newRow, 5, new QTableWidgetItem(dialog.getNote()));

        for(int i = 0; i < 6; ++i)
        {
            if(studentTable->item(newRow, i))
                studentTable->item(newRow, i)->setTextAlignment(Qt::AlignCenter);
        }
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

    // 기존 데이터 읽어오기
    QString name = studentTable->item(row, 0) ? studentTable->item(row, 0)->text() : "";
    QString phone = studentTable->item(row, 1) ? studentTable->item(row, 1)->text() : "";
    QString birth = studentTable->item(row, 2) ? studentTable->item(row, 2)->text() : "";
    QString id = studentTable->item(row, 3) ? studentTable->item(row, 3)->text() : "";
    QString pw = studentTable->item(row, 4) ? studentTable->item(row, 4)->text() : "";
    QString note = studentTable->item(row, 5) ? studentTable->item(row, 5)->text() : "";

    Addstudentdialog dialog(QStringList(), this);
    dialog.setStudentData(name, phone, birth, id, pw, note);

    if (dialog.exec() == QDialog::Accepted)
    {
        if (studentTable->item(row, 0)) studentTable->item(row, 0)->setText(dialog.getName());
        if (studentTable->item(row, 1)) studentTable->item(row, 1)->setText(dialog.getPhone());
        if (studentTable->item(row, 2)) studentTable->item(row, 2)->setText(dialog.getBirth());
        // ID는 변경 안함 (수정 불가 처리)
        if (studentTable->item(row, 4)) studentTable->item(row, 4)->setText(dialog.getPW());
        if (studentTable->item(row, 5)) studentTable->item(row, 5)->setText(dialog.getNote());
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
        studentTable->removeRow(row);
    }
}
void Adminwindow::saveData()
{
    qDebug()<<"save Data in json...";
    QJsonArray studentArray;

    // 테이블의 모든 행을 순회하며 JSON 객체 생성
    for (int i = 0; i < studentTable->rowCount(); ++i)
    {
        QJsonObject obj;
        obj["name"] = studentTable->item(i, 0)->text();
        obj["phone"] = studentTable->item(i, 1)->text();
        //obj["age"] = studentTable->item(i, 2)->text();
        obj["birth"] = studentTable->item(i, 2)->text();
        obj["id"] = studentTable->item(i, 3)->text();
        obj["pw"] = studentTable->item(i, 4)->text();
        obj["note"] = studentTable->item(i,5)->text();

        studentArray.append(obj);
    }

    // 파일로 저장
    QJsonDocument doc(studentArray);
    QFile file("students.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}
/*
 * 설명: 저장된 JSON 파일에서 데이터를 읽어와 테이블에 로드
 */
void Adminwindow::loadData()
{
    qDebug()<<"load..json";
    QFile file("students.json");
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
    {   qDebug()<<"There is no json named students.json";
        return; // 파일이 없으면 그냥 종료
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    // 테이블에 데이터 추가
    for (const QJsonValue &value : array)
    {
        QJsonObject obj = value.toObject();
        int row = studentTable->rowCount();
        studentTable->insertRow(row);

        studentTable->setItem(row, 0, new QTableWidgetItem(obj["name"].toString()));
        studentTable->setItem(row, 1, new QTableWidgetItem(obj["phone"].toString()));
        //studentTable->setItem(row, 2, new QTableWidgetItem(obj["age"].toString()));
        studentTable->setItem(row, 2, new QTableWidgetItem(obj["birth"].toString()));
        studentTable->setItem(row, 3, new QTableWidgetItem(obj["id"].toString()));
        studentTable->setItem(row, 4, new QTableWidgetItem(obj["pw"].toString()));
        studentTable->setItem(row, 5, new QTableWidgetItem(obj["note"].toString()));
    }
}