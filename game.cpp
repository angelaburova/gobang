#include "game.h"
#include <iostream>
#include<ctime>


#define MinusInfinity (-300000)
#define PlusInfinity (300000)

/*проверка ходя для игры людей*/
int game::Check_Shot(int i, int j, int flag)
{
	if ((black[i][j] == 0) && (white[i][j] == 0))
	{
		if (flag == 1)black[i][j] = 1;
		else white[i][j] = 1;
		return 1;

	}
	else return 0;
}
/*конструктор*/
game::game()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Player[i][j] = 0;
			Computer[i][j] = 0;
			black[i][j] = 0;
			white[i][j] = 0;
		}
	}

	
}
/*проверка победы*/
int game::check_Win(int i, int j, int flag)
{
	int countStep;
	int arr[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (flag == 1) arr[i][j] = black[i][j];
			else if (flag == 2) arr[i][j] = white[i][j];
			else if (flag == 3) arr[i][j] = Player[i][j];
			else arr[i][j] = Computer[i][j];

		}
	}

	int jST, jFIN, iST, iFIN;
	int mST = i;
	int mFIN = i;
	int nST = j;
	int nFIN = j;
	int helpC = 0;
	int kST = i;
	int kFIN = i;
	int hST = j;
	int hFIN = j;
	/*начало отсчета по строке где находится фишка*/
	if (j >= 4) jST = j - 4;
	else jST = 0;
	/*конец отсчета по строке*/
	if (j <= 5)jFIN = j + 4;
	else jFIN = 9;
	/*начало отсчета по столбцу где находится фишка*/
	if (i >= 4)iST = i - 4;
	else iST = 0;
	/*конец отсчета по столбцу*/
	if (i <= 5) iFIN = i + 4;
	else iFIN = 9;

	/*стартовые координаты по левой диагонали*/
	while ((mST != 0) && (nST != 0) && (helpC < 4))
	{
		mST -= 1;
		nST -= 1;
		++helpC;
	}
	helpC = 0;
	/*финишные кооординаты по левой диагонали*/
	while ((mFIN != 9) && (nFIN != 9) && (helpC < 4))
	{
		mFIN += 1;
		nFIN += 1;
		helpC += 1;
	}
	helpC = 0;
	/*стартовые коорд по правой диагонали*/
	while ((kST != 0) && (hST != 0) && (helpC < 4) && (kST != 9))
	{
		hST -= 1;
		kST += 1;
		helpC += 1;
	}
	helpC = 0;
	/*финишные коорд по правой диагонали*/
	while ((kFIN != 0) && (hFIN != 0) && (helpC < 4) && (hFIN != 9))
	{
		hFIN += 1;
		kFIN -= 1;
		helpC += 1;
	}
	/*проверяем есть ли 5 фишек в ряд по строке*/
	for (int ii = i;;)
	{
		for (int jj = jST; jj <= jFIN; jj++)
		{
			if (arr[ii][jj] == 0) { countStep = 0; }
			else
			{
				countStep += 1;
			}
			if (countStep == 5)return 1;
		}
		break;
	}


	/*проверяем есть ли 5 фишек в ряд по столбцу*/

	countStep = 0;
	for (int jj = j;;)
	{
		for (int ii = iST; ii <= iFIN; ii++)
		{
			if (arr[ii][jj] == 0) { countStep = 0; }
			else
			{
				countStep += 1;
			}
			if (countStep == 5) return 1;
		}
		break;
	}



	/*проверяем есть ли 5 фишек в ряд по диагонали левой*/

	countStep = 0;
	for (int ii = mST; ii <= mFIN; ii++)
	{
		for (int jj = nST; jj <= nFIN; jj++)
		{
			if (arr[ii][jj] == 0) { countStep = 0; }
			else
			{
				countStep += 1;
			}
			if (countStep == 5) return 1;
			ii++;
		}
	}



	/*проверяем есть ли 5 фишек в ряд по диагонали правой*/

	countStep = 0;
	for (int ii = kST; ii >= kFIN; ii--)
	{
		for (int jj = hST; jj <= hFIN; jj++)
		{
			if (arr[ii][jj] == 0) { countStep = 0; }
			else
			{
				countStep += 1;
			}
			if (countStep == 5) return 1;
			ii--;
		}


		return 0;

	}
}
/*совмещение полей*/
void game::connect_Fields()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Player[i][j] == 1)// в общем массиве фишки игрока становятся 1
			{
				field[i][j] = 1;
			}
			else if (Computer[i][j] == 1)//фишки компьютера 2
			{
				field[i][j] = 2;
			}
			else
			{
				field[i][j] = 0;
			}

		}
	}
}
/*разделение полей*/
void game::division_Fields()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (field[i][j] == 1)// в общем массиве фишки игрока становятся 1
			{
				Player[i][j] = 1;
				Computer[i][j] = 0;
			}
			else if (field[i][j] == 2)//фишки компьютера 2
			{
				Computer[i][j] = 1;
				Player[i][j] = 0;
			}
			else
			{
				Player[i][j] = 0;
				Computer[i][j] = 0;
			}

		}
	}

}
/*шаг компьютера*/
void game::Step_Computer()
{
	connect_Fields();
	
	tree* head;
	MaxLvl = level;
	head = new tree;
	for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) head->Field[i][j] = field[i][j];
	Create_Tree(head, 0, 2);

	Traversing(head, 0, MinusInfinity, PlusInfinity);
	Record(head);

	DeleteTree(head);		//очищаем память
}
/*функция создания дерева*/
void game::Create_Tree(tree* p, int lvl, int player)
{
	if (MaxLvl > lvl)
	{
		p->NumberOfSon = CoutOfSon(p->Field, player);
		if (p->NumberOfSon)
		{
			p->p = new tree*[p->NumberOfSon];
			p->NumberOfSon = CreateSon(p, lvl, player);
		}
	}
	else if (CheckWinForComputer(p->Field)) p->NumberOfSon = 0;
	else p->NumberOfSon = 0;
}
/*провека выигрыша компьюетра*/
int game::CheckWinForComputer(int Field[10][10])
{
	int sum;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Field[i][j])
			{
				for (int k = -1; k <= 1; ++k)
				{
					for (int m = -1; m <= 1; ++m)
					{
						if (k == 0 && m == 0) continue;
						sum = 1;
						for (int n = 1;; ++n)
						{
							if (i + k*n < 0 || i + k*n>9 || j + m*n < 0 || j + m*n>9) break;
							else if (Field[i + k*n][j + m*n] == 0)  break;
							else if (Field[i + k*n][j + m*n] == Field[i][j]) ++sum;
						}
						for (int n = -1;; --n)
						{
							if (i + k*n < 0 || i + k*n>9 || j + m*n < 0 || j + m*n>9) break;
							else if (Field[i + k*n][j + m*n] == 0)  break;
							else if (Field[i + k*n][j + m*n] == Field[i][j]) ++sum;
						}
						if (sum >= 5) return Field[i][j];
					}
				}
			}
		}
	}
	return 0;
}
/*создание сыновей*/
int game::CreateSon(tree* p, int lvl, int player)
{
	int IndexForAdd = 0;
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (p->Field[i][j] == 1) ++sum1;
			else if (p->Field[i][j] == 2) ++sum2;
		}
	}



	if ((player == 1 && sum1 < 12) || (player == 2 && sum2 < 12))
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (player == 1 && p->Field[i][j] == 0)
				{
					p->p[IndexForAdd] = new tree;
					for (int i2 = 0; i2 < 10; ++i2) for (int j2 = 0; j2 < 10; ++j2) p->p[IndexForAdd]->Field[i2][j2] = p->Field[i2][j2];
					p->p[IndexForAdd]->Field[i][j] = 1;
					p->p[IndexForAdd]->i = i;
					p->p[IndexForAdd]->j = j;
					Create_Tree(p->p[IndexForAdd], lvl + 1, player == 1 ? 2 : 1);
					++IndexForAdd;
				}
				else if (player == 2 && p->Field[i][j] == 0)
				{
					p->p[IndexForAdd] = new tree;
					for (int i2 = 0; i2 < 10; ++i2) for (int j2 = 0; j2 < 10; ++j2) p->p[IndexForAdd]->Field[i2][j2] = p->Field[i2][j2];
					p->p[IndexForAdd]->Field[i][j] = 2;
					p->p[IndexForAdd]->i = i;
					p->p[IndexForAdd]->j = j;
					Create_Tree(p->p[IndexForAdd], lvl + 1, player == 1 ? 2 : 1);
					++IndexForAdd;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (player == 1 && p->Field[i][j] == 1)
				{
					for (int k = -1; k <= 1; ++k)
					{
						for (int m = -1; m <= 1; ++m)
						{
							if (i + k < 0 || i + k>9 || j + m<0 || j + m>9) continue;
							else if (p->Field[i + k][j + m] == 0)
							{
								p->p[IndexForAdd] = new tree;
								for (int i2 = 0; i2 < 10; ++i2) for (int j2 = 0; j2 < 10; ++j2) p->p[IndexForAdd]->Field[i2][j2] = p->Field[i2][j2];
								p->p[IndexForAdd]->Field[i + k][j + m] = 1;
								p->p[IndexForAdd]->Field[i][j] = 0;
								p->p[IndexForAdd]->i = i + k;
								p->p[IndexForAdd]->j = j + m;
								Create_Tree(p->p[IndexForAdd], lvl + 1, player == 1 ? 2 : 1);
								++IndexForAdd;
							}
						}
					}
				}
				else if (player == 2 && p->Field[i][j] == 2)
				{
					for (int k = -1; k <= 1; ++k)
					{
						for (int m = -1; m <= 1; ++m)
						{
							if (i + k < 0 || i + k>9 || j + m<0 || j + m>9) continue;
							else if (p->Field[i + k][j + m] == 0)
							{
								p->p[IndexForAdd] = new tree;
								for (int i2 = 0; i2 < 10; ++i2) for (int j2 = 0; j2 < 10; ++j2) p->p[IndexForAdd]->Field[i2][j2] = p->Field[i2][j2];
								p->p[IndexForAdd]->Field[i + k][j + m] = 2;
								p->p[IndexForAdd]->Field[i][j] = 0;
								p->p[IndexForAdd]->i = i + k;
								p->p[IndexForAdd]->j = j + m;
								Create_Tree(p->p[IndexForAdd], lvl + 1, player == 1 ? 2 : 1);
								++IndexForAdd;
							}
						}
					}
				}
			}
		}
	}
	return IndexForAdd;
}
/*количество сыновей у узла*/
int game::CoutOfSon(int Field[10][10], int player)
{
	int sum1 = 0;
	int sum2 = 0;
	int sum = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Field[i][j] == 1) ++sum1;
			else if (Field[i][j] == 2) ++sum2;
		}
	}
	if ((player == 1 && sum1 < 12) || (player == 2 && sum2 < 12)) return (100 - sum1 - sum2);




	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (player == 1 && Field[i][j] == 1)
			{
				for (int k = -1; k <= 1; ++k)
				{
					for (int m = -1; m <= 1; ++m)
					{
						if (i + k < 0 || i + k>9) continue;
						else if (Field[i + k][j + m] == 0) ++sum;
					}
				}
			}
			else if (player == 2 && Field[i][j] == 2)
			{
				for (int k = -1; k <= 1; ++k)
				{
					for (int m = -1; m <= 1; ++m)
					{
						if (i + k < 0 || i + k>9) continue;
						else if (Field[i + k][j + m] == 0) ++sum;
					}
				}
			}
		}
	}
	return sum;
}
/*альфа-бета отсечение и минимакс*/
int game::Traversing(tree* cur, int level, int al, int bt)
{
	int MinMax;		//возращаем значение value отцу вершины
	int val;
	if (!cur->NumberOfSon)
	{
		cur->value = cost(cur->Field);
	}
	else
	{
		if (level % 2) val = PlusInfinity;
		else val = MinusInfinity;
		for (int i = 0; i < cur->NumberOfSon; ++i)
		{
			if (cur->p[i])
			{
				MinMax = Traversing(cur->p[i], level + 1, al, bt);
				if ((level % 2) && MinMax<val) val = MinMax;
				else if ((!(level % 2)) && MinMax>val) val = MinMax;

				/*альфа бета отсечение*/
				if (!(level % 2)) al = (al > MinMax) ? al : MinMax;
				else bt = (bt < MinMax) ? bt : MinMax;
				if (bt < al) break;
			}
		}
		cur->value = val;	 
	}
	return cur->value;
}
/*оценка игры*/
int game::cost(int field[10][10])
{
	return obhod(field, 2, 1) - obhod(field, 1, 2);
}
/*обход дерева*/
int game::obhod(int field[10][10], int this_player, int enemy_player)
{
	int prev_empty;
	int post_empty;
	int streak;
	int sum = 0;

	int j;
	int i;

	/*обход по строкам*/
	for (i = 0; i < 10; ++i)
	{
		prev_empty = 0;
		post_empty = 0;
		streak = 0;
		for (j = 0; j < 10; ++j)
		{
			if (field[i][j] == 0 && !streak) ++prev_empty;
			else if (field[i][j] == 0 && streak) ++post_empty;
			else if (field[i][j] == this_player && !post_empty) ++streak;
			else if (field[i][j] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[i][j] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
		}
		if (field[i][9] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}

	/*обход по столбцам*/
	for (j = 0; j < 10; ++j)
	{
		prev_empty = 0;
		post_empty = 0;
		streak = 0;
		for (i = 0; i < 10; ++i)
		{
			if (field[i][j] == 0 && !streak) ++prev_empty;
			else if (field[i][j] == 0 && streak) ++post_empty;
			else if (field[i][j] == this_player && !post_empty) ++streak;
			else if (field[i][j] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[i][j] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
		}
		if (field[9][j] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}


	/*обход по диагонали левый низ в правый верх*/
	j = 0;
	for (i = 0; i < 10; ++i)
	{
		int k = i;
		int m = j;
		while (k >= 0 && k < 10 && m >= 0 && m < 10)
		{
			if (field[k][m] == 0 && !streak) ++prev_empty;
			else if (field[k][m] == 0 && streak) ++post_empty;
			else if (field[k][m] == this_player && !post_empty) ++streak;
			else if (field[k][m] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[k][m] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
			--k;
			++m;
		}
		if (field[0][m - 1] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}
	i = 9;
	for (j = 1; j < 10; ++j)
	{
		int k = i;
		int m = j;
		while (k >= 0 && k < 10 && m >= 0 && m < 10)
		{
			if (field[k][m] == 0 && !streak) ++prev_empty;
			else if (field[k][m] == 0 && streak) ++post_empty;
			else if (field[k][m] == this_player && !post_empty) ++streak;
			else if (field[k][m] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[k][m] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
			--k;
			++m;
		}
		if (field[0][m - 1] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}


	/*обход по диагонали левый верх в правый низ*/
	j = 0;
	for (i = 0; i < 10; ++i)
	{
		int k = i;
		int m = j;
		while (k >= 0 && k < 10 && m >= 0 && m < 10)
		{
			if (field[k][m] == 0 && !streak) ++prev_empty;
			else if (field[k][m] == 0 && streak) ++post_empty;
			else if (field[k][m] == this_player && !post_empty) ++streak;
			else if (field[k][m] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[k][m] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
			++k;
			++m;
		}
		if (field[9][m - 1] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}
	i = 0;
	for (j = 1; j < 10; ++j)
	{
		int k = i;
		int m = j;
		while (k >= 0 && k < 10 && m >= 0 && m < 10)
		{
			if (field[k][m] == 0 && !streak) ++prev_empty;
			else if (field[k][m] == 0 && streak) ++post_empty;
			else if (field[k][m] == this_player && !post_empty) ++streak;
			else if (field[k][m] == this_player && post_empty)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = post_empty;
				post_empty = 0;
				streak = 1;
			}
			else if (field[k][m] == enemy_player)
			{
				sum += point(streak, prev_empty, post_empty);
				prev_empty = 0;
				post_empty = 0;
				streak = 0;
			}
			++k;
			++m;
		}
		if (field[9][m - 1] != enemy_player)
		{
			sum += point(streak, prev_empty, post_empty);
		}
	}

	return sum;
}

int game::point(int streak, int prev_empty, int post_empty)
{


	if (streak == 5) return 100000;
	else if (streak == 4 && prev_empty && post_empty) return 3000;
	else if (streak == 4 && ((!prev_empty && post_empty) || (prev_empty && !post_empty))) return 500;
	else if (streak == 3 && prev_empty && post_empty) return 100;
	else if (streak == 3 && ((!prev_empty && post_empty >= 2) || (prev_empty >= 2 && !post_empty))) return 100;
	else if (streak == 2 && ((prev_empty + post_empty) >= 3) && prev_empty && post_empty) return 40;
	else if (streak == 2 && (!prev_empty && post_empty >= 3)) return 10;
	else if (streak == 2 && (prev_empty >= 3 && !post_empty)) return 10;
	else if (streak == 1 && ((prev_empty + post_empty) >= 4) && prev_empty && post_empty) return 2;
	else if (streak == 1 && (!prev_empty && post_empty >= 4)) return 1;
	else if (streak == 1 && (prev_empty >= 4 && !post_empty)) return 1;
	else return 0;
}
/*запись результата хода*/
void game::Record(tree* head)
{
	int index;			//сохраняет индекс в массиве указателей на оптимальный вариант

	int n = head->NumberOfSon;
	for (int i = 0; i < head->NumberOfSon; ++i)
	{
		if (head->p[i])
		{
			if (head->p[i]->value == head->value)
			{
				index = i;
				break;
			}
		}
	}

	last_i2 = -1;
	last_j2 = -1;


	/*записываем результат хода в ячейки поля*/
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (field[i][j] != head->p[index]->Field[i][j])
			{
				if (head->p[index]->Field[i][j] == 2)
				{
					last_i = i;
					last_j = j;
				}
				else if (head->p[index]->Field[i][j] == 0)
				{
					last_i2 = i;
					last_j2 = j;
				}
			}
			field[i][j] = head->p[index]->Field[i][j];
		}
	}

	division_Fields();


}
/*удаление дерева*/
void game::DeleteTree(tree *p)
{
	if (!p->NumberOfSon)
	{
		for (int i = 0; i < p->NumberOfSon; ++i)
		{
			if (p->p[i]) DeleteTree(p->p[i]);
		}

		if (p->NumberOfSon > 0) delete[] p->p;	//удаление массива указателей на сыновей
		delete p;							//удаление вершины
	}
	return;
}



