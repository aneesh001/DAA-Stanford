#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int main(int argc, char *argv[]){
	if(argc != 2){
		std::cerr << "Usage: ./median <filename>" << std::endl;
		exit(1);
	}

	std::ifstream input(argv[1]);

	std::vector<int> s; //smaller half, max heap
	std::vector<int> b; //bigger half, min heap
	std::vector<int> med; //medians after each step

	int tmp;
	
	while(input >> tmp){
		if(s.empty() && b.empty()){
			s.push_back(tmp);
			std::push_heap(s.begin(), s.end());
			med.push_back(tmp);
			continue;
		}
		else{
			if(tmp < s.front()){
				s.push_back(tmp);
				std::push_heap(s.begin(), s.end());
			}
			else{
				b.push_back(tmp);
				std::push_heap(b.begin(), b.end(), std::greater<int>());
			}
		}

		// std::cerr << "One element added! " << s.size() << " " << b.size() << std::endl;

		//remove imbalance.
		int s_sz = s.size();
		int b_sz = b.size();
		if(s_sz - b_sz >= 2){
			//if s has 2 more elements than b, remove one from s and put it in b.
			std::pop_heap(s.begin(), s.end());
			int imb = s.back();
			s.pop_back();
			b.push_back(imb);
			std::push_heap(b.begin(), b.end(), std::greater<int>());
		}
		else if(b_sz - s_sz >= 2){
			//if b has 2 more elements than s, remove one from b and put it in s.
			std::pop_heap(b.begin(), b.end(), std::greater<int>());
			int imb = b.back();
			b.pop_back();
			s.push_back(imb);
			std::push_heap(s.begin(), s.end());
		}

		// //debug print
		// for(auto i: s)
		// 	std::cerr << i << " ";
		// std::cerr << std::endl;


		// for(auto i: b)
		// 	std::cerr << i << " ";
		// std::cerr << std::endl;

		//identify current median.
		if(s.size() >= b.size()){
			med.push_back(s.front());
		}
		else
			med.push_back(b.front());

		// std::cerr << "median this iter = " << med.back() << std::endl;
	}

	std::cerr << s.size() << " " << b.size() << " " << med.size() << std::endl;

	//compute final answer -- sum of all medians modulo 10000.
	long ans = 0;
	for(auto i: med)
		ans += i;

	std::cerr << ans % 10000 << std::endl;

	return 0;
}