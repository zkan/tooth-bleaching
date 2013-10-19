/*
 * Test driver to test Tooth Shade Predictor program
 */

#include "tooth_shade_predictor.h"
#include "linreg.h"

using namespace std;

int main(int argc, char *argv[]) {
    ToothShadePredictor tsp;
    
    cout << "-- Tooth Shade Predictor --" << endl;
    
    // Read the shade tabs first.
    tsp.set_standard_vita_data( "../data/input/shade-tabs.txt" );
    vector<vita> standard_vita_data = tsp.get_standard_vita_data();

    cout << "Shade Tabs: " << endl;
    for ( unsigned int i = 0; i < standard_vita_data.size(); i++ ) {
        cout << standard_vita_data[ i ].label << " ";
        for ( unsigned int j = 0; j < standard_vita_data[i].val.size(); j++ ) {
            cout << standard_vita_data[ i ].val[ j ] << " ";
        }
        cout << endl;
    }
   
    cout << endl;

    // If input from user is vita shade, then 
    // map it to L, a, and b first.
    string vita_input = "C2";
    cout << "Input " << vita_input << " maps to ";
    vector<double> X_from_vita = tsp.map_to_Lab( vita_input );
    for ( unsigned int i = 0; i < X_from_vita.size(); i++ ) {
        cout << X_from_vita[ i ];
        if ( i < X_from_vita.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << endl;
    
    cout << endl;
    // --------------------------------------------------------------
    
    // Input from user (L, a, and b).
    vector<double> X;

/*
    X.push_back( 77.6 );
    X.push_back( 3.4 );
    X.push_back( 28 );
//*/ 
/*
    X.push_back( 69.1 );
    X.push_back( 1.3 );
    X.push_back( 28.5 );
//*/
    X.push_back( 77.1 );
    X.push_back( -0.5 );
    X.push_back( 16.8 );

    // --------------------------------------------------------------

    cout << "Input X( ";
    for ( unsigned int i = 0; i < X.size(); i++ ) {
        cout << X[ i ];
        if ( i < X.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << " ) maps to ";
    string vita = tsp.map_to_vita( X[0], X[1], X[2] );
    cout << vita << endl;
   
    cout << endl;
    
    // --------------------------------------------------------------

    // Start the training and testing processes (After finishing 
    // the entire tooth bleeching process).
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
    
    vector<double> results = tsp.estimate( X );
    
    cout << "Results for X( ";
    for ( unsigned int i = 0; i < X.size(); i++ ) {
        cout << X[ i ];
        if ( i < X.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << " ): ";
    for ( unsigned int i = 0; i < results.size(); i++ ) {
        cout << results[ i ] << " ";
    }
    cout << endl;

    cout << "Delta E: ";
    cout << tsp.compute_delta_E( X, results ) << endl;
    
    cout << "Output Y( "; 
    for ( unsigned int i = 0; i < results.size(); i++ ) {
        cout << results[ i ] ;
        if ( i < results.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << " ) maps to ";
    vita = tsp.map_to_vita( results[0], results[1], results[2] );
    cout << vita << endl;

    cout << endl;

    // --------------------------------------------------------------
    
    // Start the training and testing processes (After finishing 
    // the entire tooth bleeching process).
    tsp.train2weeks( 
        "../data/input/training/L_after2weeks.txt", 
        "../data/input/training/a_after2weeks.txt", 
        "../data/input/training/b_after2weeks.txt" 
    );

    tsp.test2weeks(
        "../data/input/testing/L_after2weeks.txt", 
        "../data/input/testing/a_after2weeks.txt", 
        "../data/input/testing/b_after2weeks.txt" 
    );
    
    tsp.print_vMSE_2weeks();
    
    vector<double> results2weeks = tsp.estimate2weeks( X );
    
    cout << "Results for X( ";
    for ( unsigned int i = 0; i < X.size(); i++ ) {
        cout << X[ i ];
        if ( i < X.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << " ) after 2 weeks: ";
    for ( unsigned int i = 0; i < results2weeks.size(); i++ ) {
        cout << results2weeks[ i ] << " ";
    }
    cout << endl;

    cout << "Delta E after 2 weeks: ";
    cout << tsp.compute_delta_E( X, results2weeks ) << endl;
    
    cout << "Output after 2 weeks Y( "; 
    for ( unsigned int i = 0; i < results2weeks.size(); i++ ) {
        cout << results2weeks[ i ] ;
        if ( i < results2weeks.size() - 1 ) {
            cout << ", ";
        }
    }
    cout << " ) maps to ";
    vita = tsp.map_to_vita( results2weeks[0], results2weeks[1], results2weeks[2] );
    cout << vita << endl;

    return 1;
}

