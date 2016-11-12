#include <iostream>
#include <unordered_map>
#include <fstream>

int main(int argc, char *argv[]){
	if(argc != 2){
		std::cerr << "Usage: ./2sum <filename>" << std::endl;
		exit(1);
	}

	std::ifstream input(argv[1]);
	std::ofstream output("log.txt");
	std::unordered_map<long, int> data_map;
	data_map.reserve(1000000);
	data_map.max_load_factor(0.05);

	long tmp;
	while(input >> tmp){
		data_map[tmp] += 1;
	}

	std::cerr << "input done!" << std::endl;
	std::cerr << "load factor " << data_map.load_factor() << std::endl;

	//debug print.
	for(auto iter = data_map.begin(); iter != data_map.end(); ++iter){
		output << iter->first << " " << iter->second << std::endl;
	}

	std::cerr << "debug print done!" << std::endl;

	//solve
	long ans = 0;

	for(long i = -10000; i <= 10000; ++i){
		//try to find a pair whose sum = i.
		
		//debug print.
		if(i % 100 == 0)
			std::cerr << i << std::endl;
		
		for(auto iter = data_map.begin(); iter != data_map.end(); ++iter){
			long x = iter->first;
			long y = i - x;
			
			if(x == y)
				continue;

			auto search_y = data_map.find(y);
			if(search_y != data_map.end()){
				++ans;
				break;
			}
		}
	}

	std::cout << ans << std::endl;

	return 0;
}

//answer = 427