/*
 * Linear Regression with one or multiple variables
 * Author: Kan Ouivirach
 * Credit: David C. Swaim II, Ph.D.
 */

#ifndef _LINREG_H_
#define _LINREG_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

#define TRAINING 1
#define TESTING  2

using namespace std;

class LinearRegression {
    public:
        LinearRegression();
        LinearRegression( double alpha, int num_iters, bool norm );
        ~LinearRegression();
        
        void set_training_data( char* data_file );
        void set_testing_data( char* data_file );

        void run_gradient_descent();

        // Mode: testing or estimating
        double compute_MSE();

        double estimate( vector<double> data );
        
        void print_training_data();
        void print_testing_data();
        void print_theta();

        vector< vector<double> > get_training_data();
        vector< vector<double> > get_testing_data();
        vector<double> get_theta();
        vector<double> get_mean();
        vector<double> get_std();

    private:
        double _alpha;
        int _num_iters;
        bool _norm;
        vector< vector<double> > _training_data;
        vector< vector<double> > _testing_data;
        vector<double> _predicted_training_data;
        vector<double> _predicted_testing_data;
        vector<double> _theta;
        vector<double> _mean;
        vector<double> _std;
        
        double string_to_double( string str );

        // Mode: training and testing (add 1 to the first column in training mode)
        vector<string> split( string str, string delimiters, int mode );

        double compute_dot_product( vector<double> a, vector<double> b );
        void normalize_training_data();
        double compute_cost( vector< vector<double> > X, vector<double> y, vector<double> theta );
};

#endif
// end of linreg.h

