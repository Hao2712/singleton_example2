#include <iostream>
#include <mutex>
#include <string>
#include <map>

class ConfigurationManager {
    private:
        static ConfigurationManager* instance;
        static std::mutex mtx;
        std::map<std::string, std::string> config;
        ConfigurationManager() {
            config["server_address"] = "192.168.0.1";
            config["port"] = "8080";
            config["max_connections"] = "100";
        }
    
    public:
        static ConfigurationManager* getInstance() {
            if(instance == nullptr) {
                std::lock_guard<std::mutex> lock(mtx);
                if(instance == nullptr) {
                    instance = new ConfigurationManager();
                }
            }
            return instance;
        }

        std::string getConfigValue(const std::string& key) {
            if(config.find(key) != config.end()) {
                return config[key];
            } else {
                return "Key not found";
            }
        }

        void setConfigValue(const std::string& key, const std::string& value) {
            config[key] = value;
        }

        void loadConfig() {
            std::cout << "Loading configuration..." << std::endl;
        }

};

ConfigurationManager* ConfigurationManager::instance = nullptr;
std::mutex ConfigurationManager::mtx;

int main() {
    ConfigurationManager* configManager = ConfigurationManager::getInstance();

    configManager->loadConfig();

    std::cout << "Server Address: " << configManager->getConfigValue("server_address") << std::endl;
    std::cout << "Port: " << configManager->getConfigValue("port") << std::endl;
    std::cout << "Max Connections: " << configManager->getConfigValue("max_connections") << std::endl;

    configManager->setConfigValue("server_address", "192.168.0.2");
    std::cout << "Updated Server Address: " << configManager->getConfigValue("server_address") << std::endl;
    configManager->setConfigValue("port", "8081");
    std::cout << "Updated Port: " << configManager->getConfigValue("port") << std::endl;

}