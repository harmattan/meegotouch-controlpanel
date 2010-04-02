#ifndef DUIWINDOW_H
#define DUIWINDOW_H

class DuiWindow: public QObject {
    public:
        void raise();
        void lower();

        bool isRaised();

    private:
        bool m_IsRaised;
};

#endif // DUIWINDOW_H
