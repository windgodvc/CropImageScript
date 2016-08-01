#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>



namespace Ui {
class MainWindow;
}

class Form;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUI();

    void insertTable(std::string fileName,std::string path);

    void setLabelImage(std::string filepath);

    void generateImage(std::string filepath,std::string out,QSize size);

    void addToTree(QString s,QString s1);

    void SaveFile(std::string file);

    QAction* addToolAction(const char * action,const char *fileName,const char *describe);


private slots:

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void deleteCurrent();

    void deleteAll();

    void on_pushButton_3_clicked();

    void MaskImage();

    void StartApplication();

    void About();

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);



private:
    Ui::MainWindow *ui;

    std::string _mask;

    QImage _maskImage;

    Form *_preview;
};

#endif // MAINWINDOW_H
