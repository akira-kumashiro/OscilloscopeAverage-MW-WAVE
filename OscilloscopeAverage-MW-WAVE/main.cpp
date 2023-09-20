#include "stdafx.h"
#include"GetFolderFiles.h"
#include"FileInput.h"

//#define DEBUG

int main()
{
	std::string folderTarget;
	std::cout << "ファイルのフルパスは？" << std::endl;
	std::cin >> folderTarget;
	std::cout << folderTarget << std::endl;
	GetFolderFiles folderFilesList(folderTarget);
	std::ostringstream result;

	for (int fileNumber = 0; fileNumber < folderFilesList.fileList.size(); fileNumber++)
	{
		std::string fileName = folderFilesList.fileNameList[fileNumber];//フォルダ内ファイルリストからファイル名を取得
		std::cout << fileName << "\t:";

		FileInput fileio(folderFilesList.fileList[fileNumber].string());//csvへのデータ処理実行

		if (fileNumber == 0)
		{
			result << ",,";
			for (int i = 0; i < fileio.calcVal.size(); i++)
			{
				//std::stringstream prefix;
				//prefix << "CH" << (i + 1);
				//std::cout << fileio.calcVal.at(i).printValueMeaning(prefix.str(), true);
				//result << fileio.calcVal.at(i).printValueMeaning(prefix.str(), true); 
				std::cout << fileio.calcVal.at(i).printValueMeaning(fileio.traceName.at(i), true);
				result << fileio.calcVal.at(i).printValueMeaning(fileio.traceName.at(i), true);
				if (static_cast<unsigned long long>(i) + 1 < fileio.calcVal.size())
				{
					std::cout << ",\t";
					result << ",";
				}
			}

			std::cout << std::endl;
			result << std::endl;
		}
		fileName = std::regex_replace(fileName, std::regex("_"), ",");
		/*bool numFlag = true;
		int itr = 0;
		for (int i = 0; i < fileName.size(); i++)
		{
			if (isdigit(fileName.at(i)))//数字の場合
			{
				if (!numFlag)
					itr = i;
				numFlag = true;
			}
			else
			{
				numFlag = false;
			}
		}
		fileName.insert(itr, ",");*/
		result << fileName << ",";
		for (int i = 0; i < fileio.calcVal.size(); i++)
		{
			std::cout << fileio.calcVal.at(i).printValue(true);
			result << fileio.calcVal.at(i).printValue(true);
			if (static_cast<unsigned long long>(i) + 1 < fileio.calcVal.size())
			{
				std::cout << ",\t";
				result << ",";
			}
		}
		std::cout << std::endl;
		result << std::endl;
		/*for (int i = 0; i < fileio.date.size(); i++)
		{
			std::cout << fileio.date.at(i) << "," << fileio.time.at(i) << ", ," << fileio.triggerWord.at(i) << "," << fileio.message.at(i) << std::endl;
			result << fileio.date.at(i) << "," << fileio.time.at(i) << ", ," << fileio.triggerWord.at(i) << "," << fileio.message.at(i) << std::endl;
		}*/
	}
	std::ofstream writing_file;
	std::string filename = "result.csv";
	std::ostringstream filePath;
	filePath << folderTarget << "\\" << filename;
	writing_file.open(filePath.str(), std::ios::out);
	std::string writing_text = result.str();
	writing_file << writing_text << std::endl;
	writing_file.close();

	/*for (int fileNumber = 0; fileNumber < folderFilesList.fileList.size(); fileNumber++)
	{


		//FileInput fileio(fileFullPath);
		FileInput fileio(folderFilesList.fileList[fileNumber].string(),oscilloscopeType);
		std::cout << folderFilesList.fileList[fileNumber] << std::endl;

		for (int dataNumber = 0; dataNumber < fileio.fileDataNom.size(); dataNumber++)
		{
			GA ga(MAX_GENOM_LIST, VAR_NUM, vMax, vMin, fileio.dataDivider(dataNumber));//遺伝的アルゴリズム諸関数をまとめたクラスの宣言
			ga.timeDiv = fileio.resolution;
			ga.freq = FREQ;
			//ga.init();//変数の初期化

			for (int epoch = 0; epoch <= MAX_GENERATION; epoch++)//メインのループ
			{
				bool change = ga.selection();//選択

				ga.blxAlphaCrossover();//交叉
#ifdef ENABLE_MUTATION
				ga.mutation();//突然変異
				//ga.blxAlphaMutation();
#endif
#ifdef DEBUG
				if (epoch % (MAX_GENERATION / 10) == 0)// || change
				{
					std::cout << "itr=" << std::to_string(epoch)<<"	";
					ga.calc(true);//評価関数の計算
				}
				else
					ga.calc(false);//評価関数の計算
#endif
			}
			ga.eliteData.showData();
			eliteData[fileNumber][dataNumber] = ga.eliteData;
			eliteData[fileNumber][dataNumber].id = folderFilesList.fileList[fileNumber].filename().string() + "," + fileio.timeStamp;
			eliteData[fileNumber][dataNumber].name = fileio.traceName[dataNumber];
#ifdef DEBUG
			while (1)
				if (_kbhit() && _getch() == 27)
					break;
#endif
		}
		puts("");
	}
	std::vector<std::string> identifier = { "amp","ph","functuonValue" };
	std::cout << "fileName,timeStamp,";
	for (int dataNumber = 0; dataNumber < eliteData[0].size(); dataNumber++)
	{
		for (int optParam = 0; optParam < identifier.size(); optParam++)
		{
			std::cout << eliteData[0][dataNumber].name + identifier[optParam] << ",";
		}
	}
	std::cout << std::endl;
	for (int fileNumber = 0; fileNumber < eliteData.size(); fileNumber++)
	{
		std::cout << eliteData[fileNumber][0].id << ",";
		for (int dataNumber = 0; dataNumber < eliteData[fileNumber].size(); dataNumber++)
		{
			for (int optParam = 0; optParam < eliteData[fileNumber][dataNumber].x.size(); optParam++)
			{
				printf("%8.7f,", eliteData[fileNumber][dataNumber].x[optParam]);
			}
			printf("%8.7f,", eliteData[fileNumber][dataNumber].functionValue);
		}
		puts("");
	}*/
	return 0;
}

