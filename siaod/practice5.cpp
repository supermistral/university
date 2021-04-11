#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using std::string;
using std::ofstream;
using std::ifstream;

struct FileHandler {
	string fileInput,
		fileOutput1,
		fileOutput2;
	int length = 0;

	void setFiles(string name1, string name2, string name3) {
		fileInput = name1;
		fileOutput1 = name2;
		fileOutput2 = name3;
		//this->setLengthOfInputFile();
	}

	void setLengthOfInputFile() {
		ifstream in(fileInput);
		string line;

		while (!in.eof()) {
			std::getline(in, line);
			++length;
		}

		in.close();
	}

	void division(int offset) {
		ifstream in(fileInput);
		ofstream out1(fileOutput1), out2(fileOutput2);
		string line;
		bool flagWriting = true;
		int current = 0;

		while (!in.eof()) {
			std::getline(in, line);
			if (!isdigit(line[0]))
				continue;
			flagWriting ? out1 << line << "\n" : out2 << line << "\n";

			if (++current % offset == 0) {
				current = 0;
				flagWriting = !flagWriting;
			}
		}

		this->closeFiles(in, out1, out2);
	}

	void merge(int offset) {
		ofstream out(fileInput);
		ifstream in1(fileOutput1), in2(fileOutput2);
		string line1, line2;
		bool flagReading1, flagReading2;
		int counter1, counter2;

		for (int i = 0; i < length / 2; i += offset) {
			flagReading1 = flagReading2 = true;
			counter1 = counter2 = 0;

			std::getline(in1, line1);
			std::getline(in2, line2);
			if (std::stoi(line1) < std::stoi(line2)) {
				out << line1;
				flagReading2 = false;
				flagReading1 = true;
			}
			else {
				out << line2;
				flagReading1 = false;
				flagReading2 = true;
			}

			while (
				counter1 < offset && counter2 < offset && 
				!in1.eof() && !in2.eof()
			) {
				if (flagReading1)
					std::getline(in1, line1);
				if (flagReading2)
					std::getline(in2, line2);

				if (!(isdigit(line1[0]) && isdigit(line2[0])))
					continue;

				//std::cout << line1 << " " << line2 << "\n";
				if (std::stoi(line1) < std::stoi(line2)) {
					++counter1;
					out << line1;
					flagReading2 = false;
					flagReading1 = true;
				}
				else {
					++counter2;
					out << line2;
					flagReading1 = false;
					flagReading2 = true;
				}
				out << "\n";
			}

			if (flagReading2) {
				out << std::stoi(line1) << "\n";
				++counter1;
				for (; counter1 < offset; ++counter1) {
					std::getline(in1, line1);
					if (!isdigit(line1[0]))
						break;
					out << std::stoi(line1) << "\n";
				}
			}
			else {
				out << std::stoi(line2) << "\n";
				++counter2;
				for (; counter2 < offset; ++counter2) {
					std::getline(in2, line2);
					if (!isdigit(line2[0]))
						break;
					out << std::stoi(line2) << "\n";
				}
			}
		}

		this->closeFiles(out, in1, in2);
	}

	void runSort() {
		int current = 1;
		while (current < length) {
			this->division(current);
			this->merge(current);
			current *= 2;
		}
	}

	template<typename T1, typename T2, typename T3>
	void closeFiles(T1& file1, T2& file2, T3& file3) {
		file1.close();
		file2.close();
		file3.close();
	}

	void generateData() {
		srand(static_cast<unsigned int>(time(0)));

		int n, max;
		n = 100;
		max = 100;
		ofstream output(fileInput);

		if (!output.is_open())
			return;
		for (int i = 0; i < n - 1; ++i)
			output << rand() % max << "\n";
		output << rand() % max;

		output.close();
	}

	bool checkFiles() {
		ifstream in(fileInput);
		ofstream out1(fileOutput1);
		ofstream out2(fileOutput2);

		if (!(in.is_open() && out1.is_open() && out2.is_open())) {
			std::cout << "\nError in files";
			this->closeFiles(in, out1, out2);
			return 0;
		}

		this->closeFiles(in, out1, out2);
		return 1;
	}
};

int main() {
	string fileInput	= "D:\\forwork\\siaod5\\input.txt",
		fileOutput1		= "D:\\forwork\\siaod5\\output1.txt",
		fileOutput2		= "D:\\forwork\\siaod5\\output2.txt";

	FileHandler filehandler;
	filehandler.setFiles(fileInput, fileOutput1, fileOutput2);
	if (!filehandler.checkFiles())
		return -1;
	filehandler.generateData();
	filehandler.setLengthOfInputFile();
	filehandler.runSort();

	return 0;
}
