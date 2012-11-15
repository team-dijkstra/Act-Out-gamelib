
#include "trivialterritoryfilter.h"

bool TerritoryPassFilter::operator()(Territory *) {
    return true;
}

bool TerritoryBlockFilter::operator()(Territory *) {
    return false;
}
