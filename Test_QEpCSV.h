#ifndef TEST_QEPCSV_H
#define TEST_QEPCSV_H

#include <QTest>
#include <QtCore>
#include <QEpCSV>

/**
 * @brief The Test_QEpCSV class
 */
class Test_QEpCSV: public QObject
{
    Q_OBJECT
private:

    QStringList parseString(const QString &string)
    {
        auto arr = string.toUtf8();
        QBuffer buff(&arr);
        buff.open(QIODevice::ReadOnly);
        QEpCSVReader csv;
        csv.setDevice(&buff);
        return csv.readLine();
    }

private slots:

    void testEmptyString()
    {
        auto values = parseString("");
        QVERIFY(values.empty());
    }

    void testEmptyValues()
    {
        auto values = parseString(";;\n");
        QCOMPARE(values.size(), 3);
    }

    void testSimpleValues()
    {
        auto values = parseString("a;b;c\n");
        QCOMPARE(values.size(), 3);
        QCOMPARE(values.at(0), QString("a"));
        QCOMPARE(values.at(1), QString("b"));
        QCOMPARE(values.at(2), QString("c"));
    }

    void testSimpleEscapedValues()
    {
        auto values = parseString("\"\";\"Some value\";""\n");
        QCOMPARE(values.size(), 3);
        QCOMPARE(values.at(0), QString());
        QCOMPARE(values.at(1), QString("Some value"));
        QCOMPARE(values.at(2), QString());
    }

    void testEscapedValues0() {
        auto values = parseString("\"Test \"\"Value;\"\";\";100.00;Socks\n");
        QCOMPARE(values.size(), 3);
        QCOMPARE(values.at(0), QString("Test \"Value;\";"));
        QCOMPARE(values.at(1), QString("100.00"));
        QCOMPARE(values.at(2), QString("Socks"));
    }

};

QTEST_MAIN(Test_QEpCSV)

#endif // TEST_QEPCSV_H
