#ifndef MWINDOW_H
#define MWINDOW_H

/* Fake MWindow
 *
 * See mapplicationwindow.h on details of how to use it.
 *
 */

class MWindow: public QObject {
    public:
        void raise();
        void lower();

        bool isRaised();

    private:
        bool m_IsRaised;
};

#endif // MWINDOW_H
