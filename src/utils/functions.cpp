#include "../../include/utils/functions.hpp"
#include "../../include/pages/page.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iomanip>
#include <vector>
#include <string>

namespace ShareMe
{
    namespace Functions
    {
        void FitText(sf::Text& text, sf::Vector2f size)
        {
            for (uint8_t i = 1; true; i++)
            {
                text.setCharacterSize(i);
                
                auto tSize = text.getGlobalBounds().getSize();
                
                if (tSize.x >= size.x || tSize.y >= size.y)
                {
                    text.setCharacterSize(i - 24);
                    break;
                }
            }
        }

        float GetMiddle(float object, float container, float start, float minus)
        {
            return std::round(start + ((container - object) / 2) - minus);
        }

        float GetTextMaxHeight(const sf::Text& text)
        {
            sf::Text temp;
            temp.setFont(*text.getFont());
            temp.setString("qwertyuıopğüasdfghjklşizxcvbnmöçQWERTYUIOPĞÜASDFGHJKLŞİZXCVBNMÖÇ");
            temp.setCharacterSize(text.getCharacterSize());
            
            return temp.getGlobalBounds().height;
        }

        std::string GenerateSalt(size_t length) 
        {
            std::vector<unsigned char> salt(length);
            if (RAND_bytes(salt.data(), salt.size()) != 1) {
                throw std::runtime_error("RAND_bytes failed");
            }

            std::ostringstream oss;
            for (unsigned char byte : salt) {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }

            return oss.str();
        }

        std::string SHA256(const std::string& data) 
        {
            EVP_MD_CTX* context = EVP_MD_CTX_new();
            if (context == nullptr) { 
                throw std::runtime_error("EVP_MD_CTX_new failed"); 
            }

            const EVP_MD* md = EVP_sha256();

            if (EVP_DigestInit_ex(context, md, nullptr) != 1) {
                EVP_MD_CTX_free(context);
                throw std::runtime_error("EVP_DigestInit_ex failed");
            }

            if (EVP_DigestUpdate(context, data.c_str(), data.size()) != 1) {
                EVP_MD_CTX_free(context);
                throw std::runtime_error("EVP_DigestUpdate failed");
            }

            unsigned char hash[EVP_MAX_MD_SIZE];
            unsigned int lengthOfHash = 0;
            if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
                EVP_MD_CTX_free(context);
                throw std::runtime_error("EVP_DigestFinal_ex failed");
            }

            EVP_MD_CTX_free(context);

            std::ostringstream oss;
            for (unsigned int i = 0; i < lengthOfHash; ++i) {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
            }

            return oss.str();
        }

        bool SaveTokens(const AuthorizationData& authorizationData)
        {
            if (!std::filesystem::exists("./data"))
            {
                bool dirCreateResult = std::filesystem::create_directory("./data");

                if (!dirCreateResult)
                    return false;
            }

            std::ofstream file("./data/tokens.txt");

            if (file.is_open())
            {
                file << authorizationData.accessToken << "\n" << authorizationData.refreshToken << std::endl;
                return true;
            }

            return false;
        }

        std::optional<AuthorizationData> GetTokens()
        {
            if (!std::filesystem::exists("./data/tokens.txt"))
                return std::nullopt;

            std::ifstream file("./data/tokens.txt");

            if (file.is_open())
            {
                AuthorizationData data;

                std::getline(file, data.accessToken);
                std::getline(file, data.refreshToken);

                return data;
            }

            return std::nullopt;
        }
    }
}