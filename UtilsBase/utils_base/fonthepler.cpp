#include "fonthepler.h"

#include <QDebug>
//#include <QCoreApplication>
#include <QFontDatabase>






FontHepler* FontHepler::_fontHelper = nullptr;


FontHepler *FontHepler::instance()
{
    if(!_fontHelper)
    {
        _fontHelper = new FontHepler();
    }

    return _fontHelper;
}

void FontHepler::initFont()
{
    if(_fontHelper)
    {
        //加载字体库
        int fontId = QFontDatabase::addApplicationFont(":/font/SourceHanSans-Bold.otf");
        // 获取字体族名称
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "FontHepler::initFont() = " << fontName;

        fontId = QFontDatabase::addApplicationFont(":/font/SourceHanSans-Regular.otf");
        fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "FontHepler::initFont() = " << fontName;


        // 在 QSS 中使用外部字体
//        QString styleSheet = "QWidget { font-family: '" + Alibaba PuHuiTi + "'; }";
//        qApp->setStyleSheet(styleSheet);

    }
}


FontHepler::FontHepler(QObject *parent)
    : QObject{parent}
{






}
