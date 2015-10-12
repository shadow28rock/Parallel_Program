#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double func_ch_x(double x); //вычисляем гиперболический косинус 
double func_sqrt_x(double x); //вычисляем кубический корень
void   func_read_data();       //читаем данные из файла
double func_abs(double x, double y);
void  func_eval(double a, double b,  double eps);
int main(void)
{
        func_read_data();
        return 0;
}
void func_eval(double a, double b, double eps) 
{
	FILE *file; char* filename = "output.txt"; 
	file = fopen(filename,"w+"); 
	while(a<=b) 
		{ 
			double temp = func_ch_x(a/5); 
			//запишем в файл промежуточный результат - почему-то не работает!!!; 
			//fprintf(file, "%f" ,temp); 
			printf("x= %f, result: %f\n",a,temp); 
			a+=eps; 
		} 
	fclose(file); 
}
void func_read_data()
{
char *str; char *token, *last;
FILE *fp;
fp  = fopen("input.txt","r");
ssize_t read; size_t sz;
while ((read = getline(&str, &sz, fp)) != -1)
    {   
        token = strtok_r(str, " ",&last);
        double a = atof(token); //начальная граница
        token = strtok_r(NULL, " ",&last);
        double b = atof(token); //конечная граница
        token = strtok_r(NULL, " ",&last);
        double eps = atof(token); //шаг
	printf("Входные данные: a=%f,b=%f, eps=%f\n", a, b, eps);
        func_eval(a,b,eps); //вычислили значения функций на интервале
    }
        fclose(fp);
}
double func_ch_x(double x)//вычисляем гиперболический косинус
{
        double exp = 1;
        double temp = 1;
        int n = 2;
        while(n<100)
        {
                temp*=x*x/((n-1)*n);
                exp += temp;
                n+= 2;
        }
        return exp;
}
double func_sqrt_x(double x)//вычисляем корень 3 степени
{
        double val = x + 1; 
        double x0 = val;
        double x1 = (2*x0 + val/(x0*x0))/3;
        while (func_abs(x0,x1) > 0.0001)
        {
                x0 = x1;
                x1 = (2*x0 + val/(x0*x0))/3;
        }
        return x1;
}
double func_abs(double x0, double x1)
{
   if (x1 > x0) return x1 - x0;
   else return x0 - x1;
}


