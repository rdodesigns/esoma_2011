/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 78 [algorithms] (Mon Mar 21 07:10:45 EDT 2011)
 * @parent 5fb8ec37cac7fbd385497d0d7a9d92d223b052fe
 *
 * @section DESCRIPTION
 *
 * Tests the moving window version of the variance calculation, and tests the
 * abiility of the algorithm to correctly calculate the variance against a well
 * behaved standard.
 *
 * This is done because for large values that have little difference the
 * calculated variance can be significantly off due to the two squared factors
 * in the running algorithm versus one squared term in the standard. Coupled
 * with the precision limits of number representation on computers we have a
 * catastrophic failure. However, the standard algorithm is O(n^2), while the
 * running algorithm is O(1).
 *
 * Over the ranges in use by the problems in the Esoma system (which are due to
 * real life physical constrants of space and rotation) the running algorithm
 * performs with insignificant error (far below the measurement bounds).
 *
 * Sample Output under probable sizes and limits of physical parameters.
 * Done loop of 256 elements with holding size 32 with range 20000.
 * Average error    = 1.0434e-07.
 * Average variance = 3.5057e+07.
 * Percent Error    = 2.9976e-15.
 * Time standard    = 0.000204 seconds.
 * Time running     = 3.9e-05 seconds.
 * Time difference  = 0.000165 seconds.
 * Time percent     = 523.08% faster.
 *
 * Sample output at ridiculous scales (9 minutes of runtime run and saved).
 * Done loop of 16384 elements with holding size 16384 with range 20000.
 * Average error    = 7.0302e-07.
 * Average variance = 3.2896e+07.
 * Percent Error    = 2.1427e-14.
 * Time standard    = 5.1213 seconds.
 * Time running     = 0.002355 seconds.
 * Time difference  = 5.1189 seconds.
 * Time percent     = 2.1737e+05% faster.
 *
 *
 * More information on the standard here:
 * http://www.johndcook.com/standard_deviation.html
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 * Resources and brainstorming assistance provided through a collaboration with
 * the MIT Media Lab and Tufts University. Contact information is provided
 * below.
 *
 * Ryan Orendorff
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 *
 * Dr. John Moore
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 * Professor Fiorenzo Omenetto
 * Tufts University
 * Department of Biomedical Engineering
 * 4 Colby Street
 * Medford, MA 02155 USA
 */

#include <iostream>
#include <vector>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define PI 3.14159265
#define SIZE 32
#define ITER 256
#define LIMIT 20000

//#define verbose

class StandardCalculations
{
  public:
    StandardCalculations() : size(SIZE)
    {
      for (int i = 0; i < size; i++)
        data.push_back(0);
    } // Fill with 0s to start.
    ~StandardCalculations(){}

    void addValue(double number) // Note this removes the last number.
    {
      data.push_back(number);
      data.erase(data.begin());
    }

    double variance()
    {
      double sum1 = 0;
      double sum2 = 0;

      for (int i = 0; i < size; i++)
        sum1 = sum1 + data[i];

      double mean = sum1/size;

      for (int i = 0; i < size; i++)
        sum2 = sum2 + (data[i] - mean)*(data[i] - mean);

      return sum2/(size-1);
    }


  protected:

  private:
    vector<double> data;
    int size;

};


class RunningWindowCalculations
{
  public:
    RunningWindowCalculations() : size(SIZE), sum(0), sum_squared(0)
    {
      for (int i = 0; i < size; i++)
        data.push(0);
    } // Fill with 0s to start.
    ~RunningWindowCalculations(){}

    void addValue(double number) // Note this removes the last number.
    {
      data.push(number);

      sum = sum + number - data.front();
      sum_squared = sum_squared + number*number - (data.front()*data.front());

      data.pop(); // Done at the end to ensure data has at least one value.
    }

    double variance()
    {
      return (1./(size*(size-1)))*(size*(sum_squared) - sum*sum);
    }

  protected:

  private:
    queue<double> data;
    int size;
    double sum;
    double sum_squared;
};

int main()
{
  srand(time(NULL));

  StandardCalculations standard;
  RunningWindowCalculations running;

  double error_sum = 0;
  double var_sum   = 0;
  cout.precision(5);

  //---------------------------------------------------------------------------
  // Variance Error Tests
  // --------------------------------------------------------------------------
#ifdef verbose
  cout << "+--------------------------------------------------------+" << endl;
  cout << "| Number       | Normal      | Running     | Difference  |" << endl;
  cout << "+--------------------------------------------------------+" << endl;
#endif

  // For loop to check both calculation methods.
  for (int i = 0; i < ITER; i++)
  {
    // Range is an approximate from OpenNI output.
    double value = ( (rand() % 100000000) / 100000000.0 ) * LIMIT ;

    standard.addValue(value);
    running.addValue(value);

    double var_standard = standard.variance();
    double var_running  = running.variance();

    double diff = var_standard - var_running;

#ifdef verbose
    cout << "| ";
    cout.width(12);
    cout << value;
    cout << " |";
    cout.width(12);
    cout << var_standard;
    cout << " |";
    cout.width(12);
    cout << var_running;
    cout << " |" ;
    cout.width(12);
    cout << diff;
    cout << " |" << endl;
#endif

    error_sum += ( (diff >= 0 ? diff : -1*diff));
      var_sum += var_standard;
  }
#ifdef verbose
  cout << "+--------------------------------------------------------+" << endl;
#endif

  double var_average   = var_sum / ITER;
  double error_average = error_sum / ITER;
  double percent = 1 - (var_average - error_average)/var_average;

  cout << "Done loop of " << ITER << " elements with holding size "
                                  << SIZE << " with range "
                                                       << LIMIT << "." << endl;
  cout << "Average error    = " << error_average << "." << endl;
  cout << "Average variance = " << var_average << "." << endl;
  cout << "Percent Error    = " << percent << "." << endl;


  //---------------------------------------------------------------------------
  // Clock Tests
  // --------------------------------------------------------------------------
  StandardCalculations speed_std;
  RunningWindowCalculations speed_run;

  clock_t start, end;

  // Standard
  start = clock();
  for (int i = 0; i < ITER; i++) {
    double value = ( (rand() % 100000000) / 100000000.0 ) * LIMIT ;
    speed_std.addValue(value);
    double toss = speed_std.variance();
  }
  end = clock();

  double time_std = (double)(end-start)/CLOCKS_PER_SEC;
  cout << "Time standard    = "
  << time_std
  << " seconds." << "\n";


  // Running
  start = clock();
  for (int i = 0; i < ITER; i++) {
    double value = ( (rand() % 100000000) / 100000000.0 ) * LIMIT ;
    speed_run.addValue(value);
    double toss = speed_run.variance();
  }
  end = clock();

  double time_run = (double)(end-start)/CLOCKS_PER_SEC;
  cout << "Time running     = "
  << time_run
  << " seconds." << "\n";

  cout << "Time difference  = " << time_std - time_run << " seconds." << endl;
  cout << "Time percent     = " << time_std/time_run * 100<< "% faster." << endl;

}
