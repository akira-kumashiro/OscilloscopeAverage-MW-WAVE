#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <filesystem>
#include <algorithm>

class FileInput
{
private:

public:
	FileInput(std::string _filename);

	std::vector<std::vector<double>> fileData;//CSVs”(CSV—ñ”)
	//std::vector<double> average;//•½‹Ï’l
	std::vector<std::vector<double>> fileDataNom;//CSV—ñ”(CSVs”)
	std::vector<std::vector<double>> dataInput(std::string filename);
	std::vector<std::string> split(std::string& input, char delimiter);
	std::vector<double> dataDivider(int line);
	std::vector<std::vector<double>> getNormValue(std::vector<std::vector<double>>);
	//std::vector<double> minVal, maxVal;
	class CalcVal
	{
	public:
		double average;
		double minVal, maxVal;
		double variance;
		CalcVal(double _average, double _min, double _max, double _var)
		{
			average = _average;
			minVal = _min;
			maxVal = _max;
			variance = _var;
		}

		CalcVal()
		{
			average = 0.0;
			minVal = 0.0;
			maxVal = 0.0;
			variance = 0.0;
		}

		std::string printValue(bool enableVariance)
		{
			std::stringstream ret;
			if (enableVariance)
			{
				ret << average << "," << variance;
			}
			else
			{
				ret << average << "," << minVal << "," << maxVal;
			}

			return ret.str();
		}

		std::string printValueMeaning(std::string prefix, bool enableVariance)
		{
			std::stringstream ret;
			if (enableVariance)
			{
				ret << prefix << "_Average," << prefix << "_variance";
			}
			else
			{
				ret << prefix << "_Average," << prefix << "_min," << prefix << "_max";
			}

			return ret.str();
		}

		~CalcVal()
		{

		}
	};
	std::vector<CalcVal> calcVal;
	//std::string timeStamp;
	//double resolution;
	std::vector<std::string> traceName;
	~FileInput();
};

