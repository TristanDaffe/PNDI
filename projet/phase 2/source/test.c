#include "classificationPerformances.h"

void main() {

	int realClasses[13] = { 5, 2, 5, 3, 5, 3, 2, 4, 4, 6, 1, 2, 4 };
	int estimateClasses[13] = { 5, 5, 1, 2, 1, 3, 2, 4, 6, 6, 6, 6, 4, };

	displayResultsByClass(realClasses, estimateClasses, 13);
	displayAccuracy(realClasses, estimateClasses, 13);
	displayConfusionMatrix(realClasses, estimateClasses, 13);
}