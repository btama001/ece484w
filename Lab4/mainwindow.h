#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_brightSlider_sliderMoved(int position);

    void on_contSlider_sliderMoved(int position);

    void on_saveButton_clicked();

    void on_TransferButton_clicked();

    void on_TransferModButton_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
