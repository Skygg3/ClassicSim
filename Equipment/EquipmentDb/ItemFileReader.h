#ifndef ITEMFILEREADER_H
#define ITEMFILEREADER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>

class Item;

class ItemFileReader: public QObject {
public:
    ItemFileReader(QObject* parent = 0):
        QObject(parent) {}

    void read_items(QVector<Item *> &items, const QString &path);

protected:
    void item_file_handler(QXmlStreamReader &reader, QVector<Item*>& items);

    void info_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void class_restriction_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void stats_element_reader(QXmlStreamReader &reader, QVector<QPair<QString, QString>> &stats);
    void proc_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &procs);

    void add_mandatory_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);
    void add_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);

    void create_item(QVector<Item *> &items, QMap<QString, QString> &item_map, QVector<QPair<QString, QString> > &stats, QVector<QMap<QString, QString>> &procs);

    void extract_info(QMap<QString, QString> &item, QMap<QString, QString> &info);
    void extract_stats(QMap<QString, QString> &item, QMap<QString, QString> &stats);
    void extract(QVector<QString> handled_keys, QMap<QString, QString> &source, QMap<QString, QString> &target);

    void warn_remaining_keys(QMap<QString, QString> &item);
private:
};

#endif // ITEMFILEREADER_H