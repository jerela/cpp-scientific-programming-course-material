/* Writing z-scores.
The attached file sample_vector.txt contains floating-point values separated by line breaks.
Write a program that reads the file and writes another file “sample_vector_normalized.txt” that contains the same values, but modified so that the mean of the values is 0 and the standard deviation is 1.
Hint: save the values to a container or array, then calculate their mean and standard deviation. Subtract the mean from all values and divide all values by the standard deviation. Write the results to the new file.
*/

#include <iostream>
#include <vector>
#include <fstream>

// function to calculate standard deviation from elements in a vector
double calcStandardDeviation(std::vector<double> vec, double mean) {
	double standardDeviation = 0;
	// calculate standard deviation; in this case we calculate the population standard deviation although sample standard deviation would be more valid if the values represent a sample of a larger population
	// the choice doesn't really matter in the context of what this assignment is supposed to teach
	for (int i = 0; i < vec.size(); ++i) {
		standardDeviation += pow(vec[i] - mean, 2);
	}
	return sqrt(standardDeviation / vec.size());
}

// function to calculate mean from elements in a vector
double calcMean(std::vector<double> vec) {
	double sum = 0;
	for (int i = 0; i < vec.size(); ++i) {
		sum += vec[i];
	}
	return sum / vec.size();
}

int main()
{
    // read 'sample_vector.txt' into a vector
	std::vector<double> data;
	std::fstream fin("sample_vector.txt", std::ios_base::in);
	// check to make sure we managed to open the file
	if (fin.is_open()) {
		// as long as we haven't reached the end of the file, read values one by done
		while (!fin.eof()) {
			double value;
			fin >> value;
			// if statement to avoid adding the last value twice
			if (data.size() > 0) {
				if (data.back() != value) {
					data.push_back(value);
				}
			}
			else {
				data.push_back(value);
			}
		}
	}

	// calculate mean and standard deviation
	double mean = calcMean(data);
	double standardDeviation = calcStandardDeviation(data, mean);

	// calculate z-scores
	std::vector<double> zScores;
	for (unsigned int i = 0; i < data.size(); ++i) {
		zScores.push_back((data[i] - mean) / standardDeviation);
	}

	// write z-scores to 'sample_vector_normalized.txt'
	std::fstream fout("sample_vector_normalized.txt", std::ios_base::out);
	if (fout.is_open()) {
		for (unsigned int i = 0; i < zScores.size(); ++i) {
			fout << zScores[i] << std::endl;
		}
	}

}
