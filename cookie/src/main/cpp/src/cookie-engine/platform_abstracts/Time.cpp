//
// Created by Michael on 4/15/2022.
//


#include "Time.hpp"

std::chrono::steady_clock::time_point cookie::Time::getProgramTime() {
	return std::chrono::steady_clock::now();
}

