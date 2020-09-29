
#include <iostream>
template <typename T, size_t s>
class Array
{
public:
	Array() = default;
	int Length() const {
		return length;
	}
	T& operator[] (size_t index) {
		if (index > length) {
			__debugbreak();
		}
		return m_Data[index];
	}
	T* Data() const { return m_Data; }

	void ForEach(void(*func)(T, int))const
	{
		for (size_t i = 0; i < length; i++)
		{
			func(m_Data[i], i);
			//std::cout << m_Data[i];
		}

	}
	void ForEach(void(*func)(T))const
	{
		for (size_t i = 0; i < length; i++)
		{
			func(m_Data[i]);
			//std::cout << m_Data[i];
		}

	}
	template <typename t>
	Array Map(t(*func)(T, int)) const
	{

		Array<t, s > newarray;

		for (size_t i = 0; i < length; i++)
		{
			newarray[i] = func(m_Data[i], i);
		}
		return newarray;
	}
	template <typename t>
	Array Map(t(*func)(T)) const
	{

		Array<t, s > newarray;

		for (size_t i = 0; i < length; i++)
		{
			newarray[i] = func(m_Data[i]);
		}
		return newarray;
	}
	Array Reverse()
	{
		T rev_array[s];
		for (int i = 0, j = length - 1; i < s; i++)
		{
			rev_array[i] = m_Data[j];
			j--;
		}
		for (int i = 0; i < length; i++)
		{
			m_Data[i] = rev_array[i];
		}
		return *this;
	}
	Array Filter(bool(*func)(T, int))
	{
		Array<bool, s> cheacking_array;
		int true_counter = 0;
		for (int i = 0; i < length; i++)
		{
			if (func(m_Data[i], i))
			{
				true_counter++;
				cheacking_array[i] = true;
			}
			else
			{
				cheacking_array[i] = false;
			}
		}
		Array<T, s> filtered_array;
		int j = 0;
		for (int i = 0; i < length; i++)
		{
			if (cheacking_array[i])
			{
				filtered_array[j] = m_Data[i];
				j++;
			}
		}
		filtered_array[true_counter] = '\0';
		if (filtered_array[true_counter] == 0) {
		}
		filtered_array.length = true_counter;
		return filtered_array;
	}
	template <typename t>
	Array Filter(bool(*func)(T))
	{
		Array<bool, s> cheacking_array;
		int true_counter = 0;
		for (int i = 0; i < length; i++)
		{
			if (func(m_Data[i]))
			{
				true_counter++;
				cheacking_array[i] = true;
			}
			else
			{
				cheacking_array[i] = false;
			}
		}
		Array<T, s> filtered_array;
		int j = 0;
		for (int i = 0; i < length; i++)
		{
			if (cheacking_array[i])
			{
				filtered_array[j] = m_Data[i];
				j++;
			}
		}
		filtered_array.length = true_counter;
		return filtered_array;
	}
	Array Sort()
	{

		for (int j = length; j > 0; j--)
		{
			int total_swaps = 0;
			for (int i = 0; i < length; i++)
			{
				if (i + 1 == length)break;
				if (sort_l(m_Data[i], m_Data[i + 1]))
				{
					T temp;
					temp = m_Data[i];
					m_Data[i] = m_Data[i + 1];
					m_Data[i + 1] = temp;
					total_swaps++;
				}

			}
			if (!total_swaps) break;

		}
		return *this;
	}

	Array Sort(bool(*func)(T, T))
	{

		for (int j = length; j > 0; j--)
		{
			int total_swaps = 0;
			for (int i = 0; i < length; i++)
			{
				if (i + 1 == length)break;
				if (!func(m_Data[i], m_Data[i + 1]))
				{
					T temp;
					temp = m_Data[i];
					m_Data[i] = m_Data[i + 1];
					m_Data[i + 1] = temp;
					total_swaps++;
				}
			}
			if (!total_swaps) break;

		}
		return *this;
	}
	void PrintArray()
	{
		for (int i = 0; i < length; i++)
		{
			std::cout << m_Data[i] << std::endl;
		}
	}
private:
	T m_Data[s];
	size_t length = s;
	bool sort_l(T first_element, T second_element)
	{
		if (first_element > second_element)
		{
			return true;
		}
		else {
			return false;

		}
	}
};


struct vector2D
{
	int x;
	int y;
};


int main()
{
	Array <int, 5> data;
	
	data[0] = 60;
	data[1] = 70;
	data[2] = 10;
	data[3] = 40;
	data[4] = 50;


	data.ForEach([](int Data) {
		std::cout << "for each " << Data<< std::endl;
		});


	data.Reverse();
	std::cout << "reversed\n";
	data.PrintArray();

	auto filteredArray = data.Filter([](int D, int index) ->bool {
		return D > 40;
		});
	std::cout << "filter greater than 40\n";

	filteredArray.PrintArray();


	//std::cout << filteredArray.Length();
	std::cout << "sort\n";

	data.Sort();
	data.PrintArray();
	data.Sort();

	data.Map<int>([](int D, int index)->int {
		return D * 3;
		}).Reverse() // <----- here
			.ForEach([](int Data, int index) {
			std::cout << "chaining  " << Data << std::endl;
				});

		//data.Reverse().ForEach([](int Data, int index) {
		   // std::cout << index << ". " << Data << std::endl;
		   // });
		//
		std::cout << "\n sorting in class or struct\n";

		Array<vector2D, 5> vector2D_array;

		vector2D_array[0].x = 60;
		vector2D_array[1].x = 70;
		vector2D_array[2].x = 10;
		vector2D_array[3].x = 40;
		vector2D_array[4].x = 50;

		vector2D_array.Sort([](vector2D e1, vector2D e2)->bool
			{
				if (e2.x > e1.x) return true;
				else return false;
			}).ForEach([](vector2D data)
				{
					std::cout << data.x<<std::endl;
				});
}


