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
    Q_PROPERTY(char separator READ separator WRITE setSeparator)
public:
    explicit QEpCSVReader(QObject *parent = nullptr);

    QIODevice *device() const;
    void setDevice(QIODevice *device);

    char separator() const;
    void setSeparator(char separator);

    /**
     * @brief Read a line (row) and parse it.
     * @return String values of row.
     */
    QStringList readLine();

private:

    void push(char c);
    void appendValue(QStringList &values);

    enum State{
        Start,
        Value
    };

    QIODevice *m_device = nullptr;

    State m_state = Start;
    bool m_escapedValue = false;
    char m_separator = ';';
    QByteArray m_valueBuffer;
};

#endif // QEPCSVREADER_H
