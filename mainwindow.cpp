#include "mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    text1=new QTextEdit;

    QFont f;
    f.setPixelSize(30);
    text1->setFont(f);//设置text1字体大小为30
    //QColor c;
    //c.setRgb(255,0,0);
    //text1->setTextColor(c);//设置颜色为红色

    this->setCentralWidget(text1);//将TextEdit放到对话框的中间

    file=this->menuBar()->addMenu("文件");//在菜单栏加入一个菜单项
    edit=this->menuBar()->addMenu("编辑");
    build=this->menuBar()->addMenu("构建");
    help=this->menuBar()->addMenu("帮助 ");

    file_open=new QAction("打开",this);//建立一个下拉
    file_open->setShortcut(tr("ctrl+o"));//将open的菜单的快捷方式设置为ctrl+o
    file->addAction(file_open);//将file_open加入到file菜单下面
    file->addSeparator();//加入一个分割符

    file_save=new QAction("保存",this);
    file_save->setShortcut(tr("ctrl+s"));
    file->addAction(file_save);
    file->addSeparator();

    file_exit=new QAction("退出",this);
    file->addAction(file_exit);//将file_open加入到file菜单下面

    build_compile=new QAction("编译",this);
    build->addAction(build_compile);
    build->addSeparator();

    build_run=new QAction("运行",this);
    build->addAction(build_run);

    help_about=new QAction("关于",this);
    help_about->setShortcut(tr("ctrl+h"));
    help->addAction(help_about);

    edit_selectAll=new QAction("全选",this);
    edit_selectAll->setShortcut(tr("ctrl+a"));
    edit->addAction(edit_selectAll);
    edit->addSeparator();


    edit_copy=new QAction("拷贝",this);
    edit_copy->setShortcut(tr("ctrl+c"));
    edit->addAction(edit_copy);
    edit->addSeparator();

    edit_paste=new QAction("粘贴",this);
    edit_paste->setShortcut(tr("ctrl+v"));
    edit->addAction(edit_paste);
    edit->addSeparator();

    edit_cut=new QAction("剪切",this);
    edit_cut->setShortcut(tr("ctrl+x"));
    edit->addAction(edit_cut);

    //QT的消息槽机制
    connect(file_open,SIGNAL(triggered()),this,SLOT(on_open()));
    //第一个参数是触该事件的控件
    //第二个参数是对于Action来讲，固定写法SIGNAL(triggered())
    //第三个参数固定写法this
    //第四个参数指定点击Action后会执行哪个动作

    connect(help_about,SIGNAL(triggered()),this,SLOT(on_about()));

    connect(file_exit,SIGNAL(triggered()),this,SLOT(on_exit()));

    connect(edit_copy,SIGNAL(triggered()),this,SLOT(on_copy()));

    connect(edit_paste,SIGNAL(triggered()),this,SLOT(on_paste()));

    connect(edit_selectAll,SIGNAL(triggered()),this,SLOT(on_selectAll()));

    connect(file_save,SIGNAL(triggered()),this,SLOT(on_save()));

    connect(build_compile,SIGNAL(triggered()),this,SLOT(on_compile()));

    connect(build_run,SIGNAL(triggered()),this,SLOT(on_run()));

}

MainWindow::~MainWindow()
{
    delete text1;
}

void MainWindow::on_open()
{
    filename=QFileDialog::getOpenFileName();//打开一个标准文件对话框，返回用户选择的文件名
    if(filename.isEmpty()){//如果用户没选择任何文件
        return;
    }

    QString content;//是QT定义的一个字符串类
    //filename.toStdString().data();//将QString转化为const char *
    FILE *pfr=fopen(filename.toStdString().data(),"r");
    if(pfr==NULL){
       QMessageBox::information(this,"系统提示","文件打开失败");
    }else{
      while(!feof(pfr)){
          char buf[1024]={0};
          fgets(buf,sizeof(buf),pfr);
          content+=buf;
      }
    }
    fclose(pfr);
    text1->setText(content);//将QString里的字符串放到text1里面
}

void MainWindow::on_about()
{
    QMessageBox::information(this,"关于","许永军：版权所有2015~2016");
}

void MainWindow::on_exit()
{
    exit(0);
}

void MainWindow::on_copy()
{
   text1->copy();
}

void MainWindow::on_paste()
{
   text1->paste();
}

void MainWindow::on_cut()
{
    text1->cut();
}

void MainWindow::on_selectAll()
{
    text1->selectAll();
}

void MainWindow::on_compile()
{
    QString destname=filename;
    destname.replace(".c",".exe");//将filename中的.c替换为.exe
    QString command="gcc -o " + destname + " " + filename;
    system(command.toStdString().data());
}

void MainWindow::on_run()
{
    QString destname=filename;
    destname.replace(".c",".exe");//将filename中的.c替换为.exe
    system(destname.toStdString().data());
}

void  MainWindow::on_save()
{
    filename=QFileDialog::getSaveFileName();
    if(filename.isEmpty()){
        return;
    }
    FILE *pfw=fopen(filename.toStdString().data(),"w");
    if(pfw==NULL){
        QMessageBox::information(this,"错误","文件保存失败");
    }else{
         //text1->toPlainText().toStdString().data();//将用户在text1控件中输入的字符串转化为const char *
         fputs(text1->toPlainText().toStdString().data(),pfw);
    }
    fclose(pfw);
}
