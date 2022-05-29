//
// Created by Antiufieiev Michael on 16.08.2021.
//

#ifndef COOKIE_ENGINE_ERRORHANDLER_HPP
#define COOKIE_ENGINE_ERRORHANDLER_HPP

#include <exception>

class ErrorHandler {
	virtual void checkForErrorAndPrint() = 0;
	virtual void logException(const std::exception &exception) = 0;
};


#endif //COOKIE_ENGINE_ERRORHANDLER_HPP
