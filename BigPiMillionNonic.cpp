/** 
 * BigPiMillionNonic.cpp
 * 
 * Compile: g++ -std=c++11 BigPiMillionNonic.cpp -lmpir -o BigPiMillionNonic
 * Run: ./BigPiMillionNonic
 *
 * Use the Multiple Precision Integers and Rationals (MPIR) Library
 * to compute and print the first million decimal places of pi using 
 * Nonic convergence.
 * Include timings.
 *
 * Author: Alex Lim
 */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <mpir.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace std::chrono;

const int MAX_ITERATIONS = 10;
const int PLACES         = 1000000;     // desired decimal places
const int PRECISION      = PLACES + 1;  // +1 for the digit 3 before the decimal

const int BASE       = 10;  // base 10 numbers
const int BIT_COUNT  = 8;   // bits per machine word

const int BLOCK_SIZE = 10;                // print digits in blocks
const int LINE_SIZE  = 100;               // digits to print per line
const int LINE_COUNT = PLACES/LINE_SIZE;  // lines to print
const int GROUP_SIZE = 5;                 // line grouping size

void root4(mpf_t& root4, const mpf_t& x);
void power4(mpf_t& xxxx, const mpf_t& x);
void print(const mpf_t& pi);

/**
 * The main.
 * Set constants, initialize variables, and iterate
 * to compute pi to the desired number of decimal places.
 */
int main()
{
    steady_clock::time_point start_time = steady_clock::now();
    steady_clock::time_point now_time;
    long elapsed_time;

    mpf_set_default_prec(BIT_COUNT*PRECISION);  // precision in bits

    mpf_t one, two, four, six, sqrt2, sqrt2x4;
    mpf_t y, y_prev, a, a_prev, y4, yRoot4, aTerm, powers2, y2;

    // Multiple-precision constants.
    mpf_init(one);  mpf_set_str(one,  "1", BASE);
    mpf_init(two);  mpf_set_str(two,  "2", BASE);
    mpf_init(four); mpf_set_str(four, "4", BASE);
    mpf_init(six);  mpf_set_str(six,  "6", BASE);

    // Multiple-precision variables.
    mpf_init(y);
    mpf_init(a);
    mpf_init(y4);
    mpf_init(yRoot4);
    mpf_init(aTerm);
    mpf_init(y2);

    cout << "Initializing:"; cout.flush();
    steady_clock::time_point init_time = steady_clock::now();

    // Variables.
    cout << " variables"; cout.flush();
    mpf_init(y_prev); mpf_sub(y_prev, sqrt2, one);
    mpf_init(a_prev); mpf_sub(a_prev, six, sqrt2x4);
    mpf_init(powers2); mpf_set_str(powers2, "2", BASE);

    // The square root of 2.
    cout << " sqrt2"; cout.flush();
    mpf_init(sqrt2);   mpf_sqrt(sqrt2, two);

    cout << " y_prev"; cout.flush();
    mpf_sub(y_prev, sqrt2, one);

    cout << " a_prev"; cout.flush();
    mpf_init(sqrt2x4); mpf_mul(sqrt2x4, four, sqrt2);
    mpf_sub(a_prev,  six,   sqrt2x4);

    mpf_set_str(powers2, "2", BASE);

    now_time = steady_clock::now();
    elapsed_time = duration_cast<milliseconds>(now_time - init_time).count();
    cout << " (" << elapsed_time << " ms)" << endl;

    // Loop MAX_ITERATIONS times.
    cout << "Iterations:" << endl;
    for (int i = 1; i <= MAX_ITERATIONS; i++)
    {
        steady_clock::time_point iter_time = steady_clock::now();
        cout << setw(4) << i << ": y4"; cout.flush();

        power4(y4, y_prev);

        mpf_t temp1, temp2;
        mpf_init(temp1);
        mpf_init(temp2);

        cout << " yRoot4"; cout.flush();
        mpf_sub(temp1, one, y4);
        root4(yRoot4, temp1);

        cout << " y"; cout.flush();
        mpf_sub(temp1, one, yRoot4);
        mpf_add(temp2, one, yRoot4);
        mpf_div(y, temp1, temp2);

        cout << " aTerm"; cout.flush();
        mpf_add(temp1, one, y);
        power4(temp2, temp1);
        mpf_mul(aTerm, a_prev, temp2);

        cout << " powers2"; cout.flush();
        mpf_mul(powers2, four, powers2);

        cout << " y2"; cout.flush();
        mpf_mul(y2, y, y);

        cout << " a"; cout.flush();
        mpf_add(temp1, one, y);
        mpf_add(temp1, temp1, y2);
        mpf_mul(temp1, temp1, y);
        mpf_mul(temp1, temp1, powers2);
        mpf_sub(a, aTerm, temp1);

        mpf_set(a_prev, a);
        mpf_set(y_prev, y);

        now_time = steady_clock::now();
        elapsed_time = duration_cast<milliseconds>(now_time - iter_time).count();
        cout << " (" << elapsed_time << " ms)" << endl;
    }

    mpf_t pi;
    mpf_init(pi);

    steady_clock::time_point invert_time = steady_clock::now();
    cout << "Inverting:";
    mpf_div(pi, one, a);

    now_time = steady_clock::now();
    elapsed_time = duration_cast<milliseconds>(now_time - invert_time).count();
    cout << " (" << elapsed_time << " ms)" << endl;

    now_time = steady_clock::now();
    duration<double>  total_time = duration_cast<duration<double>>(now_time - start_time);

    print(pi);
    cout << "Done! Total compute time = " << total_time.count() << " seconds" << endl;
    return 0;
}

/**
 * Compute the 4th root of a multiple-precision number x.
 * @param root4 the computed multiple-precision 4th root of x.
 * @param x the multiple-precision number.
 */
void root4(mpf_t& root4, const mpf_t& x)
{
    mpf_t root2;
    mpf_init(root2);

    mpf_sqrt(root2, x);
    mpf_sqrt(root4, root2);
}

/**
 * Compute the 4th power of a multiple-precision number x.
 * @param xxxx the computed multiple-precision 4th power of x.
 * @param x the multiple-precision number.
 */
void power4(mpf_t& xxxx, const mpf_t& x)
{
    mpf_t xx;
    mpf_init(xx);

    mpf_mul(xx, x, x);
    mpf_mul(xxxx, xx, xx);
}

/**
 * Print the decimal places of a multiple-precision number x.
 * @param pi the multiple-precision number to print.
 */
void print(const mpf_t& pi)
{
    mp_exp_t exp;  // exponent (not used)

    // Convert the multiple-precision number x to a C string.
    char *str = NULL;
    char *s = mpf_get_str(str, &exp, BASE, PRECISION, pi);
    char *p = s+1;  // skip the 3 before the decimal point

    cout << endl;
    cout << "3.";

    char block[BLOCK_SIZE + 1];  // 1 extra for the ending \0

    // Loop for each line.
    for (int i = 1; i <= LINE_COUNT; i++)
    {
        // Loop to print blocks of digits in each line.
        for (int j = 0; j < LINE_SIZE; j += BLOCK_SIZE)
        {
            strncpy(block, p+j, BLOCK_SIZE);
            block[BLOCK_SIZE] = '\0';
            cout << block << " ";
        }

        cout << endl << "  ";

        // Print a blank line for grouping.
        if (i%GROUP_SIZE == 0) cout << endl << "  ";

        p += LINE_SIZE;
    }

    free(s);
}
