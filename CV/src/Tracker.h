#ifndef TRACKER_H_
#define TRACKER_H_

/*
 * This class is reponsible for running the tracking application
 */
class Tracker
{
public:
    Tracker();
    ~Tracker();
    void track();
    bool m_foundFile;
    bool m_isTracking;
};

#endif // TRACKER_H_
