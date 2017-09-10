#include "Utils.hpp"

 std::vector< std::vector<int>> read_file(std::string F) {

   std::ifstream fid;
   fid.open(F);

   std::string line;
   std::vector< std::vector<int>> m;

   while (getline( fid, line )) {
      std::istringstream is(line);
      m.push_back(std::vector<int>( std::istream_iterator<int>(is),std::istream_iterator<int>()));
   }

   fid.close();
   return m;
}


inputs read_parameters(std::string F) {

  std::ifstream fid;

  if (fid.is_open())
  {
    fid.close();
  };

	fid.open(F);
	inputs in;

	while (!fid.eof()) {
		std::string data;
		std::string parameter;
		std::string symbol;
		fid >> parameter;

		if (parameter.compare("PopulationSize") == 0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.population_size;

		};

		if (parameter.compare("GenerationsNumber") == 0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.n_generations;

		};

		if (parameter.compare("TerminationConditionType")==0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.stop_condition;

		};

		if (parameter.compare("ParentSelectionType")==0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.select_parents;
		};

		if (parameter.compare("TournamentSize")==0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.tournament_size;
		};

		if (parameter.compare("CrossoverType")==0) {
			fid >> symbol >> data;
			std::istringstream (data) >> in.type_co;

		};

		if (parameter.compare("CrossoverRate")==0) {
			fid >> symbol >> in.prob_co;
		};

		if (parameter.compare("CrossoverPointsNumber")==0) {
			fid >> symbol >>  data;
			std::istringstream (data) >> in.points_co;
		};

		if (parameter.compare("MutationType")==0) {
			fid >> symbol >>data;
			std::istringstream (data) >> in.mutation_type;
		};

		if (parameter.compare("MutationRate")==0) {
			fid >> symbol >>  in.prob_mut;
		};

		if (parameter.compare("Elitism")==0) {
			fid >> symbol >> in.elitism;
		};

	};
	fid.close();
	return in;

};
