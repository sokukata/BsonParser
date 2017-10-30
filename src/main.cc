#include <iostream>
#include <fstream>
#include <vector>
#include "bson.hh"

using namespace std;

std::vector<char> bson_to_vector(string filename)
{
    ifstream file;
    std::vector<char> bson_vector;
    
    file.open(filename);
    file.seekg(0, std::ios::end);
    auto file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    if (file_size)
    {
        bson_vector.resize(file_size);
        file.read(&bson_vector.front(), file_size);
    }
    return bson_vector;
}


int main(int argc, char * argv[])
{
    if (argc < 2)
        return 1;

    std::vector<char> bson_vector = bson_to_vector(argv[1]);
    BSON *document = new BSON(bson_vector);
    document->parse();
}
