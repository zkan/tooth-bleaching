/*
 * Tooth Shade Predictor
 * Author: Kan Ouivirach
 */

#ifndef _TOOTH_SHADE_PREDICTOR_H_
#define _TOOTH_SHADE_PREDICTOR_H_

#define BEFORE_BLEECHING 1
#define AFTER_BLEECHING  2

#include "linreg.h"

struct vita {
    string label;
    vector<double> val;
};

class ToothShadePredictor {
    public:
        ToothShadePredictor();
        ~ToothShadePredictor();
        
        void train( char* L_training_data, char* a_training_data, char* b_training_data );
        void test( char* L_testing_data, char* a_testing_data, char* b_testing_data );
        vector<double> estimate( vector<double> data );
        
        void train2weeks( char* L_2weeks_training_data, char* a_2weeks_training_data, char* b_2weeks_training_data );
        void test2weeks( char* L_2weeks_testing_data, char* a_2weeks_testing_data, char* b_2weeks_testing_data );
        vector<double> estimate2weeks( vector<double> data );
        
        // Data before and data after must have the same dimension.
        double compute_delta_E( vector<double> data_before, vector<double> data_after );
        
        // Mode: before and after bleeching
        void set_standard_vita_data( char* data_file, int mode );
       
        // Mode: before and after bleeching
        string map_to_vita( double L, double a, double b, int mode );

        vector<vita> get_standard_vita_data_before();
        vector<vita> get_standard_vita_data_after();

        void print_vMSE();
        void print_vMSE_2weeks();

    private:
        LinearRegression _L_model;
        LinearRegression _a_model;
        LinearRegression _b_model;
        LinearRegression _L_2weeks_model;
        LinearRegression _a_2weeks_model;
        LinearRegression _b_2weeks_model;
        vector<double> _vMSE;
        vector<double> _vMSE_2weeks;
        vector<vita> _standard_vita_data_before;
        vector<vita> _standard_vita_data_after;

        double string_to_double( string str );
        vector<string> split( string str, string delimiters );
};

#endif
// end of tooth_shade_predictor.h

