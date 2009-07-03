#ifndef DCPLANGUAGE_H
#define DCPLANGUAGE_H
namespace DcpLanguage 
{
    enum {
            None = -1,
            Main = 0,
            Display,
            Keyboard
    };
    const int NoReferer = -1;

    const QString KeyMain = "Main";
    const QString KeyKeyboard = "Keyboard";
    const QString KeyDisplay = "Display";
}
#endif // DCPLANGUAGE_H
