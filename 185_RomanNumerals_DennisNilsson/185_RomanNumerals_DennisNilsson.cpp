// 185_RomanNumerals_DennisNilsson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

int ans, len, count, buffer[100], visited[10] = { 0 };
char input[100], roman[8] = { "IVXLCDM" }, record[8];

bool romanSum()
{
	int arr[100] = { 0 };
	int value[3] = { 0 };
	int index = 0;
	bool correct;
	for (int i = 0; i < len; i++)
	{
		if (input[i] != '+' && input[i] != '=')
		{
			if (buffer[input[i]] >= buffer[input[i + 1]])
				value[index] += buffer[input[i]];
			else if (buffer[input[i]] <= buffer[input[i + 1]])
				value[index] += -buffer[input[i]];
			if (arr[input[i]]++ == 0)
				record[count++] = input[i];
		}
		else
			index++;
	}
	return value[0] + value[1] == value[2];
}
int dfs(int n)
{
	if (n == count)
	{
		int num[3] = { 0 }, cnt = 0;
		for (int i = 0; i < len; i++)
		{
			if (input[i] != '+' && input[i] != '=')
				num[cnt] = num[cnt] * 10 + buffer[input[i]];
			else
				cnt++;
		}
		if (num[0] + num[1] == num[2])
			ans++;
	}
	else for (int i = 0; i < 10; i++)
	{
		buffer[record[n]] = i;
		if (visited[i] || buffer[input[0]] == 0)
			continue;
		visited[i] = 1;
		dfs(n + 1);
		visited[i] = 0;
	}
	return ans;
}
int main()
{
	while (std::cin >> input)
	{
		if (input[0] == '#')
		{
			break;
		}
		ans = 0;
		count = 0;
		len = strlen(input);
		buffer['I'] = 1;
		for (int i = 1; i < 7; i++)
		{
			if (i % 2 != 0)
			{
				buffer[roman[i]] = buffer[roman[i - 1]] * 5;
			}
			if (i % 2 == 0)
			{
				buffer[roman[i]] = buffer[roman[i - 1]] * 2;
			}
		}

		if (romanSum())
			std::cout << "Correct ";
		else if (!romanSum())
			std::cout << "Incorrect ";
		if (dfs(0) > 1)
			std::cout << "ambiguous" << std::endl;
		else if (dfs(0) == 1)
			std::cout << "valid" << std::endl;
		else
			std::cout << "impossible" << std::endl;
	}
	return 0;
}

