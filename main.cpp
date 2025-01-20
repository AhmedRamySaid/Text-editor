#include "Application/MainWindow/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window and show it
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();  // Enter the application event loop
}
