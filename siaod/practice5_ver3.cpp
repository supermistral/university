#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <chrono>

using std::string;
using std::ofstream;
using std::ifstream;

class FileHandler {
	string fileInput, fileOutput1, fileOutput2;
	int length = 0, requiredNumber = 4;
	std::vector<std::vector<string>> fileFields;


public:
	FileHandler(string, string, string,
		std::vector<std::vector<string>>);
	void division(int);
	void merge(int);
	void runSort();
	string getField(string);
	bool compareLines(string, string);
	string getRandomValue(string);
	string getRandomValue(std::vector<string>);
	string generateLine();
	void generateData();
	bool checkFiles();
	void printFile();

	void naturalFirstDivision();
	void naturalDivision();
	void naturalMerge(int&);
	void runNaturalSort();

	template<typename T1, typename T2, typename T3>
	void closeFiles(T1&, T2&, T3&);

	int moves = 0, comps = 0;
};



int main() {
	string fileInput	= "D:\\forwork\\siaod5\\input.txt",
		fileOutput1		= "D:\\forwork\\siaod5\\output1.txt",
		fileOutput2		= "D:\\forwork\\siaod5\\output2.txt";

	std::vector<std::vector<string>> fields = {
		{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}, 
		{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
		{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
		{"18-70"},
		{"150-210"},
		{"green", "blue", "black", "brown"},
		{"black", "blond", "brown", "grey"},
		{"1000-1000000"},
		{"yes", "no"},
		{"yes", "no"}
	};

	FileHandler filehandler(fileInput, fileOutput1, fileOutput2, fields);
	if (!filehandler.checkFiles())
		return -1;
	filehandler.generateData();
	//auto begin = std::chrono::steady_clock::now();
	filehandler.runNaturalSort();
	//int k = 0;
	//filehandler.naturalDivision(k);
	//filehandler.naturalMerge();
	//int k = 0;
	//filehandler.naturalFirstDivision(k);
	//filehandler.naturalMerge();
	//filehandler.naturalDivision(k);
	//filehandler.runSort();
	//auto end = std::chrono::steady_clock::now();
	//auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//std::cout << total.count() << " ms";
	std::cout << "Comps: " << filehandler.comps << "\nMoves: " << filehandler.moves
		<< "\nTotal: " << filehandler.comps + filehandler.moves;
	return 0;
}



FileHandler::FileHandler(
	string name1, string name2, string name3,
	std::vector<std::vector<string>> buf
) : fileInput(name1), fileOutput1(name2), fileOutput2(name3),
	fileFields(buf) {
};

void FileHandler::division(int offset) {
	ifstream	in(fileInput);
	ofstream	out1(fileOutput1), out2(fileOutput2);
	string		line;
	int			flagFirstLine = 1;

	while (!in.eof()) {
		for (int i = 0; i < offset && std::getline(in, line); ++i) {
			if (flagFirstLine != 1)
				out1 << "\n";
			else
				flagFirstLine = 2;
			out1 << line;
		}
		for (int i = 0; i < offset && std::getline(in, line); ++i) {
			if (flagFirstLine != 2)
				out2 << "\n";
			else
				flagFirstLine = 0;
			out2 << line;
		}
	}
	this->closeFiles(in, out1, out2);
};

void FileHandler::merge(int offset) {
	ofstream	out(fileInput);
	ifstream	in1(fileOutput1), in2(fileOutput2);
	string		line1, line2;
	int			counter1, counter2;

	for (int i = 0; i < length / 2; i += offset) {
		counter1 = counter2 = 0;
		line1 = line2 = "";
		std::getline(in1, line1);
		std::getline(in2, line2);

		if (line1 != "" && line2 != "") {
			while (counter1 < offset && counter2 < offset) {
				if (i > 0 || counter1 > 0 || counter2 > 0)
					out << "\n";

				++comps; ++moves;
				if (this->compareLines(line1, line2)) {
					++counter1;
					out << line1;
					if (in1.eof() || counter1 == offset)
						break;
					std::getline(in1, line1);
				}
				else {
					++counter2;
					out << line2;
					if (in2.eof() || counter2 == offset)
						break;
					std::getline(in2, line2);
				}
			}
		}

		if (counter1 < offset) {
			out << "\n" << line1;
			++counter1;
			++moves;
			for (; counter1 < offset && std::getline(in1, line1); ++counter1) {
				out << "\n" << line1;
				++moves;
			}
		}
		else {
			out << "\n" << line2;
			++counter2;
			++moves;
			for (; counter2 < offset && std::getline(in2, line2); ++counter2) {
				out << "\n" << line2;
				++moves;
			}
		}
	}
	this->closeFiles(out, in1, in2);
};

void FileHandler::runSort() {
	for (int current = 1; current < length; current *= 2) {
		this->division(current);
		this->merge(current);
		//this->printFile();
	}
};

template<typename T1, typename T2, typename T3>
void FileHandler::closeFiles(T1& file1, T2& file2, T3& file3) {
	file1.close();
	file2.close();
	file3.close();
};

string FileHandler::getField(string line) {
	size_t ind = 0;
	for (int i = 0; i < requiredNumber - 1; ++i) {
		ind = line.find(" ", ind) + 1;
	}
	size_t nextSpace = line.find(" ", ind);
	if (nextSpace == std::string::npos)
		nextSpace = line.size();
	return line.substr(ind, nextSpace - ind);
};

bool FileHandler::compareLines(string line1, string line2) {
	string requiredField1 = this->getField(line1);
	string requiredField2 = this->getField(line2);
	if (isdigit(requiredField1[0]))
		return std::stoi(requiredField1) <= std::stoi(requiredField2)
		? true : false;
	return requiredField1 < requiredField2
		? true : false;
};

string FileHandler::getRandomValue(string val) {
	if (isdigit(val[0])) {
		int firstBorder = std::stoi(val.substr(0, val.find("-")));
		int secondBorder = std::stoi(val.substr(val.find("-") + 1, val.size()));
		int num = rand() % (secondBorder - firstBorder) + firstBorder;
		return std::to_string(num);
	}
	string line;
	line.push_back(val[rand() % val.size()]);
	return line;
};

string FileHandler::getRandomValue(std::vector<string> buf) {
	return buf[rand() % buf.size()];
};

string FileHandler::generateLine() {
	string line = "";
	for (size_t i = 0; i < fileFields.size(); ++i) {
		if (fileFields[i].size() == 1)
			line += this->getRandomValue(fileFields[i][0]) + " ";
		else
			line += this->getRandomValue(fileFields[i]) + " ";
	}
	return line;
};

void FileHandler::generateData() {
	srand(static_cast<unsigned int>(time(0)));

	std::cout << "Number of lines = "; std::cin >> length;
	//std::cout << "Sort key = "; std::cin >> requiredNumber;
	ofstream output(fileInput);

	for (int i = 0; i < length - 1; ++i)
		output << this->generateLine() << "\n";
	output << this->generateLine();

	output.close();
};

bool FileHandler::checkFiles() {
	ifstream in(fileInput);
	ofstream out1(fileOutput1), out2(fileOutput2);

	if (!(in.is_open() && out1.is_open() && out2.is_open())) {
		std::cout << "\nError in files";
		this->closeFiles(in, out1, out2);
		return 0;
	}

	this->closeFiles(in, out1, out2);
	return 1;
};

void FileHandler::printFile() {
	ifstream in(fileInput);
	string line;

	while (std::getline(in, line))
		std::cout << line << "\n";
	std::cout << "\n";
	in.close();
};

void FileHandler::naturalFirstDivision() {
	ifstream	in(fileInput);
	ofstream	out1(fileOutput1), out2(fileOutput2);
	ofstream*	out = &out1;
	string		line1, line2;
	bool		flagWriting = true;

	std::getline(in, line1);
	line2 = line1;

	while (!in.eof()) {
		line1 = line2;
		*out << line1 << "\n";
		while (std::getline(in, line2) && ++comps && this->compareLines(line1, line2)) {
			*out << line2 << "\n";
			line1 = line2;
		}
		*out << "\n";
		flagWriting = !flagWriting;
		out = flagWriting ? &out1 : &out2;
	}
	if (line1 != line2)
		*out << line2 << "\n\n";
		
	this->closeFiles(in, out1, out2);
};

void FileHandler::naturalDivision() {
	ifstream	in(fileInput);
	ofstream	out1(fileOutput1), out2(fileOutput2);
	ofstream*	out = &out1;
	string		line;
	bool		flagWriting = true;

	for (;;) {
		while (std::getline(in, line) && line != "") {
			*out << line << "\n";
		}
		if (in.eof())
			break;
		*out << "\n";
		flagWriting = !flagWriting;
		out = flagWriting ? &out1 : &out2;
	}

	this->closeFiles(in, out1, out2);
}

void FileHandler::naturalMerge(int& amountOfSeries) {
	ofstream	out(fileInput);
	ifstream	in1(fileOutput1), in2(fileOutput2);
	string		line1, line2;
	int			sumCounter = 0;

	for (; sumCounter < length; ++amountOfSeries) {
		std::getline(in1, line1);
		std::getline(in2, line2);

		for (; line1 != "" && line2 != ""; ++sumCounter) {
			++comps; ++moves;
			if (this->compareLines(line1, line2)) {
				out << line1;
				std::getline(in1, line1);
			}
			else {
				out << line2;
				std::getline(in2, line2);
			}
			out << "\n";
		}
		for (; line1 != ""; ++sumCounter) {
			++moves;
			out << line1 << "\n";
			std::getline(in1, line1);
		}
		for (; line2 != ""; ++sumCounter) {
			++moves;
			out << line2 << "\n";
			std::getline(in2, line2);
		}
		out << "\n";
	}
	this->closeFiles(out, in1, in2);
};

void FileHandler::runNaturalSort() {
	int amountOfSeries;
	this->naturalFirstDivision();

	for (;;) {
		amountOfSeries = 0;
		this->naturalMerge(amountOfSeries);
		if (amountOfSeries == 1)
			break;
		this->naturalDivision();
		//this->printFile();
	}
};
