#ifndef SIMPLEMOVINGAVERAGE_H
#define SIMPLEMOVINGAVERAGE_H

#include <vector>
#include <algorithm>
#include <random>

/*!
 * \brief Генерация случайного синусоидального сигнала
 * \param size Размер выходного сигнала
 * \return Вектор с отсчетами сигнала
 */
template<typename T>
std::vector<T> generateSinData(unsigned size)
{
  std::vector<T> result;
  result.reserve(size);

  static std::random_device randomDevice;
  static std::mt19937 generator(randomDevice());
  static std::uniform_real_distribution<T> distr(-10, 10);

  for(unsigned i = 0; i < size; i++)
    result.push_back(100.0 * std::sin(i / 100.0) - distr(generator));

  return result;
}

/*!
 * \brief Алгоритм простого скользящего среднего без центрирования выходного сигнала
 *
 * \details Реализован итеративный алгоритм с оптимизацией по памяти.
 * Не тратиться память на хранение усредненных точек входящих в окно и
 * тратиться производительность на дополнительное деление.
 *
 * \param array Входной сигнал
 * \param windowSize Размер окна
 * \return Выходной сглаженный сигнал
 */
template<typename T>
std::vector<T> simpleMovingAverage(const std::vector<T>& array, unsigned long windowSize)
{
  std::vector<T> result;
  result.reserve(array.size());
  T sum{};
  unsigned long size = 0;

  for(unsigned long i = 0; i < std::min(windowSize, array.size()); i++)
  {
    size++;
    sum += array[i];
    result.push_back(sum / size);
  }

  sum /= size;
  for(unsigned long i = windowSize; i < array.size(); i++)
  {
    sum = sum - (array[i - windowSize] / windowSize) + (array[i] / windowSize);
    result.push_back(sum);
  }

  return result;
}

#endif // SIMPLEMOVINGAVERAGE_H
