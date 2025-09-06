#include "QSpellDatabaseWindow.hpp"

const QString QAbstractDatabaseWindow::FixStart = QString("<font color=#7B68EE>");
const QString QAbstractDatabaseWindow::FixEnd = QString("</font>");
const QString QAbstractDatabaseWindow::HighlightStart = QString("<span style=\"background-color: #FFEFD5\">");
const QString QAbstractDatabaseWindow::HighlightEnd = QString("</span>");

QHash<QString, QAbstractDatabaseWindow*> QAbstractDatabaseWindow::Databases;
HexBitset<QSpellDatabaseWindow::Number> QSpellDatabaseWindow::RevisedBitset;
