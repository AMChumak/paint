#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBar();

    setWindowTitle("AMC Paint");
    setMinimumSize(640, 480);
}


void MainWindow::newFile() {}
void MainWindow::open() {}
void MainWindow::save() {}
void MainWindow::undo() {}
void MainWindow::redo() {}
void MainWindow::clear() {}
void MainWindow::resize() {}
void MainWindow::setPen() {}
void MainWindow::insert() {}
void MainWindow::line() {}
void MainWindow::fill() {}
void MainWindow::insert4Polygon() {}
void MainWindow::insert5Polygon() {}
void MainWindow::insert6Polygon() {}
void MainWindow::insert7Polygon() {}
void MainWindow::insert8Polygon() {}
void MainWindow::insert4Star() {}
void MainWindow::insert5Star() {}
void MainWindow::insert6Star() {}
void MainWindow::insert7Star() {}
void MainWindow::insert8Star() {}
void MainWindow::setKcolor() {}
void MainWindow::setRcolor() {}
void MainWindow::setRGcolor() {}
void MainWindow::setGcolor() {}
void MainWindow::setGBcolor() {}
void MainWindow::setBcolor() {}
void MainWindow::setBRcolor() {}
void MainWindow::setWcolor() {}
void MainWindow::about() {}

void MainWindow::createActions()
{
    newFileAct = new QAction("New", this);
    newFileAct->setStatusTip("Create a new file");
    newFileAct->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    connect(newFileAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction("Open", this);
    openAct->setStatusTip("Open a file");
    openAct->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction("Save", this);
    saveAct->setStatusTip("Save the file");
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    undoAct = new QAction("Undo", this);
    undoAct->setStatusTip("Undo the last action");
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction("Redo", this);
    redoAct->setStatusTip("Redo the next action");
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    clearAct = new QAction("Clear", this);
    clearAct->setStatusTip("Clear the screen");
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));

    resizeAct = new QAction("Resize", this);
    resizeAct->setStatusTip("Resize the canvas");
    connect(resizeAct, SIGNAL(triggered()), this, SLOT(resize()));

    setPenAct = new QAction("Set Pen", this);
    setPenAct->setStatusTip("Set pen parameters");
    connect(setPenAct, SIGNAL(triggered()), this, SLOT(setPen()));

    insertAct = new QAction("Insert", this);
    insertAct->setStatusTip("Insert a figure");
    connect(insertAct, SIGNAL(triggered()), this, SLOT(insert()));

    lineAct = new QAction("Line", this);
    lineAct->setStatusTip("Choose line tool");
    connect(lineAct, SIGNAL(triggered()), this, SLOT(line()));

    fillAct = new QAction("Fill", this);
    fillAct->setStatusTip("Choose fill tool");
    connect(fillAct, SIGNAL(triggered()), this, SLOT(fill()));

    insert4PolygonAct = new QAction("Square", this);
    insert4PolygonAct->setStatusTip("Insert square");
    connect(insert4PolygonAct, SIGNAL(triggered()), this, SLOT(insert4Polygon()));

    insert5PolygonAct = new QAction("Pentagon", this);
    insert5PolygonAct->setStatusTip("Insert pentagon");
    connect(insert5PolygonAct, SIGNAL(triggered()), this, SLOT(insert5Polygon()));

    insert6PolygonAct = new QAction("Hexagon", this);
    insert6PolygonAct->setStatusTip("Insert hexagon");
    connect(insert6PolygonAct, SIGNAL(triggered()), this, SLOT(insert6Polygon()));

    insert7PolygonAct = new QAction("Heptagon", this);
    insert7PolygonAct->setStatusTip("Insert heptagon");
    connect(insert7PolygonAct, SIGNAL(triggered()), this, SLOT(insert7Polygon()));

    insert8PolygonAct = new QAction("Octagon", this);
    insert8PolygonAct->setStatusTip("Insert octagon");
    connect(insert8PolygonAct, SIGNAL(triggered()), this, SLOT(insert8Polygon()));

    insert4StarAct = new QAction("Square Star", this);
    insert4StarAct->setStatusTip("Insert square star");
    connect(insert4StarAct, SIGNAL(triggered()), this, SLOT(insert4Star()));

    insert5StarAct = new QAction("Pentagonal star", this);
    insert5StarAct->setStatusTip("Insert pentagonal star");
    connect(insert5StarAct, SIGNAL(triggered()), this, SLOT(insert5Star()));

    insert6StarAct = new QAction("Hexagonal star", this);
    insert6StarAct->setStatusTip("Insert hexagonal star");
    connect(insert6StarAct, SIGNAL(triggered()), this, SLOT(insert6Star()));

    insert7StarAct = new QAction("Heptagonal star", this);
    insert7StarAct->setStatusTip("Insert heptagonal star");
    connect(insert7StarAct, SIGNAL(triggered()), this, SLOT(insert7Star()));

    insert8StarAct = new QAction("Octagonal star", this);
    insert8StarAct->setStatusTip("Insert octagonal star");
    connect(insert8StarAct, SIGNAL(triggered()), this, SLOT(insert8Star()));

    setKcolorAct = new QAction("Black", this);
    setKcolorAct->setStatusTip("Choose the black color");
    connect(setKcolorAct, SIGNAL(triggered()), this, SLOT(setKcolor()));

    setRcolorAct = new QAction("Red", this);
    setRcolorAct->setStatusTip("Choose the red color");
    connect(setRcolorAct, SIGNAL(triggered()), this, SLOT(setRcolor()));

    setRGcolorAct = new QAction("Yellow", this);
    setRGcolorAct->setStatusTip("Choose the yellow color");
    connect(setRGcolorAct, SIGNAL(triggered()), this, SLOT(setRGcolor()));

    setGcolorAct = new QAction("Green", this);
    setGcolorAct->setStatusTip("Choose the green color");
    connect(setGcolorAct, SIGNAL(triggered()), this, SLOT(setGcolor()));

    setGBcolorAct = new QAction("Cyan", this);
    setGBcolorAct->setStatusTip("Choose the cyan color");
    connect(setGBcolorAct, SIGNAL(triggered()), this, SLOT(setGBcolor()));

    setBcolorAct = new QAction("Blue", this);
    setBcolorAct->setStatusTip("Choose the blue color");
    connect(setBcolorAct, SIGNAL(triggered()), this, SLOT(setBcolor()));

    setBRcolorAct = new QAction("Magenta", this);
    setBRcolorAct->setStatusTip("Choose the magenta color");
    connect(setBRcolorAct, SIGNAL(triggered()), this, SLOT(setBRcolor()));

    setWcolorAct = new QAction("White", this);
    setWcolorAct->setStatusTip("Choose the white color");
    connect(setWcolorAct, SIGNAL(triggered()), this, SLOT(setWcolor()));

    aboutAct = new QAction("About", this);
    aboutAct->setStatusTip("About the application");
    aboutAct->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));



}
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("File");
    fileMenu->setToolTipsVisible(true);
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu("Edit");
    editMenu->setToolTipsVisible(true);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(clearAct);
    editMenu->addAction(resizeAct);
    editMenu->addAction(setPenAct);
    editMenu->addAction(lineAct);
    editMenu->addAction(fillAct);
    editMenu->addAction(insertAct);

    aboutMenu = menuBar()->addMenu("About");
    aboutMenu->setToolTipsVisible(true);
    aboutMenu->addAction(aboutAct);
}
void MainWindow::createToolBar()
{
    mainToolBar = addToolBar("Paint Toolbar");
    mainToolBar->addAction(newFileAct);
    mainToolBar->addAction(openAct);
    mainToolBar->addAction(saveAct);
    mainToolBar->addSeparator();
    mainToolBar->addAction(setPenAct);
    mainToolBar->addAction(lineAct);
    mainToolBar->addAction(fillAct);
    mainToolBar->addAction(clearAct);
    mainToolBar->addSeparator();
    mainToolBar->addAction(insert4PolygonAct);
    mainToolBar->addAction(insert5PolygonAct);
    mainToolBar->addAction(insert6PolygonAct);
    mainToolBar->addAction(insert7PolygonAct);
    mainToolBar->addAction(insert8PolygonAct);
    mainToolBar->addAction(insert4StarAct);
    mainToolBar->addAction(insert5StarAct);
    mainToolBar->addAction(insert6StarAct);
    mainToolBar->addAction(insert7StarAct);
    mainToolBar->addAction(insert8StarAct);
    mainToolBar->addSeparator();
    mainToolBar->addAction(setKcolorAct);
    mainToolBar->addAction(setWcolorAct);
    mainToolBar->addAction(setRcolorAct);
    mainToolBar->addAction(setRGcolorAct);
    mainToolBar->addAction(setGcolorAct);
    mainToolBar->addAction(setGBcolorAct);
    mainToolBar->addAction(setBcolorAct);
    mainToolBar->addAction(setBRcolorAct);
    mainToolBar->addAction(aboutAct);
}
