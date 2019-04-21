#include <utility>
#include "./movie/MovieRepository.h"
#include "./csv/CSVRepository.h"

class CSVMovieRepo: public CSVRepository<Movie>, public MovieRepository {
public:
  explicit CSVMovieRepo(const std::string& filename): CSVRepository(filename) {
  }
};
