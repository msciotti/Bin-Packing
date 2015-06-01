#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class BPinstance{
private:
	int _nitems;
	double *_sizes;
	int _nbins;
	vector<vector<double>> bins;
	void initWithRandomSizes(){
		random_device rd;
		mt19937 gen(rd());		//Uncomment/recomment either mt19937 to use a random seed or a given seed
		//mt19937 gen(1729);
		uniform_real_distribution<> distr(0, 1);
		double rval;
		int count = 0;
		while (count < _nitems){
			rval = distr(gen);
			if (rval > 0.0)
				_sizes[count++] = rval;
		}
	}
public:
	BPinstance(int n, double *s = NULL): _nbins(0),_nitems(n){
		if (s == NULL){
			_sizes = new double[n];
			initWithRandomSizes();
		}
		else 
			_sizes = s;
	}
	~BPinstance(){}
	inline int nbins() { return _nbins; }
	void outputInstance(){
		cout << "The instance has " << _nitems << " items. The sizes are as follows:\n";
		for (int i = 0; i < _nitems; i++){
			cout << setw(6) << fixed << setprecision(4) << _sizes[i] << " ";
			if ((i + 1) % 10 == 0)
				cout << endl;
		}
		cout << endl;
	}

	void pack(void){
		int itemcount, bincount, i;
		double currentitem, binsum;
		bool packed;
		vector<double> currentbin;

		sort(_sizes, _sizes + _nitems);		//Sorts items increasingly
		reverse(_sizes, _sizes + _nitems);	//Reverses the order to decreasing

		itemcount = 0;
		while (itemcount < _nitems){			

			currentitem = _sizes[itemcount];	
			packed = false;
			while (!packed){						//While the item is not packed
				bincount = 0;

				//See if it fits in a bin
				while ((bincount < _nbins) && !packed){
					currentbin = bins[bincount];				//Get current bin
					binsum = 0;
					for (i = 0; i < currentbin.size(); i++){		//Check what's in the bin
						binsum += currentbin[i];
					}
					if (binsum + currentitem <= 1.0){			//If the item fits, add it to the bin
						currentbin.push_back(currentitem);
						bins[bincount] = currentbin;
						packed = true;
					}

					bincount++;									//If not, go to the next bin
				}

				//If it doesn't fit in a bin, create a new bin and add the item to it
				if (!packed){
					vector<double> newbin;
					newbin.push_back(currentitem);
					bins.push_back(newbin);
					packed = true;
					_nbins++;									//Increment total number of bins
				}
			}
			itemcount++;
		}

	}
	void showBins(){
		for (unsigned int i = 0; i < bins.size(); i++){
			cout << "Bin " << i + 1 << " contents: ";
			for (unsigned int j = 0; j < bins[i].size(); j++)	//Iterates through each bin to output their contents
				cout << bins[i][j] << " ";
			cout << endl;
		}
	}
	int estimateExtraBinsUsed(){
		int optimal = (2 * _nbins) / 3;		//The ratio of optimal bins to extra ones is 3:2
		return _nbins - optimal;
	}
};

int main(void){
	// Example from the text
	double givenSizes[] = { 0.3, 0.2, 0.4, 0.85, 0.5, 0.2, 0.4, 0.1 };
	BPinstance given(8, givenSizes);
	cout << "Example from the text:\n";
	given.outputInstance();
	given.pack();
	given.showBins();
	cout << "Estimated number of extra bins: " << given.estimateExtraBinsUsed() << endl;

	// Random number of items
	int randNum;
	cout << "Input number of random items to pack: ";
	cin >>  randNum;
	BPinstance randomBP(randNum);
	cout << "\nA random instance with " << randNum << " items:\n";
	randomBP.outputInstance();
	randomBP.pack();
	randomBP.showBins();
	cout << "Estimated number of extra bins: " << randomBP.estimateExtraBinsUsed() << endl;

	return 0;
}
