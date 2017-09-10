#include "sudoku.hpp"
#include "Utils.hpp"
#include "GA.hpp"

int main() {

    std::vector< std::vector<int>> m = read_file("Sudoku_Sample.txt");
    inputs in = read_parameters("Parameters.txt");

    in.print();

    int x;
    std::cout << "\n Parameter test (1) success rate (2) solve (3): ";
    std::cin  >> x;

    if (x == 1) {
        std::ofstream F;
        F.open("output.csv");
        F << "Algorithm \n";
        F << "CrossOver Type " << in.type_co <<"\n";
        F << "Prob Mutation " << in.prob_mut <<"\n";
        F << "Prob CO " << in.prob_co <<"\n";
        std::vector<std::vector<int>> results;
        for (int i = 0; i <15; i++) {
            GA gen_algo(m,in);
            gen_algo.init();
            gen_algo.evolve();

            results.push_back(gen_algo.get_bestFit());

        }

        for (int k = 0 ; k < (int) results.size();k++) {
                for(int l = 0 ; l < (int) results[k].size(); l++) {
                    F << results[k][l] << ",";
                }
                F << "\n";
        }

        F.close();

    }

    if (x==2) {
        for (int i= 0; i <10; i++) {
            GA gen_algo(m,in);
            gen_algo.set_print_off();
            gen_algo.init();
            gen_algo.evolve();
            std::cout << i << ": " << gen_algo.get_generations() << " / " << in.n_generations << "\n";
        }
    } else {
        GA gen_algo(m,in);
        gen_algo.init();
        gen_algo.evolve();

    }

    return 0;
}
