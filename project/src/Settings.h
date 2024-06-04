#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <fstream>
#include <iostream>
#include "Crosshair.h"

struct Settings {
    //Default difficulty is easy
    int difficulty;
    CrosshairConfig crosshair;

    Settings() : difficulty(1) {}

    void loadSettings(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> difficulty;
            file.close();
        } else {
            std::cerr << "Unable to open settings file: " << filename << std::endl;
        }
    }

    void saveSettings(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << difficulty;
            file.close();
        } else {
            std::cerr << "Unable to open settings file: " << filename << std::endl;
        }
    }
};

#endif