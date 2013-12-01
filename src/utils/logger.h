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

static inline void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

static inline void logMessage( const std::string &msg)
{
	std::cout << msg << std::endl;
}

#endif /* LOGGER_H_ */
