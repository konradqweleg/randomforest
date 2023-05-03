#include "csv.h"


Cnumpy csv::read_cnumpy_from_csv(std::string path_to_file, std::string delimiter) {
    return (*reader_csv).read_csv_as_cnumpy(path_to_file, delimiter);
}


csv::csv(ReadCSV *csv_reader_mechanism) {
    reader_csv = csv_reader_mechanism;
}


csv::~csv(){
    delete reader_csv;
}