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
    QStackedWidget *stackedWidget;
    QTableWidget *studentTable;
    QLineEdit *searchEdit;
    QComboBox *searchOpt;
protected:
    // 이벤트 필터 함수 추가
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // ADMIN_WINDOW_H
