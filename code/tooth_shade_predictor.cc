#include "tooth_shade_predictor.h"

ToothShadePredictor::ToothShadePredictor() {
}

ToothShadePredictor::~ToothShadePredictor() {
}

void ToothShadePredictor::train( char* L_training_data, char* a_training_data, char* b_training_data ) {
    this->_L_model.set_training_data( L_training_data );
    this->_a_model.set_training_data( a_training_data );
    this->_b_model.set_training_data( b_training_data );
    
    this->_L_model.run_gradient_descent();
    this->_a_model.run_gradient_descent();
    this->_b_model.run_gradient_descent();
}

void ToothShadePredictor::test( char* L_testing_data, char* a_testing_data, char* b_testing_data ) {
    this->_L_model.set_testing_data( L_testing_data );
    this->_a_model.set_testing_data( a_testing_data );
    this->_b_model.set_testing_data( b_testing_data );
    
    this->_vMSE.push_back( this->_L_model.compute_MSE() );
    this->_vMSE.push_back( this->_a_model.compute_MSE() );
    this->_vMSE.push_back( this->_b_model.compute_MSE() );
}

vector<double> ToothShadePredictor::estimate( vector<double> data ) {
    vector<double> results;
    
    results.push_back( this->_L_model.estimate( data ) );
    results.push_back( this->_a_model.estimate( data ) );
    results.push_back( this->_b_model.estimate( data ) );
    
    return results;
}

void ToothShadePredictor::train2weeks( char* L_2weeks_training_data, char* a_2weeks_training_data, char* b_2weeks_training_data ) {
    this->_L_2weeks_model.set_training_data( L_2weeks_training_data );
    this->_a_2weeks_model.set_training_data( a_2weeks_training_data );
    this->_b_2weeks_model.set_training_data( b_2weeks_training_data );
    
    this->_L_2weeks_model.run_gradient_descent();
    this->_a_2weeks_model.run_gradient_descent();
    this->_b_2weeks_model.run_gradient_descent();
}

void ToothShadePredictor::test2weeks( char* L_2weeks_testing_data, char* a_2weeks_testing_data, char* b_2weeks_testing_data ) {
    this->_L_2weeks_model.set_testing_data( L_2weeks_testing_data );
    this->_a_2weeks_model.set_testing_data( a_2weeks_testing_data );
    this->_b_2weeks_model.set_testing_data( b_2weeks_testing_data );
    
    this->_vMSE_2weeks.push_back( this->_L_2weeks_model.compute_MSE() );
    this->_vMSE_2weeks.push_back( this->_a_2weeks_model.compute_MSE() );
    this->_vMSE_2weeks.push_back( this->_b_2weeks_model.compute_MSE() );
}

vector<double> ToothShadePredictor::estimate2weeks( vector<double> data ) {
    vector<double> results;
    
    results.push_back( this->_L_2weeks_model.estimate( data ) );
    results.push_back( this->_a_2weeks_model.estimate( data ) );
    results.push_back( this->_b_2weeks_model.estimate( data ) );
    
    return results;
}

double ToothShadePredictor::compute_delta_E( vector<double> data_before, vector<double> data_after ) {
    double delta_E = 0;
    
    double L_diff = data_before[0] - data_after[0];
    double a_diff = data_before[1] - data_after[1];
    double b_diff = data_before[2] - data_after[2];
    
    delta_E = sqrt( pow( L_diff, 2 ) + pow( a_diff, 2 ) + pow( b_diff, 2 ) );
    
    return delta_E;
}

void ToothShadePredictor::set_standard_vita_data( char* data_file ) {
    ifstream ifile;
    ifile.open( data_file );

    vector<string> tokens;
    vector<double> val;
    string line;

    while ( ! ifile.eof() ) {
        getline( ifile, line );
        // skip an empty line
        if ( line.empty() ) {
            continue;
        }
        
        // split the data into tokens and always NOT add 1 to the first column
        tokens = split( line, ", " );
        
        vita v;

        v.label = tokens[0];
        for ( unsigned int i = 1; i < tokens.size(); i++ ) {
            v.val.push_back( string_to_double( tokens[ i ] ) );
        }

        this->_standard_vita_data.push_back( v );

        v.val.clear();
    }
}

vector<double> ToothShadePredictor::map_to_Lab( string vita ) {
    for ( unsigned int i = 0; i < this->_standard_vita_data.size(); i++ ) {
        if ( vita == this->_standard_vita_data[ i ].label ) {
            return this->_standard_vita_data[ i ].val;
        }
    }

    return this->_standard_vita_data[0].val;
}

string ToothShadePredictor::map_to_vita( double L, double a, double b ) {
    string vita;
    double dist = 100000;
    
    for ( unsigned int i = 0; i < this->_standard_vita_data.size(); i++ ) {
        double L_diff = L - this->_standard_vita_data[ i ].val[0];
        double a_diff = a - this->_standard_vita_data[ i ].val[1];
        double b_diff = b - this->_standard_vita_data[ i ].val[2];
        
        double dist_to_current_vita = sqrt( pow( L_diff, 2 ) + pow( a_diff, 2 ) + pow( b_diff, 2 ) );
        if ( dist > dist_to_current_vita ) {
            vita = this->_standard_vita_data[ i ].label;
            dist = dist_to_current_vita;
        } 
    }
    
    return vita;
}

vector<vita> ToothShadePredictor::get_standard_vita_data() {
    return this->_standard_vita_data;
}

void ToothShadePredictor::print_vMSE() {
    cout << "MSE for Each Model: ";
    for ( unsigned int i = 0; i < this->_vMSE.size(); i++ ) {
        cout << this->_vMSE[ i ] << " ";
    }
    cout << endl;
}

void ToothShadePredictor::print_vMSE_2weeks() {
    cout << "MSE for Each Model (2 weeks): ";
    for ( unsigned int i = 0; i < this->_vMSE_2weeks.size(); i++ ) {
        cout << this->_vMSE_2weeks[ i ] << " ";
    }
    cout << endl;
}

// credit: uvts_cvs's reply at
// http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c
double ToothShadePredictor::string_to_double( string str ) {
    istringstream i( str );
    double val;
    
    if ( ! ( i >> val ) ) {
        return 0;
    }

    return val;
}

// credit: heeen's reply at 
// http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
vector<string> ToothShadePredictor::split( string str, string delimiters ) {
    vector<string> tokens;
    
    // skip delimiters at beginning
    string::size_type last_pos = str.find_first_not_of( delimiters, 0 );
    // find first "non-delimiter"
    string::size_type pos = str.find_first_of( delimiters, last_pos );

    // npos is a static member constant value (-1) with the greatest 
    // possible value for an element of type size_t.
    // credit: http://www.cplusplus.com/reference/string/string/npos/
    while ( string::npos != pos || string::npos != last_pos ) {
        // found a token, add it to the vector
        tokens.push_back( str.substr( last_pos, pos - last_pos ) );
        // skip delimiters
        last_pos = str.find_first_not_of( delimiters, pos );
        // find next "non-delimiter"
        pos = str.find_first_of( delimiters, last_pos );
    }

    return tokens;
}

