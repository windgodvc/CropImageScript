#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBitmap>
#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>

#include <iostream>
#include "form.h"
//#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    initUI();

}

MainWindow::~MainWindow()
{
    _preview->deleteLater();
    delete ui;
}

void MainWindow::initUI()
{
    //QPalette palette;
    //palette.setColor(QPalette::Window,QColor(120,71,37));

    //this->setPalette(palette);


    connect(addToolAction("&Mask","load.png","open Mask file."),SIGNAL(triggered()),this,SLOT(MaskImage()));
    connect(addToolAction("&Star","publish.png","Star"),SIGNAL(triggered()),this,SLOT(StartApplication()));
    connect(addToolAction("&About","about.png","About"),SIGNAL(triggered()),this,SLOT(About()));

    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setWindowTitle("Batch Image Processing");
    QApplication::setStyle("fusion");

    ui->tableWidget->setColumnWidth(0,45);
    ui->tableWidget->setColumnWidth(1,this->width());
    ui->tableWidget->setAlternatingRowColors(true);

    addToTree("32","32");
    addToTree("48","48");
    addToTree("72","72");
    addToTree("96","96");
    addToTree("144","144");
    addToTree("192","192");


    connect(ui->DeleteCurren,SIGNAL(triggered()),this,SLOT(deleteCurrent()));
    connect(ui->DeleteAll,SIGNAL(triggered()),this,SLOT(deleteAll()));

    _preview = NULL;
}


QAction* MainWindow::addToolAction(const char * action,const char *fileName,const char *describe){
    QAction* Action = new QAction(action, this);
    Action->setShortcut(QKeySequence::Open);
    Action->setStatusTip(tr(describe));
    std::string str = std::string(":/res/") + fileName;
    Action->setText(action);
    Action->setIcon(QIcon(str.c_str()));
    ui->toolBar->addAction(Action);
    return Action;

}

void MainWindow::insertTable(std::string fileName, std::string path)
{
    int count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(count + 1);
    ui->tableWidget->setItem(count,0,new QTableWidgetItem(fileName.c_str()));
    ui->tableWidget->setItem(count,1,new QTableWidgetItem(path.c_str()));
    ui->tableWidget->setItem(count,2,new QTableWidgetItem("Wait"));

}

void MainWindow::setLabelImage(std::string filepath)
{
    QPixmap image(filepath.c_str());
    auto mask = _maskImage.copy();
    image = image.scaled(mask.rect().size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QImage resultImage(image.rect().size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawImage(0, 0, image.toImage());
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.end();
    _preview->getLabel()->setPixmap(QPixmap::fromImage(resultImage));
    _preview->getLabel()->resize(image.rect().size());

}

void MainWindow::generateImage(std::string filepath, std::string out,QSize size)
{
    QImage image(filepath.c_str());
    auto mask = _maskImage.copy();
    image = image.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    mask  = mask.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QImage resultImage(image.rect().size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawImage(0, 0, image);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.end();
    resultImage.save(out.c_str());
}

void MainWindow::addToTree(QString s, QString s1)
{
    QStringList strlist;
    strlist<<s<<s1;
    ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(strlist));
}

void MainWindow::SaveFile(std::string file)
{
    QDir dir;
    QString filedir;
    QString result;

    filedir = QFileInfo(file.c_str()).absolutePath();
    std::string fileName = QFileInfo(file.c_str()).fileName().toStdString();

    fileName = fileName.substr(0,fileName.rfind("."));
    result = filedir +"/"+ fileName.c_str() + "/";

    dir.mkdir(result);

    std::string suffix =  QFileInfo(file.c_str()).suffix().toStdString();

    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        QSize size;
        size.setWidth((*it)->text(0).toInt());
        size.setHeight((*it)->text(1).toInt());
        char newfileName[200];
        sprintf(newfileName,"%s%s-%d*%d.%s",result.toStdString().c_str(),fileName.c_str(),size.width(),size.height(),suffix.c_str());
        generateImage(file,newfileName,size);
        ++it;
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
            event->acceptProposedAction();
        }
}


void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
        if (urls.isEmpty()) {
            return;
        }

        QString fileName = urls.first().toLocalFile();
        if (fileName.isEmpty()) {
            return;
        }

   int i = ui->tableWidget->rowCount();
   for(auto &itor:urls){
       if(!QFileInfo(itor.toLocalFile()).isFile()){
           continue ;
       }
       if(itor.toLocalFile().toStdString().find(".png") != -1 ||
          itor.toLocalFile().toStdString().find(".jpg") != -1 || itor.toLocalFile().toStdString().find(".bmp") != -1){
           if(ui->tableWidget->findItems(itor.toLocalFile(),Qt::MatchExactly).isEmpty()){
               insertTable(tr("%01").arg(i).toStdString(),itor.toLocalFile().toStdString());
               i++;
           }
       }

   }

}


void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if(_mask.empty()){
        QMessageBox::information(NULL,"错误","Mask 层未设置!");
        return ;
    }
    if(!_preview){
        _preview = new Form(NULL);
    }
    setLabelImage(item->text().toStdString());
    _preview->show();
}

void MainWindow::MaskImage()
{
    std::string temp =  QFileDialog::getOpenFileName(this, tr("Open File"),
                                 "/home",
                                 tr("Images (*.png)")).toStdString();
    if(temp != "") _mask = temp;
    if(_mask.empty()) return;
    _maskImage.load(_mask.c_str());
}

void MainWindow::StartApplication()
{
    if(_mask.empty()){
        QMessageBox::information(NULL,"错误","Mask 层未设置!");
        return ;
    }
    int row = ui->tableWidget->rowCount();

    bool flag = false;
    for(int i = 0; i < row;i++){
        auto item = ui->tableWidget->item(i,1);
        if(ui->tableWidget->item(i,2)->text() != "Done"){
            SaveFile(item->text().toStdString());
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Done"));
            flag = true;
        }

    }

    if(flag) QMessageBox::information(this,"输出","输出图片成功!");
}

void MainWindow::About()
{
    QMessageBox::about(this,"关于本软件","<p>软件功能</p> \n <p>批量生成自定尺寸和形状支持透明.</p>\n<p>version 0.5</p>\n<a href=\"mailto:windgodvc@126.com\">My Mail</a> <br/>  Projet addres:<a href=\"https://github.com/windgodvc/ImageProcessing\"> ImageProcessing </a>");
}


void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* curItem=ui->treeWidget->itemAt(pos);  //获取当前被点击的节点
    if(curItem==NULL)return;           //在空白位置右击
    auto menu = new QMenu(this);
    menu->addAction(ui->DeleteCurren);
    menu->addAction(ui->DeleteAll);
    menu->exec(QCursor::pos());
}

void MainWindow::deleteCurrent()
{
    auto row = ui->treeWidget->currentIndex().row();
    if(row != -1){
        ui->treeWidget->takeTopLevelItem(row);
    }
}

void MainWindow::deleteAll()
{
    int count = ui->treeWidget->topLevelItemCount();
    for(int i = 0; i < count;i++){
        auto item = ui->treeWidget->takeTopLevelItem(0);
        delete item; item = NULL;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->spinBox->text().isNull() || ui->spinBox_2->text().isNull()) return ;

    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
         //do something like
        if((*it)->text(0) == ui->spinBox->text() && (*it)->text(1) == ui->spinBox_2->text()){
            QMessageBox::information(this,"错误","数据重复!重复添加会影响效率的哦!");
            return ;
        }
        ++it;
    }

    addToTree(ui->spinBox->text(),ui->spinBox_2->text());
}
