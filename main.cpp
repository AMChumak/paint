#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("AMC Paint");
    window.resize(640,480);
    window.show();
    return app.exec();
}