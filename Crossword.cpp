#define _GNU_SOURCE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "vector.h"
#include <math.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#define PLACE_SUCCESS 1
#define PLACE_FAILURE 0

class Puzzle
{
private:
	int Size;
	int wordcount;
	int CheckCountWords, CheckCountWords2;
	myVector<int> location;//координаты начала слова (х,у) и положение (вертикаль, горизонталь)
	string* solution;//поле, куда заносится решение
	myVector<string> words;//рабочий массив
	myVector<string> words2;//дубликат исходного отсортированного, чтобы при каждой попытке обновлять рабочий массив с новым порядком слов
	int step;

	struct compare_Sizegth {
		bool operator()(const std::string& first, const std::string& second) {
			return first.size() > second.size();
		}
	};


public:
	Puzzle() {
		wordcount = 0;
		CheckCountWords = 0;
		CheckCountWords2 = 0;
		step = 0;
		Size = 0;
	}

	~Puzzle()
	{
		delete[] solution;
		location.~myVector();//но ведь прога сама в конце их вызовет? ...уточнить...
		words.~myVector();
		words2.~myVector();
	}

	void displayBoards()
	{
		int i, j;
		if (CheckCountWords + 1 == CheckCountWords2)//сколько слов поставили и сколько их на самом деле (проверка: поставили ли все слова?)
		{
			for (i = 0; i <= Size - 1; i++)
			{
				for (j = 0; j <= Size - 1; j++)
				{
					if (solution[i][j] == '.')
						cout << "  ";
					else cout << " " << solution[i][j];
				}
				printf("\n");
			}
		}
		else {
			step++;
			if (step == wordcount) cout << "no solution\n" << endl;
			else LocalMain();
		}
		system("pause");
	}
	/*
	void wordSorter()
	{
		words = words2;
		//for (auto h = 0; h < wordcount + 1; h++)
		//	words.push_back(words2[h]);
		words.MySwap(step, words2); 
		//for (i = step, j = 0; i < wordcount; j++, i++)
		//{
		//	words[j] = words2[i];
		//	if (j < step)
		//		words[wordcount - step + j] = words2[j];//составляем новую комбинацию расстановки слов
		//}
		return;
	}
*/
	int GetFromFile(string File_name)
	{
		wordcount = 0;

		ifstream read(File_name);
		if (!read) {
			cout << "Wrong name" << endl;
			return 0;
		}
		string readfile = { 0 };
		while (read >> readfile) {
			int j = 0;
			int mem = 0;

			if (readfile[0] == '\n') break;
			if (readfile[0] == '\0') break;

			if (readfile.length() < 2)
			{
				printf("Минимальная длина слова - 2\n"); return 0;
			}

			words.push_back(readfile);
			wordcount++;
		}
		read.close();
		CheckCountWords2 = wordcount;
		return 1;
	}

	void LocalMain() {
		CheckCountWords = 0;
		int mem = 0;

		if (step == 0)
		{
			string File_name;
			cout << "Имя файла:";
			getline(cin, File_name);

			if (!GetFromFile(File_name))
				return; //получаем массив со словами
			sort(words.begin(), words.end(), compare_Sizegth());

			for (auto& el : words)
			{
				Size += el.length();
			}
			solution = new string[Size];///выделение памяти

			for (auto h = 0; h < wordcount; h++)
				words2.push_back(words[h]);
			wordcount--;//чтобы не писать везде wordcount-1

			for (int i = 0; i < wordcount * 3; i++)
				location.push_back(0);
		}

		if (wordcount == 0)
			return;

		if (step != 0) {//очищение решений, полученных при предыдущей попытке
			location.clear();
			solution->clear();
			words.clear();
			words = words2;
			words.MySwap(step, words2);
			//wordSorter();
		}

		mem = 0;
		while (mem < Size)
		{
			solution[mem].replace('\0', 0, Size, '.');
			mem++;
		}

		for (int i = 0; i < wordcount * 3; i++)
			location.push_back(0);

		puzzleMaker();
		displayBoards();
	}

	void puzzleMaker()
	{
		int i;
		wordPlace(0, Size / 2, (Size - words[0].length()) / 2, 1); //ставим ТОЛЬКО первое слово 
		location[0] = (Size - words[0].length() / 2);//x
		location[1] = (Size / 2);//положение первого слова// y
		location[2] = 1;// горизонт/вертик
						   //location[0][i]: i=0 - положение по х; i=1 - по у; i=2 - ориентация
		for (i = wordcount; i >= 1; i--)
		{
			if (placeFinder(i)) //расстановка остальных слов
				CheckCountWords++;
			else location[3 * i] = (-1);
		}
	}

	int placeFinder(int wordnumber)
	{
		int value, i, j, k;
		int change = words[wordnumber].length();
		if (change != 0) {
			for (i = 0; i <= change; i++)
			{ //идем по слову
				for (j = 0; j < Size; j++)
				{
					for (k = 0; k < Size; k++)
					{
						if (words[wordnumber][i] == solution[j][k])
						{ //ищем совпадающие буквы в слове и в поле слов
							int vertikal = k - i;
							int gorizontal = j - i;

							if ((gorizontal > -1 && gorizontal + change - 1 < Size) && (wordPlace(wordnumber, gorizontal, k, 0)))
							{   // влезет или нет       
								//пробуем поставить слово по горизонтали
								location[3 * wordnumber] = k;/////
								location[3 * wordnumber + 1] = gorizontal;
								location[3 * wordnumber + 2] = 0;
								return PLACE_SUCCESS;

							}
							if ((vertikal > -1 && vertikal + change - 1 < Size) && (wordPlace(wordnumber, j, vertikal, 1)))
							{//а теперь вертикаль 
								location[3 * wordnumber] = vertikal;
								location[3 * wordnumber] = j;
								location[3 * wordnumber] = 1;
								return PLACE_SUCCESS;
							}
						}
					}
				}
			}
		}
		return PLACE_FAILURE;
	}

	int wordPlace(int wordnumber, int y, int x, int orientation)
	{
		int zamena;
		int wordpos;
		int sdvig;
		wordpos = 0;
		int i, j, adjacentcount;
		i = 0; j = 0; adjacentcount = 0;
		sdvig = y + words[wordnumber].length();//
		if (orientation == 0) { //ето вертикаль
			if (solution[y - 1][x] != '.' && y - 1 > 0) return PLACE_FAILURE; //рядом уже что-то стоит
			if (solution[sdvig][x] != '.' && y + sdvig < Size) return PLACE_FAILURE;
			zamena = sdvig - 1;
			for (j = y; j <= zamena; j++)
			{
				if (solution[j][x] != '.' && solution[j][x] != words[wordnumber][wordpos]) return PLACE_FAILURE; //наличие свободного места

				if (solution[j][x] != words[wordnumber][wordpos])
				{
					if (solution[j][x + 1] != '.')adjacentcount++; //проверка границ(чтобы не слеплялись слова)
					if (solution[j][x - 1] != '.')adjacentcount++;
				}
				wordpos++;
			}
			if (adjacentcount > 0) return PLACE_FAILURE;
			while (words[wordnumber][i] != '\0')
			{ //если все ок - сохраняем положение слова
				solution[y][x] = words[wordnumber][i];
				i++;
				y++;
			}
		}
		else if (orientation == 1)
		{ //а ето горизонталь

			if (solution[y][x - 1] != '.' && x - 1 > 0) return PLACE_FAILURE;
			if (solution[y][x + words[wordnumber].length()] != '.' && x + words[wordnumber].length() < Size) return PLACE_FAILURE;
			for (j = x; j <= x + words[wordnumber].length() - 1; j++) {
				if (solution[y][j] != '.' && solution[y][j] != words[wordnumber][wordpos]) return PLACE_FAILURE;

				if (solution[y][j] != words[wordnumber][wordpos])
				{
					if (solution[y + 1][j] != '.')adjacentcount++;
					if (solution[y - 1][j] != '.')adjacentcount++;//проверка сверху и снизу
				}
				wordpos++;
			}
			if (adjacentcount > 0) return PLACE_FAILURE;

			while (words[wordnumber][i] != '\0')
			{
				solution[y][x] = words[wordnumber][i];//все ок - заносим слово
				i++;
				x++;
			}
		}
		return PLACE_SUCCESS;
	}

};

/*
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Puzzle Crossword;
	Crossword.LocalMain();
	system("pause");
	return 0;
}*/
