#include "QEpCSVReader.h"

QEpCSVReader::QEpCSVReader(QObject *parent): QObject(parent)
{
}

QIODevice *QEpCSVReader::device() const
{
    return m_device;
}

void QEpCSVReader::setDevice(QIODevice *device)
{
    m_device = device;
}

QStringList QEpCSVReader::readLine()
{

    constexpr char escapeChar = '"';
    constexpr char CR = '\r';

    QStringList values;
    char c,cc;
    while (m_device->getChar(&c)) {
        if (c == m_separator) {
            if (!m_escapedValue) {
                appendValue(values);
                continue;
            }
        } else if (c == '\n') {
            appendValue(values);
            continue;
        } else if (c == escapeChar) {
            if (m_escapedValue) {
                if (m_device->getChar(&cc)) {
                    if (cc != escapeChar) {
                        m_escapedValue = false;
                        m_device->ungetChar(cc);
                        continue;
                    }
                } else {
                    m_escapedValue = false;
                    continue;
                }
            } else {
                m_escapedValue = true;
                continue;
            }
        } else if (c == CR) {
            continue; // Allways skip this char.
        }
        push(c);
    }
    return values;
}

void QEpCSVReader::push(char c)
{
    m_valueBuffer.push_back(c);
    m_state = Value;
}

void QEpCSVReader::appendValue(QStringList &values)
{
    values.push_back(QString::fromUtf8(m_valueBuffer));
    m_valueBuffer.clear();
    m_escapedValue = false;
    m_state = Start;
}

char QEpCSVReader::separator() const
{
    return m_separator;
}

void QEpCSVReader::setSeparator(char separator)
{
    m_separator = separator;
}
