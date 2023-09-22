#ifndef FONTHEPLER_H
#define FONTHEPLER_H

#include <QObject>

class FontHepler : public QObject
{
    Q_OBJECT
public:


public:
    /*获取单列类的指针*/
    static FontHepler* instance();

    //初始化字体对象
    void initFont();



private:



    //默认构造函数,传入字体文件+字体名称
    explicit FontHepler(QObject *parent = 0);

private:
    //字体类
    static FontHepler* _fontHelper;
    //图形字体索引
    static int iconFontIndex;


};

#endif // FONTHEPLER_H
