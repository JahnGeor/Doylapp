#ifndef WRITER_H
#define WRITER_H
#include <QString>
#include <QFile>
#include <QDir>
class Writer
{
public:
    int id;
    QString fName;
    QString name;
    QString sName;
    QString bio;
    QString date;
    QString country;

    Writer();
    void findw(int x);
    void set(QString s);
    void setBio(int x);
};

int idsearch(QString z);
void recheck(int id);
int idsearch_2(QString z, int i);


class Art {
public:
    int id;
    QString name;
    QString date;
    int idw;
    QString info;
    Art();
    QString genre;
    void finda(int id, int idw);
    void set(QString s);


};

int removeFolder(QDir & dir);

#endif // WRITER_H
