/*
 * Test driver to test Tooth Shade Predictor program
 */

#include "tooth_shade_predictor.h"
#include "linreg.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "-- Tooth Shade Predictor --" << endl;

    ToothShadePredictor tsp;

    tsp.train( 
        "../data/input/training/L.txt", 
        "../data/input/training/a.txt", 
        "../data/input/training/b.txt" 
    );

    tsp.test(
        "../data/input/testing/L.txt", 
        "../data/input/testing/a.txt", 
        "../data/input/testing/b.txt" 
    );

    tsp.print_vMSE();

    // Input unknown data
    vector<double> X;

    X.push_back( 77.6 );
    X.push_back( 3.4 );
    X.push_back( 28 );

    vector<double> results = tsp.estimate( X );
    
    cout << "Results for X( 77.6, 3.4, 28 ): ";
    for ( unsigned int i = 0; i < results.size(); i++ ) {
        cout << results[ i ] << " ";
    }
    cout << endl;

    cout << "Delta E: ";
    cout << tsp.compute_delta_E( X, results ) << endl;

/*
    lr.set_standard_vita_data( "../data/input/color-map-before.txt", BEFORE_BLEECHING );
    lr.set_standard_vita_data( "../data/input/color-map-after.txt", AFTER_BLEECHING );

    vector<vita> standard_vita_data_before = lr.get_standard_vita_data_before();
    vector<vita> standard_vita_data_after = lr.get_standard_vita_data_after();

    cout << "Standard Vita Before Bleeching" << endl;
    for ( unsigned int i = 0; i < standard_vita_data_before.size(); i++ ) {
        cout << standard_vita_data_before[ i ].label << " ";
        for ( unsigned int j = 0; j < standard_vita_data_before[i].val.size(); j++ ) {
            cout << standard_vita_data_before[ i ].val[ j ] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "Standard Vita After Bleeching" << endl;
    for ( unsigned int i = 0; i < standard_vita_data_after.size(); i++ ) {
        cout << standard_vita_data_after[ i ].label << " ";
        for ( unsigned int j = 0; j < standard_vita_data_after[i].val.size(); j++ ) {
            cout << standard_vita_data_after[ i ].val[ j ] << " ";
        }
        cout << endl;
    }
    cout << endl;
*/    
    return 1;
}

