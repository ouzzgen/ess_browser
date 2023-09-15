#ifndef MYWEBBROWSER_H
#define MYWEBBROWSER_H

#include <iostream>
#include <QMainWindow>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QBoxLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QAction>
#include <QWidget>
#include <QtGui>
#include <QVector>

class MyWebBrowser : public QMainWindow
{
    Q_OBJECT

public:
    MyWebBrowser(QWidget *parent = 0);
    ~MyWebBrowser();

private slots:
    void yeni_sekme();
    void downloadRequested(QWebEngineDownloadItem* downloaditem);

public slots:
    void load_uri_or_file();
    void url_changed();
    void link_hovered();
private:
    QFrame *mainFrame;
    QVBoxLayout *mainVBox;
    QHBoxLayout *hBox;
    QTabBar *tabbar;
    QMenu *fileMenu, *editMenu, *helpMenu;
    QAction *addTabAction;
    QTabWidget *webTabs;
    QWebEngineView *webView;

    QPushButton *but;
    QUrl urlVar;
    // QScopedPointer<QWebEngineProfile> m_profile;

QLineEdit *line;
QVBoxLayout *pageVBox;
QHBoxLayout *pageHBox;
// yeni sekme
QVBoxLayout *mainvb = new QVBoxLayout;
QHBoxLayout *barBox = new QHBoxLayout;
QLineEdit *addrline = new QLineEdit;
QPushButton *gobutton = new QPushButton;
   QWebEngineView *tabWebView;

   QVector<QLineEdit*> linesVec;
   QVector<QPushButton*> gobutVec;
   QVector<QWebEngineView*> webVec;
};

#endif // MYWEBBROWSER_H
