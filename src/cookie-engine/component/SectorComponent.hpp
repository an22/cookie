//
// Created by Michael on 6/2/2022.
//

#ifndef COOKIE_ENGINE_SECTORCOMPONENT_HPP
#define COOKIE_ENGINE_SECTORCOMPONENT_HPP

#include <unordered_set>
#include <memory>
#include "Component.hpp"
#include "Sector.hpp"


namespace cookie {
	class SectorComponent : public Component {
	private:
		std::unordered_set<std::shared_ptr<Sector>> sectors;
	public:
		void onNewSector(std::shared_ptr<Sector> sector);
		void clear();
	};
}


#endif //COOKIE_ENGINE_SECTORCOMPONENT_HPP
