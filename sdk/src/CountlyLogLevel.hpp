#ifndef __COUNTLY_LOG_LEVEL_HPP
#define __COUNTLY_LOG_LEVEL_HPP

namespace countly {

class LogLevel {
public:
	typedef enum {
		TRACE, DEBUG, INFO, WARN, SEVERE
	} Level;
};

}

#endif
