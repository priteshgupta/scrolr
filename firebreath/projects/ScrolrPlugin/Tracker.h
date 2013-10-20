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
    void runThread();
    void initialize();
    void runInitialize();
    bool m_foundFile;
    bool m_isTracking;
    boost::thread* m_thread;
    
    // The current offsets
    int yOffset;
    int xOffset;

    // Initial values for x and y, set in the initialize
    int yInit;
    int xInit;
};

#endif // TRACKER_H_
