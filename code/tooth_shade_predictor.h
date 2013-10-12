/*
 * Tooth Shade Predictor
 * Author: Kan Ouivirach
 */

#ifndef _TOOTH_SHADE_PREDICTOR_H_
#define _TOOTH_SHADE_PREDICTOR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

#define TRAINING         1
#define TESTING          2
#define BEFORE_BLEECHING 3 
#define AFTER_BLEECHING  4

using namespace std;

struct vita {
    string label;
    vector<double> val;
};

class ToothShadePredictor {
    public:
        ToothShadePredictor();
        ~ToothShadePredictor();

    private:

};

#endif
// end of tooth_shade_predictor.h

