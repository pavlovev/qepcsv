#ifndef QEPCSV_GLOBAL_H
#define QEPCSV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QEPCSV_LIBRARY)
#  define QEPCSV_EXPORT Q_DECL_EXPORT
#else
#  define QEPCSV_EXPORT Q_DECL_IMPORT
#endif

#endif // QEPCSV_GLOBAL_H
