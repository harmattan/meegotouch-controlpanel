#ifndef DCPTIME_H
#define DCPTIME_H

class DcpTime {

public:
	DcpTime() :
		m_Hour(0),
		m_Min(0),
		m_Sec(0)
 	{}

	void setTime(int hour, int min = 0, int sec = 0);

	void setSystemTime();

	int hour();
	int min();
	int sec();

private:

	int m_Hour;
	int m_Min;
	int m_Sec;
};


inline int DcpTime::hour() {
	return m_Hour;
}

inline int DcpTime::min() {
	return m_Min;
}

inline int DcpTime::sec() {
	return m_Sec;
}

#endif // DCPTIME_H
