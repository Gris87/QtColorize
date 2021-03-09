#ifndef QTCOLORIZELOG_H
#define QTCOLORIZELOG_H



#include <QDebug>



// #define QTCOLORIZE_LOG_ENABLED
#ifdef QTCOLORIZE_LOG_ENABLED
#define COLORIZE_LOG(params) qDebug params
#else
#define COLORIZE_LOG(params)
#endif



#endif // QTCOLORIZELOG_H
