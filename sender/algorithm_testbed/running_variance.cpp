/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 77 [algorithms] (Mon Mar 21 05:50:14 EDT 2011)
 * @parent dfe253bbd15c99b209f9e824900e988faf082d8a
 *
 * @section DESCRIPTION
 *
 * The functions for acquiring useful data out of the Kinect using the OpenNI
 * framework. These mostly act as bridges to preexisting methods that provide
 * additional information in less convenient structs.
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

#define PI 3.14159265

using namespace std;

#define SIZE 32

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
  cout.precision(5);

  cout << "| Number   | Normal  | Running | Difference  |" << endl;
  cout << "+--------------------------------------------+" << endl;

  // For loop to check both calculation methods.
  for (int i = 0; i < 256; i++)
  {
    double value = ( (rand() % 1000000) / 1000000.0 ) * 2*PI;

    standard.addValue(value);
    running.addValue(value);

    double var_standard = standard.variance();
    double var_running  = running.variance();

    double diff = var_standard - var_running;

    cout << "| ";
    cout.width(8);
    cout << value;
    cout << " |";
    cout.width(8);
    cout << var_standard;
    cout << " |";
    cout.width(8);
    cout << var_running;
    cout << " |" ;
    cout.width(12);
    cout << diff;
    cout << " |" << endl;

    error_sum += ( (diff >= 0 ? diff : -1*diff));
  }

  cout << "+--------------------------------------------+" << endl;
  cout << "Done loop, absolute error sum over 256 elements = " << error_sum << "." << endl;

}
