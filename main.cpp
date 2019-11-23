#include<stdio.h>
#include<math.h>
#include<iostream>
int x[20], y[20], r[20], st, ed, n, i, j, k, cases;
char dr[4], mark[20];
double dc[20][20], arg[20][20], len[20][20], xi[20][20], yi[20][20], xj[20][20], yj[20][20];
double pxa[20], pya[20], pxb[20], pyb[20], eps, pi, d, cur, ans;
using namespace std;
double dis(double x, double y) 
{
	return sqrt(x * x + y * y);
}

double angle(double x, double y) 
{
	if (y > 0)
		return acos(x / dis(x, y));
	if (y < 0)
		return 2 * pi - acos(x / dis(x, y));
	if (x > 0)
		return 0;
	return pi;
}

int cross(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd)     
{
	double cra, crb;
	cra = (xb - xa) * (yc - ya) - (xc - xa) * (yb - ya);
	crb = (xb - xa) * (yd - ya) - (xd - xa) * (yb - ya);   
	if (cra * crb > -eps)									
		return 0;
	cra = (xd - xc) * (ya - yc) - (xa - xc) * (yd - yc);
	crb = (xd - xc) * (yb - yc) - (xb - xc) * (yd - yc);
	if (cra * crb > -eps)
		return 0;
	return 1;
}

void go(int v, double a)
{
	int j, k;
	double add;
	for (j = 0; j < n; j++)
		if (mark[j] && len[v][j] > 0)
		{
			for (k = 0; k < i; k++)
				if (cross(pxa[k], pya[k], pxb[k], pyb[k], xi[v][j], yi[v][j], xj[v][j], xj[v][j]))
					break;
			if (k < i)
				continue;
			pxa[i] = xi[v][j];
			pya[i] = yi[v][j];
			pxb[i] = xj[v][j];
			pyb[i] = yj[v][j];
			add = len[v][j];
			if (a > 0) {
				if (r[v] < 0)
				{
					if (arg[v][j] > a - eps)
						add -= r[v] * (arg[v][j] - a);
					else
						add -= r[v] * (2 * pi + arg[v][j] - a);
				}
				else
				{
					if (a > arg[v][j] - eps)
						add += r[v] * (a - arg[v][j]);
					else
						add += r[v] * (2 * pi + a - arg[v][j]);
				}
			}
			mark[j] = 0;
			cur += add;
			i++;
			if (cur < ans)
				if (j == ed)
					ans = cur;
				else
					go(j, arg[v][j]);
			i--;
			cur -= add;
			mark[j] = 1;
		}		
}
int main()
{
	eps = 1e-8;
	pi = acos(-1.0);
	while (cin>>n && n)
	{
		for (i = 0; i < n; i++)
		{
			cin >> x[i];
			cin >> y[i];
			cin >> r[i];
			cin >> dr;
			if (dr[1])
				r[i] = -r[i];
			mark[i] = 1;
		}
		cin >> st;										 
		cin >> ed;
		cin >> d;
		mark[st] = 0;									
		for (i = 0; i < n; i++)							
			for (j = 0; j < n; j++)
				dc[i][j] = dis(x[j] - x[i], y[j] - y[i]);  
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (i != j)
				{
					arg[i][j] = angle(x[j] - x[i], y[j] - y[i]) + acos((r[i] - r[j]) / dc[i][j]); 
					if (arg[i][j] >= 2 * pi)
						arg[i][j] -= 2 * pi;
					if (arg[i][j] < 0)
						arg[i][j] += 2 * pi;
					len[i][j] = sqrt(dc[i][j] * dc[i][j] - (r[j] - r[i]) * (r[j] - r[i]));      
					if (len[i][j] > d)															
						len[i][j] = -1;
					else
					{
						xi[i][j] = x[i] + r[i] * cos(arg[i][j]); yi[i][j] = y[i] + r[i] * sin(arg[i][j]); 
						xj[i][j] = x[j] + r[j] * cos(arg[i][j]); yi[i][j] = y[j] + r[j] * sin(arg[i][j]); 
						for (k = 0; k < n; k++) 
							if (k != i && k != j)   
							{
								if ((xj[i][j] - xi[i][j]) * (x[k] - xi[i][j]) + (yj[i][j] - yi[i][j]) * (y[k] - yi[i][j]) <= 0)
									continue;
								if ((xi[i][j] - xj[i][j]) * (x[k] - xj[i][j]) + (yi[i][j] - yj[i][j]) * (y[k] - yj[i][j]) <= 0)
									continue;
								if (fabs((xj[i][j] - xi[i][j]) * (y[k] - yi[i][j]) - (yj[i][j] - yi[i][j]) * (x[k] - xi[i][j])) / len[i][j] > labs(r[k]) + eps)
									continue;
								len[i][j] = -1;
								break;
							}
					}
				}
		cur = 0;   
		ans = 2e9;
		i = 0;
		go(st, -2);
		printf("Case %d: ", ++cases);
		if (ans < 1e9)
			if (int(ans * 100 + 0.5) % 10)
				printf("length = %.2lf\n", ans);
			else {
				if (int(ans * 100 + 0.5) % 100)
					printf("length = %.1lf\n", ans);
				else
					printf("length = %.0lf\n", ans);
			}
		else
			printf("Cannot reach destination shaft");
	}
	return 0;
}