//
// Created by Michael on 6/2/2022.
//

#include "SectorComponent.hpp"
#include "Sector.hpp"

void cookie::SectorComponent::onNewSector(std::shared_ptr<Sector> sector)  {
	sectors.insert(std::move(sector));
}

void cookie::SectorComponent::clear()  {
	sectors.clear();
}