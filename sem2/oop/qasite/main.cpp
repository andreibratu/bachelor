#include "mainwindow.h"
#include <QApplication>

#include <QVector>
#include "question.h"
#include "answer.h"
#include "store.h"
#include "userwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Store *store = new Store(&a);
    MainWindow w{store};
    for(auto user : store->getUsers())
    {
        UserWindow* window = new UserWindow(store, user, &w);
        window->show();
    }
    store->init();
    w.show();
    return a.exec();
}
