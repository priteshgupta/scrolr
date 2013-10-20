#ifndef TRACKER_H_
#define TRACKER_H_

#include <boost/thread.hpp>

/*
 * This class is reponsible for running the tracking application
 */
class Tracker
{
public:
    Tracker();
    ~Tracker();
    void track();
    void initialize();
    void runThread();
    bool m_foundFile;
    bool m_isTracking;
    
    boost::thread* m_thread;
};

#endif // TRACKER_H_
