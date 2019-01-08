// 185_RomanNumerals_DennisNilsson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

const int x = 90;
char input[10], arr[3][9], maps[9];
int roman[x], first[x], visited[x], used[10], digit[x];
int ans;
int value[3];

// x = 128
//used = 10
// arr 3 9
//maps 9

void dfs(int d, int n)
{
	if (ans > 1)
	{
		return;
	}
	if (d >= n)
	{
		for (int i = 0; i < 3; ++i)
		{
			value[i] = 0;
			for (int j = 0; arr[i][j]; ++j)
			{
				value[i] = value[i] * 10 + digit[arr[i][j]];
				std::cout << "this is digit " << digit[arr[i][j]] << std::endl;
			}
		}
		ans += (value[0] + value[1] == value[2]);
		return;
	}
	else
	{
		for (int i = 0; i <= 9; ++i)
		{
			if (used[i] || !i && first[maps[d]]) // if used[i] = 1, if i = 0 && first[maps[d]] = 1
			{
				continue; // skip current iteration
			}

			digit[maps[d]] = i;
			used[i] = 1;
			dfs(d + 1, n);
			used[i] = 0;
			if (ans > 1)
			{
				return;
			}
		}
	}
}

int main()
{
	roman['I'] = 1;
	roman['X'] = 10;
	roman['C'] = 100;
	roman['M'] = 1000;
	roman['V'] = 5;
	roman['L'] = 50;
	roman['D'] = 500;

	int rvalue[3];

	while (std::cin >> input)
	{
		if (input[0] == '#')
		{
			break;
		}
		int size = 0, count = 0, sum = 0;
		std::memset(visited, 0, sizeof(visited));
		
		for (int i = 0; input[i]; ++i)
		{
			if (input[i] == '+' || input[i] == '=')
			{
				arr[size++][count] = 0;
				count = 0;
			}
			else
			{
				arr[size][count++] = input[i];
				if (!visited[input[i]])
				{
					visited[input[i]] = 1;
					maps[sum++] = input[i];
				}
			}
		}arr[size++][count] = 0;

		std::memset(first, 0, sizeof(first));
		int c = 0;
		for (int i = 0; i < 3; ++i)
		{
			rvalue[i] = 0;
			
			for (int j = 0; arr[i][j]; ++j)
			{
				std::cout << "this is j " << j << std::endl;
				if (arr[i][j + 1] && roman[arr[i][j]] < roman[arr[i][j + 1]])
				{
					rvalue[i] -= roman[arr[i][j]];
				}
				else
				{
					rvalue[i] += roman[arr[i][j]];
				}
				c++;
			}
			first[arr[i][0]] = 1;
			
		}
		std::cout << "this is count " << c << std::endl;
		if (rvalue[0] + rvalue[1] == rvalue[2])
		{
			std::cout << "Correct ";
		}
		else
		{
			std::cout << "Incorrect ";
		}
		ans = 0;
		std::memset(used, 0, sizeof(used));

		dfs(0, sum);
		if (ans > 1)
		{
			std::cout << "ambiguous" << std::endl;
		}
		else if (ans == 1)
		{
			std::cout << "valid" << std::endl;
		}
		else
		{
			std::cout << "impossible" << std::endl;
		}
	}
	return 0;
}

