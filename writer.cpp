#include "writer.h"
#include <QDebug>
#include <QDir>
Writer::Writer()
{

}

int idsearch(QString z) {
    Writer w;
    QString s, x;
    QStringList lst;
    QFile file("data//writers.txt");
    if(file.open(QIODevice::ReadOnly)) {
        while(!file.atEnd()) {
        s = file.readLine();
        s.remove("\r\n");
        lst = s.split(" ");

        x = lst.at(1)+" "+lst.at(2)+" "+lst.at(3);

        if (x == z) {
            file.close();
            return lst.at(0).toInt();
        }
        }
    }

    file.close();
    return 0;

}


Art::Art() {


}

void Writer::set(QString s) {
    QStringList lst = s.split(" ");
    id = lst.at(0).toInt();
    fName = lst.at(1);
    name = lst.at(2);
    sName = lst.at(3);
    date = lst.at(4);
    country = lst.at(5);
    setBio(id);
}

void Art::set(QString s) {
    QStringList lst = s.split(" ");
    id = lst.at(0).toInt();
    name = lst.at(1);
    date = lst.at(2);
    genre = lst.at(3);
    idw = lst.at(4).toInt();
    QFile file("data//"+QString::number(idw)+"//"+QString::number(id)+".txt");
    if(file.open(QIODevice::ReadOnly)) {
        info = file.readAll();
    }
    file.close();
}

void Art::finda(int idx, int idwr) {
    QString s;
    QStringList lst;
    QFile file("data//"+QString::number(idwr)+"//"+"art.txt");
    if(file.open(QIODevice::ReadOnly)) {
        while(!file.atEnd()) {
        s = file.readLine();
        s.remove("\n");
        s.remove("\r");
        lst = s.split(" ");

        if(lst.at(0).toInt() == idx) {

            set(s);
            file.close();
            break;
        }
    }

}
}

void Writer::setBio(int id) {
    QFile file("data//"+ QString::number(id)+"//bio.txt");
    if(file.open(QIODevice::ReadOnly)) {
        bio = file.readAll();
    }
    file.close();
}

    void Writer:: findw(int x) {
    QFile file("data//writers.txt");
    QString s;
    QStringList lst;
    Writer w;
    if(file.open(QIODevice::ReadOnly)) {
        while(!file.atEnd()) {
        s = file.readLine();
        s.remove("\n");
        s.remove("\r");
        lst = s.split(" ");

        if(lst.at(0).toInt() == x) {
        set(s); file.close(); break;
        }
        }
    }

}

int idsearch_2(QString z, int i) {
    z.replace(" ", "_");
    Art a;
    QString s, x;
    QStringList lst;
    QFile file("data//"+QString::number(i)+"//art.txt");
    qDebug() << "--";
    if(file.open(QIODevice::ReadOnly)) {

        while(!file.atEnd()) {

        s = file.readLine();
        s.remove("\n");
        lst = s.split(" ");

        qDebug() << "-!-";

        if (lst.at(1) == z) {
            qDebug() << "---";
            file.close();
            qDebug() << "!" << lst.at(0).toInt();
            return lst.at(0).toInt();
        } else qDebug() << "----";
        }
    } else qDebug() << "war";

    file.close();
    return 0;

}



int removeFolder(QDir & dir)
{
  int res = 0;

  QStringList lstDirs = dir.entryList(QDir::Dirs |
                  QDir::AllDirs |
                  QDir::NoDotAndDotDot);

  QStringList lstFiles = dir.entryList(QDir::Files);


  foreach (QString entry, lstFiles)
  {
   QString entryAbsPath = dir.absolutePath() + "/" + entry;
   QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
   QFile::remove(entryAbsPath);
  }


  foreach (QString entry, lstDirs)
  {
   QString entryAbsPath = dir.absolutePath() + "/" + entry;
   QDir dr(entryAbsPath);
   removeFolder(dr);
  }


  if (!QDir().rmdir(dir.absolutePath()))
  {
    res = 1;
  }
  return res;
}
