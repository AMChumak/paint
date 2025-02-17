#include "MainWindow.h"
#include <QAction>
#include <QFileDialog>
#include <QFrame>
#include <QMenu>
#include <QMenuBar>
#include <QResizeEvent>
#include <QStyle>

#include <oneapi/tbb/detail/_machine.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scrollArea = new QScrollArea(this);
    renderArea = new RenderArea(this);
    scrollArea->resize(1200, 1200);
    scrollArea->setWidget(renderArea);
    scrollArea->move(0, menuBar()->height());

    connect(renderArea, &RenderArea::mousePressed, this, &MainWindow::onCanvasPressed);
    connect(renderArea, &RenderArea::mouseMoved, this, &MainWindow::onMouseMovedOverCanvas);


    createActions();
    createMenus();
    createToolBar();
    setWindowTitle("AMC Paint");
    setMinimumSize(640, 480);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    clickCount = 0;
    scrollArea->resize(event->size().width(), event->size().height());
    update();
    QMainWindow::resizeEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    renderArea->loadLastScreen();
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::newFile()
{
    clickCount = 0;
    renderArea->initFile();
}
void MainWindow::open()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty()) {
        return;
    }
    renderArea->loadFile(fileName);
}
void MainWindow::save()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "*.png");
    if (fileName.isEmpty()) {
        return;
    }
    renderArea->saveFile(fileName);
}
void MainWindow::undo()
{
    clickCount = 0;
    renderArea->undo();
}
void MainWindow::redo()
{
    clickCount = 0;
    renderArea->redo();
}
void MainWindow::clean()
{
    clickCount = 0;
    renderArea->clean();
}
void MainWindow::resize() {}
void MainWindow::setPen() {}
void MainWindow::insert() {}
void MainWindow::line()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_LINE;
}
void MainWindow::fill()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_FILL;
}
void MainWindow::insert4Polygon()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 4;
}
void MainWindow::insert5Polygon()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 5;
}
void MainWindow::insert6Polygon()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 6;
}
void MainWindow::insert7Polygon()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 7;
}
void MainWindow::insert8Polygon()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 8;
}
void MainWindow::insert4Star()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 4;
}
void MainWindow::insert5Star()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 5;
}
void MainWindow::insert6Star()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 6;
}
void MainWindow::insert7Star()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 7;
}
void MainWindow::insert8Star()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 8;
}
void MainWindow::setKcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::black);
}
void MainWindow::setRcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::red);
}
void MainWindow::setRGcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::yellow);
}
void MainWindow::setGcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::green);
}
void MainWindow::setGBcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::cyan);
}
void MainWindow::setBcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::blue);
}
void MainWindow::setBRcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::magenta);
}
void MainWindow::setWcolor()
{
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::white);
}
void MainWindow::about() {}

void MainWindow::onCanvasPressed(const QPoint &point)
{
    clickCount++;
    switch (currentMode) {
    case MODE_FILL: {
        if (clickCount == 1) {
            renderArea->fillArea(point);
            renderArea->make_screenshot();
            clickCount = 0;
        }
        break;
    }
    default: {
        if (clickCount == 2) {
            renderArea->make_screenshot();
            clickCount = 0;
        }
        break;
    }
    }
}
void MainWindow::onMouseMovedOverCanvas(const QPoint &point)
{
    if (point.x() == 0 || point.x() == renderArea->width() - 1 || point.y() == 0
        || point.y() == renderArea->height() - 1) {
        return;
    }
    switch (currentMode) {
    case MODE_LINE: {
        if (clickCount == 1) {
            QPoint begin = renderArea->getCurrentPressed();
            renderArea->drawLine(begin, point);
        }
        break;
    }
    case MODE_POLYGON: {
        if (clickCount == 1) {
            QPoint center = renderArea->getCurrentPressed();
            renderArea->drawPolygon(center, point, currentVerticesCount);
        }
        break;
    }
    case MODE_STAR: {
        if (clickCount == 1) {
            QPoint center = renderArea->getCurrentPressed();
            renderArea->drawStar(center, point, currentVerticesCount);
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::createActions()
{
    newFileAct = new QAction("New", this);
    newFileAct->setStatusTip("Create a new file");
    newFileAct->setIcon(QIcon(":/resources/new_file.png"));
    connect(newFileAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction("Open", this);
    openAct->setStatusTip("Open a file");
    openAct->setIcon(QIcon(":/resources/open.png"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction("Save", this);
    saveAct->setStatusTip("Save the file");
    saveAct->setIcon(QIcon(":/resources/save.png"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    undoAct = new QAction("Undo", this);
    undoAct->setStatusTip("Undo the last action");
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setIcon(QIcon(":/resources/undo.png"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction("Redo", this);
    redoAct->setStatusTip("Redo the next action");
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setIcon(QIcon(":/resources/redo.png"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cleanAct = new QAction("clean", this);
    cleanAct->setStatusTip("clean the screen");
    cleanAct->setIcon(QIcon(":/resources/clean.png"));
    connect(cleanAct, SIGNAL(triggered()), this, SLOT(clean()));

    resizeAct = new QAction("Resize", this);
    resizeAct->setStatusTip("Resize the canvas");
    resizeAct->setIcon(QIcon(":/resources/resize.png"));
    connect(resizeAct, SIGNAL(triggered()), this, SLOT(resize()));

    setPenAct = new QAction("Set Pen", this);
    setPenAct->setStatusTip("Set pen parameters");
    setPenAct->setIcon(QIcon(":/resources/set_pen.png"));
    connect(setPenAct, SIGNAL(triggered()), this, SLOT(setPen()));

    insertAct = new QAction("Insert", this);
    insertAct->setStatusTip("Insert a figure");
    insertAct->setIcon(QIcon(":/resources/hexagon.png"));
    connect(insertAct, SIGNAL(triggered()), this, SLOT(insert()));

    lineAct = new QAction("Line", this);
    lineAct->setStatusTip("Choose line tool");
    lineAct->setIcon(QIcon(":/resources/line.png"));
    connect(lineAct, SIGNAL(triggered()), this, SLOT(line()));

    fillAct = new QAction("Fill", this);
    fillAct->setStatusTip("Choose fill tool");
    fillAct->setIcon(QIcon(":/resources/fill.png"));
    connect(fillAct, SIGNAL(triggered()), this, SLOT(fill()));

    insert4PolygonAct = new QAction("Square", this);
    insert4PolygonAct->setStatusTip("Insert square");
    insert4PolygonAct->setIcon(QIcon(":/resources/square.png"));
    connect(insert4PolygonAct, SIGNAL(triggered()), this, SLOT(insert4Polygon()));

    insert5PolygonAct = new QAction("Pentagon", this);
    insert5PolygonAct->setStatusTip("Insert pentagon");
    insert5PolygonAct->setIcon(QIcon(":/resources/pentagon.png"));
    connect(insert5PolygonAct, SIGNAL(triggered()), this, SLOT(insert5Polygon()));

    insert6PolygonAct = new QAction("Hexagon", this);
    insert6PolygonAct->setStatusTip("Insert hexagon");
    insert6PolygonAct->setIcon(QIcon(":/resources/hexagon.png"));
    connect(insert6PolygonAct, SIGNAL(triggered()), this, SLOT(insert6Polygon()));

    insert7PolygonAct = new QAction("Heptagon", this);
    insert7PolygonAct->setStatusTip("Insert heptagon");
    insert7PolygonAct->setIcon(QIcon(":/resources/heptagon.png"));
    connect(insert7PolygonAct, SIGNAL(triggered()), this, SLOT(insert7Polygon()));

    insert8PolygonAct = new QAction("Octagon", this);
    insert8PolygonAct->setStatusTip("Insert octagon");
    insert8PolygonAct->setIcon(QIcon(":/resources/octagon.png"));
    connect(insert8PolygonAct, SIGNAL(triggered()), this, SLOT(insert8Polygon()));

    insert4StarAct = new QAction("Square Star", this);
    insert4StarAct->setStatusTip("Insert square star");
    insert4StarAct->setIcon(QIcon(":/resources/square_star.png"));
    connect(insert4StarAct, SIGNAL(triggered()), this, SLOT(insert4Star()));

    insert5StarAct = new QAction("Pentagonal star", this);
    insert5StarAct->setStatusTip("Insert pentagonal star");
    insert5StarAct->setIcon(QIcon(":/resources/pentagonal_star.png"));
    connect(insert5StarAct, SIGNAL(triggered()), this, SLOT(insert5Star()));

    insert6StarAct = new QAction("Hexagonal star", this);
    insert6StarAct->setStatusTip("Insert hexagonal star");
    insert6StarAct->setIcon(QIcon(":/resources/hexagonal_star.png"));
    connect(insert6StarAct, SIGNAL(triggered()), this, SLOT(insert6Star()));

    insert7StarAct = new QAction("Heptagonal star", this);
    insert7StarAct->setStatusTip("Insert heptagonal star");
    insert7StarAct->setIcon(QIcon(":/resources/heptagonal_star.png"));
    connect(insert7StarAct, SIGNAL(triggered()), this, SLOT(insert7Star()));

    insert8StarAct = new QAction("Octagonal star", this);
    insert8StarAct->setStatusTip("Insert octagonal star");
    insert8StarAct->setIcon(QIcon(":/resources/octagonal_star.png"));
    connect(insert8StarAct, SIGNAL(triggered()), this, SLOT(insert8Star()));

    setKcolorAct = new QAction("Black", this);
    setKcolorAct->setStatusTip("Choose the black color");
    setKcolorAct->setIcon(QIcon(":/resources/set_k_color.png"));
    connect(setKcolorAct, SIGNAL(triggered()), this, SLOT(setKcolor()));

    setRcolorAct = new QAction("Red", this);
    setRcolorAct->setStatusTip("Choose the red color");
    setRcolorAct->setIcon(QIcon(":/resources/set_r_color.png"));
    connect(setRcolorAct, SIGNAL(triggered()), this, SLOT(setRcolor()));

    setRGcolorAct = new QAction("Yellow", this);
    setRGcolorAct->setStatusTip("Choose the yellow color");
    setRGcolorAct->setIcon(QIcon(":/resources/set_rg_color.png"));
    connect(setRGcolorAct, SIGNAL(triggered()), this, SLOT(setRGcolor()));

    setGcolorAct = new QAction("Green", this);
    setGcolorAct->setStatusTip("Choose the green color");
    setGcolorAct->setIcon(QIcon(":/resources/set_g_color.png"));
    connect(setGcolorAct, SIGNAL(triggered()), this, SLOT(setGcolor()));

    setGBcolorAct = new QAction("Cyan", this);
    setGBcolorAct->setStatusTip("Choose the cyan color");
    setGBcolorAct->setIcon(QIcon(":/resources/set_gb_color.png"));
    connect(setGBcolorAct, SIGNAL(triggered()), this, SLOT(setGBcolor()));

    setBcolorAct = new QAction("Blue", this);
    setBcolorAct->setStatusTip("Choose the blue color");
    setBcolorAct->setIcon(QIcon(":/resources/set_b_color.png"));
    connect(setBcolorAct, SIGNAL(triggered()), this, SLOT(setBcolor()));

    setBRcolorAct = new QAction("Magenta", this);
    setBRcolorAct->setStatusTip("Choose the magenta color");
    setBRcolorAct->setIcon(QIcon(":/resources/set_br_color.png"));
    connect(setBRcolorAct, SIGNAL(triggered()), this, SLOT(setBRcolor()));

    setWcolorAct = new QAction("White", this);
    setWcolorAct->setStatusTip("Choose the white color");
    setWcolorAct->setIcon(QIcon(":/resources/set_w_color.png"));
    connect(setWcolorAct, SIGNAL(triggered()), this, SLOT(setWcolor()));

    aboutAct = new QAction("About", this);
    aboutAct->setStatusTip("About the application");
    aboutAct->setIcon(QIcon(":/resources/about.png"));
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
    editMenu->addAction(cleanAct);
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
    mainToolBar->addAction(cleanAct);
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
