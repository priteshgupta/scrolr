#ifndef TRACKER_H_
#define TRACKER_H_

/*
 * This class is reponsible for running the tracking application
 */
class Tracker
{
public:
    Tracker();
    void track();
    bool m_foundFile;
};

#endif // TRACKER_H_
