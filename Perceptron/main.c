#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_num(int lower, int upper)
{
  srand(time(0));

  int num = (rand() % (upper - lower + 1)) + lower; 
  return num;
}

int sign(double n)
{
  if (n >= 0)
  {
    return 1;
  }
  else
  {
    return -1;
  } 
}

typedef struct Perceptron
{
  double weights[2];
} Perceptron;

void init_perception(Perceptron* p)
{
  p->weights[0] = get_random_num(-1, 1);
  p->weights[1] = get_random_num(-1, 1);
}

int guess(Perceptron* p, double inputs[])
{
  double sum = 0;
  for (int i = 0; i < 2; ++i)
  {
    sum += inputs[i] * p->weights[i];
  }
  int output = sign(sum);
  return output;
}

void train(Perceptron* p, double inputs[], int target)
{
  int p_guess = guess(*&p, inputs);
  int error = target - p_guess;
  double learning_rate = 0.1;
  for (int i = 0; i < 2; ++i)
  {
    p->weights[i] += error * inputs[i] * learning_rate;
  } 
}

int main(void)
{
  Perceptron p;
  init_perception(&p);
  double input[2] = { 0.2, -0.3 };
  int p_guess = guess(&p, input);
  printf("%f, %f, guess: %d\n", p.weights[0], p.weights[1], p_guess);
  train(&p, input, 1);
  printf("%f, %f\n", p.weights[0], p.weights[1]);
}
