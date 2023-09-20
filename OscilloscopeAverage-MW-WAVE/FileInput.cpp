#include "FileInput.h"

FileInput::FileInput(std::string _filename)
{
	fileData = dataInput(_filename);
	fileDataNom = getNormValue(fileData);
}

std::vector<std::vector<double>> FileInput::dataInput(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		std::cerr << "Could not open the file - '"
			<< filename << "'" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	std::vector<double> result;
	std::vector<std::vector<double>> fileData;

	/*std::getline(ifs, line);
	
	std::vector < std::string> strvec = split(line, ',');
	for (int i = 1; i < strvec.size(); i++)
	{
		std::string temp = strvec[i];
		traceName.push_back(temp);
	}*/
	/*else
	{
		if (strvec[0].find("TraceName") != std::string::npos)
		{

		}
		else if (strvec[0].find("HResolution") != std::string::npos)
		{
			resolution = stof(strvec[1]);
		}
	}*/

	
	while (std::getline(ifs, line))
	{
		std::vector < std::string> strvec = split(line, ',');
		if (line.size() == 0)
		{
			break;
		}
		/*if (fileData.size() == 0)
		{
			for (int i = 1; i < strvec.size(); i++)
			{
				traceName.push_back(strvec[i]);
			}
			break;
		}*/
		std::vector<double> lineData;
		for (int i = 1; i < strvec.size(); i++)
		{
			try
			{
				float cellValue = stof(strvec.at(i));
				lineData.push_back(cellValue);
			}
			catch (std::invalid_argument const& ex)
			{
				if (strvec.at(i).size() != 0)
				{
					traceName.push_back(strvec.at(i));
				}
			}
			//printf("%5.4f", stof(strvec.at(i)));
			/*if (strvec.at(i).find(":") == std::string::npos)
				lineData.push_back(stof(strvec.at(i)));
			else
				timeStamp = strvec.at(i);*/
		}
		//puts("");
		if (lineData.size() != 0)
		{
			fileData.push_back(lineData);
		}
	}
	
	return fileData;
}

std::vector<std::string> FileInput::split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, delimiter))
	{
		result.push_back(field);
	}

	return result;
}

std::vector<double> FileInput::dataDivider(int line)
{
	return fileDataNom[line];
}

std::vector<std::vector<double>> FileInput::getNormValue(std::vector<std::vector<double>>)
{
	std::vector<std::vector<double>> result(fileData[0].size(), std::vector<double>(fileData.size()));

	for (int j = 0; j < fileData[0].size(); j++)
	{
		//double ave = 0.0, min = 0.0, max= 0.0;
		CalcVal value;

		for (int i = 0; i < fileData.size(); i++)
		{
			result[j][i] = fileData[i][j];
		}

		value.average = std::accumulate(result[j].begin(), result[j].end(), 0.0) / result[j].size();
		value.variance= std::inner_product(std::begin(result[j]), std::end(result[j]), std::begin(result[j]), 0.0) / std::size(result[j]) - value.average * value.average;
		value.minVal = *min_element(result[j].begin(), result[j].end());
		value.maxVal = *max_element(result[j].begin(), result[j].end());
		//average.push_back(ave);
		//minVal.push_back(min);
		//maxVal.push_back(max);
		calcVal.push_back(value);
	}
	return result;
}

FileInput::~FileInput()
{
}
