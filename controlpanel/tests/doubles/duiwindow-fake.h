#ifndef DUIWINDOW_H
#define DUIWINDOW_H

/* Fake DuiWindow
 *
 * See duiapplicationwindow.h on details of how to use it.
 *
 */

class DuiWindow: public QObject {
    public:
        void raise();
        void lower();

        bool isRaised();

    private:
        bool m_IsRaised;
};

#endif // DUIWINDOW_H
