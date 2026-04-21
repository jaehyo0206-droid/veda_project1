#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H
//#include "ui_adminwindow.h"
#include "add_student_dialog.h"
#include <QWidget>
#include <QStackedWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>

struct AttendanceSummary {
    int totalDays = 100;
    int completedDays = 0;
    int present = 0;
    int late = 0;
    int early = 0;
    int out = 0;
    int abs = 0;
};

struct Student {
    QString id;
    QString pw;
    QString name;
    QString phone;
    QString birth;
    QString note;
    
    AttendanceSummary attendance;
};

class Adminwindow : public QWidget // MainWindow를 Widget으로 변경
{
    Q_OBJECT

public:
    Adminwindow(QWidget *parent = nullptr); // 생성자 수정

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnSave_clicked(); // 추가된 저장 버튼 슬롯
    void on_btnDelete_clicked();
    void on_btnSearch_clicked();

private:
    void setupUI();
    QWidget* createStudentPage();
    QWidget* createAttendancePage();
    QWidget* createStatsPage();
    QWidget* createAttendanceStatusPage(); // 추가
    void loadDummyData();
    void loadAttendanceData(QTableWidget *table); // 추가
    void saveData();
    void loadData();

    void refreshStudentTable();
    void refreshAttendanceTable();

    QMap<QString, Student> studentDatabase;

    QStackedWidget *stackedWidget;
    QTableWidget *studentTable;
    QTableWidget *attendanceTable; // 추가: 출결 테이블 멤버 변수
    QLineEdit *searchEdit;
    QComboBox *searchOpt;
protected:
    // 이벤트 필터 함수 추가
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // ADMIN_WINDOW_H
