#ifndef FONTHEPLER_H
#define FONTHEPLER_H

#include <QObject>
/*Qt 对字体的使用
 * 1. qt 加载字体库
 * 2. qss中使用第三方的字体库
 * https://blog.csdn.net/weixin_43165135/article/details/129929272
 *
*/




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
