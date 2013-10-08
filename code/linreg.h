/*
    Linear Regression with one or multiple variables
    Author: Kan Ouivirach
    Credit: David C. Swaim II, Ph.D.
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
#define BEFORE   3
#define AFTER    4

using namespace std;

struct tooth_color {
    string label;
    vector<double> val;
};

class LinearRegression {
    public:
        LinearRegression();
        ~LinearRegression();

        void read_training_data(char* file_data);
        void read_testing_data(char* file_data);
        void read_tooth_color_data(char* file_data, int mode);
        void print_data();
        void gradient_descent(double alpha, int num_iters, bool norm);
        void print_theta();
        vector<double> get_theta();
        vector<double> get_mean();
        vector<double> get_std();
        vector< vector<double> > get_testing_data();
        vector<double> get_testing_predicted_data();
        void classify(vector< vector<double> > X);
        double distanceCalculate(double x1, double y1, double z1, double x2, double y2, double z2);
        vector<tooth_color> tooth_color_data_before;
        vector<tooth_color> tooth_color_data_after;

    private:
        vector< vector<double> > _data;
        vector< vector<double> > _testing_data;
        vector<double> _mean;
        vector<double> _std;
        vector<double> _predicted_data;
        vector<double> _testing_predicted_data;
        vector<double> _theta;
        
        double string_to_double(string str);
        vector<string> split(string str, string delimiters, int mode);
        double dot_product(vector<double> a, vector<double> b);
        void feature_normalize();
        double compute_cost(vector< vector<double> > X, vector<double> y, vector<double> theta);
};

#endif
// end of linreg.h

