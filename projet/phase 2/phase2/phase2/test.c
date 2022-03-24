#include "classificationPerformances.h"

void main() {

	int realClasses[8] = { 5, 2, 5, 3, 5, 3, 2, 4 };
	int estimateClasses[8] = { 5, 5, 1, 2, 1, 3, 2, 4 };

	displayResultsByClass(realClasses, estimateClasses, 8);
}