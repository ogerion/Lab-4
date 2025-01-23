#include <QApplication>
#include <sequence/LinkedListSequence.h>
#include <iostream>
#include <string>
#include"UnorderedMap.h"
#include "UI/mainwindow.h"
#include "Game.h"
#include "IDictionary.h"
#include "tests/testIDictionary.h"
#include "tests/testGame.h"
#include "tests/testGraph.h"
#include "UnorderedMapGraph.h"
int main(int argc, char *argv[])
{    

    testGameBot();
    testIDictionary();
    testGraph();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
