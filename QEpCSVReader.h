#ifndef QEPCSVREADER_H
#define QEPCSVREADER_H

#include "QEpCSV_global.h"
#include <QtCore>

/**
 * @brief Simple CSV parser for Qt.
 */
class QEPCSV_EXPORT QEpCSVReader: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QIODevice* device READ device  WRITE setDevice)
    Q_PROPERTY(QChar separator READ separator WRITE setSeparator)
public:
    explicit QEpCSVReader(QObject *parent = nullptr);

    QIODevice *device() const;
    void setDevice(QIODevice *device);

    void setCodec(QTextCodec *codec);

    QChar separator() const;
    void setSeparator(QChar separator);

    /**
     * @brief Read a line (row) and parse it.
     * @return String values of row.
     */
    QStringList readLine();

private:

    void push(QChar c);
    void appendValue(QStringList &values);

    enum State{
        Start,
        Value
    };

    QIODevice *m_device = nullptr;
    QTextStream m_in;

    bool m_escapedValue = false;
    QChar m_separator = ';';
    QString m_valueBuffer;
};

#endif // QEPCSVREADER_H
