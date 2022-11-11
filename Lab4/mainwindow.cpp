#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myudp.h"
#include <QFileDialog>
#include <iostream>
#include <QPixmap>
#include <fstream>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QByteArray>
#include <QImage>
#include <QVector>
#include <QBuffer>
#include <QIODevice>
#include <QColor>
#include <iomanip>
#include <sstream>
#include <string>
#include <array>
#include <QUdpSocket>
#include <QtNetwork>
#include <QElapsedTimer>
#include <QDataStream>
#include <QImageWriter>
#include <QThread>

using namespace std;

// file paths for uploading images and QImage object declared outside
// because used by many functions

QString file_Path;
QImage image;
int global_contrast;
int global_brightness;
QByteArray image_array;
int total_bytes;

MyUDP server;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // slider configurations for a new window
    ui->setupUi(this);
    ui->brightSlider->setSliderPosition(50);
    ui->contSlider->setSliderPosition(50);
    ui->b_label->setText("Brightness: 50");
    ui->c_label->setText("Contrast: 50");
}

MainWindow::~MainWindow()
{
    delete ui;
}

MyUDP::MyUDP(QObject *parent):
    QObject(parent)
{
    socket = new QUdpSocket(this);
    cout << " check ip address" << endl;
    socket->bind(QHostAddress("192.168.29.141"),80);

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void MyUDP::SayHello()
{
    socket->writeDatagram(image_array,QHostAddress("192.168.29.141"),80);
}

void MyUDP::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
}

void MainWindow::on_pushButton_clicked()
{

    // file path set to user selected file in dialog box

    file_Path = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "C:/Users/", tr("Image Files (*.png *.jpg *.bmp)"));

    cout << "file path is  " << file_Path.toStdString() << endl;

    // image set as a QImage object of the file in file_path

    image = QImage(file_Path);

    // output the image as a pixmap object in labelpic

    ui->labelpic->setPixmap(QPixmap::fromImage(image));


}


void MainWindow::on_brightSlider_sliderMoved(int position)
{

    // defined function to relate the position of slider to a smaller range from 0 to 2
    float relative_position = float(position)/50;

    global_brightness = position;
    ui->b_label->setText("Brightness: " + QString::number(position));
    //defined image as a QImage object from file path

    image = QImage(file_Path).convertToFormat(QImage::Format_Grayscale8);

    // extract intensity values of all pixels from current image
    // new brightness calculated by multiplying by the relative position of slider to the current brightness of pixel

    for (int b = 0 ; b < image.width() ; b++)
    {
        for (int a = 0; a < image.height() ; a++)
        {
            float curr_bright = float(qGray(image.pixel(b,a)));
            int new_bright = floor(curr_bright * relative_position + ((position-50)*5));

            // sets a maximum and minimum value for brightness so pixels do not invert

            if (new_bright > 255)
            {
                new_bright = 255;
            }
            else if (new_bright < 0)
            {
                new_bright = 0;
            }
            image.setPixel(b,a,qRgb(new_bright,new_bright,new_bright));
        }
    }

    // output the new image to the labelpic

    ui->labelpic->setPixmap(QPixmap::fromImage(image));



}


void MainWindow::on_contSlider_sliderMoved(int position)
{

    // extract image from the file path and convert to a QImage object
    image = QImage(file_Path).convertToFormat(QImage::Format_Grayscale8);

    ui->c_label->setText("Contrast: " + QString::number(position));

    float contrast = ((float(position)/50)-1)*128;

    float factor = (259*(255+contrast))/(255*(259-contrast));

    global_contrast = position;

    for (int b = 0 ; b < image.width() ; b++)
    {
        for (int a = 0; a < image.height() ; a++)
        {
            int curr_bright = qGray(image.pixel(b,a));
            int new_bright = floor((factor*(curr_bright-128))+128);

            if (new_bright > 255)
            {
                new_bright = 255;
            }
            else if (new_bright < 0)
            {
                new_bright = 0;
            }
            image.setPixel(b,a,qRgb(new_bright,new_bright,new_bright));

        }
    }

    // output image to pixmap in labelpic

    ui->labelpic->setPixmap(QPixmap::fromImage(image));



}


void MainWindow::on_saveButton_clicked()
{

    // define image as the current image being displayed in the labelpic pixmap
    image = ui->labelpic->pixmap().toImage().convertToFormat(QImage::Format_Grayscale8);

    // define the save file dialog

    QString save_fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.bmp)"));

    //saves image if save_fileName has a string
    if (!save_fileName.isEmpty())
    {
      image.save(save_fileName);
    }
}


void MainWindow::on_TransferButton_clicked()
{
    total_bytes = 0;
    image_array.clear();
    image_array.append("new_image");
    server.SayHello();
    image = QImage(file_Path);

    string height = "new_image height=" + to_string(image.height());
    string width = "new_image width=" + to_string(image.width());

    image_array.clear();
    image_array.append(height);
    server.SayHello();

    image_array.clear();
    image_array.append(width);
    server.SayHello();

    image_array.clear();
    image_array.append("new_image np");
    server.SayHello();

    for (int b = 0 ; b < image.height() ; b++)
    {
        string pixel_values = "";
        for (int a = 0; a < image.width() ; a++)
        {
            int curr_bright = qGray(image.pixel(b,a));
            pixel_values = pixel_values + to_string(curr_bright) + ",";

        }
            cout << pixel_values << endl;
            image_array.clear();
            image_array.append(pixel_values);
            server.SayHello();
            QThread::msleep(2);
    }


    image_array.clear();
    image_array.append("END");
    server.SayHello();

}


void MainWindow::on_TransferModButton_clicked()
{
    image_array.clear();
    image_array.append("new_image");
    server.SayHello();
    image = ui->labelpic->pixmap().toImage().convertToFormat(QImage::Format_Grayscale8);


    string height = "new_image height=" + to_string(image.height());
    string width = "new_image width=" + to_string(image.width());

    image_array.clear();
    image_array.append(height);
    server.SayHello();

    image_array.clear();
    image_array.append(width);
    server.SayHello();

    image_array.clear();
    image_array.append("new_image np");
    server.SayHello();

    for (int b = 0 ; b < image.height() ; b++)
    {
        string pixel_values = "";
        for (int a = 0; a < image.width() ; a++)
        {
            int curr_bright = qGray(image.pixel(b,a));
            pixel_values = pixel_values + to_string(curr_bright) + ",";

        }
            cout << pixel_values << endl;
            image_array.clear();
            image_array.append(pixel_values);
            server.SayHello();
            QThread::msleep(2);
    }


    image_array.clear();
    image_array.append("END");
    server.SayHello();


}


void MainWindow::on_pushButton_2_clicked()
{
    // open dialog box to choose file in computer
    QString file_Path_overlay = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "C:/Users/", tr("Image Files (*.png *.jpg *.bmp)"));

    // set overlay image as QImage chosen from dialog box above
    // set original image as QImage converted from existing pixmap in label_pic

    QImage overlay = QImage(file_Path_overlay).convertToFormat(QImage::Format_Grayscale8);
    QImage original = ui->labelpic->pixmap().toImage().convertToFormat(QImage::Format_Grayscale8);


    // iterate through every pixel on the overlay QImage using for loops, one for height and one for width.
    // extract the pixel intensity from the overlay image and then replace the pixel in the original image
    // at the same coordinates.

    for ( int y = 0 ; y < overlay.height() ; y++)
    {
        for ( int x = 0 ; x < overlay.width(); x++)
        {

             int intensity = qGray(overlay.pixel(x,y));

             if (x <= original.width() || y <= original.height())
             {
             original.setPixelColor(x+200,y,qRgb(intensity,intensity,intensity));
             }
             else
             {
                 cout <<" out of range";
             }
             //cout << "intensity = " << intensity << endl;
        }
    }

    // set the output of the new image as a pixmap object on label_pic to display to GUI

    ui->labelpic->setPixmap(QPixmap::fromImage(original));
}

