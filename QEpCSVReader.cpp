#include "QEpCSVReader.h"

QEpCSVReader::QEpCSVReader(QObject *parent): QObject(parent)
{
}

QIODevice *QEpCSVReader::device() const
{
    return m_in.device();
}

void QEpCSVReader::setDevice(QIODevice *device)
{
    m_in.setDevice(device);
}

void QEpCSVReader::setCodec(QTextCodec *codec)
{
    m_in.setCodec(codec);
}

QStringList QEpCSVReader::readLine()
{
    constexpr QChar escapeChar = '"';
    constexpr QChar CR = '\r';
    constexpr QChar LF = '\n';

    QStringList values;
    if (m_in.atEnd()) {
        return values;
    }

    auto lineData = m_in.readLine();
    lineData.push_back(LF);

    QChar c,cc;
    QTextStream lineStream(&lineData);
    while (!lineStream.atEnd()) {
        lineStream >> c;
        if (c == m_separator) {
            if (!m_escapedValue) {
                appendValue(values);
                continue;
            }

        } else if (c == LF) {
            appendValue(values);
            break;

        } else if (c == escapeChar) {
            if (m_escapedValue) {
                if (!lineStream.atEnd()) {
                    lineStream >> cc;
                    if (cc != escapeChar) {
                        m_escapedValue = false;
                        lineStream.seek(lineStream.pos() - 1);
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
    if (!m_valueBuffer.isEmpty()) {
        appendValue(values);
    }
    return values;
}

void QEpCSVReader::push(QChar c)
{
    m_valueBuffer.push_back(c);
}

void QEpCSVReader::appendValue(QStringList &values)
{
    values.push_back(m_valueBuffer);
    m_valueBuffer.clear();
    m_escapedValue = false;
}

QChar QEpCSVReader::separator() const
{
    return m_separator;
}

void QEpCSVReader::setSeparator(QChar separator)
{
    m_separator = separator;
}
