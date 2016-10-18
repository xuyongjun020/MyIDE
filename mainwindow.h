#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextEdit>
#include<QMenu>
#include<QMenuBar>
#include<QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString filename;
    QTextEdit *text1;
    QMenu *file;
    QMenu *edit;
    QMenu *build;
    QMenu *help;

    QAction *build_compile;
    QAction *build_run;

    QAction * file_open;//下拉
    QAction * file_save;
    QAction * file_exit;
    QAction * help_about;
    QAction * edit_selectAll;
    QAction * edit_copy;
    QAction * edit_paste;
    QAction *edit_cut;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open();//alt+enter会自动添加到cpp中

    void on_about();

    void on_save();

    void on_exit();

    void on_copy();

    void on_paste();

    void on_cut();

    void on_selectAll();

    void on_compile();

    void on_run();
};


#endif // MAINWINDOW_H
