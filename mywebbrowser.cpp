#include "mywebbrowser.h"

MyWebBrowser::MyWebBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    mainFrame = new QFrame(this);

    mainVBox = new QVBoxLayout();
// tabbar = new QTabBar;
webTabs = new QTabWidget();

line = new QLineEdit();


webTabs->tabBar()->setEnabled(true);
pageVBox = new QVBoxLayout;
pageHBox = new QHBoxLayout;
webTabs->tabBar()->show();
    mainFrame->setLayout(mainVBox);
    setCentralWidget(mainFrame);

    fileMenu = new QMenu("File");
    editMenu = new QMenu("Edit");
    helpMenu = new QMenu("Help");
addTabAction = new QAction(this);
addTabAction->setText("Add tab");
fileMenu->addAction(addTabAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(helpMenu);

    but = new QPushButton("gopress");

    // webView = new QWebEngine(this);
    // webView->setParent(this);
    webView = new QWebEngineView;


    // webTabs->addTab(webView, "web");
    webTabs->setMovable(true);
    webTabs->show();
    webView->show();

    linesVec.append(line);
    gobutVec.append(but);
    webVec.append(webView);
    urlVar = QUrl::fromEncoded("https://www.google.com");
    webView->load(urlVar);
    pageHBox->addWidget(line);
    pageHBox->addWidget(but);
    pageVBox->addLayout(pageHBox);
    pageVBox->addWidget(webView);

        QWidget* w1=new QWidget(this);
        QVBoxLayout* lay1=new QVBoxLayout;
        lay1->setSizeConstraint(QLayout::SetMaximumSize);
        w1->setLayout(lay1);
        webTabs->addTab(w1, "new");
        lay1->addLayout(pageVBox);
        // mainVBox->addWidget(line);
mainVBox->addWidget(webTabs);

connect(addTabAction, SIGNAL(triggered()), this, SLOT(yeni_sekme()));
connect(but, SIGNAL(clicked(bool)), this, SLOT(load_uri_or_file()));

// connect(gobutton, SIGNAL(clicked(bool)), this, SLOT(load_uri_or_file(addrline, tabWebView)));
connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(url_changed()));
connect(webView->page(), SIGNAL(linkHovered(QString)), this, SLOT(link_hovered()));
/*
connect(downitem, &QWebEngineDownloadItem::stateChanged,
        this, &MyWebBrowser::downloadRequested);
        */
/*
if(downitem->state() == QWebEngineDownloadItem::DownloadRequested) {
    connect(downitem, &QWebEngineDownloadItem::stateChanged,
            this, &MyWebBrowser::downloadRequested);
}
*/
connect(webView->page()->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
               this, SLOT(downloadRequested(QWebEngineDownloadItem*)));

}

MyWebBrowser::~MyWebBrowser()
{
}

void MyWebBrowser::downloadRequested(QWebEngineDownloadItem* downloaditem)
{
    std::cout << "download request\n";
    auto ad = webView->page()->url();
    // auto ad = webView->page()->profile()->downloadPath();
    std::cout << ad.toString().toStdString() << "\n";
    // auto ad = downitem->downloadDirectory();
    // webView->page()->download(ad, "kek");
    auto hes = downloaditem->url();
    std::cout << "ditem: " << hes.toString().toStdString() << "\n";
    // downloaditem->accept();
    QFileDialog *fd = new QFileDialog();

    QString path = fd->getSaveFileName(this, tr("Save as"), QDir(downloaditem->downloadDirectory()).filePath(downloaditem->downloadFileName()));
    downloaditem->setDownloadDirectory(QFileInfo(path).path());
    downloaditem->setDownloadFileName(QFileInfo(path).fileName());
    downloaditem->accept();
}

void MyWebBrowser::url_changed()
{
    std::cout << "Url changed\n";
    if(webView->url().isLocalFile()) {
        std::cout << "Local\n";
    }
    int n = webTabs->currentIndex();
    QString st = webVec.at(n)->url().toString();
    linesVec.at(n)->setText(st);
}

void MyWebBrowser::yeni_sekme()
{
    QWidget* wid1=new QWidget(this);
        QVBoxLayout* layvbox = new QVBoxLayout;
        layvbox->setSizeConstraint(QLayout::SetMaximumSize);
        wid1->setLayout(layvbox);

    mainvb = new QVBoxLayout;
    barBox = new QHBoxLayout;
    addrline = new QLineEdit;
    gobutton = new QPushButton("go");
    tabWebView = new QWebEngineView;


    tabWebView->show();
    wid1->show();
    barBox->addWidget(addrline);
    barBox->addWidget(gobutton);
    mainvb->addLayout(barBox);
    mainvb->addWidget(tabWebView);
    layvbox->addLayout(mainvb);
    webTabs->addTab(wid1, "New Tab");

    connect(tabWebView, SIGNAL(urlChanged(QUrl)), this, SLOT(url_changed()));
    connect(tabWebView->page(), SIGNAL(linkHovered(QString)), this, SLOT(link_hovered()));

    connect(gobutton, SIGNAL(clicked(bool)), this, SLOT(load_uri_or_file()));
    connect(tabWebView->page()->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
                   this, SLOT(downloadRequested(QWebEngineDownloadItem*)));
    linesVec.append(addrline);
    gobutVec.append(gobutton);
    webVec.append(tabWebView);
    // tabWebView->focusWidget();

}

void MyWebBrowser::link_hovered()
{
    std::cout << "link hovered\n";

   // emit linkH
    int i = webTabs->currentIndex();
    if(webVec.at(i)->page()->NavigationTypeLinkClicked)
    {
        std::cout << "Link clicked!\n";
    }
}

void MyWebBrowser::load_uri_or_file()
{
    // warning: gobutton not handled
    std::cout << "func used\n";
    int n = webTabs->currentIndex();
    QString adr = linesVec.at(n)->text();
    // QUrl url = QUrl(adr);
    QUrl url = QUrl::fromUserInput(adr);

    std::cout << "tab no: " << n << "\n";
    webVec.at(n)->load(url);

    // tabWebView->load(url);
}
