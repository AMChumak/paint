#include "MainWindow.h"
#include "ResizeWindow.h"
#include <QAction>
#include <QActionGroup>
#include <QColorDialog>
#include <QFileDialog>
#include <QFrame>
#include <QMenu>
#include <QMenuBar>
#include <QResizeEvent>
#include <QStyle>

#include "InsertWindow.h"
#include "WidthWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_layout = new QVBoxLayout;
    scrollArea = new QScrollArea(this);
    renderArea = new RenderArea(scrollArea);
    scrollArea->setWidget(renderArea);
    m_layout->addWidget(menuBar());
    m_layout->addWidget(scrollArea);
    window = new QWidget();
    window->setLayout(m_layout);
    setCentralWidget(window);


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
void MainWindow::resize()
{
    clickCount = 0;
    auto *resizeWindow
        = new ResizeWindow(this, QSize{renderArea->width() - 2, renderArea->height() - 2});
    QRect rect = geometry();
    resizeWindow->move(
        rect.width() / 2 - resizeWindow->width() / 2,
        rect.height() / 2 - resizeWindow->height() / 2);
    resizeWindow->show();
    connect(resizeWindow, &ResizeWindow::getNewSize, renderArea, &RenderArea::resizeImage);
}

void MainWindow::insert()
{
    renderArea->loadLastScreen();
    clickCount = 0;
    insertAct->setChecked(false);
    lastCheckedToolAction->setChecked(true);
    auto *insertWindow = new InsertWindow(this, renderArea->width(), renderArea->height());
    QRect rect = geometry();
    insertWindow->move(
        rect.width() / 2 - insertWindow->width() / 2,
        rect.height() / 2 - insertWindow->height() / 2);
    insertWindow->show();
    connect(insertWindow, &InsertWindow::insertFigure, this, &MainWindow::onFigurePrepared);
}
void MainWindow::line()
{
    lastCheckedColorAction = lineAct;
    lineAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_LINE;
}
void MainWindow::fill()
{
    lastCheckedColorAction = fillAct;
    fillAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_FILL;
}
void MainWindow::insert4Polygon()
{
    lastCheckedColorAction = insert4PolygonAct;
    insert4PolygonAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 4;
}
void MainWindow::insert5Polygon()
{
    lastCheckedColorAction = insert5PolygonAct;
    insert5PolygonAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 5;
}
void MainWindow::insert6Polygon()
{
    lastCheckedColorAction = insert6PolygonAct;
    insert6PolygonAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 6;
}
void MainWindow::insert7Polygon()
{
    lastCheckedColorAction = insert7PolygonAct;
    insert7PolygonAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 7;
}
void MainWindow::insert8Polygon()
{
    lastCheckedColorAction = insert8PolygonAct;
    insert8PolygonAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_POLYGON;
    currentVerticesCount = 8;
}
void MainWindow::insert4Star()
{
    lastCheckedColorAction = insert4StarAct;
    insert4StarAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 4;
}
void MainWindow::insert5Star()
{
    lastCheckedColorAction = insert5StarAct;
    insert5StarAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 5;
}
void MainWindow::insert6Star()
{
    lastCheckedColorAction = insert6StarAct;
    insert6StarAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 6;
}
void MainWindow::insert7Star()
{
    lastCheckedColorAction = insert7StarAct;
    insert7StarAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 7;
}
void MainWindow::insert8Star()
{
    lastCheckedColorAction = insert8StarAct;
    insert8StarAct->setChecked(true);
    clickCount = 0;
    renderArea->loadLastScreen();
    currentMode = MODE_STAR;
    currentVerticesCount = 8;
}

void MainWindow::penWidth()
{
    WidthWindow *penWidthWindow = new WidthWindow(this, renderArea->getPenWidth());
    QRect rect = geometry();
    penWidthWindow->move(
        rect.width() / 2 - penWidthWindow->width() / 2,
        rect.height() / 2 - penWidthWindow->height() / 2);
    penWidthWindow->show();
    connect(penWidthWindow, &WidthWindow::widthChanged, renderArea, &RenderArea::setPenWidth);
}

void MainWindow::palette()
{
    paletteAct->setChecked(false);
    lastCheckedColorAction->setChecked(true);
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        lastCheckedColorAction = paletteAct;
        paletteAct->setChecked(true);
        renderArea->setColor(color);
    }
}

void MainWindow::setKcolor()
{
    lastCheckedColorAction = setKcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::black);
}
void MainWindow::setRcolor()
{
    lastCheckedColorAction = setRcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::red);
}
void MainWindow::setRGcolor()
{
    lastCheckedColorAction = setRGcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::yellow);
}
void MainWindow::setGcolor()
{
    lastCheckedColorAction = setGcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::green);
}
void MainWindow::setGBcolor()
{
    lastCheckedColorAction = setGBcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::cyan);
}
void MainWindow::setBcolor()
{
    lastCheckedColorAction = setBcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::blue);
}
void MainWindow::setBRcolor()
{
    lastCheckedColorAction = setBRcolorAct;
    clickCount = 0;
    renderArea->loadLastScreen();
    renderArea->setColor(Qt::magenta);
}
void MainWindow::setWcolor()
{
    lastCheckedColorAction = setWcolorAct;
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
    case MODE_FIGURE: {
        if (clickCount == 1) {
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
    case MODE_FIGURE: {
        if (clickCount == 0) {
            QPoint center = point;
            if (figureType == InsertWindow::FigureTypes_POLYGON) {
                renderArea->drawPolygon(center, center + offset, currentVerticesCount);
            } else if (figureType == InsertWindow::FigureTypes_STAR) {
                renderArea->drawStar(center, center + offset, currentVerticesCount);
            }
        }
        break;
    }
    default:
        break;
    }
}
void MainWindow::onFigurePrepared(
    const QPoint &offset, const int &countVerteces, InsertWindow::FigureTypes figureType)
{
    insertAct->setChecked(true);
    lastCheckedColorAction = insertAct;
    this->offset = offset;
    currentVerticesCount = countVerteces;
    this->figureType = figureType;
    currentMode = MODE_FIGURE;
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

    paletteAct = new QAction("Palette", this);
    paletteAct->setStatusTip("Choose color");
    paletteAct->setIcon(QIcon(":/resources/palette.png"));
    paletteAct->setCheckable(true);
    connect(paletteAct, SIGNAL(triggered()), this, SLOT(palette()));

    penWidthAct = new QAction("Width", this);
    penWidthAct->setStatusTip("Set the pen width");
    penWidthAct->setIcon(QIcon(":/resources/pen_width.png"));
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    insertAct = new QAction("Insert", this);
    insertAct->setStatusTip("Insert a figure");
    insertAct->setIcon(QIcon(":/resources/hexagon.png"));
    insertAct->setCheckable(true);
    connect(insertAct, SIGNAL(triggered()), this, SLOT(insert()));

    lineAct = new QAction("Line", this);
    lineAct->setStatusTip("Choose line tool");
    lineAct->setIcon(QIcon(":/resources/line.png"));
    lineAct->setCheckable(true);
    connect(lineAct, SIGNAL(triggered()), this, SLOT(line()));

    fillAct = new QAction("Fill", this);
    fillAct->setStatusTip("Choose fill tool");
    fillAct->setIcon(QIcon(":/resources/fill.png"));
    fillAct->setCheckable(true);
    connect(fillAct, SIGNAL(triggered()), this, SLOT(fill()));

    insert4PolygonAct = new QAction("Square", this);
    insert4PolygonAct->setStatusTip("Insert square");
    insert4PolygonAct->setIcon(QIcon(":/resources/square.png"));
    insert4PolygonAct->setCheckable(true);
    connect(insert4PolygonAct, SIGNAL(triggered()), this, SLOT(insert4Polygon()));

    insert5PolygonAct = new QAction("Pentagon", this);
    insert5PolygonAct->setStatusTip("Insert pentagon");
    insert5PolygonAct->setIcon(QIcon(":/resources/pentagon.png"));
    insert5PolygonAct->setCheckable(true);
    connect(insert5PolygonAct, SIGNAL(triggered()), this, SLOT(insert5Polygon()));

    insert6PolygonAct = new QAction("Hexagon", this);
    insert6PolygonAct->setStatusTip("Insert hexagon");
    insert6PolygonAct->setIcon(QIcon(":/resources/hexagon.png"));
    insert6PolygonAct->setCheckable(true);
    connect(insert6PolygonAct, SIGNAL(triggered()), this, SLOT(insert6Polygon()));

    insert7PolygonAct = new QAction("Heptagon", this);
    insert7PolygonAct->setStatusTip("Insert heptagon");
    insert7PolygonAct->setIcon(QIcon(":/resources/heptagon.png"));
    insert7PolygonAct->setCheckable(true);
    connect(insert7PolygonAct, SIGNAL(triggered()), this, SLOT(insert7Polygon()));

    insert8PolygonAct = new QAction("Octagon", this);
    insert8PolygonAct->setStatusTip("Insert octagon");
    insert8PolygonAct->setIcon(QIcon(":/resources/octagon.png"));
    insert8PolygonAct->setCheckable(true);
    connect(insert8PolygonAct, SIGNAL(triggered()), this, SLOT(insert8Polygon()));

    insert4StarAct = new QAction("Square Star", this);
    insert4StarAct->setStatusTip("Insert square star");
    insert4StarAct->setIcon(QIcon(":/resources/square_star.png"));
    insert4StarAct->setCheckable(true);
    connect(insert4StarAct, SIGNAL(triggered()), this, SLOT(insert4Star()));

    insert5StarAct = new QAction("Pentagonal star", this);
    insert5StarAct->setStatusTip("Insert pentagonal star");
    insert5StarAct->setIcon(QIcon(":/resources/pentagonal_star.png"));
    insert5StarAct->setCheckable(true);
    connect(insert5StarAct, SIGNAL(triggered()), this, SLOT(insert5Star()));

    insert6StarAct = new QAction("Hexagonal star", this);
    insert6StarAct->setStatusTip("Insert hexagonal star");
    insert6StarAct->setIcon(QIcon(":/resources/hexagonal_star.png"));
    insert6StarAct->setCheckable(true);
    connect(insert6StarAct, SIGNAL(triggered()), this, SLOT(insert6Star()));

    insert7StarAct = new QAction("Heptagonal star", this);
    insert7StarAct->setStatusTip("Insert heptagonal star");
    insert7StarAct->setIcon(QIcon(":/resources/heptagonal_star.png"));
    insert7StarAct->setCheckable(true);
    connect(insert7StarAct, SIGNAL(triggered()), this, SLOT(insert7Star()));

    insert8StarAct = new QAction("Octagonal star", this);
    insert8StarAct->setStatusTip("Insert octagonal star");
    insert8StarAct->setIcon(QIcon(":/resources/octagonal_star.png"));
    insert8StarAct->setCheckable(true);
    connect(insert8StarAct, SIGNAL(triggered()), this, SLOT(insert8Star()));

    toolGroup = new QActionGroup(this);
    toolGroup->addAction(lineAct);
    toolGroup->addAction(fillAct);
    toolGroup->addAction(insertAct);
    toolGroup->addAction(insert4PolygonAct);
    toolGroup->addAction(insert5PolygonAct);
    toolGroup->addAction(insert6PolygonAct);
    toolGroup->addAction(insert7PolygonAct);
    toolGroup->addAction(insert8PolygonAct);
    toolGroup->addAction(insert4StarAct);
    toolGroup->addAction(insert5StarAct);
    toolGroup->addAction(insert6StarAct);
    toolGroup->addAction(insert7StarAct);
    toolGroup->addAction(insert8StarAct);

    setKcolorAct = new QAction("Black", this);
    setKcolorAct->setStatusTip("Choose the black color");
    setKcolorAct->setIcon(QIcon(":/resources/set_k_color.png"));
    setKcolorAct->setCheckable(true);
    connect(setKcolorAct, SIGNAL(triggered()), this, SLOT(setKcolor()));

    setRcolorAct = new QAction("Red", this);
    setRcolorAct->setStatusTip("Choose the red color");
    setRcolorAct->setIcon(QIcon(":/resources/set_r_color.png"));
    setRcolorAct->setCheckable(true);
    connect(setRcolorAct, SIGNAL(triggered()), this, SLOT(setRcolor()));

    setRGcolorAct = new QAction("Yellow", this);
    setRGcolorAct->setStatusTip("Choose the yellow color");
    setRGcolorAct->setIcon(QIcon(":/resources/set_rg_color.png"));
    setRGcolorAct->setCheckable(true);
    connect(setRGcolorAct, SIGNAL(triggered()), this, SLOT(setRGcolor()));

    setGcolorAct = new QAction("Green", this);
    setGcolorAct->setStatusTip("Choose the green color");
    setGcolorAct->setIcon(QIcon(":/resources/set_g_color.png"));
    setGcolorAct->setCheckable(true);
    connect(setGcolorAct, SIGNAL(triggered()), this, SLOT(setGcolor()));

    setGBcolorAct = new QAction("Cyan", this);
    setGBcolorAct->setStatusTip("Choose the cyan color");
    setGBcolorAct->setIcon(QIcon(":/resources/set_gb_color.png"));
    setGBcolorAct->setCheckable(true);
    connect(setGBcolorAct, SIGNAL(triggered()), this, SLOT(setGBcolor()));

    setBcolorAct = new QAction("Blue", this);
    setBcolorAct->setStatusTip("Choose the blue color");
    setBcolorAct->setIcon(QIcon(":/resources/set_b_color.png"));
    setBcolorAct->setCheckable(true);
    connect(setBcolorAct, SIGNAL(triggered()), this, SLOT(setBcolor()));

    setBRcolorAct = new QAction("Magenta", this);
    setBRcolorAct->setStatusTip("Choose the magenta color");
    setBRcolorAct->setIcon(QIcon(":/resources/set_br_color.png"));
    setBRcolorAct->setCheckable(true);
    connect(setBRcolorAct, SIGNAL(triggered()), this, SLOT(setBRcolor()));

    setWcolorAct = new QAction("White", this);
    setWcolorAct->setStatusTip("Choose the white color");
    setWcolorAct->setIcon(QIcon(":/resources/set_w_color.png"));
    setWcolorAct->setCheckable(true);
    connect(setWcolorAct, SIGNAL(triggered()), this, SLOT(setWcolor()));

    colorsGroup = new QActionGroup(this);
    colorsGroup->addAction(paletteAct);
    colorsGroup->addAction(setKcolorAct);
    colorsGroup->addAction(setRcolorAct);
    colorsGroup->addAction(setRGcolorAct);
    colorsGroup->addAction(setGcolorAct);
    colorsGroup->addAction(setGBcolorAct);
    colorsGroup->addAction(setBcolorAct);
    colorsGroup->addAction(setBRcolorAct);
    colorsGroup->addAction(setWcolorAct);

    aboutAct = new QAction("About", this);
    aboutAct->setStatusTip("About the application");
    aboutAct->setIcon(QIcon(":/resources/about.png"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    //standard values
    setKcolorAct->setChecked(true);
    lastCheckedColorAction = setKcolorAct;
    lineAct->setChecked(true);
    lastCheckedToolAction = lineAct;
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
    editMenu->addAction(paletteAct);
    editMenu->addAction(penWidthAct);
    editMenu->addSeparator();
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
    mainToolBar->addAction(penWidthAct);
    mainToolBar->addAction(paletteAct);
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
