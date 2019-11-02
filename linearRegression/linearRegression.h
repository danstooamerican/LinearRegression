#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "../data.h"
#include "../input/fileReader.h"

extern DataPoint calculate(DataArray data);

extern ExactDataPoint calculateExact(ExactDataArray data);

#endif