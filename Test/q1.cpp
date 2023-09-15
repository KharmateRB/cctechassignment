#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileReader {
public:
    FileReader(const std::string& filename) : filename_(filename) {}

    bool ReadData() {
        std::ifstream file(filename_);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename_ << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "PTS") {
                if (!ReadPTSData(file)) {
                    return false;
                }
            } else if (line == "CON") {
                if (!ReadCONData(file)) {
                    return false;
                }
            }
        }

        file.close();
        return true;
    }

    const std::vector<double>& GetPTSData() const {
        return pts_data_;
    }

    const std::vector<int>& GetCONData() const {
        return con_data_;
    }

private:
    bool ReadPTSData(std::ifstream& file) {
        double value;
        while (file >> value) {
            pts_data_.push_back(value);
        }
        return true;
    }

    bool ReadCONData(std::ifstream& file) {
        int value;
        while (file >> value) {
            con_data_.push_back(value);
        }
        return true;
    }

    std::string filename_;
    std::vector<double> pts_data_;
    std::vector<int> con_data_;
};

int main() {
    FileReader reader("data.txt");
    if (reader.ReadData()) {
        // Access the data as needed
        const std::vector<double>& ptsData = reader.GetPTSData();
        const std::vector<int>& conData = reader.GetCONData();

        // Print the data
        std::cout << "PTS Data:" << std::endl;
        for (double value : ptsData) {
            std::cout << value << std::endl;
        }

        std::cout << "CON Data:" << std::endl;
        for (int value : conData) {
            std::cout << value << std::endl;
        }
    }

    return 0;
}
