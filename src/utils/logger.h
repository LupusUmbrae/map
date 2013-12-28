/*
 * logger.h
 *
 *  Created on: 30 Nov 2013
 *      Author: Robin
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string.h>
#include <ostream>
#include <iostream>

#include <SDL2/SDL.h>

//! Static method to log an SDL error with a custom string to helpo location
/*!
 *
 * @param os Output stream to print the message to
 * @param msg Custom message
 */
static inline void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

//! Static method to log a custom string
static inline void logMessage(const std::string &msg) {
	std::cout << msg << std::endl;
}

#endif /* LOGGER_H_ */
