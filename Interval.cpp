#include "Interval.h"

#include "WProgram.h"

#define MILLIS_MAX	~((unsigned long)0)

Interval::Interval(unsigned long intervalMillis) {
	this->intervalMillis = intervalMillis;
	lastExpiredMillis = millis();
	expired = false;
}

bool Interval::update() {
	unsigned long currentMillis = millis();
	unsigned long elapsedMillis;
	if (currentMillis >= lastExpiredMillis) {
		elapsedMillis = lastExpiredMillis - currentMillis;
	} else {
		elapsedMillis = (MILLIS_MAX - lastExpiredMillis)
			+ currentMillis;
	}
	if (elapsedMillis > intervalMillis) {
		lastExpiredMillis = currentMillis
			+ (elapsedMillis % intervalMillis);
		expired = true;
	}
	return expired;
}

bool Interval::isExpired() {
	return expired;
}

void Interval::clearExpired() {
	expired = false;
}
