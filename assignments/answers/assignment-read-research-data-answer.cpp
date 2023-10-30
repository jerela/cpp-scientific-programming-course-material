/*Reading formatted research data.
The attached file ik_orientations.mot is contains measurement data that is separated into labeled columns with tab delimiters. The data is from a measurement of human motion. The first column of the data contains the time values each point was measured and the other columns are the joint angles of a person at those times. The first 6 lines are metadata that won’t be needed in this assignment.
Write a program that takes as command-line input a column label and time value (e.g. “pelvis_tilt 5.25”) and the program then prints to screen all values from that column label where the corresponding times are smaller than the user-given time.
Hint: Check topic 2 to refresh your memory about command-line arguments. Despite its extension, the file is a text file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{
	// read label and time point from command line arguments
	std::string label;
	double time;
	if (argc == 3) {
		label = argv[1];
		time = std::stod(argv[2]);
	}
	else {
		std::cout << "Try format: 'assignment-research-data label time'" << std::endl;
		return 0;
	}

	// prepare a vector to hold the relevant lines of the file
	std::vector<std::string> lines;

    // read 'ik_orientations.mot' line by line
    std::fstream fin("ik_orientations.mot", std::ios_base::in);
    // check to make sure we managed to open the file
    if (fin.is_open()) {
		bool metadata = true;
		// as long as we haven't reached the end of the file, read values one by done
        while (!fin.eof()) {
			std::string line;
			std::getline(fin, line);
			// if line contains "time", enable addition to vector
			if (metadata) {
				if (line.find("time") != std::string::npos) {
					metadata = false;
				}
			}
			if (!metadata)
				lines.push_back(line);
			
		}
	}
	else {
		std::cout << "Error opening file" << std::endl;
	}

	// parse labels from first line
	std::vector<std::string> labels;
	std::stringstream labelsLine(lines[0]);
	std::string labelString;
	while (labelsLine >> labelString) {
		labels.push_back(labelString);
		//std::cout << labelString << std::endl; // enable to print all read column labels
	}

	// find index in labels matching label from command line
	int index = -1;
	for (int i = 0; i < labels.size(); i++) {
		if (labels[i] == label) {
			index = i;
			break;
		}
	}

	// print all values from column matching label where time is smaller than user-given time
	for (unsigned int line = 1; line < lines.size(); ++line) {
		std::stringstream currentLine(lines[line]);
		double currentTime = -1;
		currentLine >> currentTime;

		// if time is equal to or larger than user-given time, stop printing
		if (currentTime >= time)
			break;

		// set stream back to the beginning in case we want to print 'time' label
		currentLine.seekg(0);
		// skip to column matching label
		for (unsigned int column = 0; column < index; ++column) {
			std::string tempString;
			currentLine >> tempString;
		}
		// print the value from the current column
		std::string currentValue;
		currentLine >> currentValue;
		std::cout << currentTime << "\t" << currentValue << std::endl;
	}

	std::cout << "If you see this message, the program finished without error.";


}
